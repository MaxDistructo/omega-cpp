#include "mafia.h"
#include "roles.h"
#include "role.h"

using namespace std;

vector<Player*> players = {};
mdcore::Logger::Logger logger = mdcore::Logger::Logger("Mafia");
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

bool playerJoin(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
{
    if(!checkForPlayer(ID)){
        Player* newPlayer = nullptr;

        newPlayer = new (nothrow) Player(ID);
        if(newPlayer == nullptr)
        {
            logger.error("Unable to allocate memory for new player!");
            exit(-1);
        }

        players.push_back(newPlayer);
        return true;
    }
    else
    {
        return false;
    }
}

bool playerRemove(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
{
    
    for(vector<Player*>::iterator iter = players.begin(); iter < players.end(); iter++)
    {
        auto* player = players[iter-players.begin()];
        if(player->getID() == ID)
        {
            players.erase(iter);
            return true;
        }
    }
    return false;
}

bool checkForPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
{
   for(vector<Player*>::iterator iter = players.begin(); iter < players.end(); iter++)
    {
        auto* player = players[iter-players.begin()];
        if(player->getID() == ID)
        {
            return true;
        }
    }
    return false;
}

Player* getPlayer(SleepyDiscord::Snowflake<SleepyDiscord::User> ID)
{
    for(vector<Player*>::iterator iter = players.begin(); iter < players.end(); iter++)
    {
        auto* player = players[iter-players.begin()];
        if(player->getID() == ID)
        {
            return player;
        }
    }
    return nullptr;
}

bool setPlayerRole(SleepyDiscord::Snowflake<SleepyDiscord::User> ID, std::string r)
{
    if(checkForPlayer(ID)){
        auto player = getPlayer(ID);
        for(auto role : roles)
        {
            if(role->getName() == r)
            {
                player->setRole(role);
                return true;
            }
        }
    }
    return false;
}