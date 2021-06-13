#pragma once
#include "sleepy_discord/sleepy_discord.h"

namespace omega{
    class GamePlayer
    {
        public:
            GamePlayer(){};
            GamePlayer(SleepyDiscord::DiscordClient* CLIENT, SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
            {
                client = CLIENT;
                id = ID;
            };
            ~GamePlayer(){};
            SleepyDiscord::Snowflake<SleepyDiscord::User> getID()
            {
                return id;
            }
            SleepyDiscord::User getUser()
            {
                return client->getUser(id).cast();
            }
            bool operator==(GamePlayer p)
            {
                return id == p.getID();
            }
            friend std::string operator+(GamePlayer* p, std::string& s)
            {
                s + p->client->getUser(p->id).cast().username;
                return s;
            }
            friend std::string operator+=(GamePlayer* p, std::string& s)
            {
                s + p;
                return s;
            }
            friend std::string operator+(std::string& s, GamePlayer* p)
            {
                s + p->client->getUser(p->id).cast().username;
                return s;
            }
            friend std::string operator+=(std::string& s, GamePlayer* p)
            {
                s + p;
                return s;
            }
        protected:
            SleepyDiscord::DiscordClient* client;
            SleepyDiscord::Snowflake<SleepyDiscord::User> id;    
    };
}