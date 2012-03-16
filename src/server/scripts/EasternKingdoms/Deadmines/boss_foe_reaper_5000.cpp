/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "deadmines.h"

/* ScriptData
SDName: Foe Reaper 5000
SD%Complete: 10
SDComment: Boss Script
SDCategory: Dead Mines
EndScriptData */

/*
enum Yells
{
    SAY_AGGRO = "ONLINE STUFF"

};
*/

enum Spells
{
    SPELL_OFFLINE         = 88348,
    SPELL_SRO             = 88522,
    SPELL_SRO_H           = 91720,
    SPELL_OVERDRIVE       = 88481,
    SPELL_HARVEST         = 88495,
    SPELL_HARVEST_SWEAP   = 88521,
    SPELL_HARVEST_SWEAP_H = 91718,
    SPELL_REAPER_STRIKE   = 88490,
    SPELL_REAPER_STRIKE_H = 91717
    
};

class boss_foe_reaper_5000 : public CreatureScript
{
public:
    boss_foe_reaper_5000() : CreatureScript("boss_foe_reaper_5000") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_foe_reaper_5000AI (creature);
    }

    struct boss_foe_reaper_5000AI : public ScriptedAI
    {
        boss_foe_reaper_5000AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

            uint32 m_uiSpell1Timer;                                 // Timer for spell 1 when in combat
            uint32 m_uiSpell2Timer;                                 // Timer for spell 2 when in combat
            uint32 m_uiSpell3Timer;                                 // Timer for spell 3 when in combat

        void Reset()
        {
                m_uiSpell1Timer = 5000;                             // 10 seconds
                m_uiSpell2Timer = urand(10000, 25000);              // between 10 and 25 seconds
                m_uiSpell3Timer = 20000;                            // 20 seconds
        }

        void EnterCombat(Unit* /*who*/)
        {
            //Say Online Stuff Text
            //DoScriptText(SAY_AGGRO, me, who);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (m_uiSpell1Timer <= uiDiff)
            {
                //Cast spell one on our current target.
                if (me->IsWithinDist(me->getVictim(), 25.0f))
                    DoCast(me->getVictim(), SPELL_REAPER_STRIKE);

                m_uiSpell1Timer = 5000;
            }
            else
                m_uiSpell1Timer -= uiDiff;

            if (m_uiSpell2Timer <= uiDiff)
            {
                //Cast spell two on our current target.
                DoCast(me->getVictim(), SPELL_OVERDRIVE);
                m_uiSpell2Timer = 37000;
            }
            else
                m_uiSpell2Timer -= uiDiff;


            if (m_uiSpell3Timer <= uiDiff)
            {
                //Cast spell tree on our current target.
                DoCast(me->getVictim(), SPELL_HARVEST);

                m_uiSpell3Timer = 20000;
            }
            else
                m_uiSpell3Timer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_foe_reaper_5000()
{
    new boss_foe_reaper_5000();
}