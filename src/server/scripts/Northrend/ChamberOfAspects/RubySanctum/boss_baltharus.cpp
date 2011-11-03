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

struct Locations
{
    float x, y, z;
};

static Locations SpawnLoc[]=
{
    {3152.329834f, 359.41757f, 85.301605f}, // Baltharus target point
    {3153.06f, 389.486f, 86.2596f}, // Baltharus initial point
};

enum Equipment
{
    EQUIP_MAIN = 49888,
    EQUIP_OFFHAND = EQUIP_NO_CHANGE,
    EQUIP_RANGED = EQUIP_NO_CHANGE,
    EQUIP_DONE = EQUIP_NO_CHANGE,
};

enum BossSpells
{
    SPELL_BLADE_TEMPEST = 75125, // every 22 secs
    SPELL_ENERVATING_BRAND = 74502, // friendlys in 12yards = 74505
    SPELL_REPELLING_WAVE = 74509, // once if call clone
    SPELL_SABER_LASH = 40504, // every 10-15 secs
    SPELL_SUMMON_CLONE = 74511, // summons npc 39899 (Clone)
    SPELL_CHANNEL_SPELL = 76221, // Channeling dummy spell
};

/*######
## boss_baltharus
######*/

class boss_baltharus : public CreatureScript
{
public:
    boss_baltharus() : CreatureScript("boss_baltharus") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_baltharusAI(creature);
    }

    struct boss_baltharusAI : public ScriptedAI
    {
        boss_baltharusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        Creature* dummyTarget;
        Creature* clone;
        bool inCombat;
        bool intro;
        uint8 Stage;

        uint32 ChannelTimer;
        uint32 EnevatingTimer;
        uint32 SaberLashTimer;

        void Reset()
        {
            if(!instance)
                return;

            if (me->isAlive()) instance->SetData(TYPE_BALTHARUS, NOT_STARTED);
            me->SetRespawnDelay(7*DAY);

            Stage = 0;
            clone = NULL;
            inCombat = false;
            intro = false;

            ChannelTimer = 1*IN_MILLISECONDS;
            EnevatingTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            SaberLashTimer = urand(10*IN_MILLISECONDS,15*IN_MILLISECONDS);

            if (dummyTarget = me->GetMap()->GetCreature( instance->GetData64(NPC_BALTHARUS_TARGET)))
            {
                if (!dummyTarget->isAlive()) dummyTarget->Respawn();

                dummyTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                dummyTarget->GetMotionMaster()->MoveIdle();
            }
            else if (dummyTarget = me->SummonCreature(NPC_BALTHARUS_TARGET, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 1000))
            {
                dummyTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                dummyTarget->GetMotionMaster()->MoveIdle();
            }

            if(Creature* target = me->GetMap()->GetCreature( instance->GetData64(NPC_XERESTRASZA)))
                me->SetUInt64Value(UNIT_FIELD_TARGET, target->GetGUID());
        }

        void JustReachedHome()
        {
            if (!instance) return;

            instance->SetData(TYPE_BALTHARUS, FAIL);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if(!instance || intro ||
                who->GetTypeId() != TYPEID_PLAYER ||
                !who->IsWithinDistInMap(me, 60.0f)) return;

            instance->SetData(TYPE_EVENT, 10);
            DoScriptText(-1666305,me);
            intro = true;
        }

        void JustDied(Unit* killer)
        {
            if (!instance) return;

          // if (dummyTarget && dummyTarget->isSummon())
          // dummyTarget->ForcedDespawn();

            DoScriptText(-1666303,me);
            instance->SetData(TYPE_BALTHARUS, DONE);
        }

        void KilledUnit(Unit* victim)
        {
        switch (urand(0,1)) {
            case 0:
                   DoScriptText(-1666301,me,victim);
                   break;
            case 1:
                   DoScriptText(-1666302,me,victim);
                   break;
            }
        }

        void JustSummoned(Creature* summoned)
        {
            if(!instance || !summoned) return;

            if ( summoned->GetEntry() != NPC_BALTHARUS_TARGET )
            {
                 if (!clone) clone = summoned;
                 else if (!clone->isAlive()) clone = summoned;
                 clone->SetInCombatWithZone();
            }
        }

        void SummonedCreatureJustDied(Creature* summoned)
        {
             if (!instance || !summoned) return;

             if (summoned == clone) clone = NULL;
        }

        void EnterCombat(Unit* who)
        {
            if (!instance) return;
            if (who->GetTypeId() != TYPEID_PLAYER) return;

            if (dummyTarget) dummyTarget->ForcedDespawn();

            SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

            inCombat = true;
            me->InterruptNonMeleeSpells(true);
            SetCombatMovement(true);
            instance->SetData(TYPE_BALTHARUS, IN_PROGRESS);
            DoScriptText(-1666300,me);
        }

        void DamageTaken(Unit* doneBy, uint32 &Damage)
        {
            if (!instance) return;

            if (!me || !me->isAlive())
                return;

            if(doneBy->GetGUID() == me->GetGUID())
              return;

            if (clone && clone->isAlive())
            {
                doneBy->DealDamage(clone, Damage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                Damage = 0;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance) return;

            if (!inCombat && !me->IsNonMeleeSpellCasted(false))
            {
                if (ChannelTimer <= diff)
                {
                    DoCast(dummyTarget, SPELL_CHANNEL_SPELL);
                    ChannelTimer = 1*IN_MILLISECONDS;
                } else ChannelTimer -= diff;
            }

            if (!UpdateVictim())
                return;

            switch (Stage)
            {
                case 0:
                     if ( HealthBelowPct(67)) Stage = 1;
                     break;

                case 1:
                     me->InterruptNonMeleeSpells(true);
                     if (Is25ManRaid())
                         DoCast(SPELL_SUMMON_CLONE);
                     Stage = 2;
                     break;

                case 2:
                     if (me->IsNonMeleeSpellCasted(false)) return;
                     DoCast(SPELL_REPELLING_WAVE);
                     Stage = 3;

                case 3:
                     if ( HealthBelowPct(51)) Stage = 4;
                     break;

                case 4:
                     me->InterruptNonMeleeSpells(true);
                     if (!Is25ManRaid())
                            DoCast(SPELL_SUMMON_CLONE);
                     Stage = 5;
                     break;

                case 5:
                     if (me->IsNonMeleeSpellCasted(false)) return;
                     DoCast(SPELL_REPELLING_WAVE);
                     Stage = 6;

                case 6:
                     if ( HealthBelowPct(34)) Stage = 7;
                     break;

                case 7:
                     me->InterruptNonMeleeSpells(true);
                     if (Is25ManRaid())
                         DoCast(SPELL_SUMMON_CLONE);
                     Stage = 8;
                     break;

                case 8:
                     if (me->IsNonMeleeSpellCasted(false)) return;
                     DoCast(SPELL_REPELLING_WAVE);
                     Stage = 9;

                case 9:
                default:
                     break;
            }

            if (EnevatingTimer <= diff)
            {
                DoCast(SPELL_ENERVATING_BRAND);
                EnevatingTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            } else EnevatingTimer -= diff;

            if (SaberLashTimer <= diff)
            {
                DoCast(SPELL_SABER_LASH);
                SaberLashTimer = urand(10*IN_MILLISECONDS,15*IN_MILLISECONDS);
            } else SaberLashTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## mob_baltharus_clone
######*/

class mob_baltharus_clone : public CreatureScript
{
public:
    mob_baltharus_clone() : CreatureScript("mob_baltharus_clone") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_baltharus_cloneAI(creature);
    }

    struct mob_baltharus_cloneAI : public ScriptedAI
    {
        mob_baltharus_cloneAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint32 BladeTempestTimer;
        uint32 EnevatingTimer;
        uint32 SaberLashTimer;

        void Reset()
        {
            if(!instance) return;

            BladeTempestTimer = 22*IN_MILLISECONDS;
            EnevatingTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            SaberLashTimer = urand(10*IN_MILLISECONDS,15*IN_MILLISECONDS);

            me->SetRespawnDelay(7*DAY);
        }

        void KilledUnit(Unit* victim)
        {
        switch (urand(0,1)) {
            case 0:
                   DoScriptText(-1666301,me,victim);
                   break;
            case 1:
                   DoScriptText(-1666302,me,victim);
                   break;
            }
        }

        void JustDied(Unit* killer)
        {
            if (!instance) return;
        }

        void EnterCombat(Unit* who)
        {
            if (!instance) return;

            SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

            me->SetInCombatWithZone();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance) return;

            if (instance->GetData(TYPE_BALTHARUS) != IN_PROGRESS)
                me->ForcedDespawn();

            if (!UpdateVictim())
                return;

            if (BladeTempestTimer <= diff)
            {
                DoCast(me,SPELL_BLADE_TEMPEST);
                BladeTempestTimer = 22*IN_MILLISECONDS;
            } else BladeTempestTimer -= diff;

            if (EnevatingTimer <= diff)
            {
                DoCast(SPELL_ENERVATING_BRAND);
                EnevatingTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            } else EnevatingTimer -= diff;

            if (SaberLashTimer <= diff)
            {
                DoCast(SPELL_SABER_LASH);
                SaberLashTimer = urand(10*IN_MILLISECONDS,15*IN_MILLISECONDS);
            } else SaberLashTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## mob_xerestrasza
######*/

static Locations SpawnLocXer[]=
{
    {3155.540039f, 342.391998f, 84.596802f}, // 0 - start point
    {3152.329834f, 359.41757f, 85.301605f}, // 1 - second say
    {3152.078369f, 383.939178f, 86.337875f}, // 2 - other says and staying
    {3154.99f, 535.637f, 72.8887f}, // 3 - Halion spawn point
};

class mob_xerestrasza : public CreatureScript
{
public:
    mob_xerestrasza() : CreatureScript("mob_xerestrasza") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_xerestraszaAI(creature);
    }

    struct mob_xerestraszaAI : public ScriptedAI
    {
        mob_xerestraszaAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        uint32 nextEvent;
        uint32 nextPoint;
        uint32 UpdateTimer;
        bool movementstarted;
        bool onSessionEvent;

        void Reset()
        {
            if(!instance) return;
            nextEvent = 0;
            nextPoint = 0;
            movementstarted = false;
            UpdateTimer = 2000;
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            instance->SetData(TYPE_XERESTRASZA, NOT_STARTED);
            me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->SetSpeed(MOVE_WALK, 0.8f, true);
            me->SetRespawnDelay(7*DAY);
       }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || !movementstarted) return;
            if (id == nextPoint)
            {
                movementstarted = false;
                instance->SetData(TYPE_EVENT,nextEvent);
                me->GetMotionMaster()->MovementExpired();
            }
        }

        void StartMovement(uint32 id, uint32 _nextEvent)
        {
            nextPoint = id;
            nextEvent = _nextEvent;
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(id, SpawnLocXer[id].x, SpawnLocXer[id].y, SpawnLocXer[id].z);
            instance->SetData(TYPE_EVENT,0);
            movementstarted = true;
        }

        void AttackStart(Unit *who)
        {
            //ignore all attackstart commands
            return;
        }

        void MoveInLineOfSight(Unit *who)
        {
            if(!instance || !who || who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (instance->GetData(TYPE_BALTHARUS) != DONE
                || instance->GetData(TYPE_XERESTRASZA) != NOT_STARTED) return;

            if(!who->IsWithinDistInMap(me, 60.0f)) return;

            instance->SetData(TYPE_XERESTRASZA, IN_PROGRESS);
            instance->SetData(TYPE_EVENT, 30);
            onSessionEvent = true;
        }

        void UpdateAI(const uint32 diff)
        {
            if(!instance) return;

            if (instance->GetData(TYPE_EVENT_NPC) == NPC_XERESTRASZA)
            {
                UpdateTimer = instance->GetData(TYPE_EVENT_TIMER);
                if (UpdateTimer <= diff)
                {
                    switch (instance->GetData(TYPE_EVENT))
                    {
// Xerestrasza intro
                        case 10:
                              UpdateTimer = 7000;
                              instance->SetData(TYPE_EVENT, 20);
                              break;
                        case 20:
                              DoScriptText(-1666000,me);
                              instance->SetData(TYPE_EVENT,0);
                              break;
// Xerestrasza event
                        case 30:
                             // me->SetActive(true);
                              DoScriptText(-1666001,me);
                              StartMovement(1,40);
                              break;
                        case 40:
                              DoScriptText(-1666002,me);
                              StartMovement(2,50);
                              break;
                        case 50:
                              DoScriptText(-1666003,me);
                              UpdateTimer = 12000;
                              instance->SetData(TYPE_EVENT,60);
                              break;
                        case 60:
                              DoScriptText(-1666004,me);
                              UpdateTimer = 12000;
                              instance->SetData(TYPE_EVENT,70);
                              break;
                        case 70:
                              DoScriptText(-1666005,me);
                              UpdateTimer = 10000;
                              instance->SetData(TYPE_EVENT,80);
                              break;
                        case 80:
                              DoScriptText(-1666006,me);
                              UpdateTimer = 10000;
                              instance->SetData(TYPE_EVENT,90);
                              break;
                        case 90:
                              DoScriptText(-1666007,me);
                              UpdateTimer = 10000;
                              instance->SetData(TYPE_EVENT,100);
                              break;
                        case 100:
                              DoScriptText(-1666008,me);
                              UpdateTimer = 4000;
                              instance->SetData(TYPE_EVENT,110);
                              break;
                        case 110:
                              UpdateTimer = 2000;
                              instance->SetData(TYPE_EVENT,0);
                              instance->SetData(TYPE_XERESTRASZA, DONE);
                              me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                              me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                             // me->SetActive(false);
                              break;
// Halion spawn
                        case 200:
                              //me->SetActive(true);
                              {
                              Creature* halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_REAL));
                              if (instance->GetData(TYPE_BALTHARUS) == DONE &&
                                  instance->GetData(TYPE_RAGEFIRE) == DONE &&
                                  instance->GetData(TYPE_XERESTRASZA) == DONE &&
                                  instance->GetData(TYPE_ZARITHRIAN) == DONE &&
                                  instance->GetData(TYPE_HALION) != DONE)
                                  {
                                  if (!halion)
                                      halion = me->SummonCreature(NPC_HALION_REAL, SpawnLocXer[3].x, SpawnLocXer[3].y, SpawnLocXer[3].z, 6.23f, TEMPSUMMON_MANUAL_DESPAWN, HOUR*IN_MILLISECONDS);
                                  if (halion && !halion->isAlive())
                                      halion->Respawn();
                                  if (halion)
                                      halion->SetCreatorGUID(0);
                                  }
                              }
                              UpdateTimer = 4000;
                              instance->SetData(TYPE_EVENT,210);
                              break;
                        case 210:
                              //me->SetActive(false);
                              UpdateTimer = 2000;
                              instance->SetData(TYPE_EVENT,0);
                              break;

                        default:
                          break;
                    }
                 } else UpdateTimer -= diff;
                 instance->SetData(TYPE_EVENT_TIMER, UpdateTimer);
            }
        }
    };
};

void AddSC_boss_baltharus()
{
    new boss_baltharus();
    new mob_baltharus_clone();
    new mob_xerestrasza();
}