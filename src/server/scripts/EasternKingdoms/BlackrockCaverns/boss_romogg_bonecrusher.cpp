/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
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
SfName: BlackRock Caverns
Sf%Complete: 80%
SfComment: based on Naios & PaladMaster's work
SfCategory: BlackRock
EndScriptData */

#include "ScriptPCH.h"
#include "blackrock_caverns.h"

enum Spells
{
    SPELL_CALL_FOR_HELP             = 82137,
    SPELL_QUAKE                     = 75272,
    SPELL_THE_SKULLCRACKER          = 75543,
    SPELL_WOUNDING_STRIKE           = 69651,

    SPELL_CHAINS_OF_WOE             = 75539,
    SPELL_CHAINS_OF_WOE_VISUAL      = 75441,
    SPELL_CHAINS_OF_WOE_AURA        = 82192,

};

enum Events
{
    EVENT_QUAKE                     = 1,
    EVENT_CHAINS_OF_WOE             = 2,
    EVENT_WOUNDING_STRIKE           = 3
};

class boss_romogg_bonecrusher : public CreatureScript
{
public:
    boss_romogg_bonecrusher() : CreatureScript("boss_romogg_bonecrusher") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_romogg_bonecrusherAI (creature);
    }

    struct boss_romogg_bonecrusherAI : public ScriptedAI
    {
        boss_romogg_bonecrusherAI(Creature* creature) : ScriptedAI(creature), castSkullCracker(false), chainsOfWoe(0)
        {
            instance = creature->GetInstanceScript();
            me->setActive(true);
        }

        InstanceScript* instance;
        uint32 chainsOfWoe_Timer;
        uint32 Phase;
        EventMap events;
        bool castSkullCracker;
        Creature* chainsOfWoe;

        void Reset()
        {
            if (instance)
                instance->SetData(DATA_ROMOGG_BONECRUSHER, NOT_STARTED);

            Phase = 0;
            chainsOfWoe = 0;
            chainsOfWoe_Timer = 2000;
            castSkullCracker = false;
            events.Reset();

            me->GetMotionMaster()->MoveTargetedHome();

            if (chainsOfWoe != 0)
                chainsOfWoe->DespawnOrUnsummon();
            DespawnCreatures(NPC_ANGERED_EARTH);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (instance)
                instance->SetData(DATA_ROMOGG_BONECRUSHER, IN_PROGRESS);

            DoZoneInCombat();

            //me->MonsterYell(YELL_AGGRO, LANGUAGE_UNIVERSAL, 0);
            //DoPlaySoundToSet(me, SOUND_YELL_AGGRO);

            DoCast(me, SPELL_CALL_FOR_HELP, false);
            events.ScheduleEvent(EVENT_QUAKE, urand(40000, 60000), 0, 0);
            events.ScheduleEvent(EVENT_WOUNDING_STRIKE, urand(2000, 4000), 0, 0);
            DoCastAOE(SPELL_CALL_FOR_HELP, true);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (chainsOfWoe != 0)
            {
                if (chainsOfWoe->isAlive())
                { // Buggy
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();

                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            if (!i->getSource()->HasAura(SPELL_CHAINS_OF_WOE_AURA))
                                me->CastSpell(i->getSource(), SPELL_CHAINS_OF_WOE_AURA, true);
                    }
                }
                else
                {
                    chainsOfWoe->DespawnOrUnsummon();
                    chainsOfWoe = 0;
                }

                if (castSkullCracker)
                {
                    me->MonsterYell("Stand still! Rom'ogg crack your skulls!", LANGUAGE_UNIVERSAL, NULL); 

                    castSkullCracker = false;
                    DoCastAOE(SPELL_THE_SKULLCRACKER);
                    return;
                }
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_QUAKE:
                            DoCastAOE(SPELL_QUAKE);
                            if (me->GetMap()->IsHeroic())
                            {
                                // Summon Angered Earth
                                Position myPos;
                                me->GetPosition(&myPos);

                                for (uint8 i = 1; i <= 5; i++)
                                    me->SummonCreature(NPC_ANGERED_EARTH, myPos, TEMPSUMMON_CORPSE_DESPAWN);
                            }
                            events.ScheduleEvent(EVENT_QUAKE, 25000);
                            break;
                        case EVENT_CHAINS_OF_WOE:
                            DoCastAOE(SPELL_CHAINS_OF_WOE);
                            castSkullCracker = true;
                            events.ScheduleEvent(EVENT_CHAINS_OF_WOE, 20000);
                            break;
                        case EVENT_WOUNDING_STRIKE:
                            DoCastVictim(SPELL_WOUNDING_STRIKE);
                            events.ScheduleEvent(EVENT_WOUNDING_STRIKE, 15000);
                            break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        }

        void JustSummoned(Creature* summon)
        {
            summon->setActive(true);

            if(summon->GetEntry() == NPC_CHAINS_OF_WOE)
            {
                summon->CastSpell(summon, SPELL_CHAINS_OF_WOE_VISUAL, true);
                summon->SetReactState(REACT_PASSIVE);
                chainsOfWoe = summon;
            }
            else if (summon->GetEntry() == NPC_ANGERED_EARTH)
            {
                summon->GetMotionMaster()->MoveChase(me->getVictim());
            }
        }

        void JustDied(Unit * /*victim*/)
        {
            DespawnCreatures(NPC_ANGERED_EARTH);
            me->MonsterYell("Boss Cho'gall not gonna be happy 'bout dis!", LANGUAGE_UNIVERSAL, NULL); 

            if (chainsOfWoe != 0)
                chainsOfWoe->DespawnOrUnsummon();

            chainsOfWoe = 0;
        }

    private:
        void DespawnCreatures(uint32 entry)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, entry, 500.0f);

            if (creatures.empty())
                return;

            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->DespawnOrUnsummon();
        }
    };
};

void AddSC_boss_romogg_bonecrusher()
{
    new boss_romogg_bonecrusher();
}
