#pragma once
#include "../player.h"
#include "../ai/ai.h"
#include "mdcore/command.h"
#include "mdcore/subcommand_listener.h"
#include "../manager/player_memory_manager.h"
#include <string>

static bool day = false;
static int day_num = 0;
static bool allow_join = true;
static omega::Mafia::PlayerMemoryManager* manager = nullptr;

omega::Mafia::Player* getPlayer(std::string arg)
{
    //FIXME: Upgrade code to get IDs from more inputs.
    //RN we just do a lazy convert from string to the long long int that a discord snowflake is
    int64_t id = stoi(arg);
    manager->getOrCreate(id);
}

class MafiaCommand : public mdcore::Command
{
    MafiaCommand()
    {
        setName("mafia");
        setHelp("mafia - All the mafia related commands. Use mafia help to see all subcommands");
    };
    ~MafiaCommand(){};
    void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
    {
        //Init the manager with the client* we get from the Dispatcher
        if(manager == nullptr)
        {
            manager = new (std::nothrow) omega::Mafia::PlayerMemoryManager(client);
        }
        listener.onMessage(client, event, args);
    };
    private:
        std::vector<mdcore::Command> commands;
        mdcore::SubcommandListener listener;
};

class MafiaJoin : mdcore::Command
{
    MafiaJoin()
    {
        setName("join");
        setHelp("join - Join the Mafia game currently running");
    }
    ~MafiaJoin(){};
    void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
    {
        manager->create(event.author.ID);
    };
};
namespace omega::Mafia::Ai{
    class MafiaDo : mdcore::Command
    {
        public:
            MafiaDo()
            {
                setName("do");
                setHelp("Use your action");
            }
            ~MafiaDo(){};
            void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
            {
                SleepyDiscord::User u = event.author;
                if(args.size() == 3){
                    std::vector<Player*> targets = { getPlayer(args[2]) };
                    useAbility(manager->get(event.author.ID), targets, day);
                }
                else if(args.size() == 4)
                {
                    std::vector<Player*> targets = { getPlayer(args[2]), getPlayer(args[3]) };
                    useAbility(manager->get(event.author.ID), targets, day);
                }
                else
                {
                    std::vector<Player*> targets = { getPlayer(args[2]) };
                    if(*manager->get(event.author.ID)->getRole() == "potion_master")
                    {
                        if(args[3] == "attack"){
                            useAbility(manager->get(event.author.ID), targets, Abilities::ATTACK, day);
                        }
                        else if(args[3] == "heal")
                        {
                            useAbility(manager->get(event.author.ID), targets, Abilities::GRANT_DEFENCE, day);
                        }
                        else if(args[3] == "invest" || args[3] == "investigate" || args[3] == "reveal")
                        {
                            useAbility(manager->get(event.author.ID), targets, Abilities::INVEST_ABSOLUTE, day);
                        }
                    }
                    else if(*manager->get(event.author.ID)->getRole() == "pirate")
                    {
                        if(day)
                        {
                            useAbility(manager->get(event.author.ID), targets, day);
                        }
                        else
                        {
                            //TODO: Properly set flag so when the pirate action runs, all the data is avaliable.s
                            useAbility(manager->get(event.author.ID), targets, day);
                        }
                    }
                }
            }
    };
    class MafiaProgress : mdcore::Command
    {
        public:
            MafiaProgress()
            {
                setName("progress");
                setHelp("Move the day night cycle forward");

            };
            ~MafiaProgress(){};
            void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
            {
                //Run all abilities
                runAllAbilities();
                //Invert the day variable to whatever it's not
                day = !day;
                //If it's a day, move the day count forward 1
                if(day)
                {
                    day_num++;
                };
            }
    };
}