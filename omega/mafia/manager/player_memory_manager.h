#pragma once
#include "../player.h"
#include <map>
#include <string>
#include "sleepy_discord/sleepy_discord.h"

using BackendIterator = typename std::map<SleepyDiscord::Snowflake<SleepyDiscord::User>, omega::Mafia::Player*>::const_iterator;

namespace omega{
namespace Mafia{
    class PlayerMemoryManager
        {
            public:
                PlayerMemoryManager(SleepyDiscord::DiscordClient* clientin)
                {
                    client = clientin;
                };
                ~PlayerMemoryManager()
                {
                    for(auto entry : backend)
                    {
                        delete entry.second;
                    }
                    backend.clear();
                };
                omega::Mafia::Player* get(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
                {
                    BackendIterator it = backend.find(id);
                    if(it != backend.end())
                    {
                        return it->second;
                    }
                    //Not in backend
                    return nullptr;
                };
                bool create(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
                {
                    omega::Mafia::Player* t = new Player(id, client);
                    if(t != nullptr)
                    {
                        backend[id] = t;
                        return true;
                    }
                    return false;
                };
                omega::Mafia::Player* getOrCreate(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
                {
                    omega::Mafia::Player* test = get(id);
                    if(test != nullptr)
                    {
                        return test;
                    }
                    bool result = create(id);
                    if(!result)
                    {
                        return nullptr;
                    }
                    return get(id);
                };
                void remove(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
                {
                    omega::Mafia::Player* t = get(id);
                    if(t != nullptr)
                    {
                        delete t;
                        backend[id] = nullptr;
                    }
                };
            private:
                std::map<SleepyDiscord::Snowflake<SleepyDiscord::User>, Player*> backend;
                SleepyDiscord::DiscordClient* client;
        };
}
}