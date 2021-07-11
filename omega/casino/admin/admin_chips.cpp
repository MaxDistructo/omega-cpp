#include "admin_chips.h"

namespace omega::Casino{
    bool addChips(Player* player, int count)
    {
        player->addChips(count);
    }
    bool removeMoney(Player* player, int count)
    {
        player->removeMoney(count);
    }
    bool resetPlayer(Player* player)
    {
        int chips = player->getMoney();
        player->removeMoney(chips);
    }
    bool freezePlayer(Player* player)
    {
        player->addMeta(Player::Metadata::FROZEN, "true");
    }
}