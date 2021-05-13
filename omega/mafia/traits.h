#pragma once

enum Trait
{
    //Passive Traits
    DEFENCE,
    BLOCK_IMMUNE,
    UNIQUE,

    //Night Abils
    DEAD_TALK,
    ANON_DEAD_TALK,
    VAMP_TALK,
    VAMP_READ,
    MAF_TALK,

    //Settable Traits
    CLEANED,
    STONED,
    JAILED, //Also makes user transport immune
    FRAMED,
    FORGED,
    DOUSED,
    BLOCKED,
    INFECTED,
    CANNOT_HEAL,
    CANNOT_WHISPER,
    CAN_PROMOTE,
    INNOCENT_EVIL,
    KILL_BLOCKERS,
    MUST_KILL,
    REVEALED
};