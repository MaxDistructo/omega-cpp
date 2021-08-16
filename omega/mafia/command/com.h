#pragma once
#include "../player.h"
#include "../ai/ai.h"
#include "../data.h"

#include "mdcore/command.h"
#include "mdcore/subcommand_listener.h"

#include <string>

static bool day = false;
static int day_num = 0;
static bool allow_join = true;

namespace omega::Mafia{
    class MafiaJoin : public mdcore::Command
    {
        public:
            MafiaJoin()
            {
                setName("join");
                setHelp("join - Join the Mafia game currently running");
            }
            ~MafiaJoin(){};
            void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
            {
                if(allow_join){
                    manager->create(event.author.ID);
                }
                else
                {
                }
            };
    };
    class MafiaDo : public mdcore::Command
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
                    std::vector<Player*> targets = { getPlayerFromManager(event, args[2]) };
                    Ai::useAbility(manager->get(event.author.ID), targets, day);
                }
                else if(args.size() == 4)
                {
                    std::vector<Player*> targets = { getPlayerFromManager(event, args[2]), getPlayerFromManager(event, args[3]) };
                    Ai::useAbility(manager->get(event.author.ID), targets, day);
                }
                else
                {
                    std::vector<Player*> targets = { getPlayerFromManager(event, args[2]) };
                    if(*manager->get(event.author.ID)->getRole() == "potion_master")
                    {
                        if(args[3] == "attack"){
                            Ai::useAbility(manager->get(event.author.ID), targets, Abilities::ATTACK, day);
                        }
                        else if(args[3] == "heal")
                        {
                            Ai::useAbility(manager->get(event.author.ID), targets, Abilities::GRANT_DEFENCE, day);
                        }
                        else if(args[3] == "invest" || args[3] == "investigate" || args[3] == "reveal")
                        {
                            Ai::useAbility(manager->get(event.author.ID), targets, Abilities::INVEST_ABSOLUTE, day);
                        }
                    }
                    else if(*manager->get(event.author.ID)->getRole() == "pirate")
                    {
                        if(day)
                        {
                            Ai::useAbility(manager->get(event.author.ID), targets, day);
                        }
                        else
                        {
                            //TODO: Properly set flag so when the pirate action runs, all the data is avaliable.s
                            Ai::useAbility(manager->get(event.author.ID), targets, day);
                        }
                    }
                }
            }
    };
    class MafiaProgress : public mdcore::Command
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
                Ai::runAllAbilities();
                //Invert the day variable to whatever it's not
                day = !day;
                //If it's a day, move the day count forward 1
                if(day)
                {
                    day_num++;
                };
            }
    };
class MafiaCommand : public mdcore::Command
{
    MafiaCommand()
    {
        setName("mafia");
        setHelp("mafia - All the mafia related commands. Use mafia help to see all subcommands");
        MafiaJoin joinCommand;
        MafiaDo doCommand;
        MafiaProgress progressCommand;
        listener.registerCommand(&joinCommand);
        listener.registerCommand(&doCommand);
        listener.registerCommand(&progressCommand);
    };
    ~MafiaCommand(){};
    void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
    {
        //Init the manager with the client* we get from the Dispatcher
        if(manager == nullptr)
        {
            manager = new (std::nothrow) PlayerMemoryManager(client);
        }
        //Pass to the subcommand listener now that the master command setup is done.
        listener.onMessage(client, event, args);
    };
    private:
        mdcore::SubcommandListener listener;
};
}