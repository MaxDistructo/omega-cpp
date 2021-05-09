#include "abils.h"
#include "role.h"
#include "modifiers.h"

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
        setAbilities({Abilities::KILL_VISITORS, Abilities::ONLY_SELF});
        setTraits({Trait::BLOCK_IMMUNE, Trait::UNIQUE});
        addModifier("attack", 2);
    }
    ~Veteran();
};
class VampireHunter : Role
{
    VampireHunter()
    {
        setName("vampire_hunter");
        setAbilities({Abilities::STAKE});
        setTraits({Trait::CAN_PROMOTE, Trait::VAMP_READ});
        addModifier("promoted_role", Modifier::PROMOTE_VIGILANTE);
    }
    ~VampireHunter();
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
        setAbilities({Abilities::REVEAL, Abilities::ONLY_SELF});
        setTraits({Trait::UNIQUE});
    }
    ~Mayor();
};
class Retributionist : Role
{
    Retributionist()
    {
        setName("retributionist");
        setAbilities({Abilities::USE_OTHER});
        setTraits({Trait::UNIQUE});
    }
    ~Retributionist();
};
class Medium : Role
{
    Medium()
    {
        setName("medium");
        setAbilities({Abilities::SEANCE});
        setTraits({Trait::ANON_DEAD_TALK});
    };
    ~Medium();
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

class Godfather : Role
{
    Godfather()
    {
        setName("godfather");
        setAbilities({Abilities::ATTACK});
        setTraits({Trait::DEFENCE, Trait::INNOCENT_EVIL, Trait::UNIQUE, Trait::MAF_TALK});
        addModifier("defence", 1);
    };
    ~Godfather();
};

class Mafioso : Role 
{
    Mafioso()
    {
        setName("mafioso");
        setAbilities({Abilities::ATTACK});
        setTraits({Trait::UNIQUE, Trait::MAF_TALK});
        addModifier("attack", 1);
    };
    ~Mafioso();
};

class Janitor : Role
{
    Janitor(){
        setName("janitor");
        setAbilities({Abilities::CLEAN});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    };
    ~Janitor();
};

class Framer : Role 
{
    Framer()
    {
        setName("framer");
        setAbilities({Abilities::FRAME});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    };
    ~Framer();
};

class Forger : Role
{
    Forger()
    {
        setName("forger");
        setAbilities({Abilities::FORGE});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    };
    ~Forger();
};

class Disguiser : Role 
{
    Disguiser()
    {
        setName("disguiser");
        setAbilities({Abilities::DISGUISE});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    }
    ~Disguiser();
};

class Ambusher : Role
{
    Ambusher()
    {
        setName("ambusher");
        setAbilities({Abilities::KILL_VISITOR});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    };
    ~Ambusher();
};

class Hypnotist : Role 
{
    Hypnotist()
    {
        setName("hypnotist");
        setAbilities({Abilities::HYPNO});
        setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
        addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
    };
    ~Hypnotist();
};

class SerialKiller : Role
{
    SerialKiller()
    {
        setName("serial_killer");
        setAbilities({Abilities::ATTACK});
        setTraits({Trait::DEFENCE});
        addModifier("attack", 1);
        addModifier("defence", 1);
    };
    ~SerialKiller();
};

class Werewolf : Role 
{
    Werewolf()
    {
        setName("werewolf");
        setAbilities({Abilities::RAMPAGE});
        setTraits({Trait::DEFENCE});
        addModifier("attack", 2);
        addModifier("defence", 1);
    }
    ~Werewolf();
};

class Arsonist : Role
{
    Arsonist()
    {
        setName("arsonist");
        setAbilities({Abilities::DOUSE});
        setTraits({Trait::DEFENCE});
        addModifier("attack", 2);
        addModifier("defence", 1);
    };
    ~Arsonist();
};

class Vampire : Role
{
    Vampire()
    {
        setName("vampire");
        setAbilities({Abilities::CONVERT});
        setTraits({Trait::VAMP_TALK});
        addModifier("attack", 1);
    };
    ~Vampire();
};

class Survivor : Role
{
    Survivor()
    {
        setName("survivor");
        setAbilities({Abilities::GRANT_DEFENCE, Abilities::ONLY_SELF});
        setTraits({});
    };
    ~Survivor();
};

class Amnesiac : Role
{
    Amnesiac()
    {
        setName("amnesiac");
        setAbilities({Abilities::REMEMBER});
        setTraits({});
    };
    ~Amnesiac();
};

class Witch : Role
{
    Witch()
    {
        setName("witch");
        setAbilities({Abilities::USE_OTHER, Abilities::INVEST_ABSOLUTE});
        setTraits({});
    };
    ~Witch();
};

class Executioner : Role
{
    Executioner()
    {
        setName("executioner");
        setAbilities({});
        setTraits({Trait::DEFENCE, Trait::MUST_KILL});
        addModifier("defence", 1);
    };
    ~Executioner();
};

class Jester : Role
{
    Jester()
    {
        setName("jester");
        setAbilities({});
        setTraits({});
    };
    ~Jester();
};
