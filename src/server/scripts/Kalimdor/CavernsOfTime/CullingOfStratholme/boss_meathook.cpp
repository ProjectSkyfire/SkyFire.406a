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
SFName: Boss meathook
SFAuthor: Tartalo
SF%Complete: 100
SFComment: It may need timer adjustment
SFCategory:
Script Data End */

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CONSTRICTING_CHAINS                   = 52696, //Encases the targets in chains, dealing 1800 Physical damage every 1 sec. and stunning the target for 5 sec.
    H_SPELL_CONSTRICTING_CHAINS                 = 58823,
    SPELL_DISEASE_EXPULSION                     = 52666, //Meathook belches out a cloud of disease, dealing 1710 to 1890 Nature damage and interrupting the spell casting of nearby enemy targets for 4 sec.
    H_SPELL_DISEASE_EXPULSION                   = 58824,
    SPELL_FRENZY                                = 58841 //Increases the caster's Physical damage by 10% for 30 sec.
};

enum Yells
{
    SAY_AGGRO                                   = -1595026,
    SAY_SLAY_1                                  = -1595027,
    SAY_SLAY_2                                  = -1595028,
    SAY_SLAY_3                                  = -1595029,
    SAY_SPAWN                                   = -1595030,
    SAY_DEATH                                   = -1595031
};

class boss_meathook : public CreatureScript
{
public:
    boss_meathook() : CreatureScript("boss_meathook") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_meathookAI (creature);
    }

    struct boss_meathookAI : public ScriptedAI
    {
        boss_meathookAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            if (instance)
                DoScriptText(SAY_SPAWN, me);
        }

        uint32 ChainTimer;
        uint32 DiseaseTimer;
        uint32 FrenzyTimer;

        InstanceScript* instance;

        void Reset()
        {
            ChainTimer = urand(12000, 17000);   //seen on video 13, 17, 15, 12, 16
            DiseaseTimer = urand(2000, 4000);   //approx 3s
            FrenzyTimer = urand(21000, 26000);  //made it up

            if (instance)
                instance->SetData(DATA_MEATHOOK_EVENT, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (instance)
                instance->SetData(DATA_MEATHOOK_EVENT, IN_PROGRESS);
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (DiseaseTimer <= diff)
            {
                DoCastAOE(SPELL_DISEASE_EXPULSION);
                DiseaseTimer = urand(1500, 4000);
            }
            else DiseaseTimer -= diff;

            if (FrenzyTimer <= diff)
            {
                DoCast(me, SPELL_FRENZY);
                FrenzyTimer = urand(21000, 26000);
            }
            else FrenzyTimer -= diff;

            if (ChainTimer <= diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_CONSTRICTING_CHAINS); //anyone but the tank
                ChainTimer = urand(2000, 4000);
            }
            else ChainTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);

            if (instance)
                instance->SetData(DATA_MEATHOOK_EVENT, DONE);
        }

        void KilledUnit(Unit* victim)
        {
            if (victim == me)
                return;

            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3), me);
        }
    };
};

void AddSC_boss_meathook()
{
    new boss_meathook();
}
