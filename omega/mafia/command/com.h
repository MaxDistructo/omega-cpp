#include "../player.h"
#include "../ai/ai.h"
#include "mdcore/command.h"
#include "mdcore/subcommand_listener.h"

static bool day = false;
static int day_num = 0;
static bool allow_join = true;
static std::map<SleepyDiscord::Snowflake<SleepyDiscord::User>, Player*> players;

Player* getPlayer(std::string arg)
{
    //TODO: FINISH ME
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
        static mdcore::SubcommandListener listener({},"");
        listener.onMessage(client, event, args);
    };
    private:
        std::vector<mdcore::Command> commands;
        std::string buildHelp(std::vector<mdcore::Command> commands)
        {
            return "";
        }
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
        players[event.author.ID] = new (std::nothrow) Player(event.author.ID, client);
    };
};

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
                useAbility(players[event.author.ID], targets, day);
            }
            else if(args.size() == 4)
            {
                std::vector<Player*> targets = { getPlayer(args[2]), getPlayer(args[3]) };
                useAbility(players[event.author.ID], targets, day);
            }
            else
            {
                std::vector<Player*> targets = { getPlayer(args[2]) };
                if(*players[event.author.ID]->getRole() == "potion_master")
                {
                    if(args[3] == "attack"){
                        useAbility(players[event.author.ID], targets, Abilities::ATTACK, day);
                    }
                    else if(args[3] == "heal")
                    {
                        useAbility(players[event.author.ID], targets, Abilities::GRANT_DEFENCE, day);
                    }
                    else if(args[3] == "invest" || args[3] == "investigate" || args[3] == "reveal")
                    {
                        useAbility(players[event.author.ID], targets, Abilities::INVEST_ABSOLUTE, day);
                    }
                }
                else if(*players[event.author.ID]->getRole() == "pirate")
                {
                    if(day)
                    {
                        useAbility(players[event.author.ID], targets, day);
                    }
                    else
                    {
                        //TODO: Properly set flag so when the pirate action runs, all the data is avaliable.s
                        useAbility(players[event.author.ID], targets, day);
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