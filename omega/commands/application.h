#pragma once
#include "../main.h"
#include "../resources.h"

class ApplicationSubmitted: public EventListener
{
    public:
        ApplicationSubmitted(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user): EventListener(channel, user){};
        ~ApplicationSubmitted(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override 
        {
            application_storage[message.author.ID].push_back(message.content);
            client->sendMessage(getChannel(), "Your application has been submitted.");
            std::string application_message = "Application ( <@!" + message.author.ID + "> )\n";
            for(auto line : application_storage[message.author.ID])
            {
                application_message += "\n" + line;
            }
            client->sendMessage(982743781440909312, application_message);
        };
};

class EventHostApplicationQ3: public EventListener
{
    public:
        EventHostApplicationQ3(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user): EventListener(channel, user){};
        ~EventHostApplicationQ3(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override 
        {
            application_storage[message.author.ID].push_back(message.content);
            client->sendMessage(getChannel(), "Do you agree to abide by the Server Rules and enforce them during your event(s)?");
            application_storage[message.author.ID].push_back("Do you agree to abide by the Server Rules and enforce them during your event(s)?");
            e_dispatcher->enqueueListener("submitted-" + message.author.ID, new (std::nothrow) ApplicationSubmitted(getChannel(), message.author.ID));
        };
};

class EventHostApplicationQ2: public EventListener
{
    public:
        EventHostApplicationQ2(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user): EventListener(channel, user){};
        ~EventHostApplicationQ2(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override 
        {
            application_storage[message.author.ID].push_back(message.content);
            client->sendMessage(getChannel(), "What do you plan to be hosting?");
            application_storage[message.author.ID].push_back("What do you plan to be hosting?");
            e_dispatcher->enqueueListener("eventhost2-" + message.author.ID, new (std::nothrow) EventHostApplicationQ3(getChannel(), message.author.ID));
        };
};

class EventHostApplicationQ1 : public EventListener
{
    public:
        EventHostApplicationQ1(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channel, SleepyDiscord::Snowflake<SleepyDiscord::User> user): EventListener(channel, user){};
        ~EventHostApplicationQ1(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message message) override 
        {
            application_storage[message.author.ID].push_back(message.content);
            client->sendMessage(getChannel(), "Do you have any previous experience hosting/running events?");
            application_storage[message.author.ID].push_back("Do you have any previous experience hosting/running events?");
            e_dispatcher->enqueueListener("eventhost1-" + message.author.ID, new (std::nothrow) EventHostApplicationQ2(getChannel(), message.author.ID));
        };
}; 

class EventHostApplication: public mdcore::Command
{
    public:
        EventHostApplication()
        {
            setName("eventhost");
            setHelp("Apply to be an eventhost");
        };
        ~EventHostApplication(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            auto dm_channel = client->createDirectMessageChannel(event.author.ID.string()).cast();
            client->sendMessage(dm_channel.ID, "When would you be avaliable to host? (Specify with timezone)");
            application_storage[event.author.ID].push_back("When would you be avaliable to host? (Specify with timezone)");
            e_dispatcher->registerListener("eventhost-" + event.author.ID, new (std::nothrow) EventHostApplicationQ1(dm_channel, event.author.ID));
        };
};

class ApplyCommand: public mdcore::Command
{
    public:
        mdcore::SubcommandListener* listener = nullptr;
        ApplyCommand()
        {
            setName("apply");
            setHelp("Apply to be a staff member!");
        };
        ~ApplyCommand(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            if(listener == nullptr)
            {
                auto* eventhost = new (std::nothrow) EventHostApplication();
                std::vector<mdcore::Command*> commands;
                commands.push_back(eventhost);
                listener = new (std::nothrow) mdcore::SubcommandListener(1, commands);
            }
            listener->onMessage(client, event, args);
        };
};