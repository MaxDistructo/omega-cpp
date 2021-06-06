#pragma once

#include "traits.h"
#include "abils.h"
#include <string>
#include <vector>
#include <map>
#include "wincons.h"
#include <cstring>

class Role
{
    public:
        Role(){};
        ~Role(){};
        std::string getName()
        {
            return name;
        };
        const std::vector<Trait> getTraits()
        {
            return traits;
        };
        const std::vector<Abilities> getAbilities()
        {
            return abilities;
        };
        const int getModifier(std::string key)
        {
            try{
                return abilityModifiers[key];
            }
            catch(...)
            {
                return -1;
            }
        }
        const std::map<std::string, int> getModifiers()
        {
            return abilityModifiers;
        }
        const WinCondition getWinCondition()
        {
            return wincon;
        };
        template<class T>
        bool operator==(T& s)
        {
            return name == s;
        }
        template<class T>
        bool operator!=(T& s)
        {
            return name != s;
        }
        bool operator==(Role r)
        {
            return *this == r.name;
        }
        bool operator!=(Role r)
        {
            return *this != r.name;
        }
        bool operator==(const char* s)
        {
            return strcmp(name.c_str(), s) == 0;
        }
        bool operator!=(const char* s)
        {
            return strcmp(name.c_str(), s) != 0;
        }
    protected:
        void setName(std::string n)
        {
            name = n;
        };
        void setAbilities(std::vector<Abilities> a)
        {
            abilities = a;
        };
        void setTraits(std::vector<Trait> t)
        {
            traits = t;
        };
        void addModifier(std::string key, int value)
        {
            abilityModifiers[key] = value;
        };
        void setWinCondition(WinCondition w)
        {
            wincon = w;
        };
    private:
        std::vector<Trait> traits = {};
        std::vector<Abilities> abilities = {};
        std::string name = "";
        std::map<std::string, int> abilityModifiers = {};
        WinCondition wincon = WinCondition::WITH_LIKE;
};