#include "omega_mafia.h"
#include "command/com.h"

using namespace std;
namespace omega::Mafia{
    mdcore::Logger logger = mdcore::Logger("Mafia");
    vector<Role*> roles = {
            new (nothrow) Investigator(),
            new (nothrow) Lookout(),
            new (nothrow) Sheriff(),
            new (nothrow) Jailor(),
            new (nothrow) Vigilante(),
            new (nothrow) Veteran(),
            new (nothrow) VampireHunter(),
            new (nothrow) Escort(),
            new (nothrow) Transporter(),
            new (nothrow) Mayor(),
            new (nothrow) Retributionist(),
            new (nothrow) Medium(),
            new (nothrow) Bodyguard(),
            new (nothrow) Doctor(),
            new (nothrow) Godfather(),
            new (nothrow) Mafioso(),
            new (nothrow) Janitor(),
            new (nothrow) Framer(),
            new (nothrow) Forger(),
            new (nothrow) Disguiser(),
            new (nothrow) Consigliere(),
            new (nothrow) Consort(),
            new (nothrow) Ambusher(),
            new (nothrow) Hypnotist(),
            new (nothrow) Blackmailer(),
            new (nothrow) SerialKiller(),
            new (nothrow) Werewolf(),
            new (nothrow) Arsonist(),
            new (nothrow) Vampire(),
            new (nothrow) Survivor(),
            new (nothrow) Amnesiac(),
            new (nothrow) Witch(),
            new (nothrow) Executioner(),
            new (nothrow) Jester()
        };
    vector<string> hypno_strings
    {

    };

    bool playerJoin(SleepyDiscord::Snowflake<SleepyDiscord::User> ID, SleepyDiscord::DiscordClient* c)
    {
        if(!checkForPlayer(ID)){
            manager->create(ID);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool playerRemove(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
    {
        manager->remove(ID);
        return true;
    }

    bool checkForPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
    {
        return manager->get(ID) != nullptr;
    }

    std::string getInvestResults(Role* r)
    {
        return "";
    }
}