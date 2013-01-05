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
SFName: Isle_of_Queldanas
SF%Complete: 100
SFComment: Quest support: 11524, 11525, 11532, 11533, 11542, 11543, 11541
SFCategory: Isle Of Quel'Danas
EndScriptData */

/* ContentData
npc_converted_sentry
npc_greengill_slave
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_converted_sentry
######*/

enum NPCs
{
    DARKSPINE_MYRMIDON     = 25060
};

enum Says
{
    SAY_CONVERTED_1        = -1000188,
    SAY_CONVERTED_2        = -1000189
};

enum Spells
{
    SPELL_CONVERT_CREDIT   = 45009,
    ENRAGE                 = 45111,
    ORB_OF_MURLOC_CONTROL  = 45109
};

enum Quests
{
   DISRUPT_THE_GREENGILL_COAST  = 11541
};

class npc_converted_sentry : public CreatureScript
{
public:
    npc_converted_sentry() : CreatureScript("npc_converted_sentry") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_converted_sentryAI (creature);
    }

    struct npc_converted_sentryAI : public ScriptedAI
    {
        npc_converted_sentryAI(Creature* creature) : ScriptedAI(creature) {}

        bool Credit;
        uint32 Timer;

        void Reset()
        {
            Credit = false;
            Timer  = 2500;
        }

        void MoveInLineOfSight(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (!Credit)
            {
                if (Timer <= diff)
                {
                    uint32 i = urand(1, 2);
                    if (i == 1)
                        DoScriptText(SAY_CONVERTED_1, me);
                    else
                        DoScriptText(SAY_CONVERTED_2, me);

                    DoCast(me, SPELL_CONVERT_CREDIT);
                    if (me->isPet())
                        me->ToPet()->SetDuration(7500);
                    Credit = true;
                }
                else Timer -= diff;
            }
        }
    };
};

/*######
## npc_greengill_slave
######*/

class npc_greengill_slave : public CreatureScript
{
public:
    npc_greengill_slave() : CreatureScript("npc_greengill_slave") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_greengill_slaveAI(creature);
    }

    struct npc_greengill_slaveAI : public ScriptedAI
    {
        npc_greengill_slaveAI(Creature* creature) : ScriptedAI(creature) {}

        uint64 PlayerGUID;

        void EnterCombat(Unit* /*who*/) {}

        void Reset()
        {
            PlayerGUID = 0;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == ORB_OF_MURLOC_CONTROL && !me->HasAura(ENRAGE))
            {
                PlayerGUID = caster->GetGUID();
                if (PlayerGUID)
                {
                    Unit* player = Unit::GetUnit((*me), PlayerGUID);
                    if (player && CAST_PLR(player)->GetQuestStatus(DISRUPT_THE_GREENGILL_COAST) == QUEST_STATUS_INCOMPLETE)
                        DoCast(player, 45110, true);
                }
                DoCast(me, ENRAGE);
                Unit* Myrmidon = me->FindNearestCreature(DARKSPINE_MYRMIDON, 70);
                if (Myrmidon)
                {
                    me->AddThreat(Myrmidon, 100000.0f);
                    AttackStart(Myrmidon);
                }
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_isle_of_queldanas()
{
    new npc_converted_sentry();
    new npc_greengill_slave();
}
