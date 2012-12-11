/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* Script Data Start
SFName: Boss Glubtok
SFAuthor: JeanClaude
SF%Complete: 25
SFComment: TODO: Check spellId's and clean up door events. also 2 fix warnings@lines(140,146,184)
SFCategory: dungeon script
Script Data End */

#include "ScriptPCH.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GameObject.h"
#include "deadmines.h"

enum Spells
{
    //Glubtok    these need checked http://www.wowhead.com/npc=47162#abilities 
    SPELL_FIRE_BLOSSOM          = 88129, // Fireball explodes on the ground
    SPELL_FROST_BLOSSOM         = 88169, // Iceball explodes on the ground
    SPELL_ARCANE_POWER          = 88009, // Spell Phase 2
    SPELL_FIST_OF_FLAME			= 87859, // elemental_fists
    SPELL_FIST_OF_FROST			= 87861, // elemental_fists    
    SPELL_BLINK                 = 38932
};


#define SAY_AGGRO "Let's do it!"
#define SAY_DIED "'Sploded dat one!"
#define SAY_FLAME "Elemental Fists!"
#define SAY_ARCANE "Glubtok show you da power of arcane!"

#define spell_elemental_fists RAND(87859, 91273)

const Position pos[1] =
{
    {-192.328003f, -450.244995f, 54.521500f, 0.00f}
};

enum Phases
{
    PHASE_NORMAL        = 1,
    PHASE_50_PERCENT    = 2,
};

class boss_glubtok : public CreatureScript
{
public:
    boss_glubtok() : CreatureScript("boss_glubtok") {}

    struct boss_glubtokAI : public ScriptedAI
    {
        boss_glubtokAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        uint8 Phase;

        uint32 elemental_fists;
        uint32 ArcanePowerTimer;
        uint32 blinkTimer;
        uint32 PhaseChangeTimer;
        uint32 NormalCastTimer;
        uint8 BlossomSpell;

        uint32 SUPER_FROST_BLOSSOMS; // wtf are these...
        uint32 SUPER_FIRE_BLOSSOMS;

        bool Phased;

        void Reset()
        {
            Phased                  = false;
            Phase                   = PHASE_NORMAL;

            elemental_fists         = 20000;
            blinkTimer              = 12000;

            NormalCastTimer         = 3000;
            SUPER_FROST_BLOSSOMS    = 2000;
            SUPER_FIRE_BLOSSOMS     = 2000;
        }

        void EnterCombat(Unit* who)
        {
            me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

        void JustDied(Unit* /*Killer*/)
        {
            me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
            return;

            if (me->HealthBelowPct(51) && Phase == PHASE_50_PERCENT && Phased == false)
            {
                me->SetReactState(REACT_PASSIVE);
                me->MonsterYell(SAY_ARCANE, LANG_UNIVERSAL, NULL);
                DoCast(me, SPELL_ARCANE_POWER);
                Position pos;
                me->GetPosition(&pos);

                if (NormalCastTimer <= diff)
                {
                   if (!me->IsNonMeleeSpellCasted(false))
                    {
                        uint8 Available[2];
                        switch (BlossomSpell)
                        {
                            case SUPER_FIRE_BLOSSOM:
                                Available [0] = SUPER_FIRE_BLOSSOM;
                                break;
                            case SUPER_FROST_BLOSSOM:
                                Available [1] = SUPER_FROST_BLOSSOM;
                                break;
                        }

                        BlossomSpell = Available[urand(0, 1)];
                        switch (BlossomSpell)
                        {
                            case SUPER_FIRE_BLOSSOM:
                                if (Unit* target =SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true));
                                DoCast(SPELL_FIRE_BLOSSOM);
                                SUPER_FIRE_BLOSSOMS = 2000;
                                break;
                            case SUPER_FROST_BLOSSOM:
                                if (Unit* target =SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true));
                                DoCast(SPELL_FROST_BLOSSOM);
                                SUPER_FROST_BLOSSOMS = 2000;
                                break;
                        }
                    }
                    NormalCastTimer = 3000;

                } else NormalCastTimer -= diff;

                Phase  = PHASE_50_PERCENT;
                Phased = true;

            }

            if (PhaseChangeTimer <= diff && Phase == PHASE_NORMAL)
            {
                if (PhaseChangeTimer<= diff)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    elemental_fists     = 20000;
                    blinkTimer          = 12000;
                    Phase               = PHASE_NORMAL;
                } else PhaseChangeTimer -= diff;

                if (elemental_fists <= diff && Phase == PHASE_NORMAL)
                {
                    if (elemental_fists<= diff)
                    {
                        DoCast(me, elemental_fists);
                        me->MonsterYell(SAY_FLAME, LANG_UNIVERSAL, NULL);
                        elemental_fists = 20000;
                    } else elemental_fists -= diff;
                }

                if (blinkTimer <= diff && Phase == PHASE_NORMAL)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1,10.0f, true));
                    DoCast(SPELL_BLINK);
                    blinkTimer = 12000;
                } else blinkTimer -= diff;

                DoMeleeAttackIfReady();
            }
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new boss_glubtokAI(creature);
    }
};

void AddSC_boss_glubtok()
{
    new boss_glubtok();
}
