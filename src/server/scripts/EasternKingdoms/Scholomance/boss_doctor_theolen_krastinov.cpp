/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Boss_Doctor_Theolen_Krastinov
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */

#include "ScriptPCH.h"
#include "scholomance.h"

enum eEnums
{
    SPELL_REND                  = 16509,
    SPELL_BACKHAND              = 18103,
    SPELL_FRENZY                = 8269
};

class boss_doctor_theolen_krastinov : public CreatureScript
{
public:
    boss_doctor_theolen_krastinov() : CreatureScript("boss_doctor_theolen_krastinov") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_theolenkrastinovAI (creature);
    }

    struct boss_theolenkrastinovAI : public ScriptedAI
    {
        boss_theolenkrastinovAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 Rend_Timer;
        uint32 Backhand_Timer;
        uint32 Frenzy_Timer;

        void Reset()
        {
            Rend_Timer = 8000;
            Backhand_Timer = 9000;
            Frenzy_Timer = 1000;
        }

        void JustDied(Unit* /*killer*/)
        {
            InstanceScript* instance = me->GetInstanceScript();
            if (instance)
            {
                instance->SetData(DATA_DOCTORTHEOLENKRASTINOV_DEATH, 0);

                if (instance->GetData(TYPE_GANDLING) == IN_PROGRESS)
                    me->SummonCreature(1853, 180.73f, -9.43856f, 75.507f, 1.61399f, TEMPSUMMON_DEAD_DESPAWN, 0);
            }
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            //Rend_Timer
            if (Rend_Timer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_REND);
                Rend_Timer = 10000;
            }
            else
                Rend_Timer -= Diff;

            //Backhand_Timer
            if (Backhand_Timer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_BACKHAND);
                Backhand_Timer = 10000;
            }
            else
                Backhand_Timer -= Diff;

            //Frenzy_Timer
            if (HealthBelowPct(26))
            {
                if (Frenzy_Timer <= Diff)
                {
                    DoCast(me, SPELL_FRENZY);
                    DoScriptText(EMOTE_GENERIC_FRENZY_KILL, me);

                    Frenzy_Timer = 120000;
                }
                else
                    Frenzy_Timer -= Diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_theolenkrastinov()
{
    new boss_doctor_theolen_krastinov();
}
