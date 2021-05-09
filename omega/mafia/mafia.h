#pragma once

#include "role.h"
#include "player.h"
#include <vector>
#include "mdcore/logger.h"
#include "sleepy_discord/sleepy_discord.h"
#include <map>
#include <string>
#include "../utils.h"

using namespace std;

extern vector<Player*> players;
extern vector<Role*> roles;

bool checkForPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
bool playerJoin(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
bool playerRemove(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
Player* getPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID);
bool setPlayerRole(SleepyDiscord::Snowflake<SleepyDiscord::User> ID, std::string r);
std::string getInvestResults(Role* r);
template<class T>
int getRoleIndex(T r){
    return getIndex(roles, r);
};