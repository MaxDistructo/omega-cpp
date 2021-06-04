#include "../player.h"
#include "../ai/ai.h"
#include "mdcore/command.h"
#include "mdcore/subcommand_listener.h"

static bool day = false;
static int day_bool = 0;

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
        const mdcore::SubcommandListener listener = new SubcommandListener<Command>(
            {
                MafiaDo();
            }
        , "");
        listener.onMessage(client, event, args);
    };
    private:
        std::vector<mdcore::Command> commands;
        std::string buildHelp(std::vector<mdcore::Command> commands)
        {
            return "";
        }
};

class MafiaDo : mdcore::Command
{
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
            Player* p = new (nothrow) Player(u.ID, client);
            vector<Player*> targets = {};
            targets.push_back(new (nothrow) Player(args[2], client));
            useAbility(p, targets, day);
        }
        else 
        {
            Player* p = new (nothrow) Player(u.ID, client);
            vector<Player*> targets = {};
            targets.push_back(new (nothrow) Player(args[2], client));
            targets.push_back(new (nothrow) Player(args[3], client));
            useAbility(p, targets, day);
        }
    }
}
class MafiaProgress : mdcore::Command
{
    MafiaProgress()
    {
        setName("progress");
        setHelp("Move the day night cycle forward");

    };
    ~MafiaProgress(){};
    void execute(SleepyDiscord::DiscordClient client, SleepyDiscord::Message event, std::vector<std::string> args) override
    {
        //Run all abilities

        //Invert the day variable to whatever it's not
        day = !day;
        //If it's a day, move the day count forward 1
        if(day)
        {
            day_num++;
        }
        //Cleanup all pointers we created in the last faze
        cleanupAllAbils();
    }
}