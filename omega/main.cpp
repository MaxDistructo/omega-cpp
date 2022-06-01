#include "main.h"
#include "commands/commands.h"
#include "commands/PlayerFun.h"
#include "config.h"
#include "events.h"

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

    //Game Listener, only runs when we need to listen for a message, from a specific player, in a specific channel, of specific content
    EventDispatcher e_listener;
    client.registerListener(*e_listener);

	client.run();

    return 0;
}