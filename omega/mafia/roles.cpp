#include "role.h"

class Investigator : Role
{
    Investigator()
    {
        setName("investigator");
        setAbilities({Abilities::INVEST});
        setTraits({});
    }
    ~Investigator();
};
class Lookout : Role
{
    Lookout()
    {
        setName("lookout");
        setAbilities({Abilities::WATCH});
        setTraits({});
    };
    ~Lookout();
};
class Sheriff : Role
{
    Sheriff()
    {
        setName("sheriff");
        setAbilities({Abilities::SHERIFF});
        setTraits({});
    };
    ~Sheriff();
};
class Jailor : Role
{
    Jailor()
    {
        setName("jailor");
        setAbilities({Abilities::JAIL, Abilities::GRANT_DEFENCE, Abilities::BLOCK, Abilities::ATTACK});
        setTraits({Trait::UNIQUE});
        addModifier("defence", 1);
        addModifier("attack", 3);
    };
    ~Jailor();
};
class Vigilante : Role
{
    Vigilante()
    {
        setName("vigilante");
        setAbilities({Abilities::ATTACK});
        setTraits({});
        addModifier("attack", 1);
    };
    ~Vigilante();
};
class Veteran : Role
{
    Veteran()
    {
        setName("veteran");
        setAbilities({Abilities::KILL_VISITORS});
        setTraits({Trait::BLOCK_IMMUNE, Trait::UNIQUE});
        addModifier("attack", 2);
    }
    ~Veteran();
};
class Escort : Role
{
    Escort()
    {
        setName("escort");
        setAbilities({Abilities::BLOCK});
        setTraits({Trait::BLOCK_IMMUNE});
    }
    ~Escort();
};
class Transporter : Role 
{
    Transporter()
    {
        setName("transporter");
        setAbilities({Abilities::TRANSPORT});
        setTraits({Trait::BLOCK_IMMUNE});
    }
    ~Transporter();
};
class Mayor : Role
{
    Mayor()
    {
        setName("mayor");
        setAbilities({Abilities::REVEAL});
        setTraits({Trait::CANNOT_HEAL, Trait::CANNOT_WHISPER});
    }
    ~Mayor();
};
class Retributionist : Role
{
    Retributionist()
    {
        setName("retributionist");
        setAbilities({Abilities::USE_OTHER});
        setTraits({});
    }
    ~Retributionist();
};

class Bodyguard : Role
{
    Bodyguard()
    {
        setName("bodyguard");
        setAbilities({Abilities::GRANT_DEFENCE});
        setTraits({});
        addModifier("granted_defence", 1);
        addModifier("dies_on_target_attack", 1);
    };
    ~Bodyguard();
};

class Doctor : Role 
{
    Doctor()
    {
        setName("doctor");
        setAbilities({Abilities::GRANT_DEFENCE});
        setTraits({});
        addModifier("granted_defence", 1);
    }
    ~Doctor();
};
