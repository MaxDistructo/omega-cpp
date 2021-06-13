#pragma once

#include "action.h"

namespace omega::Mafia::Ai{
    extern std::vector<Action> actions;
    void useAbility(Player* player, std::vector<Player*> target, bool day);
    void useAbility(Player* player, std::vector<Player*> targets, Abilities ability, bool day);
    void useNightAbility(Player* player, std::vector<Player*> target);
    void useDayAbility(Player* player, std::vector<Player*> target);
    std::vector<Player*> getVisitors(Player* player);
    void runAbil(Action action);
    void runAllAbilities();
}