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
                    break;
                }
                case(Game::BLACKJACK):
                {
                    return playBlackjack(player, bet);
                    break;
                }
                case(Game::FIFTY):
                {
                    return playFifty(player, bet);
                    break;
                }
                case(Game::SLOTS):
                {
                    return playSlots(player, bet);
                    break;
                }
                default:
                    return false;
            }
        }
        return false;
    }
    long getCurrentTime()
    {
        //Get the duration in milliseconds, of the time point in milliseconds,
        //of the current time, since the epoch.
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::time_point_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now()).time_since_epoch()
            ).count();
    }

}