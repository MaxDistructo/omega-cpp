#ifndef __omega__commands_h
#define __omega__commands_h

#include "../main.h"
#include "sleepy_discord/permissions.h"
#include "../mafia/command/com.h"
#include "../resources.h"

class PingCommand : public mdcore::Command
{
    public:
        PingCommand()
        {
                setName("ping");
                setHelp("A sanity check command, just responds with Pong");
        };
        ~PingCommand(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            event.reply(client, "Pong!");
        };
};

class EchoCommand : public mdcore::Command
{
    public:
        EchoCommand()
        {
            setName("echo");
            setHelp("Repeats what you say back to you");
        };
        ~EchoCommand(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            std::string return_message = "";
            bool flag = true;
            for(auto arg : args)
            {
                if(flag)
                {
                    flag = false;
                }
                else{
                    return_message += " " + arg;
                }
            }
            event.reply(client,return_message);
        };
};

class EchoEventListener: public EventListener
{
    public:
        EchoEventListener(SleepyDiscord::Message message): EventListener(message.channelID, message.author.ID)
        {};
        ~EchoEventListener() override
        {};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override
        {
            message.reply(client, message.content);
        };
};

class EventListenerTestCommand: public mdcore::Command
{
    public:
        EventListenerTestCommand()
        {
            setName("listener_test");
            setHelp("Echo command but using the next message you send in this channel.");
        };
        ~EventListenerTestCommand(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            EventListener* listener = new (std::nothrow) EchoEventListener(event);
            e_dispatcher->registerListener(event.author.ID, listener);
            event.reply(client, "The next thing you type will be echoed by the bot.");
        };
};

#endif