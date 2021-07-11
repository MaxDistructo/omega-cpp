#pragma once
#include "../casino.h"

namespace omega::Casino{
    bool giveChips(Player* player, int count);
    bool removeChips(Player* player, int count);
    bool resetPlayer(Player* player);
    bool freezePlayer(Player* player);

    class CasinoAdminGive : public mdcore::Command
    {
        CasinoAdminGive();
        ~CasinoAdminGive();
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override;
    }
    class CasinoAdminRemove : public mdcore::Command
    {
        CasinoAdminRemove();
        ~CasinoAdminRemove();
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override;
    }
    class CasinoAdminReset : public mdcore::Command
    {
        CasinoAdminReset();
        ~CasinoAdminReset();
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override;
    }
    class CasinoAdminFreeze : public mdcore::Command
    {
        CasinoAdminFreeze();
        ~CasinoAdminFreeze();
        void execute(SleepyDiscord::DiscordClient* client, SleepyDiscord::Message event, std::vector<std::string> args) override;
    }
}