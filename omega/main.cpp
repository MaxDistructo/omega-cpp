#include "main.h"
#include "commands/commands.h"
#include "commands/PlayerFun.h"
#include "config.h"
#include "events.h"
#include "resources.h"

EventDispatcher* e_dispatcher = new (std::nothrow) EventDispatcher();

int main()
{
    //Instantiate our client
    mdcore::Dispatcher client(mdcore::readToken());
    
    //Instantiate the commands
    PingCommand ping;
    EchoCommand echo;
    SlapCommand slap;
    EventListenerTestCommand test;
    
    //Create the list of commands
    std::vector<mdcore::Command*> commands = {};
	commands.push_back(*ping);
    commands.push_back(*echo);
    commands.push_back(*slap);
    commands.push_back(*test);

    //THIS MUST BE REGISTERED BEFORE THE COMMAND HANDLER
    //Create events system listener. This is exposed through the resources.h header to register new events
    client.registerListener(e_dispatcher);

    //Create the command listener
    mdcore::CommandListener c_listener(commands, prefix);
	client.registerListener(*c_listener);

	client.run();

    //If we get here, delete the event dispatcher before we leave.
    delete e_dispatcher;

    return 0;
}