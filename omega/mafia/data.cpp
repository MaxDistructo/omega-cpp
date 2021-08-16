#include "data.h"

omega::Mafia::Player* getPlayerFromManager(SleepyDiscord::Message& event, std::string arg)
    {
        //FIXME: Upgrade code to get IDs from more inputs.
        //RN we just do a lazy convert from string to the long long int that a discord snowflake is

        //Format: DiscordName#0000
        //Start by checking for a #. Basic format check for most people's lazy way of mentioning.
        if(arg.find("#") != std::string::npos)
        {
            //We have a #, Assume the basic format and check with the Message's Server to get the Member
            SleepyDiscord::ServerMember member = omega::Mafia::manager->getClient()->getMember(event.serverID, arg.substr(0, arg.find("#"))).cast();
            return omega::Mafia::manager->getOrCreate(member.ID);
        }

        int64_t id = std::stoi(arg);
        return omega::Mafia::manager->getOrCreate(id);
    }