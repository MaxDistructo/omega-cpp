#include "main.h"
#include "commands/commands.h"

int main()
{
    //Instantiate our client
    mdcore::Dispatcher client(mdcore::readToken());
    
    //Instantiate the commands
    PingCommand ping;
    EchoCommand echo;
    
    //Create the list of commands
    std::vector<mdcore::Command*> commands = {};
	commands.push_back(*ping);
    commands.push_back(*echo);

    //Create the command listener
    mdcore::CommandListener c_listener(commands, prefix);
	client.registerListener(*c_listener);
	client.run();

    return 0;
}