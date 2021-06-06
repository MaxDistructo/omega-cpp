#pragma once

#include <vector>
#include "mdcore/logger.h"
#include "sleepy_discord/sleepy_discord.h"
#include <map>
#include <string>
#include "../utils.h"
#include "omega_mafia.h"

using namespace std;

extern vector<Player*> players;
extern vector<Role*> roles;
extern vector<std::string> hypno_strings;

bool checkForPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
bool playerJoin(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
bool playerRemove(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
Player* getPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
template<class T>
bool setPlayerRole(SleepyDiscord::Snowflake<SleepyDiscord::User> ID, T r)
{
    if(checkForPlayer(ID)){
        auto player = getPlayer(ID);
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