#pragma once
#include "../player.h"
#include "../role.h"
#include "action.h"
#include "../traits.h"

extern std::vector<Action> actions;

void useAbility(Player* player, std::vector<Player*> target, bool day);
void useAbility(Player* player, std::vector<Player*> targets, Abilities ability, bool day);
void useNightAbility(Player* player, std::vector<Player*> target);
void useDayAbility(Player* player, std::vector<Player*> target);
std::vector<Player*> getVisitors(Player* player);
void runAbil(Action action);
void runAllAbilities();