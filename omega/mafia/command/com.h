#include "../player.h"
#include "mdcore/command.h"

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
        if(args[1] == "help")
        {
            client->sendMessage(event.channelID, buildHelp(commands));
        }
        else if (args[1] == "")
        {
            
        }
    };
    private:
        std::vector<mdcore::Command> commands;
        std::string buildHelp(std::vector<mdcore::Command> commands)
        {
            return "";
        }
};