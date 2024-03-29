#include "slots.h"

namespace omega::Casino
{
    static int jackpot = 500;
    std::vector<ReelItems> v_reel1 = {ReelItems::STAR, ReelItems::HEART, ReelItems::SEVEN, ReelItems::SEVEN, ReelItems::HEART, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X};
    std::vector<ReelItems> v_reel2 = {ReelItems::STAR, ReelItems::HEART, ReelItems::SEVEN, ReelItems::SEVEN, ReelItems::HEART, ReelItems::HEART, ReelItems::SEVEN, ReelItems::X, ReelItems::SEVEN, ReelItems::HEART};
    std::vector<ReelItems> v_reel3 = {ReelItems::STAR, ReelItems::HEART, ReelItems::SEVEN, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X, ReelItems::X};
    std::string createEmojiString(std::vector<ReelItems> v);
    bool playSlots(Player* player, int bet)
    {
        player->sendMessage("Rolling the slots");
        srand(getCurrentTime());
        auto reel1 = v_reel1[rand() % v_reel1.size()];
        auto reel2 = v_reel2[rand() % v_reel2.size()];
        auto reel3 = v_reel3[rand() % v_reel3.size()];

        if(reel1 == ReelItems::STAR && reel2 == ReelItems::STAR && reel3 == ReelItems::STAR)
        {
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            player->sendMessage(emojicpp::EMOJIS[":star:"] + emojicpp::EMOJIS[":star:"] + emojicpp::EMOJIS[":star:"]);
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            //WINNER, WINNER, WINNER
            player->sendMessage("YOU WIN!");
            if((jackpot/bet) > 1){
                player->giveMoney(jackpot * (jackpot/bet));
            }
            else
            {
                player->giveMoney(jackpot);
            }
            jackpot = 500;
            return true;
        }
        else if(reel1 == ReelItems::HEART && reel2 == ReelItems::HEART && reel3 == ReelItems::HEART)
        {
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            player->sendMessage(emojicpp::EMOJIS[":heart:"] + emojicpp::EMOJIS[":heart:"] + emojicpp::EMOJIS[":heart:"]);
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            //WINNER, WINNER, WINNER
            player->sendMessage("YOU WIN!");
            if(bet < (jackpot/2)){
                player->giveMoney(bet * 4);
            }
            else
            {
                player->giveMoney(bet * 2);
            }
            return true;
        }
        else if(reel1 == ReelItems::SEVEN && reel2 == ReelItems::SEVEN && reel3 == ReelItems::SEVEN)
        {
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            player->sendMessage(emojicpp::EMOJIS[":keycap_digit_seven:"] + emojicpp::EMOJIS[":keycap_digit_seven:"] + emojicpp::EMOJIS[":keycap_digit_seven:"]);
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            //WINNER, WINNER, WINNER
            player->sendMessage("YOU WIN!");
            player->giveMoney(bet * 2);
            return true;
        }
        else //LOSER!
        {
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            std::string builder = createEmojiString({reel1, reel2, reel3});
            player->sendMessage(builder);
            player->sendMessage(emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"] + emojicpp::EMOJIS[":box:"]);
            player->sendMessage("YOU LOSE");
            player->removeMoney(bet);
            return true;
        }
        return false;
    }
    std::string createEmojiString(std::vector<ReelItems> v)
    {
        std::string output;
        for(auto i : v)
        {
            if(i == ReelItems::STAR)
            {
                output += emojicpp::EMOJIS[":star:"];
            }
            else if(i == ReelItems::HEART)
            {
                output += emojicpp::EMOJIS[":heart:"];
            }
            else if(i == ReelItems::SEVEN)
            {
                output += emojicpp::EMOJIS[":keycap_digit_seven:"];
            }
            else
            {
                output += emojicpp::EMOJIS[":x:"];
            }
        }
        return output;
    }
}