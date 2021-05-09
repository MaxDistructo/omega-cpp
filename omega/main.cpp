#include "main.h"
#include "commands/commands.h"
#include "commands/PlayerFun.h"

int main()
{
    //Instantiate our client
    mdcore::Dispatcher client(mdcore::readToken());
    
    //Instantiate the commands
    PingCommand ping;
    EchoCommand echo;
    SlapCommand slap;
    
    //Create the list of commands
    std::vector<mdcore::Command*> commands = {};
	commands.push_back(*ping);
    commands.push_back(*echo);
    commands.push_back(*slap);

    //Create the command listener
    mdcore::CommandListener c_listener(commands, prefix);
	client.registerListener(*c_listener);
	client.run();

    return 0;
}