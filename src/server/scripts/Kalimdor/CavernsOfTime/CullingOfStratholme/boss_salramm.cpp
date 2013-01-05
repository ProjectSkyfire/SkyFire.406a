/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
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
SFName: Boss salramm
SFAuthor: Tartalo
SF%Complete: 80
SFComment: TODO: Intro
SFCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CURSE_OF_TWISTED_FLESH                = 58845,
    SPELL_EXPLODE_GHOUL                         = 52480,
    H_SPELL_EXPLODE_GHOUL                       = 58825,
    SPELL_SHADOW_BOLT                           = 57725,
    H_SPELL_SHADOW_BOLT                         = 58828,
    SPELL_STEAL_FLESH                           = 52708,
    SPELL_SUMMON_GHOULS                         = 52451
};

enum Yells
{
    SAY_AGGRO                                   = -1595032,
    SAY_SPAWN                                   = -1595033,
    SAY_SLAY_1                                  = -1595034,
    SAY_SLAY_2                                  = -1595035,
    SAY_SLAY_3                                  = -1595036,
    SAY_DEATH                                   = -1595037,
    SAY_EXPLODE_GHOUL_1                         = -1595038,
    SAY_EXPLODE_GHOUL_2                         = -1595039,
    SAY_STEAL_FLESH_1                           = -1595040,
    SAY_STEAL_FLESH_2                           = -1595041,
    SAY_STEAL_FLESH_3                           = -1595042,
    SAY_SUMMON_GHOULS_1                         = -1595043,
    SAY_SUMMON_GHOULS_2                         = -1595044
};

class boss_salramm : public CreatureScript
{
public:
    boss_salramm() : CreatureScript("boss_salramm") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_salrammAI (creature);
    }

    struct boss_salrammAI : public ScriptedAI
    {
        boss_salrammAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            if (instance)
                DoScriptText(SAY_SPAWN, me);
        }

        uint32 CurseFleshTimer;
        uint32 ExplodeGhoulTimer;
        uint32 ShadowBoltTimer;
        uint32 StealFleshTimer;
        uint32 SummonGhoulsTimer;

        InstanceScript* instance;

        void Reset()
        {
             CurseFleshTimer = 30000;  //30s DBM
             ExplodeGhoulTimer = urand(25000, 28000); //approx 6 sec after summon ghouls
             ShadowBoltTimer = urand(8000, 12000); // approx 10s
             StealFleshTimer = 12345;
             SummonGhoulsTimer = urand(19000, 24000); //on a video approx 24s after aggro

             if (instance)
                 instance->SetData(DATA_SALRAMM_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (instance)
                 instance->SetData(DATA_SALRAMM_EVENT, IN_PROGRESS);
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //Curse of twisted flesh timer
            if (CurseFleshTimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CURSE_OF_TWISTED_FLESH);
                CurseFleshTimer = 37000;
            }
            else CurseFleshTimer -= diff;

            //Shadow bolt timer
            if (ShadowBoltTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_SHADOW_BOLT);
                ShadowBoltTimer = urand(8000, 12000);
            }
            else ShadowBoltTimer -= diff;

            //Steal Flesh timer
            if (StealFleshTimer <= diff)
            {
                DoScriptText(RAND(SAY_STEAL_FLESH_1, SAY_STEAL_FLESH_2, SAY_STEAL_FLESH_3), me);
                if (Unit* random_target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(random_target, SPELL_STEAL_FLESH);
                StealFleshTimer = 10000;
            }
            else StealFleshTimer -= diff;

            //Summon ghouls timer
            if (SummonGhoulsTimer <= diff)
            {
                DoScriptText(RAND(SAY_SUMMON_GHOULS_1, SAY_SUMMON_GHOULS_2), me);
                if (Unit* random_target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(random_target, SPELL_SUMMON_GHOULS);
                SummonGhoulsTimer = 10000;
            }
            else SummonGhoulsTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            if (instance)
                instance->SetData(DATA_SALRAMM_EVENT, DONE);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim == me)
                return;

            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3), me);
        }
    };
};

void AddSC_boss_salramm()
{
    new boss_salramm();
}
