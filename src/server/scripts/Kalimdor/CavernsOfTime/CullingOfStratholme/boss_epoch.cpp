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
SFName: Boss epoch
SFAuthor: Tartalo
SF%Complete: 80
SFComment: TODO: Intro, consecutive attacks to a random target durin time wrap, adjust timers
SFCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CURSE_OF_EXERTION                     = 52772,
    SPELL_TIME_WARP                             = 52766, //Time slows down, reducing attack, casting and movement speed by 70% for 6 sec.
    SPELL_TIME_STOP                             = 58848, //Stops time in a 50 yard sphere for 2 sec.
    SPELL_WOUNDING_STRIKE                       = 52771, //Used only on the tank
    H_SPELL_WOUNDING_STRIKE                     = 58830
};

enum Yells
{
    SAY_INTRO                                   = -1595000, //"Prince Arthas Menethil, on this day, a powerful darkness has taken hold of your soul. The death you are destined to visit upon others will this day be your own."
    SAY_AGGRO                                   = -1595001, //"We'll see about that, young prince."
    SAY_TIME_WARP_1                             = -1595002, //"Tick tock, tick tock..."
    SAY_TIME_WARP_2                             = -1595003, //"Not quick enough!"
    SAY_TIME_WARP_3                             = -1595004, //"Let's get this over with. "
    SAY_SLAY_1                                  = -1595005, //"There is no future for you."
    SAY_SLAY_2                                  = -1595006, //"This is the hour of our greatest triumph!"
    SAY_SLAY_3                                  = -1595007, //"You were destined to fail. "
    SAY_DEATH                                   = -1595008 //"*gurgles*"
};

class boss_epoch : public CreatureScript
{
public:
    boss_epoch() : CreatureScript("boss_epoch") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_epochAI (creature);
    }

    struct boss_epochAI : public ScriptedAI
    {
        boss_epochAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        uint8 Step;

        uint32 StepTimer;
        uint32 WoundingStrikeTimer;
        uint32 TimeWarpTimer;
        uint32 TimeStopTimer;
        uint32 CurseOfExertionTimer;

        InstanceScript* instance;

        void Reset()
        {
            Step = 1;
            StepTimer = 26000;
            CurseOfExertionTimer = 9300;
            TimeWarpTimer = 25300;
            TimeStopTimer = 21300;
            WoundingStrikeTimer = 5300;

            if (instance)
                instance->SetData(DATA_EPOCH_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (instance)
                instance->SetData(DATA_EPOCH_EVENT, IN_PROGRESS);
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (CurseOfExertionTimer < diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_CURSE_OF_EXERTION);
                CurseOfExertionTimer = 9300;
            }
            else CurseOfExertionTimer -= diff;

            if (WoundingStrikeTimer < diff)
            {
                DoCastVictim(SPELL_WOUNDING_STRIKE);
                WoundingStrikeTimer = 5300;
            }
            else WoundingStrikeTimer -= diff;

            if (TimeStopTimer < diff)
            {
                DoCastAOE(SPELL_TIME_STOP);
                TimeStopTimer = 21300;
            }
            else TimeStopTimer -= diff;

            if (TimeWarpTimer < diff)
            {
                DoScriptText(RAND(SAY_TIME_WARP_1, SAY_TIME_WARP_2, SAY_TIME_WARP_3), me);
                DoCastAOE(SPELL_TIME_WARP);
                TimeWarpTimer = 25300;
            }
            else TimeWarpTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            if (instance)
                instance->SetData(DATA_EPOCH_EVENT, DONE);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim == me)
                return;

            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3), me);
        }
    };
};

void AddSC_boss_epoch()
{
    new boss_epoch();
}
