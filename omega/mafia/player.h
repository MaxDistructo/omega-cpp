#pragma once

#include "../main.h"
#include "traits.h"
#include "role.h"
#include "modifiers.h"

class Player
{
    public:
        Player(SleepyDiscord::Snowflake<SleepyDiscord::User> id)
        {
            id = ID;
        }
        ~Player();
        SleepyDiscord::Snowflake<SleepyDiscord::User> getID()
        {
            return ID;
        }
        const std::vector<Trait> getTraits()
        {
            std::vector<Trait> actualTraits;
            actualTraits.insert(actualTraits.end(), traits.begin(), traits.end());
            actualTraits.insert(actualTraits.end(), role.getTraits().begin(), role.getTraits().end());
            return actualTraits;
        }
        const std::map<std::string, int> getModifiers()
        {
            return modifiers;
        }
        const std::map<std::string, int> getEffectiveModifiers()
        {
            std::map<std::string, int> tmp;
            tmp.insert(modifiers.begin(), modifiers.end());
            tmp.insert(tmp_mods.begin(), tmp_mods.end());
            return tmp;
        }
    protected:
        void setRole(Role r)
        {
            //Reset all modifiers, if they exist
            modifiers.clear();
            //Set roles that have use numbers
            if(r == "vigilante" && role == "vampire_hunter")
            {
                modifiers["uses"] = 1;
            }
            else if(r == "survivor" && role == "guardian_angel")
            {
                modifiers["uses"] = 0;
            }
            else if((r == "vigilante" && role != "vampire_hunter") || r == "veteran" || r == "jailor" || r == "medusa")
            {
                modifiers["uses"] = 3;
            }
            else if (r == "survivor" && role != "guardian_angel")
            {
                modifiers["uses"] = 4;
            }
            else if(firstRole && r == "mafioso")
            {
                modifiers["promoted_role"] = Modifier::PROMOTE_GODFATHER;
            }
            else if(r == "guardian_angel")
            {
                modifiers["uses"] = 2;
            }
            else if(r == "doctor" || r == "bodyguard" || r == "medium")
            {
                modifiers["uses"] = 1;
            }
            else if(r == "witch")
            {
                modifiers["uses"] = 1;
                addPermModifier("defence", 1);
            }
            modifiers.insert(r.getModifiers().begin(), r.getModifiers().end());
            
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
    private:
        Player();
        SleepyDiscord::Snowflake<SleepyDiscord::User> ID;
        Role role;
        std::vector<Trait> traits = {};
        std::map<std::string, int> modifiers = {};
        std::map<std::string, int> tmp_mods = {};
        bool firstRole = true;
};