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
    SPELL_CALL_FLAMECALLER = 74398,
    SPELL_CLEAVE_ARMOR = 74367,
    SPELL_IMTIMIDATING_ROAR = 74384,
    SPELL_LAVA_GOUT = 74394,
    SPELL_BLAST_NOVA = 74392,

    NPC_FLAMECALLER = 39814,
};

enum Equipment
{
    EQUIP_MAIN = 47156,
    EQUIP_OFFHAND = 51812,
    EQUIP_RANGED = EQUIP_NO_CHANGE,
    EQUIP_DONE = EQUIP_NO_CHANGE,
};

struct Locations
{
    float x, y, z, o;
};

static Locations SpawnLoc[]=
{
    {3008.552734f, 530.471680f, 89.195290f, 6.16f}, // 0 - zarithrian start point, o = 6,16
    {3014.313477f, 486.453735f, 89.255096f, 6.16f}, // 1 - Mob spawn 1
    {3025.324951f, 580.588501f, 88.593185f, 6.16f}, // 2 - Mob spawn 2
};

class boss_zarithrian : public CreatureScript
{
public:
    boss_zarithrian() : CreatureScript("boss_zarithrian") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_zarithrianAI(creature);
    }

    struct boss_zarithrianAI : public ScriptedAI
    {
        boss_zarithrianAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint32 SummonTimer;
        uint32 CleaveTimer;
        uint32 ImtimidatingTimer;

        void Reset()
        {
            if(!instance)
                return;

            SummonTimer = 45*IN_MILLISECONDS;
            CleaveTimer = urand(10*IN_MILLISECONDS,20*IN_MILLISECONDS);
            ImtimidatingTimer = urand(15*IN_MILLISECONDS,25*IN_MILLISECONDS);

            if (me->isAlive())
            {
                instance->SetData(TYPE_ZARITHRIAN, NOT_STARTED);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (
                 instance->GetData(TYPE_BALTHARUS) == DONE &&
                 instance->GetData(TYPE_RAGEFIRE) == DONE)
                 {
                     me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                 }
        }

        void KilledUnit(Unit* victim)
        {
        switch (urand(0,1)) {
            case 0:
                   DoScriptText(-1666201,me,victim);
                   break;
            case 1:
                   DoScriptText(-1666202,me,victim);
                   break;
            }
        }

        void JustReachedHome()
        {
            if (!instance) return;
            instance->SetData(TYPE_ZARITHRIAN, FAIL);
        }

        void JustSummoned(Creature* summoned)
        {
            if(!instance || !summoned) return;

            summoned->SetInCombatWithZone();
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 60, true))
            {
                summoned->AddThreat(target, 100.0f);
                summoned->GetMotionMaster()->MoveChase(target);
            }
        }

        void EnterCombat(Unit *who)
        {
            if(!instance) return;

            SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);
            instance->SetData(TYPE_ZARITHRIAN, IN_PROGRESS);
            DoScriptText(-1666200,me);
        }

        void JustDied(Unit *killer)
        {
            if(!instance) return;

            instance->SetData(TYPE_ZARITHRIAN, DONE);
            DoScriptText(-1666203,me);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (SummonTimer <= diff)
            {
                me->SummonCreature(NPC_FLAMECALLER, SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, SpawnLoc[1].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 120000);
                me->SummonCreature(NPC_FLAMECALLER, SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, SpawnLoc[2].o, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 120000);

                if (instance->instance->GetSpawnMode() == RAID_DIFFICULTY_25MAN_NORMAL || instance->instance->GetSpawnMode() == RAID_DIFFICULTY_25MAN_HEROIC)
                    DoCast(SPELL_CALL_FLAMECALLER);

                DoScriptText(-1666204,me);
                SummonTimer = 45*IN_MILLISECONDS;
            } else SummonTimer -= diff;

            if (CleaveTimer <= diff)
            {
                DoCast(SPELL_CLEAVE_ARMOR);
                CleaveTimer = urand(10*IN_MILLISECONDS,20*IN_MILLISECONDS);
            } else CleaveTimer -= diff;

            if (ImtimidatingTimer <= diff)
            {
                DoCast(SPELL_IMTIMIDATING_ROAR);
                ImtimidatingTimer = urand(15*IN_MILLISECONDS,25*IN_MILLISECONDS);
            } else ImtimidatingTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class mob_flamecaller_ruby : public CreatureScript
{
public:
    mob_flamecaller_ruby() : CreatureScript("mob_flamecaller_ruby") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_flamecaller_rubyAI(creature);
    }

    struct mob_flamecaller_rubyAI : public ScriptedAI
    {
        mob_flamecaller_rubyAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        uint32 LavaGoutTimer;
        uint32 BlastNovaTimer;

        void Reset()
        {
            if(!instance) return;

            LavaGoutTimer = urand(8*IN_MILLISECONDS,25*IN_MILLISECONDS);
            BlastNovaTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            me->SetRespawnDelay(7*DAY);
        }

        void UpdateAI(const uint32 diff)
        {
            if (instance && instance->GetData(TYPE_ZARITHRIAN) != IN_PROGRESS)
                me->ForcedDespawn();

            if (!UpdateVictim())
                return;

            if (LavaGoutTimer <= diff)
            {
                if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_LAVA_GOUT);
                LavaGoutTimer = urand(8*IN_MILLISECONDS,25*IN_MILLISECONDS);
            } else LavaGoutTimer -= diff;

            if (BlastNovaTimer <= diff)
            {
                DoCast(SPELL_BLAST_NOVA);
                BlastNovaTimer = urand(10*IN_MILLISECONDS,25*IN_MILLISECONDS);
            } else BlastNovaTimer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_zarithrian()
{
    new boss_zarithrian();
    new mob_flamecaller_ruby();
}