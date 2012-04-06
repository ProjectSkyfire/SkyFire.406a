/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010 /dev/rsa for ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "ruby_sanctum.h"

enum Halion
{
    SPELL_TWILIGHT_PRECISION            = 78243, // Increases Halion's chance to hit by 5% and decreases all players' chance to dodge by 20%
    SPELL_BERSERK                       = 26662, // Increases the caster's attack and movement speeds by 150% and all damage it deals by 500% for 5 min. Also grants immunity to Taunt effects.
    SPELL_START_PHASE2                  = 74808, // Phases the caster into the Twilight realm, leaving behind a large rift.
    SPELL_TWILIGHT_ENTER                = 74807, // Phases the caster into the Twilight realm - phase 32
    SPELL_TWILIGHT_ENTER2               = 74812, //
    SPELL_SUMMON_TWILIGHT_PORTAL        = 74809, //

    SPELL_FIRE_PILLAR                   = 76006, // Visual intro
    SPELL_FIERY_EXPLOSION               = 76010, // Visual intro

    //NEED SCRIPT
    SPELL_TAIL_LASH                     = 74531, // A sweeping tail strike hits all enemies behind the caster, inflicting 3063 to 3937 damage and stunning them for 2 sec.
    SPELL_TWILIGHT_DIVISION             = 75063, // Phases the caster, allowing him to exist and act simultaneously in both the material and Twilight realms.
    SPELL_TWILIGHT_CUTTER               = 77844, // Inflicts 13, 875 to 16, 125 Shadow damage every second to players touched by the shadow beam
    SPELL_TWILIGHT_CUTTER_CHANNEL       = 74768, // Channeling shadow cutter visual + trigger 74769

    //CORPOREALITY
    SPELL_CORPOREALITY_EVEN             = 74826, // Deals & receives normal damage
    SPELL_CORPOREALITY_20I              = 74827, // Damage dealt increased by 10% & Damage taken increased by 15%
    SPELL_CORPOREALITY_40I              = 74828, // Damage dealt increased by 30% & Damage taken increased by 50%
    SPELL_CORPOREALITY_60I              = 74829, // Damage dealt increased by 60% & Damage taken increased by 100%
    SPELL_CORPOREALITY_80I              = 74830, // Damage dealt increased by 100% & Damage taken increased by 200%
    SPELL_CORPOREALITY_100I             = 74831, // Damage dealt increased by 200% & Damage taken increased by 400%
    SPELL_CORPOREALITY_20D              = 74832, // Damage dealt reduced by 10% & Damage taken reduced by 15%
    SPELL_CORPOREALITY_40D              = 74833, // Damage dealt reduced by 30% & Damage taken reduced by 50%
    SPELL_CORPOREALITY_60D              = 74834, // Damage dealt reduced by 60% & Damage taken reduced by 100%
    SPELL_CORPOREALITY_80D              = 74835, // Damage dealt reduced by 100% & Damage taken reduced by 200%
    SPELL_CORPOREALITY_100D             = 74836, // Damage dealt reduced by 200% & Damage taken reduced by 400%
    //METEOR STRIKE
    SPELL_METEOR                        = 74637, // Script Start (summon NPC_METEOR_STRIKE)
    SPELL_METEOR_IMPACT                 = 74641, // IMPACT ZONE FOR METEOR
    SPELL_METEOR_STRIKE                 = 74648, // Inflicts 18, 750 to 21, 250 Fire damage to enemies within 12 yards of the targeted area. Takes about 5 seconds to land.
    SPELL_METEOR_FLAME                  = 74718, // FLAME FROM METEOR
    //N10
    SPELL_FLAME_BREATH_10_NORMAL        = 74525, // Inflicts 17, 500 to 22, 500 Fire damage to players in front of Halion
    //SPELL_FLAME_BREATH_25_NORMAL        = 74526,
    //SPELL_FLAME_BREATH_10_HEROIC        = 74527,
    //SPELL_FLAME_BREATH_25_HEROIC        = 74528,
    SPELL_DUSK_SHROUD                   = 75484, // Inflicts 3, 000 Shadow damage every 2 seconds to everyone in the Twilight Realm
    SPELL_DARK_BREATH_10_NORMAL         = 74806, // Inflicts 17, 500 to 22, 500 Shadow damage to players in front of Halion
    //SPELL_DARK_BREATH_25_NORMAL         = 75954,
    //SPELL_DARK_BREATH_10_HEROIC         = 75955,
    //SPELL_DARK_BREATH_25_HEROIC         = 75956,
    //Combustion
    SPELL_MARK_OF_COMBUSTION            = 74567, // Dummy effect only
    SPELL_FIERY_COMBUSTION              = 74562, // Inflicts 4, 000 Fire damage every 2 seconds for 30 seconds to a random raider. Every time Fiery Combustion does damage, it applies a stackable Mark of Combustion.
    SPELL_COMBUSTION_EXPLODE            = 74607,
    SPELL_COMBUSTION_AURA               = 74629,
    //Consumption
    NPC_CONSUMPTION                     = 40135,
    SPELL_MARK_OF_CONSUMPTION           = 74795, // Dummy effect only
    SPELL_SOUL_CONSUMPTION              = 74792, // Inflicts 4, 000 Shadow damage every 2 seconds for 30 seconds to a random raider. Every time Soul Consumption does damage, it applies a stackable Mark of Consumption.
    SPELL_CONSUMPTION_EXPLODE           = 74799,
    SPELL_CONSUMPTION_AURA              = 74803,
    //Summons
    NPC_METEOR_STRIKE                   = 40029, //casts "impact zone" then meteor
    NPC_METEOR_STRIKE_1                 = 40041,
    NPC_METEOR_STRIKE_2                 = 40042,
    NPC_ORB_CUTTER                      = 40081,

    FR_RADIUS                           = 45,

    //SAYS
    SAY_HALION_SPAWN                    = -1666100, //17499 Meddlesome insects, you're too late! The Ruby Sanctum is lost.
    SAY_HALION_AGGRO                    = -1666101, //17500 Your world teeters on the brink of annihilation. You will all bear witness to the coming of a new age of destruction!
    SAY_HALION_SLAY_1                   = -1666102, //17501 Another hero falls.
    SAY_HALION_SLAY_2                   = -1666103, //17502 Ha Ha Ha!
    SAY_HALION_DEATH                    = -1666104, //17503 Relish this victory mortals, for it will be your last. This world will burn with the Master's return!
    SAY_HALION_BERSERK                  = -1666105, //17504 Not good enough!
    SAY_HALION_SPECIAL_1                = -1666106, //17505 The heavens burn!
    SAY_HALION_SPECIAL_2                = -1666107, //17506 Beware the shadow!
    SAY_HALION_PHASE_2                  = -1666108, //17507 You will find only suffering within the realm of Twilight. Enter if you dare.
    SAY_HALION_PHASE_3                  = -1666109, //17508 I am the light AND the darkness! Cower mortals before the Herald of Deathwing!
    EMOTE_WARNING                       = -1666110, //orbs charge warning
    EMOTE_REAL_PUSH                     = -1666111, // Out of real world message
    EMOTE_REAL_PULL                     = -1666112, // To real world message
    EMOTE_TWIL_PUSH                     = -1666113, // Out of twilight world message
    EMOTE_TWIL_PULL                     = -1666114  // To twilight world message
};

struct Locations
{
    float x, y, z;
};

static Locations SpawnLoc[]=
{
    {3154.99f, 535.637f, 72.8887f}, // 0 - Halion spawn point (center)
};

///- boss_halion (Physical version)

Creature* halion;
Creature* twilight;
uint32 HalionDamage, TwilightDamage;
uint32 HalionAura, TwilightAura;

class boss_halion : public CreatureScript
{
public:
    boss_halion() : CreatureScript("boss_halion") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halionAI(creature);
    }

    struct boss_halionAI : public ScriptedAI
    {
        boss_halionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        bool intro;
        uint8 stage;
        uint8 nextPoint;
        uint32 IntroTimer;
        uint32 IntroAppTimer;
        uint32 Enrage;
        uint32 FlameTimer;
        uint32 FieryTimer;
        uint32 MeteorTimer;
        uint32 TailLashTimer;
        bool MovementStarted;

        void Reset()
        {
            if (instance->GetData(DATA_HALION_TWILIGHT) == IN_PROGRESS || instance->GetBossState(DATA_HALION) == IN_PROGRESS)
            {
                return;
            }
            me->SetRespawnDelay(7*DAY);

            if (me->isAlive())
            {
                instance->SetData(DATA_HALION, NOT_STARTED);
                instance->SetData(DATA_HALION_EVENT, FAIL);
                me->SetDisplayId(11686);
            }

            setStage(0);
            nextPoint       = 0;
            intro           = false;
            IntroTimer      = 1*IN_MILLISECONDS;
            IntroAppTimer   = 30*IN_MILLISECONDS;
            Enrage          = 600*IN_MILLISECONDS;
            FlameTimer      = urand(10*IN_MILLISECONDS, 18*IN_MILLISECONDS);
            FieryTimer      = urand(30*IN_MILLISECONDS, 40*IN_MILLISECONDS);
            MeteorTimer     = urand(30*IN_MILLISECONDS, 35*IN_MILLISECONDS);
            TailLashTimer   = urand(15*IN_MILLISECONDS, 25*IN_MILLISECONDS);
            HalionDamage    = 0;
            HalionAura      = 0;
            SetCombatMovement(true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (GameObject* goPortal = me->FindNearestGameObject(GO_HALION_PORTAL_1, 50.0f))
                goPortal->Delete();
            if (GameObject* goPortal = me->FindNearestGameObject(GO_HALION_PORTAL_2, 50.0f))
                goPortal->Delete();
            if (GameObject* goPortal = me->FindNearestGameObject(GO_HALION_PORTAL_EXIT, 50.0f))
                goPortal->Delete();
            me->RemoveAurasDueToSpell(SPELL_TWILIGHT_ENTER);
        }

        void setStage(uint8 phase)
        {
            stage = phase;
        }

        uint8 getStage()
        {
            return stage;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!instance)
                return;

            if (!who || who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (instance->GetData(DATA_GENERAL_ZARITHRIAN) == DONE)
            {
                if (!intro && who->IsWithinDistInMap(me, 60.0f))
                    {
                        DoScriptText(-1666100, me);
                        intro = true;
                    }

                if (intro && !me->isInCombat() && who->IsWithinDistInMap(me, 20.0f))
                {
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                    me->SetInCombatWith(who);
                    SetCombatMovement(false);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->GetMotionMaster()->MoveIdle();
                    setStage(10);
                }
            } else return;
        }

        void JustReachedHome()
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_HALION_EVENT) != FAIL || getStage() == 0)
                return;

            ScriptedAI::JustReachedHome();
        }

        void EnterEvadeMode()
        {
            if (!instance) return;

            if (instance->GetData(DATA_HALION_EVENT) != FAIL) return;

            ScriptedAI::EnterEvadeMode();
        }

        void JustDied(Unit* killer)
        {
            if (!instance)
                return;

            if (GameObject* goPortal = me->FindNearestGameObject(GO_HALION_PORTAL_1, 50.0f))
                goPortal->Delete();
            DoScriptText(-1666104, me);

            if (Creature* clone = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT)))
            {
                if (clone->isAlive())
                {
                    clone->SetHealth(1);
                }
            }

            instance->SetData(DATA_HALION, DONE);
            me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
            instance->SetData(TYPE_COUNTER, COUNTER_OFF);

            // Updating achievements for all players in the map - not only in halion world
            Map* map = me->GetMap();
            Map::PlayerList const &pList = map->GetPlayers();
                if (pList.isEmpty()) return;

            for (Map::PlayerList::const_iterator i = pList.begin(); i != pList.end(); ++i)
            {
                if (Player* player = i->getSource())
                {
                    if (!player) continue;
                    if (player->isGameMaster()) continue;
                    if (!player->IsInMap(me)) continue;
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, me->GetEntry());
                }
            }
        }

        void KilledUnit(Unit* victim)
        {
            switch (urand(0, 1))
            {
                case 0:
                    DoScriptText(-1666106, me, victim);
                    break;
                case 1:
                    DoScriptText(-1666107, me, victim);
                    break;
            }
        }

        void EnterCombat(Unit* who)
        {
            if (!instance)
                return;

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoCast(SPELL_TWILIGHT_PRECISION);
            me->SetInCombatWithZone();
            instance->SetData(DATA_HALION, IN_PROGRESS);
            DoScriptText(-1666101, me);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!instance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == nextPoint)
            {
                me->GetMotionMaster()->MovementExpired();
                MovementStarted = false;
            }
        }

        void StartMovement(uint32 id)
        {
            nextPoint = id;
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
            MovementStarted = true;
        }

        void DamageTaken(Unit* doneBy, uint32& Damage)
        {
            if (!instance)
                return;

            HalionDamage += Damage;
            Creature * halionTwilight = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT));
            if (!halionTwilight)
                return;

            if (halionTwilight->GetHealth() <= 1 || !halionTwilight->isAlive())
                return;

            if (Damage < me->GetHealth())
            {
                halionTwilight->SetHealth(me->GetHealth()-Damage);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
                return;

            if (!UpdateVictim())
                return;

            switch (getStage())
            {
                case 10: //PHASE INTRO
                    if (IntroTimer <= diff)
                    {
                        DoCast(SPELL_FIRE_PILLAR);
                        IntroAppTimer = 10*IN_MILLISECONDS;
                        IntroTimer = 30*IN_MILLISECONDS;
                    }
                    else IntroTimer -= diff;

                    if (IntroAppTimer <= diff)
                    {
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                        DoCast(SPELL_FIERY_EXPLOSION);
                        me->SetDisplayId(31952);
                        SetCombatMovement(true);
                        me->GetMotionMaster()->MoveChase(me->getVictim());
                        setStage(0);
                        IntroAppTimer = 30*IN_MILLISECONDS;
                    }
                    else IntroAppTimer -= diff;
                    break;
                case 0: //PHASE 1 PHYSICAL REALM
                    if (FlameTimer <= diff)
                    {
                        DoCast(SPELL_FLAME_BREATH_10_NORMAL);
                        FlameTimer = urand(12*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else FlameTimer -= diff;

                    if (TailLashTimer <= diff)
                    {
                        DoCast(SPELL_TAIL_LASH);
                        TailLashTimer = urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else TailLashTimer -= diff;

                    if (FieryTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 45.0f, true))
                            DoCast(target, SPELL_FIERY_COMBUSTION);
                        else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                            DoCast(target, SPELL_FIERY_COMBUSTION);
                        FieryTimer = urand(25*IN_MILLISECONDS, 40*IN_MILLISECONDS);
                    } else FieryTimer -= diff;

                    if (MeteorTimer <= diff)
                    {
                        DoCast(SPELL_METEOR);
                        MeteorTimer = urand(30*IN_MILLISECONDS, 35*IN_MILLISECONDS);
                    } else MeteorTimer -= diff;

                    if (HealthBelowPct(76))
                    {
                        setStage(1);
                        me->AttackStop();
                        me->InterruptNonMeleeSpells(true);
                        SetCombatMovement(false);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    }
                    break;
                case 1: // Switch to phase 2
                    {
                        DoScriptText(-1666108, me);
                        instance->SetData(DATA_HALION_EVENT, NOT_STARTED);
                        StartMovement(0);
                        {
                            Creature* control = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_CONTROLLER));
                            if (!control)
                                control = me->SummonCreature(NPC_HALION_CONTROLLER, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
                            else if (!control->isAlive())
                                control->Respawn();
                            control->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetInCombatWith(control);
                            control->SetInCombatWith(me);
                        }
                        setStage(2);
                        break;
                    }
                case 2:
                    if (MovementStarted) return;
                    DoCast(me, SPELL_SUMMON_TWILIGHT_PORTAL);
                    setStage(3);

                    if (GameObject* goPortal = instance->instance->GetGameObject(instance->GetData64(GO_HALION_PORTAL_1)))
                          goPortal->SetPhaseMask(31, true);

                    if (GameObject* goRing = instance->instance->GetGameObject(instance->GetData64(GO_FLAME_RING)))
                          goRing->SetPhaseMask(65535, true);
                    break;
                case 3:
                    if (me->IsNonMeleeSpellCasted(false)) return;
                    DoCast(SPELL_START_PHASE2);
                    setStage(4);
                    break;

                case 4:
                    if (!me->IsNonMeleeSpellCasted(false))
                    {
                        if (Creature* control = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_CONTROLLER)))
                        {
                            me->SetInCombatWith(control);
                            control->SetInCombatWith(me);
                        }
                        Creature* twilight = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT));
                        if (!twilight)
                            twilight = me->SummonCreature(NPC_HALION_TWILIGHT, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
                        else if (!twilight->isAlive())
                            twilight->Respawn();
                        twilight->SetCreatorGUID(0);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        setStage(5);
                    }
                    break;

                case 5: // HALION awaiting end battle in TWILIGHT REALM
                    if (instance->GetData(DATA_HALION_EVENT) == IN_PROGRESS)
                        {
                            me->RemoveAurasDueToSpell(SPELL_START_PHASE2);
                            if (Creature* control = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_CONTROLLER)))
                            {
                                me->SetInCombatWith(control);
                                control->SetInCombatWith(me);
                            }
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->SetHealth(me->GetMaxHealth()/2);
                            me->SetInCombatWithZone();
                            setStage(6);
                        }
                    return;
                case 6: // Switch to phase 3
                    DoScriptText(-1666109, me);
                    instance->SetData(DATA_HALION_EVENT, SPECIAL);
                    setStage(7);
                    break;
                case 7:
                    if (me->IsNonMeleeSpellCasted(false)) return;
                    if (me->getVictim()->GetTypeId() != TYPEID_PLAYER) return;
                    SetCombatMovement(true);
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    setStage(8);
                    break;
                case 8: //PHASE 3 BOTH REALMS
                    if (Creature* twilight = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT)))
                        if (twilight->isAlive())
                            me->SetHealth(twilight->GetHealth());
                    if (FlameTimer <= diff)
                    {
                         DoCast(SPELL_FLAME_BREATH_10_NORMAL);
                         FlameTimer = urand(12*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else FlameTimer -= diff;

                    if (TailLashTimer <= diff)
                    {
                         DoCast(SPELL_TAIL_LASH);
                         TailLashTimer = urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else TailLashTimer -= diff;

                    if (FieryTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 45.0f, true))
                            DoCast(target, SPELL_FIERY_COMBUSTION);
                        else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                            DoCast(target, SPELL_FIERY_COMBUSTION);
                        FieryTimer = urand(25*IN_MILLISECONDS, 40*IN_MILLISECONDS);
                    } else FieryTimer -= diff;

                    if (MeteorTimer <= diff)
                    {
                        DoCast(SPELL_METEOR);
                        MeteorTimer = urand(30*IN_MILLISECONDS, 35*IN_MILLISECONDS);
                    } else MeteorTimer -= diff;
                    break;
                default:
                    break;
            }

            if (Enrage <= diff)
            {
                 DoCast(SPELL_BERSERK);
                 Enrage = 600*IN_MILLISECONDS;
                 DoScriptText(-1666105, me);
            } else Enrage -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///- boss_halion_twilight (Twilight version)

class boss_halion_twilight : public CreatureScript
{
public:
    boss_halion_twilight() : CreatureScript("boss_halion_twilight") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_halion_twilightAI(creature);
    }

    struct boss_halion_twilightAI : public ScriptedAI
    {
        boss_halion_twilightAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint8 stage;
        bool intro;
        uint32 Enrage;
        uint32 DuskTimer;
        uint32 DarkBreathTimer;
        uint32 SoulCunsumTimer;
        uint32 TailLashTimer;

        void Reset()
        {
            if(!instance)
                return;
            me->SetRespawnDelay(7*DAY);
            setStage(0);
            intro = false;
            Enrage = 600*IN_MILLISECONDS;
            DuskTimer = 2*IN_MILLISECONDS;
            TwilightDamage = 0;
            DarkBreathTimer = urand(12*IN_MILLISECONDS, 20*IN_MILLISECONDS);
            SoulCunsumTimer = urand(30*IN_MILLISECONDS, 40*IN_MILLISECONDS);
            TailLashTimer = urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS);

            me->SetInCombatWithZone();
            if (Creature* control = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_CONTROLLER)))
            {
                me->SetInCombatWith(control);
                control->SetInCombatWith(me);
            }

            Creature* focus = me->GetMap()->GetCreature(instance->GetData64(NPC_ORB_ROTATION_FOCUS));
            if (!focus )
                focus = me->SummonCreature(NPC_ORB_ROTATION_FOCUS, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 0, TEMPSUMMON_MANUAL_DESPAWN, 1000);
            else if (!focus->isAlive())
                focus->Respawn();

            if (Creature* halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION)))
                if (halion->isAlive())
                    me->SetHealth(halion->GetHealth());
            if (!me->HasAura(SPELL_TWILIGHT_ENTER))
                DoCast(me, SPELL_TWILIGHT_ENTER);
        }

        void setStage(uint8 phase)
        {
            stage = phase;
        }

        uint8 getStage()
        {
            return stage;
        }

        void JustReachedHome()
        {
            if (!instance) return;
            if (instance->GetData(DATA_HALION_EVENT) != FAIL || getStage() == 0)
                return;
            ScriptedAI::JustReachedHome();
        }

        void EnterEvadeMode()
        {
            if (!instance) return;

            if (instance->GetData(DATA_HALION_EVENT) != FAIL || getStage() == 0)
                return;

            ScriptedAI::EnterEvadeMode();
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!instance) return;

            if (!who || who->GetTypeId() != TYPEID_PLAYER) return;

            if ( !intro && who->IsWithinDistInMap(me, 20.0f))
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                intro = true;
                AttackStart(who);
                setStage(1);
                DoCast(SPELL_TWILIGHT_PRECISION);
            }
        }

        void JustDied(Unit* killer)
        {
            if (!instance)
                return;
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ENTER);
            if (Creature* halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION)))
            if (!halion->isAlive())
            {
                instance->SetData(DATA_HALION, DONE);
                halion->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                instance->SetData(TYPE_COUNTER, COUNTER_OFF);
            }
            me->ForcedDespawn();
        }

        void KilledUnit(Unit* victim)
        {
            switch (urand(0, 1))
            {
                case 0:
                    DoScriptText(-1666106, me, victim);
                    break;
                case 1:
                    DoScriptText(-1666107, me, victim);
                    break;
            }
        }

        void EnterCombat(Unit* who)
        {
            if (!instance)
                return;
        }

        void DamageTaken(Unit* doneBy, uint32& Damage)
        {
            if (!instance)
                return;
            TwilightDamage += Damage;
            Creature* halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION));
            if (!halion)
                return;
            if (halion->GetHealth() <=1 || !halion->isAlive())
                return;
            if (Damage < me->GetHealth())
            {
                halion->SetHealth(me->GetHealth()-Damage);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!me->HasAura(SPELL_TWILIGHT_ENTER))
                 DoCast(me, SPELL_TWILIGHT_ENTER);

            if (!instance)
            {
                me->ForcedDespawn();
                return;
            }

            if (instance->GetData(DATA_HALION) != DONE)
            {
                if (!instance || instance->GetData(DATA_HALION) != IN_PROGRESS || instance->GetData(DATA_HALION_EVENT) == FAIL)
                {
                    if (Creature* halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION)))
                        if (!halion->isAlive())
                            halion->Respawn();
                    me->ForcedDespawn();
                }
            }

            if (!UpdateVictim())
                return;

            switch (getStage())
            {
                case 1: //SPAWNED - Twilight realm
                    if (DuskTimer <= diff)
                    {
                        if (!me->IsNonMeleeSpellCasted(false))
                            DoCast(SPELL_DUSK_SHROUD);
                        DuskTimer = 2*IN_MILLISECONDS;
                    } else DuskTimer -= diff;

                    if (DarkBreathTimer <= diff)
                    {
                        DoCast(SPELL_DARK_BREATH_10_NORMAL);
                        DarkBreathTimer = urand(12*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else DarkBreathTimer -= diff;

                    if (TailLashTimer <= diff)
                    {
                        DoCast(SPELL_TAIL_LASH);
                        TailLashTimer = urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else TailLashTimer -= diff;

                    if (SoulCunsumTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 45.0f, true))
                            DoCast(target, SPELL_SOUL_CONSUMPTION);
                        else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                            DoCast(target, SPELL_SOUL_CONSUMPTION);
                        SoulCunsumTimer = urand(25*IN_MILLISECONDS, 40*IN_MILLISECONDS);
                    } else SoulCunsumTimer -= diff;

                    if (HealthBelowPct(51))
                    {
                        setStage(2);
                    }
                    break;
                case 2: //To two realms
                    instance->SetData(DATA_HALION_EVENT, IN_PROGRESS);
                    DoScriptText(-1666109, me);
                    if (GameObject* goPortal = me->SummonGameObject(GO_HALION_PORTAL_EXIT, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, 4.47206f, 0, 0, 0.786772f, -0.617243f, 99999999))
                    {
                        goPortal->SetPhaseMask(32, true);
                        goPortal->SetRespawnTime(9999999);
                        goPortal->SetOwnerGUID(NULL);
                    }
                    DoCast(SPELL_TWILIGHT_DIVISION);
                    setStage(3);
                    break;
                case 3: //PHASE 3 BOTH REALMS
                    if (DuskTimer <= diff)
                    {
                        if (!me->IsNonMeleeSpellCasted(false))
                           DoCast(SPELL_DUSK_SHROUD);
                        DuskTimer = 2*IN_MILLISECONDS;
                    } else DuskTimer -= diff;

                    if (DarkBreathTimer <= diff)
                    {
                        DoCast(SPELL_DARK_BREATH_10_NORMAL);
                        DarkBreathTimer = urand(12*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else DarkBreathTimer -= diff;

                    if (TailLashTimer <= diff)
                    {
                        DoCast(SPELL_TAIL_LASH);
                        TailLashTimer = urand(10*IN_MILLISECONDS, 20*IN_MILLISECONDS);
                    } else TailLashTimer -= diff;

                    if (SoulCunsumTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 45.0f, true))
                            DoCast(target, SPELL_SOUL_CONSUMPTION);
                        else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                            DoCast(target, SPELL_SOUL_CONSUMPTION);
                        SoulCunsumTimer = urand(25*IN_MILLISECONDS, 40*IN_MILLISECONDS);
                    } else SoulCunsumTimer -= diff;
                    break;
                default:
                    break;
            }

            if (Enrage <= diff)
            {
                DoCast(SPELL_BERSERK);
                Enrage = 600*IN_MILLISECONDS;
                DoScriptText(-1666105, me);
            } else Enrage -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

///- mob_halion_controller

struct HalionBuffLine
{
    uint32 halion, twilight;     // Buff pair
    uint8 disp_corp;             // Displayed Corporeality
};

static HalionBuffLine Buff[]=
{
    {SPELL_CORPOREALITY_100D, SPELL_CORPOREALITY_100I, 0  },
    {SPELL_CORPOREALITY_80D,  SPELL_CORPOREALITY_80I,  10 },
    {SPELL_CORPOREALITY_60D,  SPELL_CORPOREALITY_60I,  20 },
    {SPELL_CORPOREALITY_40D,  SPELL_CORPOREALITY_40I,  30 },
    {SPELL_CORPOREALITY_20D,  SPELL_CORPOREALITY_20I,  40 },
    {SPELL_CORPOREALITY_EVEN, SPELL_CORPOREALITY_EVEN, 50 },
    {SPELL_CORPOREALITY_20I,  SPELL_CORPOREALITY_20D,  60 },
    {SPELL_CORPOREALITY_40I,  SPELL_CORPOREALITY_40D,  70 },
    {SPELL_CORPOREALITY_60I,  SPELL_CORPOREALITY_60D,  80 },
    {SPELL_CORPOREALITY_80I,  SPELL_CORPOREALITY_80D , 90 },
    {SPELL_CORPOREALITY_100I, SPELL_CORPOREALITY_100D, 100 },
};

class mob_halion_controller : public CreatureScript
{
public:
    mob_halion_controller() : CreatureScript("mob_halion_controller") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_halion_controllerAI(creature);
    }

    struct mob_halion_controllerAI : public ScriptedAI
    {
        mob_halion_controllerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        Creature* halion;
        Creature* halionTwilight;
        uint32 _lastBuffReal, _lastBuffTwilight, _lastBuffNum;
        uint32 CorporealityTimer;
        bool _detectplayers;
        uint8 _lastCorreal;

        void Reset()
        {
            if (!instance) return;

            CorporealityTimer = 5*IN_MILLISECONDS;
            _detectplayers = true;
            me->SetDisplayId(11686);
            me->SetPhaseMask(65535, true);
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            _lastBuffReal = 0;
            _lastBuffTwilight = 0;
            _lastBuffNum = 5;
            _lastCorreal = 50;
            instance->SetData(TYPE_COUNTER, COUNTER_OFF);
            instance->SetData(DATA_HALION_EVENT, NOT_STARTED);
        }

        void AttackStart(Unit *who)
        {
            //ignore all attack start commands
            return;
        }

        bool doSearchPlayerAtRange(float range)
        {
            Map* map = me->GetMap();
            if (map && map->IsDungeon())
            {
                Map::PlayerList const &PlayerList = map->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (!i->getSource()->IsInMap(me)) continue;
                        if (i->getSource()->isGameMaster()) continue;
                        if (i->getSource()->isAlive() && i->getSource()->IsWithinDistInMap(me, range))
                            return true;
                    }
            }
            return false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
            {
                me->ForcedDespawn();
                return;
            }

            if (instance->GetData(DATA_HALION) != IN_PROGRESS)
            {
                me->ForcedDespawn();
                return;
            }

            if (CorporealityTimer <= diff)
            {
                if (!doSearchPlayerAtRange(100.0f))
                {
                    sLog->outDebug(LOG_FILTER_MAPS, "ruby_sanctum: cannot detect players in range! ");
                    if (!_detectplayers)
                    {
                        instance->SetData(DATA_HALION_EVENT, FAIL);
                        instance->SetData(DATA_HALION, FAIL);
                        me->ForcedDespawn();
                    }
                else
                {
                    _detectplayers = false;
                }
            }
            else
            {
                _detectplayers = true;
            }

                if (instance->GetData(DATA_HALION_EVENT) != SPECIAL) return;
                halion = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION));
                halionTwilight = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT));
                halionTwilight->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                float p_MaxHP = halion->GetMaxHealth();
                float p_RealHP = (halion && halion->isAlive()) ? HalionDamage/p_MaxHP*100 : 0.0f;
                float p_TwilightHP = (halionTwilight && halionTwilight->isAlive()) ? TwilightDamage/p_MaxHP*100 : 0.0f;
                HalionDamage = 0;
                TwilightDamage = 0;
                float m_diff = (p_TwilightHP - p_RealHP);
                int32 buffnum;

                if (m_diff < 0)
                {
                    buffnum = _lastBuffNum - 1;
                }
                else
                {
                    if (m_diff > 0)
                    {
                        buffnum = _lastBuffNum + 1;
                    }
                    else
                    {
                        buffnum = _lastBuffNum;
                    }
                }

                if (buffnum < 0) buffnum = 0;
                if (buffnum > 10) buffnum = 10;

                if (!_lastBuffReal || _lastBuffReal != Buff[buffnum].halion)
                {
                    if (halion && halion->isAlive())
                    {
                        if (_lastBuffReal)
                        {
                            halion->RemoveAurasDueToSpell(_lastBuffReal);
                        }
                        halion->CastSpell(halion, Buff[buffnum].halion, true);
                        _lastBuffReal = Buff[buffnum].halion;
                    }
                }

                if (_lastCorreal - Buff[buffnum].disp_corp < 0)
                {
                    DoScriptText(EMOTE_REAL_PULL, halion);
                    DoScriptText(EMOTE_TWIL_PUSH, halionTwilight);
                }
                else if (_lastCorreal - Buff[buffnum].disp_corp > 0)
                {
                    DoScriptText(EMOTE_REAL_PUSH, halion);
                    DoScriptText(EMOTE_TWIL_PULL, halionTwilight);
                }

                _lastBuffReal = Buff[buffnum].halion;
                _lastCorreal = (uint8)Buff[buffnum].disp_corp;
                _lastBuffNum = buffnum;

                if (!_lastBuffTwilight || _lastBuffTwilight != Buff[buffnum].twilight)
                {
                    if (halionTwilight && halionTwilight->isAlive())
                    {
                        if (_lastBuffTwilight)
                        {
                            halionTwilight->RemoveAurasDueToSpell(_lastBuffTwilight);
                        }
                        halionTwilight->CastSpell(halionTwilight, Buff[buffnum].twilight, true);
                        _lastBuffTwilight = Buff[buffnum].twilight;
                    }
                }

                instance->SetData(TYPE_COUNTER, _lastCorreal);

                CorporealityTimer = 10*IN_MILLISECONDS;
            } else CorporealityTimer -= diff;
        }
    };
};

///- mob_orb_rotation_focus

class mob_orb_rotation_focus : public CreatureScript
{
public:
    mob_orb_rotation_focus() : CreatureScript("mob_orb_rotation_focus") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_orb_rotation_focusAI(creature);
    }

    struct mob_orb_rotation_focusAI : public ScriptedAI
    {
        mob_orb_rotation_focusAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint32 _timer;
        float _direction, _nextdirection;
        bool _warning;
        bool _warning2;
        Creature* _pulsar_N;
        Creature* _pulsar_S;
        Creature* _pulsar_E;
        Creature* _pulsar_W;

        void Reset()
        {
            //me->SetDisplayId(11686);
            me->SetRespawnDelay(7*DAY);
            me->SetPhaseMask(65535, true);
            SetCombatMovement(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            _direction = 0.0f;
            _nextdirection = 0.0f;
            _timer = 50000;
            _warning = false;

            _pulsar_N = me->GetMap()->GetCreature(instance->GetData64(NPC_SHADOW_PULSAR_N));
            if (!_pulsar_N )
            {
                float x, y;
                me->GetNearPoint2D(x, y, FR_RADIUS, _direction);
                _pulsar_N = me->SummonCreature(NPC_SHADOW_PULSAR_N, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
            } else if (!_pulsar_N->isAlive())
                    _pulsar_N->Respawn();

            _pulsar_S = me->GetMap()->GetCreature(instance->GetData64(NPC_SHADOW_PULSAR_S));
            if (!_pulsar_S)
            {
                float x, y;
                me->GetNearPoint2D(x, y, FR_RADIUS, _direction + M_PI);
                _pulsar_S = me->SummonCreature(NPC_SHADOW_PULSAR_S, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
            } else if (!_pulsar_S->isAlive())
                        _pulsar_S->Respawn();
            }

        void AttackStart(Unit *who)
        {
            //ignore all attackstart commands
            return;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
                  me->ForcedDespawn();
            if (instance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (instance->GetData(DATA_ORB_S) == DONE && instance->GetData(DATA_ORB_N) == DONE)
            {
                _direction = _nextdirection;
                _nextdirection = (_direction - M_PI/64.0f);
                if (_nextdirection < 0.0f ) _nextdirection = _nextdirection + 2.0f*M_PI;
                instance->SetData(DATA_ORB_DIRECTION, (uint32)(_nextdirection*1000));
                instance->SetData(DATA_ORB_N, SPECIAL);
                instance->SetData(DATA_ORB_S, SPECIAL);
                sLog->outDebug(LOG_FILTER_MAPS, "EventMGR: creature %u send direction %u ",me->GetEntry(),instance->GetData(DATA_ORB_DIRECTION));
            }

            if (_timer%30000 - 3000 <= diff && !_warning)
            {
                DoScriptText(-1666110, me);
                _warning = true;
            }

            if (_timer%30000 - 1000 < diff && !_warning2)
            {
                Creature * halionTwilight = me->GetMap()->GetCreature(instance->GetData64(NPC_HALION_TWILIGHT));
                if (halionTwilight)
                {
                    DoScriptText(SAY_HALION_SPECIAL_2, halionTwilight);
                    _warning2 = true;
                }
            }

            if (_timer > 20000 && _timer < 30000)
            {
                _pulsar_N->CastSpell(_pulsar_S, SPELL_TWILIGHT_CUTTER_CHANNEL, true);

                Map* map = me->GetMap();
                Map::PlayerList const &pList = map->GetPlayers();
                    if (pList.isEmpty()) return;

                for (Map::PlayerList::const_iterator i = pList.begin(); i != pList.end(); ++i)
                {
                    if (Player* player = i->getSource())
                    {
                        if (!player->HasAura(SPELL_TWILIGHT_ENTER))
                            return;
                        if (player->isAlive())
                        {
                            float AB = _pulsar_N->GetDistance2d(_pulsar_S)+1;
                            float BC = _pulsar_N->GetDistance2d(player)+1;
                            float AC = _pulsar_S->GetDistance2d(player)+1;
                            float p = (AB + BC + AC)/2;
                            float DC = (2*sqrt(p*(p-AB)*(p-BC)*(p-AC)))/AB;
                            //debug_log("DC = %06.6f (AB = %06.6f, BC = %06.6f, AC = %06.6f, p = %06.6f)", DC, AB, BC, AC, p);
                            if (DC < 3.75f || DC > 52.0f)
                            {
                                player->CastSpell(player, SPELL_TWILIGHT_CUTTER, true, 0, 0, _pulsar_N->GetGUID());
                            }
                        }
                    }
                }
            }

            if (_timer <= diff)
            {
                float x, y;
                me->GetNearPoint2D(x, y, FR_RADIUS, _nextdirection);
                me->SummonCreature(NPC_ORB_CARRIER, x, y, me->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN, 5000);
                _timer = 50000;
                _warning = false;
            } else _timer -= diff;
        }
    };
};

///- mob_halion_orb

class mob_halion_orb : public CreatureScript
{
public:
    mob_halion_orb() : CreatureScript("mob_halion_orb") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_halion_orbAI(creature);
    }

    struct mob_halion_orbAI : public ScriptedAI
    {
        mob_halion_orbAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        float _direction, m_delta;
        uint32 _flag;
        uint32 _flag1;
        bool MovementStarted;
        Creature* focus;
        uint32 nextPoint;
        uint32 tc_timer;

        void Reset()
        {
            if (!instance) return;
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            tc_timer = 30000;
            me->SetPhaseMask(32, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_1);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            if (me->GetEntry() == NPC_SHADOW_PULSAR_N)
            {
                _flag = DATA_ORB_N;
                m_delta = 0.0f;
            } else if (me->GetEntry() == NPC_SHADOW_PULSAR_S)
            {
                _flag = DATA_ORB_S;
                m_delta = M_PI;
            };
            me->SetSpeed(MOVE_WALK, 8.0f);
            me->SetSpeed(MOVE_RUN, 8.0f);
            _direction = 0.0f;
            nextPoint = 0;
            MovementStarted = false;
            instance->SetData(_flag, DONE);
            sLog->outDebug(LOG_FILTER_MAPS, "EventMGR: creature %u assume _flag %u ", me->GetEntry(), _flag);
        }

        void AttackStart(Unit* who)
        {
            //ignore all attack start commands
            return;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!instance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == nextPoint)
            {
                me->GetMotionMaster()->MovementExpired();
                MovementStarted = false;
                instance->SetData(_flag, DONE);
            }
        }

        void StartMovement(uint32 id)
        {
            if (!instance) return;
            nextPoint = id;
            float x, y;
            instance->SetData(_flag, IN_PROGRESS);
            MovementStarted = true;
            _direction = ((float)instance->GetData(DATA_ORB_DIRECTION)/1000 + m_delta);
            if (_direction > 2.0f*M_PI) _direction = _direction - 2.0f*M_PI;
            if (focus = me->GetMap()->GetCreature(instance->GetData64(NPC_ORB_ROTATION_FOCUS)))
                focus->GetNearPoint2D(x, y, FR_RADIUS, _direction);
                else me->ForcedDespawn();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(id, x, y, me->GetPositionZ());
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
                  me->ForcedDespawn();
            if (instance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (!MovementStarted && instance->GetData(_flag) == SPECIAL)
            {
                StartMovement(1);
            }
        }
    };
};

///- mob_orb_carrier

class mob_orb_carrier : public CreatureScript
{
public:
    mob_orb_carrier() : CreatureScript("mob_orb_carrier") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_orb_carrierAI(creature);
    }

    struct mob_orb_carrierAI : public ScriptedAI
    {
        mob_orb_carrierAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        bool MovementStarted;

        void Reset()
        {
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            me->SetPhaseMask(32, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            MovementStarted = false;
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); //or remove???
            me->SetSpeed(MOVE_RUN, 10.0f, true);
        }

        void AttackStart(Unit *who)
        {
            return;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!instance) return;

            if (type != POINT_MOTION_TYPE || !MovementStarted) return;

            if (id == 1)
            {
                me->GetMotionMaster()->MovementExpired();
                MovementStarted = false;
                me->ForcedDespawn();
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance || instance->GetData(DATA_HALION) != IN_PROGRESS)
                  me->ForcedDespawn();

            if (!MovementStarted)
            {
                float x, y;
                float _direction = ((float)instance->GetData(DATA_ORB_DIRECTION)/1000.0f + M_PI - M_PI/32.0f);
                if (_direction > 2.0f*M_PI) _direction = _direction - 2.0f*M_PI;
                if (Creature* focus = me->GetMap()->GetCreature(instance->GetData64(NPC_ORB_ROTATION_FOCUS)))
                    focus->GetNearPoint2D(x, y, FR_RADIUS, _direction);
                else me->ForcedDespawn();
                me->GetMotionMaster()->Clear();
                me->GetMotionMaster()->MovePoint(1, x, y, me->GetPositionZ());
                MovementStarted = true;
            }
        }
    };
};

///- mob_soul_consumption

class mob_soul_consumption : public CreatureScript
{
public:
    mob_soul_consumption() : CreatureScript("mob_soul_consumption") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_soul_consumptionAI(creature);
    }

    struct mob_soul_consumptionAI : public ScriptedAI
    {
        mob_soul_consumptionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        float _Size0;
        float _Size;
        uint32 ConsumptTimer;
        bool grow;

        void Reset()
        {
            me->SetPhaseMask(32, true);
            SetCombatMovement(false);
            ConsumptTimer = 60*IN_MILLISECONDS;
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            DoCast(SPELL_CONSUMPTION_AURA);
            _Size0 = me->GetFloatValue(OBJECT_FIELD_SCALE_X);
            _Size = _Size0;
            grow = false;
        }

        void AttackStart(Unit *who)
        {
            return;
        }

        void UpdateAI(const uint32 diff)
        {
            if (instance && instance->GetData(DATA_HALION) != IN_PROGRESS)
                me->ForcedDespawn();

            if (ConsumptTimer <= diff)
            {
                me->ForcedDespawn();
            }
            else ConsumptTimer -= diff;

            Map::PlayerList const &players = instance->instance->GetPlayers();
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                if (Player* player = i->getSource())
                {
                    if (player->isAlive() && player->HasAura(SPELL_MARK_OF_CONSUMPTION))
                    {
                        Aura *aura = player->GetAura(SPELL_MARK_OF_CONSUMPTION);
                        uint32 stacs;
                        stacs = aura->GetStackAmount();
                        if(!grow)
                        {
                            _Size = (_Size + (stacs*0.1));
                            me->SetFloatValue(OBJECT_FIELD_SCALE_X, _Size);
                            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MARK_OF_CONSUMPTION);
                            grow = true;
                        }
                    }
                }
            }
        }
    };
};

///- mob_fiery_combustion

class mob_fiery_combustion : public CreatureScript
{
public:
    mob_fiery_combustion() : CreatureScript("mob_fiery_combustion") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_fiery_combustionAI(creature);
    }

    struct mob_fiery_combustionAI : public ScriptedAI
    {
        mob_fiery_combustionAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        float _Size0;
        float _Size;
        uint32 ConbustTimer;
        bool grow;

        void Reset()
        {
            me->SetPhaseMask(1, true);
            ConbustTimer = 60*IN_MILLISECONDS;
            SetCombatMovement(false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            DoCast(SPELL_COMBUSTION_AURA);
            _Size0 = me->GetFloatValue(OBJECT_FIELD_SCALE_X);
            _Size = _Size0;
            grow = false;
        }

        void AttackStart(Unit *who)
        {
            return;
        }

        void UpdateAI(const uint32 diff)
        {
            if (instance && instance->GetData(DATA_HALION) != IN_PROGRESS)
                me->ForcedDespawn();

            if (ConbustTimer <= diff)
            {
                me->ForcedDespawn();
            } else ConbustTimer -= diff;

            Map::PlayerList const &players = instance->instance->GetPlayers();
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                if (Player* player = i->getSource())
                {
                    if (player->isAlive() && player->HasAura(SPELL_MARK_OF_COMBUSTION))
                    {
                        Aura* aura = player->GetAura(SPELL_MARK_OF_COMBUSTION);
                        uint32 stacs;
                        stacs= aura->GetStackAmount();
                        if(!grow)
                        {
                            _Size = (_Size + (stacs*0.1));
                            me->SetFloatValue(OBJECT_FIELD_SCALE_X, _Size);
                            me->RemoveAura(SPELL_MARK_OF_COMBUSTION, player->GetGUID());
                            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_MARK_OF_COMBUSTION);
                            grow = true;
                        }
                    }
                }
            }
        }
    };
};

///- mob_halion_meteor

#define TARGETS_10 5
#define TARGETS_25 7

class mob_halion_meteor : public CreatureScript
{
public:
    mob_halion_meteor() : CreatureScript("mob_halion_meteor") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_halion_meteorAI(creature);
    }

    struct mob_halion_meteorAI : public ScriptedAI
    {
        mob_halion_meteorAI(Creature* creature) : ScriptedAI(creature)
        {
            Reset();
        }

        float direction;
        uint8 stage;
        uint32 MeteorImpactTimer;
        uint32 MeteorStrikeTimer;

        void setStage(uint8 phase)
        {
            stage = phase;
        }

        uint8 getStage()
        {
            return stage;
        }

        void Reset()
        {
            me->SetDisplayId(11686);
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            MeteorImpactTimer = 0.5*IN_MILLISECONDS;
            MeteorStrikeTimer = 4.5*IN_MILLISECONDS;
            setStage(0);
            me->SetInCombatWithZone();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }

        void UpdateAI(const uint32 diff)
        {
            switch (getStage())
            {
                case 0:
                    if (MeteorImpactTimer <= diff)
                    {
                        DoCast(SPELL_METEOR_IMPACT);
                        MeteorImpactTimer = 0.5*IN_MILLISECONDS;
                        setStage(1);
                    } else MeteorImpactTimer -= diff;
                    break;
                case 1:
                    if (MeteorStrikeTimer <= diff)
                    {
                        DoCast(SPELL_METEOR_STRIKE);
                        MeteorStrikeTimer = 4.5*IN_MILLISECONDS;
                        setStage(2);
                    } else MeteorStrikeTimer -= diff;
                    break;
                case 2:
                    // Place summon flames there
                    {
                        direction = 2.0f*M_PI*((float)urand(0, 15)/16.0f);
                        float x, y, radius;
                        radius = 0.0f;
                        for (uint8 i = 0; i < RAID_MODE(TARGETS_10, TARGETS_25, TARGETS_10, TARGETS_25); ++i)
                        {
                            radius = radius + 5.0f;
                            me->GetNearPoint2D(x, y, radius, direction);
                            me->SummonCreature(NPC_METEOR_STRIKE_1, x, y, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 20000);
                            me->GetNearPoint2D(x, y, radius, direction+M_PI);
                            me->SummonCreature(NPC_METEOR_STRIKE_1, x, y, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 20000);
                        }
                    };
                    {
                        direction = direction + M_PI/4;
                        float x, y, radius;
                        radius = 0.0f;
                        for (uint8 i = 0; i < RAID_MODE(TARGETS_10, TARGETS_25, TARGETS_10, TARGETS_25); ++i)
                        {
                            radius = radius + 5.0f;
                            me->GetNearPoint2D(x, y, radius, direction);
                            me->SummonCreature(NPC_METEOR_STRIKE_1, x, y, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 20000);
                            me->GetNearPoint2D(x, y, radius, direction+M_PI);
                            me->SummonCreature(NPC_METEOR_STRIKE_1, x, y, me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 20000);
                        }
                    };
                    setStage(3);
                    break;
                case 3:
                    if (MeteorImpactTimer <= diff)
                    {
                        DoCast(SPELL_METEOR_IMPACT);
                        me->ForcedDespawn();
                        MeteorImpactTimer = 0.5*IN_MILLISECONDS;
                    } else MeteorImpactTimer -= diff;
                    break;
                default:
                     break;
            }
        }
    };
};

///- mob_halion_flame

class mob_halion_flame : public CreatureScript
{
public:
    mob_halion_flame() : CreatureScript("mob_halion_flame") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_halion_flameAI(creature);
    }

    struct mob_halion_flameAI : public ScriptedAI
    {
        mob_halion_flameAI(Creature* creature) : ScriptedAI(creature)
        {
            Reset();
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetDisplayId(11686);
            me->SetRespawnDelay(7*DAY);
            SetCombatMovement(false);
            me->SetInCombatWithZone();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!me->HasAura(SPELL_METEOR_FLAME))
                DoCast(SPELL_METEOR_FLAME);
        }
    };
};

class go_halion_portal_twilight : public GameObjectScript
{
    public:

        go_halion_portal_twilight() : GameObjectScript("go_halion_portal_twilight") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            InstanceScript* instance = (InstanceScript*)go->GetInstanceScript();
            if(!instance) return false;
            player->CastSpell(player, SPELL_TWILIGHT_ENTER, false);
            return true;
        }
};

class go_halion_portal : public GameObjectScript
{
public:

    go_halion_portal() : GameObjectScript("go_halion_portal") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        InstanceScript* instance = (InstanceScript*)go->GetInstanceScript();
        if (!instance) return false;
        player->RemoveAurasDueToSpell(SPELL_TWILIGHT_ENTER);
        return true;
    }
};

class spell_halion_fiery_combustion : public SpellScriptLoader
{
public:
    spell_halion_fiery_combustion() : SpellScriptLoader("spell_halion_fiery_combustion") { }

    class spell_halion_fiery_combustion_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_halion_fiery_combustion_AuraScript)
        enum Spells
        {
            SPELL_MARK_OF_COMBUSTION = 74567,
            SPELL_COMBUSTION_EXPLODE = 74607
        };

        bool Validate(SpellEntry const* /*spellEntry*/)
        {
            if (!sSpellStore.LookupEntry(SPELL_MARK_OF_COMBUSTION))
                return false;
            if (!sSpellStore.LookupEntry(SPELL_COMBUSTION_EXPLODE))
                return false;
            return true;
        }

        void HandlePeriodicTick(AuraEffect const * /*aurEff*/)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_MARK_OF_COMBUSTION, true);
        }

        void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (Aura *mark = target->GetAura(SPELL_MARK_OF_COMBUSTION))
                {
                    int32 bp = 2000 * mark->GetStackAmount();
                    target->CastCustomSpell(target, SPELL_COMBUSTION_EXPLODE, &bp, 0, 0, true);
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_halion_fiery_combustion_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            OnEffectRemove += AuraEffectRemoveFn(spell_halion_fiery_combustion_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_halion_fiery_combustion_AuraScript();
    }
};

class spell_halion_soul_consumption : public SpellScriptLoader
{
public:
    spell_halion_soul_consumption() : SpellScriptLoader("spell_halion_soul_consumption") { }

    class spell_halion_soul_consumption_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_halion_soul_consumption_AuraScript)
        enum Spells
        {
            SPELL_MARK_OF_CONSUMPTION = 74795,
            SPELL_CONSUMPTION_EXPLODE = 74799
        };

        bool Validate(SpellEntry const* /*spellEntry*/)
        {
            if (!sSpellStore.LookupEntry(SPELL_MARK_OF_CONSUMPTION))
                return false;
            if (!sSpellStore.LookupEntry(SPELL_CONSUMPTION_EXPLODE))
                return false;
            return true;
        }

        void HandlePeriodicTick(AuraEffect const * /*aurEff*/)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, SPELL_MARK_OF_CONSUMPTION, true);
        }

        void HandleEffectRemove(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* target = GetTarget())
            {
                if (Aura* mark = target->GetAura(SPELL_MARK_OF_CONSUMPTION))
                {
                    int32 bp = 2000 * mark->GetStackAmount();
                    target->CastCustomSpell(target, SPELL_CONSUMPTION_EXPLODE, &bp, 0, 0, true);
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_halion_soul_consumption_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            OnEffectRemove += AuraEffectRemoveFn(spell_halion_soul_consumption_AuraScript::HandleEffectRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_halion_soul_consumption_AuraScript();
    }
};

void AddSC_boss_halion()
{
    new boss_halion();
    new boss_halion_twilight();
    new mob_halion_meteor();
    new mob_halion_flame();
    new mob_halion_orb();
    new mob_halion_controller();
    new mob_orb_rotation_focus();
    new mob_orb_carrier();
    new mob_soul_consumption();
    new mob_fiery_combustion();
    new go_halion_portal_twilight();
    new go_halion_portal();
    new spell_halion_fiery_combustion();
    new spell_halion_soul_consumption();
}
