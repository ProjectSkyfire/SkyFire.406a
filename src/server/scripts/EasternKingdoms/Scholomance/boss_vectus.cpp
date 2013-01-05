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
SDName: Boss_Vectus
SD%Complete: 100
SDComment:
SDCategory: Scholomance
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SPELL_FLAMESTRIKE            = 18399,
    SPELL_BLAST_WAVE             = 16046,
    SPELL_FIRESHIELD             = 19626,
    SPELL_FRENZY                 = 8269 //28371,
};

class boss_vectus : public CreatureScript
{
public:
    boss_vectus() : CreatureScript("boss_vectus") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_vectusAI (creature);
    }

    struct boss_vectusAI : public ScriptedAI
    {
        boss_vectusAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 FireShield_Timer;
        uint32 BlastWave_Timer;
        uint32 Frenzy_Timer;

        void Reset()
        {
            FireShield_Timer = 2000;
            BlastWave_Timer = 14000;
            Frenzy_Timer = 0;
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            //FireShield_Timer
            if (FireShield_Timer <= Diff)
            {
                DoCast(me, SPELL_FIRESHIELD);
                FireShield_Timer = 90000;
            }
            else
                FireShield_Timer -= Diff;

            //BlastWave_Timer
            if (BlastWave_Timer <= Diff)
            {
                DoCast(me->getVictim(), SPELL_BLAST_WAVE);
                BlastWave_Timer = 12000;
            }
            else
                BlastWave_Timer -= Diff;

            //Frenzy_Timer
            if (HealthBelowPct(25))
            {
                if (Frenzy_Timer <= Diff)
                {
                    DoCast(me, SPELL_FRENZY);
                    DoScriptText(EMOTE_GENERIC_FRENZY_KILL, me);

                    Frenzy_Timer = 24000;
                }
                else
                    Frenzy_Timer -= Diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_vectus()
{
    new boss_vectus();
}
