#ifndef __omega__commands_h
#define __omega__commands_h

#include "../main.h"
#include "sleepy_discord/permissions.h"

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

class CheckCommand : public mdcore::Command
{
    public:
        CheckCommand()
        {
            setName("check");
            setHelp("Checks permissions for a user");
        };
        ~CheckCommand(){};
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override
        {
            SleepyDiscord::ServerMember member = client->getMember(event.serverID, event.author.ID).cast();
            SleepyDiscord::Permission permissions = SleepyDiscord::getPermissions(client->getServer(event.serverID), member, client->getChannel(event.channelID));
            std::vector<SleepyDiscord::Permission> all_permissions = 
            {
                SleepyDiscord::Permission::CREATE_INSTANT_INVITE,
                SleepyDiscord::Permission::KICK_MEMBERS         ,
                SleepyDiscord::Permission::BAN_MEMBERS          ,
                SleepyDiscord::Permission::ADMINISTRATOR        ,
                SleepyDiscord::Permission::MANAGE_CHANNELS      ,
                SleepyDiscord::Permission::MANAGE_GUILD         ,
                SleepyDiscord::Permission::ADD_REACTIONS        ,
                SleepyDiscord::Permission::VIEW_AUDIT_LOG       ,
                SleepyDiscord::Permission::VIEW_CHANNEL         ,
                SleepyDiscord::Permission::SEND_MESSAGES        ,
                SleepyDiscord::Permission::SEND_TTS_MESSAGES    ,
                SleepyDiscord::Permission::MANAGE_MESSAGES      ,
                SleepyDiscord::Permission::EMBED_LINKS          ,
                SleepyDiscord::Permission::ATTACH_FILES         ,
                SleepyDiscord::Permission::READ_MESSAGE_HISTORY ,
                SleepyDiscord::Permission::MENTION_EVERYONE     ,
                SleepyDiscord::Permission::USE_EXTERNAL_EMOJIS  ,
                SleepyDiscord::Permission::CONNECT              ,
                SleepyDiscord::Permission::SPEAK                ,
                SleepyDiscord::Permission::MUTE_MEMBERS         ,
                SleepyDiscord::Permission::DEAFEN_MEMBERS       ,
                SleepyDiscord::Permission::MOVE_MEMBERS         ,
                SleepyDiscord::Permission::USE_VAD              ,
                SleepyDiscord::Permission::PRIORITY_SPEAKER     ,
                SleepyDiscord::Permission::CHANGE_NICKNAME      ,
                SleepyDiscord::Permission::MANAGE_NICKNAMES     ,
                SleepyDiscord::Permission::MANAGE_ROLES         ,
                SleepyDiscord::Permission::MANAGE_WEBHOOKS      ,
                SleepyDiscord::Permission::MANAGE_EMOJIS        
            };

            for(auto permission : all_permissions)
            {

            }


            
        };
}; 

#endif