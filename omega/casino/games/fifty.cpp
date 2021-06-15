#include "fifty.h"
#include <stdlib.h>
#include <chrono>

namespace omega::Casino{
    bool playFifty(Player* player, int bet)
    {
        player->sendMessage("Time to play: 50/50!");
        player->sendMessage("If you win, you will double your money.");
        player->sendMessage("If you lose, you will lose everything!");
        //Seed the random generator fairly lazily. We can create something better in the future
        srand(getCurrentTime());
        int rand_val = rand() % 2;
        if(rand_val)
        {
            player->giveMoney(bet * 2);
            player->sendMessage("You WIN!");
            return true;
        }
        else
        {
            player->removeMoney(bet);
            player->sendMessage("You LOSE.");
            return true;
        }
        return false;
    };
}