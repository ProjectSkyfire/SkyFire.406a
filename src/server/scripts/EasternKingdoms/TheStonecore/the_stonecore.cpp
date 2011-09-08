/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
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
#include "the_stonecore.h"

/***************************************TRASH SPELLS*************************************/
// Crystalspawn Giant (42810) Health: 536, 810 - 1, 202, 925
// update creature_template set
enum Spells
{
    SPELL_QUAKE              = 81008,
    H_SPELL_QUAKE            = 92631,

    // IMP (43014) Health: 4, 468 - 7, 749, Mana: 16, 676 - 17, 816
    SPELL_FELL_FIREBALL      = 80344,
    H_SPELL_FELL_FIREBALL    = 92638,

    // Millhouse Manastorm (43391) Health: 386, 505 - 513, 248, Mana: 186, 560 - 197, 380
    SPELL_BLUR               = 81216,
    SPELL_MILL_FEAR          = 81442,
    SPELL_FROSTBOLT_VOLLEY   = 81440,
    H_SPELL_FROSTBOLT_VOLLEY = 92642,
    SPELL_IMPENDING_DOOM     = 86830,
    SPELL_SHADOW_BOLT        = 81439,
    H_SPELL_SHADOW_BOLT      = 92641,
    SPELL_SHADOWFURY         = 81441,
    H_SPELL_SHADOWFURY       = 92644,
    SPELL_TIGULE             = 81220,

    // Rock Borer (43917, 42845) Health: 6, 702 - 11, 624
    SPELL_ROCK_BORE          = 80028,
    H_SPELL_ROCK_BORE        = 92630,

    // Stonecore Berserker (43430) Health: 312, 753 - 387, 450
    SPELL_SCHARGE            = 81574,
    SPELL_SPINNING_SLASH     = 81568,

    // Stonecore Bruiser (42692) Health: 590, 491 - 1, 202, 925
    SPELL_BODY_SLAM          = 80180,
    SPELL_SHOCKWAVE          = 80195,
    H_SPELL_SHOCKWAVE        = 92640,

    // Stonecore Earthshaper (43537) Health: 250, 201 - 309, 960, Mana: 19, 394
    SPELL_DUST_STORM         = 81463,
    SPELL_FORCE_OF_EARTH     = 81459,
    SPELL_GROUND_SHOCK       = 81530,
    H_SPELL_GROUND_SHOCK     = 92628,
    SPELL_LAVA_BURST         = 81576,
    H_SPELL_LAVA_BURST       = 92626,

    // Stonecore Flayer (42808) Health: 312, 753 - 387, 450
    SPELL_FLAY               = 79922,

    // Stonecore Magmalord (42789) Health: 312, 753 - 387, 450, Mana: 25, 014 - 26, 724
    SPELL_IGNITE             = 80151,
    H_SPELL_IGNITE           = 92636,
    SPELL_MAGMA_ERUPTION     = 80038,

    // Stonecore Rift Conjurer (42691) Health: 312, 753 - 387, 450, Mana: 16, 676 - 17, 816
    SPELL_DEMON_PORTAL       = 80308,
    SPELL_SHADOWBOLT         = 80279,
    H_SPELL_SHADOWBOLT       = 92637,

    //Stonecore Sentry (42695) Health: 6, 702 - 11, 624

    // Stonecore Warbringer (42696) Health: 312, 753 - 387, 450
    SPELL_CLEAVE             = 15496,
    SPELL_RAGE               = 80158,
};

enum eEvents
{
    EVENT_NONE,
    EVENT_QUAKE,
    EVENT_FELL_FIREBALL,
    EVENT_BLUR,
    EVENT_MILL_FEAR,
    EVENT_FROSTBOLT_VOLLEY,
    EVENT_IMPENDING_DOOM,
    EVENT_SHADOW_BOLT,
    EVENT_SHADOWFURY,
    EVENT_TIGULE,
    EVENT_ROCK_BORE,
    EVENT_SCHARGE,
    EVENT_SPINNING_SLASH,
    EVENT_BODY_SLAM,
    EVENT_SHOCKWAVE,
    EVENT_DUST_STORM,
    EVENT_FORCE_OF_EARTH,
    EVENT_GROUND_SHOCK,
    EVENT_LAVA_BURST,
    EVENT_FLAY,
    EVENT_IGNITE,
    EVENT_MAGMA_ERUPTION,
    EVENT_DEMON_PORTAL,
    EVENT_SHADOWBOLT,
    EVENT_CLEAVE,
    EVENT_RAGE,
};

// Crystalspawn Giant AI
class mob_crystalspawn_giant : public CreatureScript
{
public:
    mob_crystalspawn_giant() : CreatureScript("mob_crystalspawn_giant") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_crystalspawn_giantAI(pCreature);
    }

    struct mob_crystalspawn_giantAI : public ScriptedAI
    {
        mob_crystalspawn_giantAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_QUAKE, 5000 + rand()%5000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_QUAKE:
                        DoCast(me->getVictim(), SPELL_QUAKE);
                        events.RescheduleEvent(EVENT_QUAKE, 5000 + rand()%5000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

// Imp AI
class mob_impp : public CreatureScript
{
public:
    mob_impp() : CreatureScript("mob_impp") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_imppAI(pCreature);
    }

    struct mob_imppAI : public ScriptedAI
    {
        mob_imppAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_FELL_FIREBALL, 1000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_FELL_FIREBALL:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_FELL_FIREBALL);
                        events.RescheduleEvent(EVENT_FELL_FIREBALL, 1000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

// Rock Borer AI
class mob_rock_borer : public CreatureScript
{
public:
    mob_rock_borer() : CreatureScript("mob_rock_borer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_rock_borerAI(pCreature);
    }

    struct mob_rock_borerAI : public ScriptedAI
    {
        mob_rock_borerAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ROCK_BORE, 1000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_ROCK_BORE:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_ROCK_BORE);
                        events.RescheduleEvent(EVENT_ROCK_BORE, 1000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

// Millhouse Manastorm AI
class mob_millhouse_manastorm : public CreatureScript
{
public:
    mob_millhouse_manastorm() : CreatureScript("mob_millhouse_manastorm") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_millhouse_manastormAI(pCreature);
    }

    struct mob_millhouse_manastormAI : public ScriptedAI
    {
        mob_millhouse_manastormAI(Creature *c) : ScriptedAI(c)
        {
        }

        EventMap events;

        void Reset()
        {
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_MILL_FEAR, 10000);
            events.ScheduleEvent(EVENT_FROSTBOLT_VOLLEY, 7000 + rand()%10000);
            events.ScheduleEvent(EVENT_IMPENDING_DOOM, 10000 + rand()%10000);
            events.ScheduleEvent(EVENT_SHADOW_BOLT, 1000);
            events.ScheduleEvent(EVENT_SHADOWFURY, 5000 + rand()%15000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_MILL_FEAR:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_MILL_FEAR);
                        events.RescheduleEvent(EVENT_MILL_FEAR, 10000);
                        return;
                    case EVENT_SHADOW_BOLT:
                        DoCast(me->getVictim(), SPELL_SHADOW_BOLT);
                        events.RescheduleEvent(EVENT_SHADOWBOLT, 1000);
                        return;
                    case EVENT_FROSTBOLT_VOLLEY:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_FROSTBOLT_VOLLEY);
                        events.RescheduleEvent(EVENT_FROSTBOLT_VOLLEY, rand()%15000);
                        return;
                    case EVENT_IMPENDING_DOOM:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_IMPENDING_DOOM);
                        events.RescheduleEvent(EVENT_IMPENDING_DOOM, rand()%15000);
                        return;
                    case EVENT_SHADOWFURY:
                        if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                            DoCast(pTarget, SPELL_SHADOWFURY);
                        events.RescheduleEvent(SPELL_SHADOWFURY, 5000 + rand()%15000);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_the_stonecore()
{
    new mob_crystalspawn_giant();
    new mob_impp();
    new mob_millhouse_manastorm();
    new mob_rock_borer;
}