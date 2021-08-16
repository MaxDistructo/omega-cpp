#pragma once

#include "manager/player_memory_manager.h"
#include <vector>
#include "role.h"
#include "roles.h"

namespace omega::Mafia{
    #ifndef PLAYER_MEMORY_MANAGER
    #define PLAYER_MEMORY_MANAGER
    static omega::Mafia::PlayerMemoryManager* manager = nullptr;
    #endif
    static std::vector<Role*> roles = {
            new Investigator(),
            new Lookout(),
            new Sheriff(),
            new Jailor(),
            new Vigilante(),
            new Veteran(),
            new VampireHunter(),
            new Escort(),
            new Transporter(),
            new Mayor(),
            new Retributionist(),
            new Medium(),
            new Bodyguard(),
            new Doctor(),
            new Godfather(),
            new Mafioso(),
            new Janitor(),
            new Framer(),
            new Forger(),
            new Disguiser(),
            new Consigliere(),
            new Consort(),
            new Ambusher(),
            new Hypnotist(),
            new Blackmailer(),
            new SerialKiller(),
            new Werewolf(),
            new Arsonist(),
            new Vampire(),
            new Survivor(),
            new Amnesiac(),
            new Witch(),
            new Executioner(),
            new Jester()
    };
    static std::vector<std::string> hypno_strings {};

    #ifndef GET_PLAYER_MANAGER
    #define GET_PLAYER_MANAGER
    omega::Mafia::Player* getPlayerFromManager(SleepyDiscord::Message& event, std::string arg);
    #endif
}