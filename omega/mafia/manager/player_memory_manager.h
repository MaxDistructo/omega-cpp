#pragma once
#include "../player.h"
#include <map>
#include <string>
#include "sleepy_discord/sleepy_discord.h"

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
                SleepyDiscord::DiscordClient* getClient()
                {
                    return client;
                }
                omega::Mafia::Player* get(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
                {
                    std::map<int64_t, omega::Mafia::Player*>::iterator it = backend.find(id.number());
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
                        backend[id.number()] = t;
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
                        backend[id.number()] = nullptr;
                    }
                };
            private:
                std::map<int64_t, Player*> backend;
                SleepyDiscord::DiscordClient* client;
        };
}
}