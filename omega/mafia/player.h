#pragma once

#include "../main.h"
#include "traits.h"
#include "role.h"

class Player
{
    public:
        Player(SleepyDiscord::Snowflake<SleepyDiscord::User> id);
        ~Player();
        SleepyDiscord::Snowflake<SleepyDiscord::User> getID()
        {
            return ID;
        }
        std::vector<Trait> getTraits()
        {
            std::vector<Trait> actualTraits;
            actualTraits.insert(actualTraits.end(), traits.begin(), traits.end());
            actualTraits.insert(actualTraits.end(), role.getTraits().begin(), role.getTraits().end());
            return actualTraits;
        }
    private:
        Player();
        SleepyDiscord::Snowflake<SleepyDiscord::User> ID;
        Role role;
        std::vector<Trait> traits;

};