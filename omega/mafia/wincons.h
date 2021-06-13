#pragma once

namespace omega::Mafia{
    enum WinCondition
    {
        TOWN,
        MAFIA,
        LYNCHED,
        TARGET_KILLED,
        COVEN,
        WITH_LIKE,
        EVILS,
        ALIVE,
        ABILITY_SUCCESSES,
        PROMOTED
    };
}