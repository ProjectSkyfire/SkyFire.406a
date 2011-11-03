/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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
#include "ruby_sanctum.h"

enum BossSpells
{
    SPELL_ENRAGE = 78722, //soft enrage + fire nova
    SPELL_FLAME_BREATH = 74404,
    SPELL_BEACON = 74453, //mark for conflag, in enter to fly phase, 2 in 10, 5 in 25
    SPELL_CONFLAGATION = 74452, // after fly up
    SPELL_CONFLAGATION_1 = 74454, // Triggered?
    SPELL_CONFLAGATION_2 = 74456, // Aura
};

struct Locations
{
    float x, y, z;
};

static Locations SpawnLoc[]=
{
    {3151.3898f, 636.8519f, 78.7396f}, // 0 Saviana start point
    {3149.635f, 668.9644f, 90.507f}, // 1 Saviana fly phase, o=4,69
};

#define TARGETS_10 2
#define TARGETS_25 5

class boss_ragefire : public CreatureScript
{
public:
    boss_ragefire() : CreatureScript("boss_ragefire") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_ragefireAI(creature);
    }

    struct boss_ragefireAI : public ScriptedAI
    {
        boss_ragefireAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint8 nextPoint;
        uint8 stage;
        uint32 FlameBreathTimer;
        uint32 Enrage;
        uint32 BeakonTimer;
        uint32 ConflagrateTimer;

        bool MovementStarted;
        bool conflagated;

        void Reset()
        {
            if(!instance)
                return;
            me->SetRespawnDelay(7*DAY);
            if (me->isAlive()) instance->SetData(TYPE_RAGEFIRE, NOT_STARTED);

            FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
            Enrage = urand(20*IN_MILLISECONDS,40*IN_MILLISECONDS);
            BeakonTimer = urand(12*IN_MILLISECONDS,22*IN_MILLISECONDS);
            ConflagrateTimer = 5*IN_MILLISECONDS;

            setStage(0);
            nextPoint = 0;
            conflagated = false;

            playerList.clear();
        }

        void setStage(uint8 phase)
        {
            stage = phase;
        }

        uint8 getStage()
        {
            return stage;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!instance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == nextPoint) {
                    me->GetMotionMaster()->MovementExpired();
                    MovementStarted = false;
                    }
        }

        void SetFly(bool command = false)
        {
            if (command)
            {
                me->HandleEmoteCommand(EMOTE_ONESHOT_FLY_SIT_GROUND_UP);
                me->SetFlying(true);
            }
            else
            {
                me->SetFlying(false);
            }
        }

        void StartMovement(uint32 id)
        {
            nextPoint = id;
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
            MovementStarted = true;
        }

        void KilledUnit(Unit* victim)
        {
            switch (urand(0,1)) {
                case 0:
                       DoScriptText(-1666401,me,victim);
                       break;
                case 1:
                       DoScriptText(-1666402,me,victim);
                       break;
                }
        }

        void JustReachedHome()
        {
            if (instance)
                instance->SetData(TYPE_RAGEFIRE, FAIL);
        }

        void EnterCombat(Unit *who)
        {
            if(!instance) return;

            instance->SetData(TYPE_RAGEFIRE, IN_PROGRESS);
            me->SetInCombatWithZone();
            DoScriptText(-1666400,me);
        }

        void JustDied(Unit *killer)
        {
            if(!instance) return;

            instance->SetData(TYPE_RAGEFIRE, DONE);
            DoScriptText(-1666403,me);
        }

        void doBeacon(bool command = false)
        {
            if (command)
            {
                 SelectTargetList(playerList, RAID_MODE(TARGETS_10,TARGETS_25,TARGETS_10,TARGETS_25), SELECT_TARGET_RANDOM, 0, true);
                 for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                 {
                     Unit *pTemp = (*itr);
                     me->CastSpell(pTemp, SPELL_BEACON, true);
                 }

                 conflagated = true;
            }
            else
            {
                 me->InterruptNonMeleeSpells(true);

                 for (std::list<Unit*>::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                 {
                     Unit *pTemp = (*itr);
                     me->CastSpell(pTemp, SPELL_CONFLAGATION_2, true);
                 }

                 playerList.clear();
                 conflagated = false;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            switch (getStage())
            {
                case 0: //GROUND
                     if (FlameBreathTimer <= diff)
                     {
                         DoCast(SPELL_FLAME_BREATH);
                         FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
                     } else FlameBreathTimer -= diff;

                     if (Enrage <= diff)
                     {
                         DoCast(SPELL_ENRAGE);
                         Enrage = urand(20*IN_MILLISECONDS,40*IN_MILLISECONDS);
                         DoScriptText(-1666405,me);
                     } else Enrage -= diff;

                     if ( HealthBelowPct(81) ) setStage(1);
                     break;

                case 1: //Air phase start
                     SetCombatMovement(false);
                     me->InterruptNonMeleeSpells(true);
                     SetFly(true);
                     doBeacon(true);
                     StartMovement(1);
                     setStage(2);
                     break;

                case 2: // Wait for movement
                     if (MovementStarted) return;
                     DoCast(SPELL_CONFLAGATION);
                     DoScriptText(-1666404,me);
                     setStage(3);
                     break;

                case 3: // Wait for cast finish
                     if (!me->IsNonMeleeSpellCasted(false))
                     {
                         doBeacon(false);
                         setStage(4);
                     }
                     break;

                case 4: // Air phase
                     if (FlameBreathTimer <= diff)
                     {
                         DoCast(SPELL_FLAME_BREATH);
                         FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
                     } else FlameBreathTimer -= diff;

                     if (BeakonTimer <= diff)
                     {
                         doBeacon(true);
                         DoCast(SPELL_CONFLAGATION);
                         BeakonTimer = urand(12*IN_MILLISECONDS,22*IN_MILLISECONDS);
                     } else BeakonTimer -= diff;

                     if (ConflagrateTimer <= diff)
                     {
                         if (conflagated)
                         {
                             //DoCast(SPELL_CONFLAGATION_1);
                             doBeacon(false);
                         }
                         ConflagrateTimer = 5*IN_MILLISECONDS;
                     } else ConflagrateTimer -= diff;

                     if ( HealthBelowPct(61) ) setStage(5);
                     break;

                case 5: //Air phase end
                     StartMovement(0);
                     setStage(6);
                     break;

                case 6: // Wait for movement
                     if (MovementStarted) return;
                     SetFly(false);
                     SetCombatMovement(true);
                     me->GetMotionMaster()->Clear();
                     me->GetMotionMaster()->MoveChase(me->getVictim());
                     setStage(7);
                     break;

                case 7: //GROUND
                     if (FlameBreathTimer <= diff)
                     {
                         DoCast(SPELL_FLAME_BREATH);
                         FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
                     } else FlameBreathTimer -= diff;

                     if (Enrage <= diff)
                     {
                         DoCast(SPELL_ENRAGE);
                         Enrage = urand(20*IN_MILLISECONDS,40*IN_MILLISECONDS);
                         DoScriptText(-1666405,me);
                     } else Enrage -= diff;

                     if ( HealthBelowPct(41) ) setStage(8);
                     break;

                case 8: //Air phase start
                     SetCombatMovement(false);
                     me->InterruptNonMeleeSpells(true);
                     SetFly(true);
                     doBeacon(true);
                     StartMovement(1);
                     setStage(9);
                     break;

                case 9: // Wait for movement
                     if (MovementStarted) return;
                     DoCast(SPELL_CONFLAGATION);
                     DoScriptText(-1666404,me);
                     setStage(10);
                     break;

                case 10: // Wait for cast finish
                     if (!me->IsNonMeleeSpellCasted(false))
                     {
                         doBeacon(false);
                         setStage(11);
                     };
                     break;

                case 11: // Air phase
                     if (FlameBreathTimer <= diff)
                     {
                         DoCast(SPELL_FLAME_BREATH);
                         FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
                     } else FlameBreathTimer -= diff;

                     if (BeakonTimer <= diff)
                     {
                         doBeacon(true);
                         DoCast(SPELL_CONFLAGATION);
                         BeakonTimer = urand(12*IN_MILLISECONDS,22*IN_MILLISECONDS);
                     } else BeakonTimer -= diff;

                     if (ConflagrateTimer <= diff)
                     {
                         if (conflagated)
                         {
                              //DoCast(SPELL_CONFLAGATION_1);
                              doBeacon(false);
                         }
                         ConflagrateTimer = 5*IN_MILLISECONDS;
                     } else ConflagrateTimer -= diff;

                     if ( HealthBelowPct(21) ) setStage(12);
                     break;

                case 12: //Air phase end
                     StartMovement(0);
                     setStage(13);
                     break;

                case 13: // Wait for movement
                     if (MovementStarted) return;
                     SetFly(false);
                     SetCombatMovement(true);
                     me->GetMotionMaster()->Clear();
                     me->GetMotionMaster()->MoveChase(me->getVictim());
                     setStage(14);
                     break;

                case 14: //GROUND
                     if (FlameBreathTimer <= diff)
                     {
                         DoCast(SPELL_FLAME_BREATH);
                         FlameBreathTimer = urand(5*IN_MILLISECONDS,15*IN_MILLISECONDS);
                     } else FlameBreathTimer -= diff;

                     if (Enrage <= diff)
                     {
                         DoCast(SPELL_ENRAGE);
                         Enrage = urand(15*IN_MILLISECONDS,30*IN_MILLISECONDS);
                         DoScriptText(-1666405,me);
                     } else Enrage -= diff;
                     break;

                default:
                    break;
            }

            DoMeleeAttackIfReady();
        }

        private:
            std::list<Unit *> playerList;
    };
};

void AddSC_boss_ragefire()
{
    new boss_ragefire();
}