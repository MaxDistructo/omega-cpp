#pragma once

#include "../main.h"
#include "mdcore/command.h"

std::string mentionUser(SleepyDiscord::User user)
{
    return (std::string)"<@!" + user.ID.string() + ">";
}

class SlapCommand : public mdcore::Command
{
    public:
        SlapCommand()
        {
            setName("slap");
            setHelp("slap @User - Slap another user");
        }
        ~SlapCommand(){};
        void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            auto botUser = client->getCurrentUser().cast();
            if(event.isMentioned(botUser))
            {
                event.reply(client, (std::string)"You have been slapped by " + mentionUser(botUser) + "!");
            }
            else 
            {
                event.reply(client, mentionUser(event.mentions[0]) + ", you have been slapped by " + mentionUser(event.author));
            }
        }
};

class TntCommand : public mdcore::Command
{
    TntCommand()
    {
        setName("tnt");
        setHelp("tnt @User - Blow another user up with some TNT!");
    }
    ~TntCommand(){}
    void execute(SleepyDiscord::DiscordClient *client, SleepyDiscord::Message event, std::vector<std::string> args) override
    {
                    auto botUser = client->getCurrentUser().cast();
            if(event.isMentioned(botUser))
            {
                event.reply(client, mentionUser(botUser) + " has blown up " + mentionUser(event.author));
            }
            else 
            {
                event.reply(client, mentionUser(event.mentions[0]) + ", you have been slapped by " + mentionUser(event.author));
            }
    }
};