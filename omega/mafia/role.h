#pragma once

#include "traits.h"
#include "abils.h"
#include <string>
#include <vector>
#include <map>

class Role
{
    public:
        Role();
        ~Role();

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
    private:
        std::vector<Trait> traits = {};
        std::vector<Abilities> abilities = {};
        std::string name = "";
        std::map<std::string, int> abilityModifiers = {};
};