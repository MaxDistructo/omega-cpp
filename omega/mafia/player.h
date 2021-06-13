#pragma once

#include "traits.h"
#include "role.h"
#include "modifiers.h"
#include "wincons.h"
#include "../main.h"

namespace omega::Mafia{
    class Player
    {
        public:
            Player(SleepyDiscord::Snowflake<SleepyDiscord::User> id, SleepyDiscord::DiscordClient* clientin)
            {
                ID = id;
                client = clientin;
            }
            ~Player(){};
            SleepyDiscord::Snowflake<SleepyDiscord::User> getID()
            {
                return ID;
            }
            const std::vector<Trait> getTraits()
            {
                std::vector<Trait> actualTraits;
                actualTraits.insert(actualTraits.end(), traits.begin(), traits.end());
                actualTraits.insert(actualTraits.end(), role->getTraits().begin(), role->getTraits().end());
                return actualTraits;
            }
            const std::map<std::string, int> getModifiers()
            {
                return modifiers;
            }
            const int getModifier(std::string key)
            {
                return modifiers[key];
            }
            const std::map<std::string, int> getEffectiveModifiers()
            {
                std::map<std::string, int> tmp;
                tmp.insert(modifiers.begin(), modifiers.end());
                tmp.insert(tmp_mods.begin(), tmp_mods.end());
                return tmp;
            }
            Role* getRole()
            {
                return role;
            }

            void setRole(Role* r)
            {
                //Reset all modifiers, if they exist
                modifiers.clear();
                //Set roles that have use numbers
                if(*r == "vigilante" && *role == "vampire_hunter")
                {
                    modifiers["uses"] = 1;
                }
                else if(*r == "survivor" && *role == "guardian_angel")
                {
                    modifiers["uses"] = 0;
                }
                else if((*r == "vigilante" && *role != "vampire_hunter") || *r == "veteran" || *r == "jailor" || *r == "medusa")
                {
                    modifiers["uses"] = 3;
                }
                else if (*r == "survivor" && *role != "guardian_angel")
                {
                    modifiers["uses"] = 4;
                }
                else if(firstRole && *r == "mafioso")
                {
                    modifiers["promoted_role"] = Modifier::PROMOTE_GODFATHER;
                }
                else if(*r == "guardian_angel")
                {
                    modifiers["uses"] = 2;
                }
                else if(*r == "doctor" || *r == "bodyguard" || *r == "medium")
                {
                    modifiers["uses"] = 1;
                }
                else if(*r == "witch")
                {
                    modifiers["uses"] = 1;
                    addPermModifier("defence", 1);
                }
                modifiers.insert(r->getModifiers().begin(), r->getModifiers().end());
                
                if(firstRole)
                {
                    firstRole = false;
                }

                role = r;
            }
                    
            void addTempModifier(std::string key, int value)
            {
                tmp_mods[key] = value;
            }
            void removePermModifier(std::string key)
            {
                modifiers.erase(key);
            }
            void addPermModifier(std::string key, int value)
            {
                modifiers[key] = value;
            }
            nlohmann::json toJson()
            {
                nlohmann::json j;
                j["id"] = ID.string();
                j["role"] = role->getName();
                j["traits"] = traits;
                j["modifiers"] = modifiers;
                j["tmp_mods"] = tmp_mods;
                j["firstRole"] = firstRole;
                return j;
            }
            bool operator==(Player p)
            {
                return ID == p.getID();
            }
            friend std::string operator+(Player* p, std::string& s)
            {
                s + p->client->getUser(p->ID).cast().username;
                return s;
            }
            friend std::string operator+=(Player* p, std::string& s)
            {
                s + p;
                return s;
            }
            friend std::string operator+(std::string& s, Player* p)
            {
                s + p->client->getUser(p->ID).cast().username;
                return s;
            }
            friend std::string operator+=(std::string& s, Player* p)
            {
                s + p;
                return s;
            }
            void kill(Role* r)
            {
                alive = false;
                client->sendMessage(client->createDirectMessageChannel(ID).cast(), "You were killed by a " + r->getName());
            }
            void sendMessage(std::string message)
            {
                client->sendMessage(client->createDirectMessageChannel(ID).cast(), message);
            }
            void addTrait(Trait t)
            {
                traits.push_back(t);
            }
            void removeTrait(Trait t)
            {
                std::vector<Trait>::iterator iter = getIterLocation(traits, t);
                if(iter != traits.end()){
                    traits.erase(iter);
                }
            }
            bool hasTrait(Trait t)
            {
                return std::count(traits.begin(), traits.end(), t);
            }
            bool isAlive()
            {
                return alive;
            }
            SleepyDiscord::User getUser()
            {
                return client->getUser(ID).cast();
            }
            bool isEvil()
            {
                if(role->getWinCondition() == WinCondition::COVEN || role->getWinCondition() == WinCondition::MAFIA || role->getWinCondition() == WinCondition::WITH_LIKE)
                {
                    if(!hasTrait(Trait::INNOCENT_EVIL)){
                        return true;
                    }
                }
                return false;
            }
        private:
            Player();
            SleepyDiscord::Snowflake<SleepyDiscord::User> ID;
            Role* role;
            std::vector<Trait> traits = {};
            std::map<std::string, int> modifiers = {};
            std::map<std::string, int> tmp_mods = {};
            bool firstRole = true;
            bool alive = true;
            SleepyDiscord::DiscordClient* client;
    };
}