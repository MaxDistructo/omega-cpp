#include "casino.h"
#include "games/games.h"

namespace omega::Casino{
    std::vector<Player*> players;

    bool giveDaily(Player* player, int bet)
    {
        if(player->getMeta(Player::Metadata::DAILY) == "true")
        {
            player->giveMoney(500);
            return true;
        }
        else
        {
            return false;
        }
    }
    bool playBettingGame(Player* player, Game game, int bet)
    {
        if(player->testRemoveMoney(bet))
        {
            switch(game){
                case(Game::DAILY):
                {
                    return giveDaily(player, bet);
                }
                case(Game::BLACKJACK):
                {
                    return playBlackjack(player, bet);
                }
                default:
                    return false;
            }
        }
        return false;
    }

}