#include "data.h"

omega::Mafia::Player* getPlayerFromManager(SleepyDiscord::Message& event, std::string arg)
    {
        //Format: <@id>
        //Every discord mention in plain text looks like this. We need to support this to allow us to take proper mentions
        if(arg.find("<@") != std::string::npos)
        {
            //Strip the ID out of the format and get the member object
            SleepyDiscord::ServerMember member = omega::Mafia::manager->getClient()->getMember(event.serverID, arg.substr(arg.find("@"), arg.find(">"))).cast();
            return omega::Mafia::manager->getOrCreate(member.ID);
        }

        const std::vector<SleepyDiscord::ServerMember> members = omega::Mafia::manager->getClient()->listMembers(event.serverID).get<std::vector<SleepyDiscord::ServerMember>>();
        //Format: DiscordName#0000
        //Start by checking for a #. Basic format check for most people's lazy way of mentioning.
        if(arg.find("#") != std::string::npos)
        {
            //We have a #, Assume the basic format and check with the Message's Server to get the Member
            std::string username = arg.substr(0, arg.find("#"));
            std::string discrim = arg.substr(arg.find("#"), arg.size()-1);
            for(auto member : members)
            {
                if(member.user.username == username && member.user.discriminator == discrim)
                {
                    return omega::Mafia::manager->getOrCreate(member.ID);
                }
            }
        }
        //Format: DiscordName
        //We now assume that they have mentioned someone without doing any normal type of mention but instead just put their name.
        //Take that name and attempt to find them in the server list
        for(auto member : members)
        {
            if(member.user.username == arg)
            {
                return omega::Mafia::manager->getOrCreate(member.ID);
            }
        }
        
        //If we still haven't returned, assume it's a number and attempt to get with that
        int64_t id = std::stoi(arg);
        //RIP, we didn't understand what was said. Return nullptr
        if(id == 0)
        {
            return nullptr;
        }
        return omega::Mafia::manager->getOrCreate(id);
    }