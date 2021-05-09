#include "ai.h"
#include <stdlib.h>
#include <time.h>
#include "../../utils.h"
#include "../mafia.h"

std::vector<Action> actions = {};

std::vector<Abilities> non_night = 
{
    Abilities::REVEAL,
    Abilities::SEANCE
};

std::vector<Abilities> both =
{
    Abilities::JAIL,
    Abilities::PIRATE
};

std::vector<Abilities> non_action = 
{
    Abilities::ONLY_SELF
};

std::map<Player*, std::vector<Player*>> visitors = {};

//Generic interface for Discord Command input
void useAbility(Player* player, std::vector<Player*> target, bool day)
{
    if(!std::count(player->getTraits().begin(), player->getTraits().end(), Trait::JAILED))
    {
        if(day)
        {
            useDayAbility(player,target);
        }
        else
        {
            useNightAbility(player, target);
        }
    }
    else 
    {
        player->sendMessage("You cannot use your ability when you are jailed!");
    }
};
void useAbility(Player* player, std::vector<Player*> targets, Abilities ability)
{
    actions.push_back({ability, targets, player});
}
//Specific implementation for night actions
void useNightAbility(Player* player, std::vector<Player*> target)
{
    auto abilities = player->getRole()->getAbilities();
    for(auto abil : abilities)
        {
            //If day abil and abil is not a non_action abil
            if(!std::count(non_night.begin(), non_night.end(), abil) && !std::count(non_action.begin(), non_action.end(), abil))
            {
                //If we have the OnlySelf flag
                if(std::count(abilities.begin(), abilities.end(), Abilities::ONLY_SELF))
                {
                    //Verify we are targeting ourself
                    if(std::count(target.begin(), target.end(), player)){
                        actions.push_back({abil, target, player});
                    }
                }
                //Otherwise, we don't care if we are targeting someone else, apply the action.
                else{
                    actions.push_back({abil, target, player});
                }
            }
        }
    
};
//Specific implementation for day actions
void useDayAbility(Player* player, std::vector<Player*> target)
{
    auto abilities = player->getRole()->getAbilities();
    for(auto abil : abilities)
    {
        //If day abil and abil is not a non_action abil
        if(std::count(non_night.begin(), non_night.end(), abil) && !std::count(non_action.begin(), non_action.end(), abil))
        {
            //If we have the OnlySelf flag
            if(std::count(abilities.begin(), abilities.end(), Abilities::ONLY_SELF))
            {
                //Verify we are targeting ourself
                if(std::count(target.begin(), target.end(), player)){
                    actions.push_back({abil, target, player});
                }
            }
            //Otherwise, we don't care if we are targeting someone else, apply the action.
            else{
                actions.push_back({abil, target, player});
            }
        }
    }
};

void runAbil(Action action)
{
    int attack = 0;
    int defence= 0;
    auto modifiers = action.user->getEffectiveModifiers();
    if(action.ability == Abilities::RAMPAGE)
    {
        //Patch rampage to be an attack instead by using an attack on all visitors
        for(auto target : action.targets)
        {
            useAbility(action.user, getVisitors(target), Abilities::ATTACK);
        }
    }
    if(action.ability == Abilities::ATTACK)
    {
        attack = action.user->getModifier("attack");
        for(auto target: action.targets)
        {
            try{
                defence = target->getModifier("defence");
            }
            catch(...){};
            if(attack > defence)
            {
                target->kill(action.user->getRole());
            }
            else
            {
                target->sendMessage("You were attacked last night!");
            }
        }
    }
    if(action.ability == Abilities::GRANT_DEFENCE)
    {
        defence = modifiers[(std::string)"granted_defence"];
        for(auto target : action.targets)
        {
            if(target->getModifier("defence") < defence){
                target->addTempModifier("defence", defence);
            }
        }
    }
    if(action.ability == Abilities::JAIL)
    {
        for(auto target : action.targets)
        {
            target->addTrait(Trait::JAILED);
        }
    }
    if(action.ability == Abilities::CLEAN)
    {
        for(auto target : action.targets)
        {
            if(!target->isAlive()){
                target->addTrait(Trait::CLEANED);
            }
        }
    }
    if(action.ability == Abilities::FRAME)
    {
        for(auto target : action.targets)
        {
            if(!target->isAlive())
            {
                target->addTrait(Trait::FRAMED);
            }
        }
    }
    if(action.ability == Abilities::FORGE)
    {
        for(auto target : action.targets)
        {
            if(!target->isAlive())
            {
                target->addTrait(Trait::FORGED);
                for(auto modifier : modifiers)
                {
                    target->addPermModifier(modifier.first, modifier.second);    
                }
                
            }
        }
    }
    if(action.ability == Abilities::DOUSE)
    {
        for(auto target : action.targets)
        {
            target->addTrait(Trait::DOUSED);
        }
        for(auto visitor : getVisitors(action.user))
        {
            visitor->addTrait(Trait::DOUSED);
        }
    }
    if(action.ability == Abilities::KILL_VISITOR)
    {
        for(auto target : action.targets)
        {
            //Kill the random visitor
            auto visitors = getVisitors(target);
            if(visitors.size() == 1){
                return;
            }
            srand(time(NULL));
            int random_visitor = rand() % visitors.size();
            while(visitors[random_visitor] == action.user)
            {
                random_visitor = rand() % visitors.size();
            }
            visitors[random_visitor]->kill(action.user->getRole());
            
            //If we are ambusher, tell all visitors about us.
            if(*action.user->getRole() == "ambusher"){
                for(auto visitor : visitors)
                {
                    visitor->sendMessage("You saw " + action.user->getUser().username + " prepare an ambush!");
                }
            }
        }
    }
    if(action.ability == Abilities::KILL_VISITORS)
    {
        for(auto visitor : getVisitors(action.user))
        {
            visitor->kill(action.user->getRole());
        }
    }
    if(action.ability == Abilities::STONE_VISITORS)
    {
        for(auto visitor : getVisitors(action.user))
        {
            visitor->kill(action.user->getRole());
            visitor->addTrait(Trait::STONED);
        }
    }
    if(action.ability == Abilities::BLOCK)
    {
        for(auto target : action.targets){
            if(!target->hasTrait(Trait::BLOCK_IMMUNE)){
                for(auto action : actions)
                {
                    if(action.user == target)
                    {
                        action.ability = Abilities::NULL_ABIL;
                    }
                }
            }
        }
    }
    if(action.ability == Abilities::TRANSPORT)
    {
        Player* target1 = action.targets[0];
        Player* target2 = action.targets[1];

        if(target1->hasTrait(Trait::JAILED) || target2->hasTrait(Trait::JAILED))
        {
            action.user->sendMessage("You were unable to transport your targets because one of them was Jailed!");
            return;
        }
        //Perform the swap of all targets.
        for(auto sub : actions)
        {
            if(vectorContains(sub.targets, target1))
            {
                int i = getIndex(sub.targets, target1);
                sub.targets[i] = target2;
            }
            if(vectorContains(sub.targets, target2))
            {
                int i = getIndex(sub.targets, target2);
                sub.targets[i] = target1;
            }
        }

    }
    if(action.ability == Abilities::USE_OTHER)
    {
        std::vector<std::vector<Action>::iterator> toDelete = {};
        for(auto sub : actions){
            if(sub.user == action.targets[0])
            {
                //Since we are looping over the actions array, we can't modify it
                //right now, so enqueue the delete into a vector for us to delete
                //later
                try{
                    toDelete.push_back(getIterLocation(actions, sub));
                }
                catch(...){};
            }
        }
        for(auto iter : toDelete)
        {
            if(iter != actions.end()){
                actions.erase(iter);
            }
        }
        useNightAbility(action.targets[0], {action.targets[1]});
    }
    if(action.ability == Abilities::INVEST)
    {
        for(auto target : action.targets)
        {
            action.user->sendMessage("Your target could be a " + getInvestResults(target->getRole()));
        }
    }
    if(action.ability == Abilities::INVEST_ABSOLUTE)
    {
        for(auto target : action.targets)
        {
            action.user->sendMessage("Your target is a " + target->getRole()->getName());
        }
    }

}

std::vector<Player*> getVisitors(Player* player)
{
    auto cached = visitors[player];
    if(cached.size() > 0)
    {
        return cached;
    }
    else
    {
        for(auto action : actions)
        {
            if(std::count(action.targets.begin(), action.targets.end(), player))
            {
                visitors[player].push_back(action.user);
            }
        }
        return visitors[player];
    }
}