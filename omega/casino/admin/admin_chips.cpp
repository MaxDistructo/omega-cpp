#include "admin_chips.h"

namespace omega::Casino{
    bool addChips(Player* player, int count)
    {
        player->giveMoney(count);
        return true;
    }
    bool removeMoney(Player* player, int count)
    {
        player->removeMoney(count);
        return true;
    }
    bool resetPlayer(Player* player)
    {
        int chips = player->getMoney();
        player->removeMoney(chips);
        return true;
    }
    bool freezePlayer(Player* player)
    {
        player->setMeta(Player::Metadata::FROZEN, "true");
        return true;
    }
}