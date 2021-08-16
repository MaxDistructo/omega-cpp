#pragma once

#include "player.h"
#include "role.h"
#include "roles.h"
#include "data.h"
#include "sleepy_discord/sleepy_discord.h"

namespace omega::Mafia{
    template<class T>
    bool setPlayerRole(SleepyDiscord::Snowflake<SleepyDiscord::User> ID, T r)
    {
        Player* player = manager->get(ID);
        if(player != nullptr){
            for(auto role : roles)
            {
                if(role->getName() == r)
                {
                    player->setRole(role);
                    return true;
                }
            }
        }
        return false;
    }
    std::string getInvestResults(Role* r);
    template <class T>
    inline int getRoleIndex(T s)
    {
        for(size_t i = 0; i < roles.size(); i++)
        {
            if(roles[i]->getName() == s)
            {
                return i;
            }
        }
        return -1;
    };
}