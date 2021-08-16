#pragma once

#include "manager/player_memory_manager.h"
#include "role.h"
#include "roles.h"

#ifndef USE_MEMORY_MANAGED
#include <vector>
using RoleVector = std::vector<omega::Mafia::Role*>;
#else
#include "manager/memory_managed_vector.h"
using RoleVector = MemoryManagedVector<Role*>;
#endif

namespace omega::Mafia{
    #ifndef PLAYER_MEMORY_MANAGER
    #define PLAYER_MEMORY_MANAGER
    static omega::Mafia::PlayerMemoryManager* manager = nullptr;
    #endif
    //We are not declaring with nothrow. If we don't get the memory, we will crash
    //This is not a concern in most cases but it is a posibility with unchecked memory allocations
    //TODO: Move this initialization to a manager
    static RoleVector roles = {
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