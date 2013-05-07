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

#include "ScriptPCH.h"
#include "vortex_pinnacle.h"

enum Texts
{
    SAY_AGGRO           = 0,
    SAY_SLAY            = 1,
    SAY_DEATH           = 2,
    SAY_ANNOUNCE        = 3,
};

enum Spells
{
    //Ertan
    SPELL_SUMMON_TEMPEST      = 86340,
    SPELL_LIGHTING_BOLT       = 86331,
    SPELL_LIGHTING_BOLT_H     = 93990,

    //Ertans Vortex
	SPELL_STORMS_EDGE         = 93992,
	SPELL_CYCLONE_SHIELD      = 86267,
};

enum Events
{
    EVENT_LIGHTNING_BOLT    = 9,
    EVENT_SUMMON_TEMPEST    = 10,
    EVENT_SUMMON_STORM      = 11,
    EVENT_STOP              = 12,
    EVENT_PULL              = 13,
    EVENT_MOVE_OUT          = 14,
    EVENT_PULL_ANNOUNCE     = 15,

    //Tornado system
    EVENT_1     = 1,
    EVENT_2     = 2,
    EVENT_3     = 3,
    EVENT_4     = 4,
    EVENT_5     = 5,
    EVENT_6     = 6,
    EVENT_7     = 7,
    EVENT_8     = 8,
};

Position const Point8   = {-695.130f, 4.116f, 635.672f, 3.173f};
Position const Point7   = {-702.408f, 21.482f, 635.674f, 3.923f};
Position const Point6   = {-719.958f, 28.493f, 635.672f, 4.689f};
Position const Point5   = {-737.178f, 21.330f, 635.672f, 5.561f};
Position const Point4   = {-744.433f, 4.024f, 635.672f, 6.260f};
Position const Point3   = {-736.997f, -13.297f, 635.672f, 0.715f};
Position const Point2   = {-719.625f, -20.499f, 635.672f, 1.427f};
Position const Point1   = {-702.228f, -13.440f, 635.672f, 2.338f};

enum Vortexpoints
{
    POINT_1     = 1,
    POINT_2     = 2,
    POINT_3     = 3,
    POINT_4     = 4,
    POINT_5     = 5,
    POINT_6     = 6,
    POINT_7     = 7,
    POINT_8     = 8,
};

/*#####
# boss_grand_vizier_erthan
#####*/

class boss_grand_vizier_ertan : public CreatureScript
{
public:
    boss_grand_vizier_ertan() : CreatureScript("boss_grand_vizier_ertan") {}

    struct boss_grand_vizier_ertanAI : public Scripted_NoMovementAI
    {
        boss_grand_vizier_ertanAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* instance;
        EventMap events;
        uint32 Lightningtimer;

        void Reset()
        {
            events.Reset();
            instance->SetBossState(DATA_GRAND_VIZIER_ERTAN, NOT_STARTED);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
            Lightningtimer = 3000;
            me->SetReactState(REACT_PASSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_AGGRO);
            instance->SetBossState(DATA_GRAND_VIZIER_ERTAN, IN_PROGRESS);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_ADD, me);
            events.ScheduleEvent(EVENT_LIGHTNING_BOLT, 3000);
            events.ScheduleEvent(EVENT_SUMMON_STORM, 100);
            DoCast(me->getVictim(), SPELL_LIGHTING_BOLT);
            events.ScheduleEvent(EVENT_PULL_ANNOUNCE, 25000);
            me->SetReactState(REACT_AGGRESSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void KilledUnit(Unit* /*victim*/) 
        {
            Talk(SAY_SLAY);
        }

        void JustDied(Unit* /*Killer*/)
        {
            Talk(SAY_DEATH);
            instance->SetBossState(DATA_GRAND_VIZIER_ERTAN, DONE);
            instance->SendEncounterUnit(ENCOUNTER_FRAME_REMOVE, me);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (Lightningtimer <= diff)
            {
                DoCast(me->getVictim(), SPELL_LIGHTING_BOLT);
                Lightningtimer = 2000;
            }
            else
                Lightningtimer -= diff;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_LIGHTNING_BOLT:
                        break;
                    case EVENT_SUMMON_STORM:
                        {
                            Creature *t1 = me->SummonCreature(46007, Point1, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t2 = me->SummonCreature(46007, Point2, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t3 = me->SummonCreature(46007, Point3, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t4 = me->SummonCreature(46007, Point4, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t5 = me->SummonCreature(46007, Point5, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t6 = me->SummonCreature(46007, Point6, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t7 = me->SummonCreature(46007, Point7, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            Creature *t8 = me->SummonCreature(46007, Point8, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                            t1->GetMotionMaster()->MovePoint(POINT_1, Point2);
                            t2->GetMotionMaster()->MovePoint(POINT_2, Point3);
                            t3->GetMotionMaster()->MovePoint(POINT_3, Point4);
                            t4->GetMotionMaster()->MovePoint(POINT_4, Point5);
                            t5->GetMotionMaster()->MovePoint(POINT_5, Point6);
                            t6->GetMotionMaster()->MovePoint(POINT_6, Point7);
                            t7->GetMotionMaster()->MovePoint(POINT_7, Point8);
                            t8->GetMotionMaster()->MovePoint(POINT_8, Point1);
                        }
                        break;
                    case EVENT_PULL_ANNOUNCE:
                        Talk(SAY_ANNOUNCE);
                        events.ScheduleEvent(EVENT_PULL_ANNOUNCE, 33000);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new boss_grand_vizier_ertanAI (Creature);
    }
};

/*#####
# mob_cyclone_shield
#####*/
Position const Center = {-719.435f, 3.839f, 635.671f};

class mob_cyclone_shield : public CreatureScript
{
public:
    mob_cyclone_shield() : CreatureScript("npc_cyclone_shield"){}

    struct mob_cyclone_shieldAI  : public ScriptedAI
    {
        mob_cyclone_shieldAI (Creature* creature) : ScriptedAI(creature)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
            me->SetReactState(REACT_PASSIVE);
            instance = me->GetInstanceScript();
            summoned = 0;
            Shieldtimer = urand(800, 1000);
        }

        InstanceScript* instance;
        EventMap events;
        uint8 summoned;
        uint32 Shieldtimer;
        uint8 counter;

        void IsSummonedBy(Unit* /*summoner*/)
        {
            if (summoned == 0)
            {
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
                DoCastAOE(SPELL_CYCLONE_SHIELD);
                me->SetDisplayId(me->GetCreatureTemplate()->Modelid2);
                float posX = me->GetPositionX();
                float posY = me->GetPositionY();
                float posZ = me->GetPositionZ();
                Position const Home = {posX, posY, posZ};
                me->SetHomePosition(Home);
                Shieldtimer = urand(800, 1000);
                events.ScheduleEvent(EVENT_PULL, 25000);
                summoned = 1;
                me->setFaction(16);
                me->SetWalk(true);
                me->setActive(true);
            }
        }

        void MovementInform(uint32 type, uint32 pointId)
        {
            switch (pointId)
            {
                case POINT_1:
                    events.ScheduleEvent(EVENT_1, 1);
                    counter = 1;
                    break;
                case POINT_2:
                    events.ScheduleEvent(EVENT_2, 1);
                    counter = 2;
                    break;
                case POINT_3:
                    events.ScheduleEvent(EVENT_3, 1);
                    counter = 3;
                    break;
                case POINT_4:
                    events.ScheduleEvent(EVENT_4, 1);
                    counter = 4;
                    break;
                case POINT_5:
                    events.ScheduleEvent(EVENT_5, 1);
                    counter = 5;
                    break;
                case POINT_6:
                    events.ScheduleEvent(EVENT_6, 1);
                    counter = 6;
                    break;
                case POINT_7:
                    events.ScheduleEvent(EVENT_7, 1);
                    counter = 7;
                    break;
                case POINT_8:
                    events.ScheduleEvent(EVENT_8, 1);
                    counter = 8;
                    break;
                }
            }

        void UpdateAI(const uint32 diff)
        {
            if (instance->GetBossState(DATA_GRAND_VIZIER_ERTAN) == NOT_STARTED)
                me->DespawnOrUnsummon(1);

             if (instance->GetBossState(DATA_GRAND_VIZIER_ERTAN) == DONE)
                me->DespawnOrUnsummon(1);

            if (Shieldtimer <= diff)
            {
                if (Unit* target = me->SelectNearestTarget(6.0f))
                    DoCast(target, SPELL_STORMS_EDGE);
                me->getHostileRefManager().deleteReferences();
                me->CombatStop();
                me->DeleteThreatList();
                Shieldtimer = urand(1000, 1200);
            }
            else
                Shieldtimer -= diff;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_PULL:
                        me->GetMotionMaster()->MovePoint(0, Center);
                        events.ScheduleEvent(EVENT_STOP, 4000);
                        events.ScheduleEvent(EVENT_MOVE_OUT, 8000);
                        Shieldtimer = 5000;
                        break;
                    case EVENT_MOVE_OUT:
                        if (counter == 1)
                            events.ScheduleEvent(EVENT_2, 1);
                        else
                            if (counter == 2)
                                events.ScheduleEvent(EVENT_3, 1);
                            else
                                if (counter == 3)
                                    events.ScheduleEvent(EVENT_4, 1);
                                else
                                    if (counter == 4)
                                        events.ScheduleEvent(EVENT_5, 1);
                                    else
                                        if (counter == 5)
                                            events.ScheduleEvent(EVENT_6, 1);
                                        else
                                            if (counter == 6)
                                                events.ScheduleEvent(EVENT_7, 1);
                                            else
                                                if (counter == 7)
                                                    events.ScheduleEvent(EVENT_8, 1);
                                                else
                                                    if (counter == 8)
                                                        events.ScheduleEvent(EVENT_1, 1);

                        events.ScheduleEvent(EVENT_PULL, 25000);
                        Shieldtimer = 5000;
                        break;
                    case EVENT_STOP:
                        me->StopMoving();
                        break;
                    case EVENT_1:
                        me->GetMotionMaster()->MovePoint(POINT_2, Point3);
                        break;
                    case EVENT_2:
                        me->GetMotionMaster()->MovePoint(POINT_3, Point4);
                        break;
                    case EVENT_3:
                        me->GetMotionMaster()->MovePoint(POINT_4, Point5);
                        break;
                    case EVENT_4:
                        me->GetMotionMaster()->MovePoint(POINT_5, Point6);
                        break;
                    case EVENT_5:
                        me->GetMotionMaster()->MovePoint(POINT_6, Point7);
                        break;
                    case EVENT_6:
                        me->GetMotionMaster()->MovePoint(POINT_7, Point8);
                        break;
                    case EVENT_7:
                        me->GetMotionMaster()->MovePoint(POINT_8, Point1);
                        break;
                    case EVENT_8:
                        me->GetMotionMaster()->MovePoint(POINT_1, Point2);
                        break;
                    default:
                        break;
                }
            }
        }
    };
    CreatureAI* GetAI(Creature* Creature) const
    {
        return new mob_cyclone_shieldAI (Creature);
    }
};

void AddSC_boss_grand_vizier_ertan()
{
    new boss_grand_vizier_ertan();
    new mob_cyclone_shield();
}
