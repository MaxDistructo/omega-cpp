#pragma once

#include "abils.h"
#include "role.h"
#include "modifiers.h"

namespace omega::Mafia{

    class Investigator : public Role
    {
        public:
            Investigator()
            {
                setName("investigator");
                setAbilities({Abilities::INVEST});
                setTraits({});
                setWinCondition(WinCondition::TOWN);
            }
            ~Investigator();
    };
    class Lookout : public Role
    {
        public:
            Lookout()
            {
                setName("lookout");
                setAbilities({Abilities::WATCH});
                setTraits({});
                setWinCondition(WinCondition::TOWN);
            };
            ~Lookout();
    };
    class Sheriff : public Role
    {
        public:
            Sheriff()
            {
                setName("sheriff");
                setAbilities({Abilities::SHERIFF});
                setTraits({});
                setWinCondition(WinCondition::TOWN);
            };
            ~Sheriff();
    };
    class Jailor : public Role
    {
        public:
            Jailor()
            {
                setName("jailor");
                setAbilities({Abilities::JAIL, Abilities::GRANT_DEFENCE, Abilities::BLOCK, Abilities::ATTACK});
                setTraits({Trait::UNIQUE});
                addModifier("defence", 1);
                addModifier("attack", 3);
                setWinCondition(WinCondition::TOWN);
            };
            ~Jailor();
    };
    class Vigilante : public Role
    {
        public:
            Vigilante()
            {
                setName("vigilante");
                setAbilities({Abilities::ATTACK});
                setTraits({});
                addModifier("attack", 1);
                setWinCondition(WinCondition::TOWN);
            };
            ~Vigilante();
    };
    class Veteran : public Role
    {
        public:
            Veteran()
            {
                setName("veteran");
                setAbilities({Abilities::KILL_VISITORS, Abilities::ONLY_SELF});
                setTraits({Trait::BLOCK_IMMUNE, Trait::UNIQUE});
                addModifier("attack", 2);
                setWinCondition(WinCondition::TOWN);
            }
            ~Veteran();
    };
    class VampireHunter : public Role
    {
        public:
            VampireHunter()
            {
                setName("vampire_hunter");
                setAbilities({Abilities::STAKE});
                setTraits({Trait::CAN_PROMOTE, Trait::VAMP_READ});
                addModifier("promoted_role", Modifier::PROMOTE_VIGILANTE);
                setWinCondition(WinCondition::TOWN);
            }
            ~VampireHunter();
    };
    class Escort : public Role
    {
        public:
            Escort()
            {
                setName("escort");
                setAbilities({Abilities::BLOCK});
                setTraits({Trait::BLOCK_IMMUNE});
                setWinCondition(WinCondition::TOWN);
            }
            ~Escort();
    };
    class Transporter : public Role 
    {
        public:
            Transporter()
            {
                setName("transporter");
                setAbilities({Abilities::TRANSPORT});
                setTraits({Trait::BLOCK_IMMUNE});
                setWinCondition(WinCondition::TOWN);
            }
            ~Transporter();
    };
    class Mayor : public Role
    {
        public:
            Mayor()
            {
                setName("mayor");
                setAbilities({Abilities::REVEAL, Abilities::ONLY_SELF});
                setTraits({Trait::UNIQUE});
                setWinCondition(WinCondition::TOWN);
            }
            ~Mayor();
    };
    class Retributionist : public Role
    {
        public:
            Retributionist()
            {
                setName("retributionist");
                setAbilities({Abilities::USE_OTHER});
                setTraits({Trait::UNIQUE});
                setWinCondition(WinCondition::TOWN);
            }
            ~Retributionist();
    };
    class Medium : public Role
    {
        public:
            Medium()
            {
                setName("medium");
                setAbilities({Abilities::SEANCE});
                setTraits({Trait::ANON_DEAD_TALK});
                setWinCondition(WinCondition::TOWN);
            };
            ~Medium();
    };
    class Bodyguard : public Role
    {
        public:
            Bodyguard()
            {
                setName("bodyguard");
                setAbilities({Abilities::GRANT_DEFENCE});
                setTraits({});
                addModifier("granted_defence", 1);
                addModifier("dies_on_target_attack", 1);
                setWinCondition(WinCondition::TOWN);
            };
            ~Bodyguard();
    };

    class Doctor : public Role 
    {
        public:
            Doctor()
            {
                setName("doctor");
                setAbilities({Abilities::GRANT_DEFENCE});
                setTraits({});
                addModifier("granted_defence", 1);
                setWinCondition(WinCondition::TOWN);
            }
            ~Doctor();
    };

    class Godfather : public Role
    {
        public:
            Godfather()
            {
                setName("godfather");
                setAbilities({Abilities::ATTACK});
                setTraits({Trait::DEFENCE, Trait::INNOCENT_EVIL, Trait::UNIQUE, Trait::MAF_TALK});
                addModifier("defence", 1);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Godfather();
    };

    class Mafioso : public Role 
    {
        public:
            Mafioso()
            {
                setName("mafioso");
                setAbilities({Abilities::ATTACK});
                setTraits({Trait::UNIQUE, Trait::MAF_TALK});
                addModifier("attack", 1);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Mafioso();
    };

    class Janitor : public Role
    {
        public:
            Janitor(){
                setName("janitor");
                setAbilities({Abilities::CLEAN});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Janitor();
    };

    class Framer : public Role 
    {
        public:
            Framer()
            {
                setName("framer");
                setAbilities({Abilities::FRAME});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Framer();
    };

    class Forger : public Role
    {
        public:
            Forger()
            {
                setName("forger");
                setAbilities({Abilities::FORGE});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Forger();
    };

    class Disguiser : public Role 
    {
        public:
            Disguiser()
            {
                setName("disguiser");
                setAbilities({Abilities::DISGUISE});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            }
            ~Disguiser();
    };

    class Consigliere : public Role
    {
        public:
            Consigliere()
            {
                setName("consigliere");
                setAbilities({Abilities::INVEST_ABSOLUTE});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            }
            ~Consigliere();
    };

    class Consort : public Role
    {
        public:
            Consort()
            {
                setName("consort");
                setAbilities({Abilities::BLOCK});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            }
            ~Consort();
    };

    class Ambusher : public Role
    {
        public:
            Ambusher()
            {
                setName("ambusher");
                setAbilities({Abilities::KILL_VISITOR});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Ambusher();
    };

    class Hypnotist : public Role 
    {
        public:
            Hypnotist()
            {
                setName("hypnotist");
                setAbilities({Abilities::HYPNO});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            };
            ~Hypnotist(){};
    };

    class Blackmailer : public Role
    {
        public:
            Blackmailer()
            {
                setName("blackmailer");
                setAbilities({Abilities::BLACKMAIL});
                setTraits({Trait::CAN_PROMOTE, Trait::MAF_TALK, Trait::READ_WHISPERS});
                addModifier("promoted_role", Modifier::PROMOTE_MAFIOSO);
                setWinCondition(WinCondition::MAFIA);
            }
            ~Blackmailer(){};
    };

    class SerialKiller : public Role
    {
        public:
            SerialKiller()
            {
                setName("serial_killer");
                setAbilities({Abilities::ATTACK});
                setTraits({Trait::DEFENCE});
                addModifier("attack", 1);
                addModifier("defence", 1);
                setWinCondition(WinCondition::WITH_LIKE);
            };
            ~SerialKiller(){};
    };

    class Werewolf : public Role 
    {
        public:
            Werewolf()
            {
                setName("werewolf");
                setAbilities({Abilities::RAMPAGE});
                setTraits({Trait::DEFENCE});
                addModifier("attack", 2);
                addModifier("defence", 1);
                setWinCondition(WinCondition::WITH_LIKE);
            }
            ~Werewolf(){};
    };

    class Arsonist : public Role
    {
        public:
            Arsonist()
            {
                setName("arsonist");
                setAbilities({Abilities::DOUSE});
                setTraits({Trait::DEFENCE});
                addModifier("attack", 2);
                addModifier("defence", 1);
                setWinCondition(WinCondition::WITH_LIKE);
            };
            ~Arsonist(){};
    };

    class Vampire : public Role
    {
        public:
            Vampire()
            {
                setName("vampire");
                setAbilities({Abilities::CONVERT});
                setTraits({Trait::VAMP_TALK});
                addModifier("attack", 1);
                setWinCondition(WinCondition::WITH_LIKE);
            };
            ~Vampire();
    };

    class Survivor : public Role
    {
        public:
            Survivor()
            {
                setName("survivor");
                setAbilities({Abilities::GRANT_DEFENCE, Abilities::ONLY_SELF});
                setTraits({});
                setWinCondition(WinCondition::ALIVE);
            };
            ~Survivor();
    };

    class Amnesiac : public Role
    {
        public:
            Amnesiac()
            {
                setName("amnesiac");
                setAbilities({Abilities::REMEMBER});
                setTraits({});
                setWinCondition(WinCondition::PROMOTED);
            };
            ~Amnesiac();
    };

    class Witch : public Role
    {
        public:
            Witch()
            {
                setName("witch");
                setAbilities({Abilities::USE_OTHER, Abilities::INVEST_ABSOLUTE});
                setTraits({});
                setWinCondition(WinCondition::EVILS);
            };
            ~Witch();
    };

    class Executioner : public Role
    {
        public:
            Executioner()
            {
                setName("executioner");
                setAbilities({});
                setTraits({Trait::DEFENCE, Trait::MUST_KILL});
                addModifier("defence", 1);
                setWinCondition(WinCondition::TARGET_KILLED);
            };
            ~Executioner();
    };

    class Jester : public Role
    {
        public:
            Jester()
            {
                setName("jester");
                setAbilities({});
                setTraits({});
                setWinCondition(WinCondition::LYNCHED);
            };
            ~Jester();
    };
}
