#pragma once
#include "../../main.h"
#include "../../game_base.h"

namespace omega::Casino
{
    class Player : public GamePlayer
    {

        public:
            Player(SleepyDiscord::DiscordClient* client_in, SleepyDiscord::Snowflake<SleepyDiscord::User> id) : GamePlayer(client_in, id){};
            ~Player(){};
            enum Metadata
            {
                DAILY,
                DAILY_COOLDOWN,
                FROZEN
            };
            std::string getMeta(Metadata key)
            {
                return metadata[key];
            };
            void setMeta(Metadata key, std::string value)
            {
                metadata[key] = value;
            };
            bool deleteMeta(Metadata key)
            {
                metadata[key] = "";
            }
            int getMoney()
            {
                return money;
            }
            void giveMoney(int val)
            {
                money += val;
            }
            bool removeMoney(int val)
            {
                if(testRemoveMoney(val))
                {
                    money -= val;
                    return true;
                }
                return false;
            }
            bool testRemoveMoney(int val)
            {
                int money_copy = money;
                if((money_copy - val) > 0)
                {
                    return true;
                }
                return false;
            }
        private:
            int money = 0;
            
            std::map<Metadata, std::string> metadata;      
    };
}