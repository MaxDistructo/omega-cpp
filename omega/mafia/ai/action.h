#pragma once

#include "../abils.h"
#include "../player.h"
#include <vector>
#include <map>
#include <string>

namespace omega::Mafia::Ai{
    struct Action
    {
        Abilities ability;
        std::vector<Player*> targets;
        Player* user;
        std::map<std::string, int> modifiers = {};
        bool operator==(Action& a)
        {
            return ability == a.ability && targets == a.targets && user == a.user && modifiers == a.modifiers;
        }
        bool operator!=(Action& a)
        {
            return !(*this == a);
        }
    };
}