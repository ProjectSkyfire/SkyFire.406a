/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/> 
 * Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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
 
 
#include "ScriptPCH.h"

enum Yells                       //need texts and sound ids
{
SAY_AGGRO = -0,                  //sound id 24517
SAY_DEATH = -0,                  //sound id 24519
SAY_KILL_1 = -0,                 //sound id 24531
SAY_KILL_2 = -0,                 //sound id 24530
SAY_KILL_3 = -0,                 //sound id 24529
SAY_HAMMER_DROP_1 = -0,          //sound id 24520
SAY_HAMMER_DROP_2 = -0,          //sound id 24521
SAY_HAMMER_DROP_3 = -0,          //sound id 24522
SAY_HAMMER_PICKUP_1 = -0,        //sound id 24523
SAY_HAMMER_PICKUP_2 = -0,        //sound id 24524
SAY_HAMMER_PICKUP_3 = -0,        //sound id 24525
SAY_PURGE = -0,                  //sound id 24532
};

enum Spells
{
SPELL_SULFURAS_SMASH          = 98710,
SPELL_LIVING_METEOR           = 99268, //every difficult
SPELL_WRATH_OF_RAGNAROS       = 98263,
SPELL_MAGMA_SMASH             = 98313,
SPELL_CLEAVING_BLOW           = 98951, //on 40% hp
SPELL_BURNING_WOUND           = 99399,
SPELL_MAGMA_TRAP              = 98164, //every difficult
SPELL_LAVA_WAVE               = 100293,
SPELL_HAND_OF_RAGNAROS        = 98237,
};

class boss_ragnaros_cata : public CreatureScript
{
    public:
    boss_ragnaros_cata() : CreatureScript("boss_ragnaros_cata"){}

    CreatureAI* GetAI_boss_ragnaros_cata(Creature* pCreature) const
    {
        return new boss_ragnaros_cataAI(pCreature);
    }

    struct boss_ragnaros_cataAI : public ScriptedAI
    {
        boss_ragnaros_cataAI(Creature *c) : ScriptedAI(c) {}

            //spell timers
        uint32 SulfurasSmash_Timer;
        uint32 LivingMeteor_Timer;
        uint32 WrathOfRagnaros_Timer;
        uint32 MagmaSmash_Timer;
        uint32 CleavinBlow_Timer;
        uint32 BurningWound_Timer;
        uint32 MagmaTrap_Timer;
        uint32 LavaWave_Timer;
        uint32 HandOfRagnaros_Timer;

            //battle phases
            uint32 Phase1;
            uint32 Phase2;
            uint32 Phase3;
            uint32 Phase4;

        void Reset()
        {
            SulfurasSmash_Timer = 60000;
            HandOfRagnaros_Timer = 65000;
        }

        void KilledUnit(Unit * /*victim*/) {}

        void JustDied(Unit * /*victim*/) {}

        void EnterCombat(Unit * /*who*/) {}

        void UpdateAI(const uint32 uiDiff)
        {
            if (!me->getVictim())
        }

        if (!UpdateVictim())
            return;

        if(SulfurasSmash_Timer <=uiDiff)
        {
            if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_SULFURAS_SMASH);

            SulfurasSmash_Timer = 60000;
        }
        else
        SulfurasSmash_Timer -= uiDiff;

        DoMeleeAttackIfReady();  
    };	   
};

void AddSC_boss_ragnaros_cata()
{
    new boss_ragnaros_cata();
    new npc_living_meteor();
}