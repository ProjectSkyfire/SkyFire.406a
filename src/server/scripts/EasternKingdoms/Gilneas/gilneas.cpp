/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
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
#include "Unit.h"
#include "gilneas.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

//Phase 1
/*######
## npc_prince_liam_greymane_phase1
######*/

class npc_prince_liam_greymane_phase1 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase1() : CreatureScript("npc_prince_liam_greymane_phase1") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase1AI (creature);
    }

    struct npc_prince_liam_greymane_phase1AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase1AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tSay; //Time left for say
        uint32 cSay; //Current Say

        //Evade or Respawn
        void Reset()
        {
            tSay = DELAY_SAY_PRINCE_LIAM_GREYMANE; //Reset timer
            cSay = 1; //Start from 1
        }

        //Timed events
        void UpdateAI(const uint32 diff)
        {
            //Out of combat
            if (!me->getVictim())
            {
                //Timed say
                if (tSay <= diff)
                {
                    switch (cSay)
                    {
                        default:
                        case 1:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_1, me);
                            cSay++;
                            break;
                        case 2:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_2, me);
                            cSay++;
                            break;
                        case 3:
                            DoScriptText(SAY_PRINCE_LIAM_GREYMANE_3, me);
                            cSay = 1; //Reset to 1
                            break;
                    }

                    tSay = DELAY_SAY_PRINCE_LIAM_GREYMANE; //Reset the timer
                }
                else
                {
                    tSay -= diff;
                }
                return;
            }
        }
    };
};

/*######
## npc_gilneas_city_guard_phase1
######*/

class npc_gilneas_city_guard_phase1 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase1() : CreatureScript("npc_gilneas_city_guard_phase1") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase1AI (creature);
    }

    struct npc_gilneas_city_guard_phase1AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase1AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tSay; //Time left for say

        //Evade or Respawn
        void Reset()
        {
            if (me->GetGUIDLow() == 3486400)
                tSay = DELAY_SAY_GILNEAS_CITY_GUARD_GATE; //Reset timer
        }

        void UpdateAI(const uint32 diff)
        {
            //Out of combat and
            if (me->GetGUIDLow() == 3486400)
            {
                //Timed say
                if (tSay <= diff)
                {
                    //Random say
                    DoScriptText(RAND(
                        SAY_GILNEAS_CITY_GUARD_GATE_1,
                        SAY_GILNEAS_CITY_GUARD_GATE_2,
                        SAY_GILNEAS_CITY_GUARD_GATE_3),
                    me);

                    tSay = DELAY_SAY_GILNEAS_CITY_GUARD_GATE; //Reset timer
                }
                else
                {
                    tSay -= diff;
                }
            }
        }
    };
};

//Phase 2
/*######
## npc_gilneas_city_guard_phase2
######*/

class npc_gilneas_city_guard_phase2 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase2() : CreatureScript("npc_gilneas_city_guard_phase2") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase2AI (creature);
    }

    struct npc_gilneas_city_guard_phase2AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase2AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tAnimate, tSound, dmgCount, tSeek;
        bool playSound;

        void Reset()
        {
            tAnimate   = DELAY_ANIMATE;
            dmgCount   = 0;
            tSound     = DELAY_SOUND;
            playSound  = false;
            tSeek      = urand(1000, 2000);
        }

        void DamageTaken(Unit* who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_RAMPAGING_WORGEN_1)
                dmgCount ++;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tSeek <= diff)
            {
                if ((me->isAlive()) && (!me->isInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f)))
                    if (Creature* enemy = me->FindNearestCreature(NPC_RAMPAGING_WORGEN_1, 16.0f, true))
                        me->AI()->AttackStart(enemy);
                tSeek = urand(1000, 2000); //optimize cpu load, seeking only sometime between 1 and 2 seconds
            }
            else tSeek -= diff;

            if (!UpdateVictim())
                return;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_FLESH);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (playSound == true)
                tSound -= diff;

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else
                if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else
                if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                    playSound = true;
                    tAnimate = DELAY_ANIMATE;
                }
                else
                    tAnimate -= diff;
            }
        }
    };
};

/*######
## npc_prince_liam_greymane_phase2
######*/

class npc_prince_liam_greymane_phase2 : public CreatureScript
{
public:
    npc_prince_liam_greymane_phase2() : CreatureScript("npc_prince_liam_greymane_phase2") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase2AI (creature);
    }

    struct npc_prince_liam_greymane_phase2AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase2AI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tAnimate, tSound, dmgCount, tYell, tSeek;
        bool playSound, doYell;

        void Reset()
        {
            tAnimate  = DELAY_ANIMATE;
            dmgCount  = 0;
            tSound    = DELAY_SOUND;
            playSound = false;
            tSeek     = urand(1000, 2000);
            doYell    = true;
            tYell     = DELAY_YELL_PRINCE_LIAM_GREYMANE;
        }

        //There is NO phase shift here!!!!

		void DamageTaken(Unit * who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_RAMPAGING_WORGEN_1)
                dmgCount ++;
        }

        void UpdateAI(const uint32 diff)
        {
            //If creature has no target
            if (!UpdateVictim())
            {
                if (tSeek <= diff)
                {
                    //Find worgen nearby
                    if (me->isAlive() && !me->isInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f))
                        if (Creature* enemy = me->FindNearestCreature(NPC_RAMPAGING_WORGEN_1, 16.0f, true))
                            me->AI()->AttackStart(enemy);
                    tSeek = urand(1000, 2000);//optimize cpu load
                }
                else tSeek -= diff;

                //Yell only once after Reset()
                if (doYell)
                {
                    //Yell Timer
                    if (tYell <= diff)
                    {
                        //Random yell
                        DoScriptText(RAND(
                            YELL_PRINCE_LIAM_GREYMANE_1,
                            YELL_PRINCE_LIAM_GREYMANE_2,
                            YELL_PRINCE_LIAM_GREYMANE_3,
                            YELL_PRINCE_LIAM_GREYMANE_4,
                            YELL_PRINCE_LIAM_GREYMANE_5),
                        me);

                        doYell = false;
                    }
                    else
                        tYell -= diff;
                }
            }
            else
            {
                //Play sword attack sound
                if (tSound <= diff)
                {
                    me->PlayDistanceSound(SOUND_SWORD_FLESH);
                    tSound = DELAY_SOUND;
                    playSound = false;
                }

                if (playSound == true) tSound -= diff;

                //Attack
                if (dmgCount < 2)
                    DoMeleeAttackIfReady();
                else
                    if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
                else
                    if (me->getVictim()->isPet()) dmgCount = 0;
                else
                {
                    if (tAnimate <= diff)
                    {
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        playSound = true;
                        tAnimate = DELAY_ANIMATE;
                    }
                    else
                        tAnimate -= diff;
                }
                //Stop yell timer on combat
                doYell = false;
            }
        }
    };
};

/*######
## npc_rampaging_worgen
######*/

class npc_rampaging_worgen : public CreatureScript
{
public:
    npc_rampaging_worgen() : CreatureScript("npc_rampaging_worgen") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgenAI (creature);
    }

    struct npc_rampaging_worgenAI : public ScriptedAI
    {
        npc_rampaging_worgenAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tEnrage;
        uint32 dmgCount;
        uint32 tAnimate;
        uint32 tSound;
        bool playSound, willCastEnrage;

        void Reset()
        {
            tEnrage    = 0;
            dmgCount   = 0;
            tAnimate   = DELAY_ANIMATE;
            tSound     = DELAY_SOUND;
            playSound  = false;
            willCastEnrage = urand(0, 1);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_GILNEAS_CITY_GUARD || target->GetEntry() == NPC_PRINCE_LIAM_GREYMANE)
                dmgCount++;
        }

        void DamageTaken(Unit* who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (tEnrage <= diff && willCastEnrage)
            {
                if (me->GetHealthPct() <= 30)
                {
                    me->MonsterTextEmote(-106, 0);
                    DoCast(me, SPELL_ENRAGE);
                    tEnrage = CD_ENRAGE;
                }
            }
            else tEnrage -= diff;

            //play attack sound
            if (playSound == true)
                tSound -= diff;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_PLATE);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else
                if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else
                if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACKUNARMED);
                    tAnimate = DELAY_ANIMATE;
                    playSound = true;
                }
                else
                    tAnimate -= diff;
            }
        }
    };
};

class npc_rampaging_worgen2 : public CreatureScript
{
public:
    npc_rampaging_worgen2() : CreatureScript("npc_rampaging_worgen2") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgen2AI (creature);
    }

    struct npc_rampaging_worgen2AI : public ScriptedAI
    {
        npc_rampaging_worgen2AI(Creature* creature) : ScriptedAI(creature) {}

        uint16 tRun, tEnrage;
        bool onceRun, willCastEnrage;
        float x, y, z;

        void JustRespawned()
        {
            tEnrage = 0;
            tRun = 500;
            onceRun = true;
            x = me->m_positionX + cos(me->_orientation)*8;
            y = me->m_positionY + sin(me->_orientation)*8;
            z = me->m_positionZ;
            willCastEnrage = urand(0, 1);
        }

        void UpdateAI(const uint32 diff)
        {
            if (tRun <= diff && onceRun)
            {
                me->GetMotionMaster()->MoveCharge(x, y, z, 8);
                onceRun = false;
            }
            else
                tRun -= diff;

            if (!UpdateVictim())
                return;

            if (tEnrage <= diff)
            {
                if (me->GetHealthPct() <= 30 && willCastEnrage)
                {
                    me->MonsterTextEmote(-106, 0);
                    DoCast(me, SPELL_ENRAGE);
                    tEnrage = CD_ENRAGE;
                }
            }
            else
                tEnrage -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## go_merchant_square_door
######*/

class go_merchant_square_door : public GameObjectScript
{
public:
    go_merchant_square_door() : GameObjectScript("go_merchant_square_door") {}

    float x, y, z, wx, wy, angle, tQuestCredit;
    bool opened;
    uint8 spawnKind;
    Player* aPlayer;
    GameObject* go;
    uint32 DoorTimer;

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_EVAC_MERC_SQUA) == QUEST_STATUS_INCOMPLETE && go->GetGoState() == GO_STATE_READY)
        {
            aPlayer          = player;
            opened           = 1;
            tQuestCredit     = 2500;
            go->SetGoState(GO_STATE_ACTIVE);
            DoorTimer = DOOR_TIMER;
            spawnKind = urand(1, 3); //1, 2=citizen, 3=citizen&worgen (66%, 33%)
            angle = go->GetOrientation();
            x = go->GetPositionX()-cos(angle)*2;
            y = go->GetPositionY()-sin(angle)*2;
            z = go->GetPositionZ();
            wx = x-cos(angle)*2;
            wy = y-sin(angle)*2;

            if (spawnKind < 3)
            {
                if (Creature* spawnedCreature = go->SummonCreature(NPC_FRIGHTENED_CITIZEN_1, x, y, z, angle, TEMPSUMMON_TIMED_DESPAWN, SUMMON1_TTL))
                {
                    spawnedCreature->SetPhaseMask(6, 1);
                    spawnedCreature->Respawn(1);
                }
            }
            else
            {
                if (Creature* spawnedCreature = go->SummonCreature(NPC_FRIGHTENED_CITIZEN_2, x, y, z, angle, TEMPSUMMON_TIMED_DESPAWN, SUMMON1_TTL))
                {
                    spawnedCreature->SetPhaseMask(6, 1);
                    spawnedCreature->Respawn(1);
                }
            }
            return true;
        }
        return false;
    }

    void OnUpdate(GameObject* go, uint32 diff)
    {
        if (opened == 1)
        {
            if (tQuestCredit <= ((float)diff/8))
            {
                opened = 0;
                aPlayer->KilledMonsterCredit(35830, 0);
                if (spawnKind == 3)
                {
                    if (Creature* spawnedCreature = go->SummonCreature(NPC_RAMPAGING_WORGEN_2, wx, wy, z, angle, TEMPSUMMON_TIMED_DESPAWN, SUMMON1_TTL))
                    {
                        spawnedCreature->SetPhaseMask(6, 1);
                        spawnedCreature->Respawn(1);
                        spawnedCreature->getThreatManager().resetAllAggro();
                        aPlayer->AddThreat(spawnedCreature, 1.0f);
                        spawnedCreature->AddThreat(aPlayer, 1.0f);
                    }
                }
            }
            else tQuestCredit -= ((float)diff/8);
        }
        if (DoorTimer <= diff)
            {
                if (go->GetGoState() == GO_STATE_ACTIVE)
                    go->SetGoState(GO_STATE_READY);

                DoorTimer = DOOR_TIMER;
            }
        else
            DoorTimer -= diff;
    }
};

/*######
## npc_frightened_citizen
######*/

struct Point
{
    float x, y;
};

struct WayPointID
{
    int pathID, pointID;
};

struct Paths
{
    uint8 pointsCount[8]; //pathID, pointsCount
    Point paths[8][10];   //pathID, pointID, Point
};

class npc_frightened_citizen : public CreatureScript
{
public:
    npc_frightened_citizen() : CreatureScript("npc_frightened_citizen") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frightened_citizenAI (creature);
    }

    struct npc_frightened_citizenAI : public ScriptedAI
    {
        npc_frightened_citizenAI(Creature* creature) : ScriptedAI(creature) {}

        uint16 tRun, tRun2, tSay;
        bool onceRun, onceRun2, onceGet, onceSay;
        float x, y, z;
        WayPointID nearestPointID;
        Paths paths;

        Paths LoadPaths()
        {
            QueryResult result[PATHS_COUNT];
            result[0] = WorldDatabase.Query("SELECT `id`, `point`, `position_x`, `position_y` FROM waypoint_data WHERE id = 349810 ORDER BY `point`");
            result[1] = WorldDatabase.Query("SELECT `id`, `point`, `position_x`, `position_y` FROM waypoint_data WHERE id = 349811 ORDER BY `point`");
            if (result[0]) paths.pointsCount[0] = result[0]->GetRowCount();
            else
            {
                sLog->outError("waypoint_data for frightened citizen missing");
                return paths;  ///- this needs correctly fixed! -truncation from double to float (warnings, that can be fixed)
            }
            if (result[1]) paths.pointsCount[1] = result[1]->GetRowCount();
            else
            {
                sLog->outError("waypoint_data for frightened citizen missing");
                return paths;
            }
            uint8 j;
            for (uint8 i = 0; i < PATHS_COUNT; i ++)
            {
                j = 0;
                do
                {
                    Field* Fields = result[i]->Fetch();
                    paths.paths[i][j].x = Fields[2].GetFloat();
                    paths.paths[i][j].y = Fields[3].GetFloat();
                    j++;
                }
                while (result[i]->NextRow());
            }
            return paths;
        }

        void MultiDistanceMeter(Point *p, uint8 pointsCount, float *dist)
        {
            for (uint8 i = 0; i <= (pointsCount-1); i++)
                dist[i] = me->GetDistance2d(p[i].x, p[i].y);
        }

        WayPointID GetNearestPoint(Paths paths)
        {
            WayPointID nearestPointID;
            float dist[PATHS_COUNT][10], lowestDists[PATHS_COUNT];
            uint8 nearestPointsID[PATHS_COUNT], lowestDist;
            for (uint8 i = 0; i <= PATHS_COUNT-1; i++)
            {
                MultiDistanceMeter(paths.paths[i], paths.pointsCount[i], dist[i]);
                for (uint8 j = 0; j <= paths.pointsCount[i]-1; j++)
                {
                    if (j == 0)
                    {
                        lowestDists[i] = dist[i][j];
                        nearestPointsID[i] = j;
                    }
                    else if (lowestDists[i] > dist[i][j])
                    {
                        lowestDists[i] = dist[i][j];
                        nearestPointsID[i] = j;
                    }
                }
            }
            for (uint8 i = 0; i < PATHS_COUNT; i++)
            {
                if (i == 0)
                {
                    lowestDist = lowestDists[i];
                    nearestPointID.pointID = nearestPointsID[i];
                    nearestPointID.pathID = i;
                }
                else if (lowestDist > lowestDists[i])
                {
                    lowestDist = lowestDists[i];
                    nearestPointID.pointID = nearestPointsID[i];
                    nearestPointID.pathID = i;
                }
            }
            return nearestPointID;
        }

        void JustRespawned()
        {
            paths          = LoadPaths();
            tRun           = 500;
            tRun2          = 2500;
            tSay           = 1000;
            onceRun = onceRun2 = onceSay = onceGet = true;
            x = me->m_positionX + cos(me->_orientation)*5;
            y = me->m_positionY + sin(me->_orientation)*5;
            z = me->m_positionZ;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tRun <= diff && onceRun)
            {
                me->GetMotionMaster()->MoveCharge(x, y, z, 8);
                onceRun = false;
            }
            else
                tRun -= diff;

            if (tSay <= diff && onceSay)
            {
                if (me->GetEntry() == NPC_FRIGHTENED_CITIZEN_1)
                    DoScriptText(RAND(SAY_CITIZEN_1, SAY_CITIZEN_2, SAY_CITIZEN_3, SAY_CITIZEN_4, SAY_CITIZEN_5, SAY_CITIZEN_6, SAY_CITIZEN_7, SAY_CITIZEN_8), me);
                else
                    DoScriptText(RAND(SAY_CITIZEN_1b, SAY_CITIZEN_2b, SAY_CITIZEN_3b, SAY_CITIZEN_4b, SAY_CITIZEN_5b), me);
                onceSay = false;
            }
            else tSay -= diff;

            if (tRun2 <= diff)
            {
                if (onceGet)
                {
                    nearestPointID = GetNearestPoint(paths);
                    onceGet = false;
                }
                else
                {
                    if (me->GetDistance2d(paths.paths[nearestPointID.pathID][nearestPointID.pointID].x, paths.paths[nearestPointID.pathID][nearestPointID.pointID].y) > 1)
                        me->GetMotionMaster()->MoveCharge(paths.paths[nearestPointID.pathID][nearestPointID.pointID].x, paths.paths[nearestPointID.pathID][nearestPointID.pointID].y, z, 8);
                    else
                        nearestPointID.pointID ++;
                    if (nearestPointID.pointID >= paths.pointsCount[nearestPointID.pathID]) me->DespawnOrUnsummon();
                }
            }
            else tRun2 -= diff;
        }
    };
};

//Phase 4
/*######
## npc_bloodfang_worgen
######*/

class npc_bloodfang_worgen : public CreatureScript
{
public:
    npc_bloodfang_worgen() : CreatureScript("npc_bloodfang_worgen") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bloodfang_worgenAI (creature);
    }

    struct npc_bloodfang_worgenAI : public ScriptedAI
    {
        npc_bloodfang_worgenAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tEnrage;
        uint32 dmgCount;
        uint32 tAnimate;
        uint32 tSound;
        bool playSound, willCastEnrage;

        void Reset()
        {
            tEnrage    = 0;
            dmgCount   = 0;
            tAnimate   = DELAY_ANIMATE;
            tSound     = DELAY_SOUND;
            playSound  = false;
            willCastEnrage = urand(0, 1);
        }

        void DamageDealt(Unit* target, uint32 &damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_GILNEAN_ROYAL_GUARD || target->GetEntry() == NPC_SERGEANT_CLEESE || target->GetEntry() == NPC_MYRIAM_SPELLWALKER)
                dmgCount++;
        }

        void DamageTaken(Unit* who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (tEnrage <= diff && willCastEnrage)
            {
                if (me->GetHealthPct() <= 30)
                {
                    me->MonsterTextEmote(-106, 0);
                    DoCast(me, SPELL_ENRAGE);
                    tEnrage = CD_ENRAGE;
                }
            }
            else tEnrage -= diff;

            //play attack sound
            if (playSound == true)
                tSound -= diff;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_PLATE);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else
                if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else
                if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACKUNARMED);
                    tAnimate = DELAY_ANIMATE;
                    playSound = true;
                }
                else
                tAnimate -= diff;
            }
        }
    };
};

/*######
## npc_sergeant_cleese
######*/

class npc_sergeant_cleese : public CreatureScript
{
public:
    npc_sergeant_cleese() : CreatureScript("npc_sergeant_cleese") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sergeant_cleeseAI (creature);
    }

    struct npc_sergeant_cleeseAI : public ScriptedAI
    {
        npc_sergeant_cleeseAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tAnimate, tSound, dmgCount, tSeek;
        bool playSound;

        void Reset()
        {
            tAnimate   = DELAY_ANIMATE;
            dmgCount   = 0;
            tSound     = DELAY_SOUND;
            playSound  = false;
            tSeek      = urand(1000, 2000);
        }

        void DamageTaken(Unit* who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_BLOODFANG_WORGEN)
                dmgCount ++;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tSeek <= diff)
            {
                if ((me->isAlive()) && (!me->isInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f)))
                    if (Creature* enemy = me->FindNearestCreature(NPC_BLOODFANG_WORGEN, 10.0f, true))
                        me->AI()->AttackStart(enemy);
                tSeek = urand(1000, 2000); //optimize cpu load, seeking only sometime between 1 and 2 seconds
            }
            else tSeek -= diff;

            if (!UpdateVictim())
                return;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_FLESH);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (playSound == true)
                tSound -= diff;

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else
                if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else
                if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                    playSound = true;
                    tAnimate = DELAY_ANIMATE;
                }
                else
                    tAnimate -= diff;
            }
        }
    };
};

/*######
## npc_gilnean_royal_guard
######*/

class npc_gilnean_royal_guard : public CreatureScript
{
public:
    npc_gilnean_royal_guard() : CreatureScript("npc_gilnean_royal_guard") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilnean_royal_guardAI (creature);
    }

    struct npc_gilnean_royal_guardAI : public ScriptedAI
    {
        npc_gilnean_royal_guardAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 tAnimate, tSound, dmgCount, tSeek;
        bool playSound;

        void Reset()
        {
            tAnimate   = DELAY_ANIMATE;
            dmgCount   = 0;
            tSound     = DELAY_SOUND;
            playSound  = false;
            tSeek      = urand(1000, 2000);
        }

        void DamageTaken(Unit* who, uint32 &Damage)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                who->AddThreat(me, 1.0f);
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
            else if (who->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(who, 1.0f);
                me->AI()->AttackStart(who);
                dmgCount = 0;
            }
        }

        void DamageDealt(Unit* target, uint32 &damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_BLOODFANG_WORGEN)
                dmgCount ++;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tSeek <= diff)
            {
                if ((me->isAlive()) && (!me->isInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f)))
                    if (Creature* enemy = me->FindNearestCreature(NPC_BLOODFANG_WORGEN, 16.0f, true))
                        me->AI()->AttackStart(enemy);
                tSeek = urand(1000, 2000); //optimize cpu load, seeking only sometime between 1 and 2 seconds
            }
            else tSeek -= diff;

            if (!UpdateVictim())
                return;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_FLESH);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (playSound == true)
                tSound -= diff;

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else
                if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else
                if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                    playSound = true;
                    tAnimate = DELAY_ANIMATE;
                }
                else
                    tAnimate -= diff;
            }
        }
    };
};

/*######
## npc_mariam_spellwalker
######*/

class npc_mariam_spellwalker : public CreatureScript
{
public:
    npc_mariam_spellwalker() : CreatureScript("npc_mariam_spellwalker") {}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_mariam_spellwalkerAI (creature);
    }

    struct npc_mariam_spellwalkerAI : public ScriptedAI
    {
        npc_mariam_spellwalkerAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 dmgCount, tSeek;

        void Reset()
        {
            dmgCount = 0;
            tSeek = urand(1000, 2000);
        }

        void DamageDealt(Unit* target, uint32 &damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_BLOODFANG_WORGEN)
                dmgCount ++;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tSeek <= diff)
            {
                if ((me->isAlive()) && (!me->isInCombat() && (me->GetDistance2d(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()) <= 1.0f)))
                    if (Creature* enemy = me->FindNearestCreature(NPC_BLOODFANG_WORGEN, 5.0f, true))
                        me->AI()->AttackStart(enemy); //She should really only grab agro when npc Cleese is not there, so we will keep this range small
                tSeek = urand(1000, 2000); //optimize cpu load, seeking only sometime between 1 and 2 seconds
            }
            else tSeek -= diff;

            if (!UpdateVictim())
                return;

            if (dmgCount < 2)
                DoSpellAttackIfReady(SPELL_FROSTBOLT_VISUAL_ONLY); //Dummy spell, visual only to prevent getting agro (Blizz-like)
        }
    };
};

/*######
## npc_lord_darius_crowley_c2
######*/
class npc_lord_darius_crowley_c2 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c2() : CreatureScript("npc_lord_darius_crowley_c2") {}

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        for (int i = 0; i < 30; i++)
            player->KilledMonsterCredit(35582, 0);

        player->TeleportTo(654, -1533.76f, 1582.44f, 26.54f, 4.05f);
        return true;
    }
};

/*######
## npc_lord_darius_crowley_c3
######*/
class npc_lord_darius_crowley_c3 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c3() : CreatureScript("npc_lord_darius_crowley_c3") {}

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14222)
        {
            player->SendMovieStart(21);
            player->CastSpell(player, 93477, true);
            player->RemoveAurasDueToSpell(72870);
            player->CastSpell(player, 76642, true);
            player->CastSpell(player, 68630, true);
            player->CastSpell(player, 72788, true);
            player->setInWorgenForm();

            player->CastSpell(player, 69123, true);
            player->CastSpell(player, 68632, true);
            player->CastSpell(player, 68634, true);

            WorldLocation loc;
            loc.m_mapId       = 654;
            loc.m_positionX   = -1818.4f;
            loc.m_positionY   = 2294.25f;
            loc.m_positionZ   = 42.2135f;
            loc._orientation  = 3.14f;

            player->SetHomebind(loc, 4786);
        }
        return true;
    }
};

/*######
## npc_king_genn_greymane_c2
######*/
class npc_king_genn_greymane_c2 : public CreatureScript
{
public:
    npc_king_genn_greymane_c2() : CreatureScript("npc_king_genn_greymane_c2") {}

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        player->RemoveAurasDueToSpell(68630);
        player->RemoveAurasDueToSpell(76642);
        player->CastSpell(player, 68481, true);
        return true;
    }
};

/*######
## npc_greymane_horse
######*/
class npc_greymane_horse : public CreatureScript
{
public:
    npc_greymane_horse() : CreatureScript("npc_greymane_horse") { }

    struct npc_greymane_horseAI : public npc_escortAI
    {
        npc_greymane_horseAI(Creature* creature) : npc_escortAI(creature) {}

        uint32 krennansay;
        bool AfterJump;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
             krennansay = 500;//Check every 500ms initially
             AfterJump = false;
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (apply)
                {
                    Start(false, true, who->GetGUID());
                }
            }
            else if (who->GetTypeId() == TYPEID_UNIT)
            {
                SetEscortPaused(false);
            }
        }

        void WaypointReached(uint32 i)
        {
            Player* player = GetPlayerForEscort();

            switch(i)
            {
                case 5:
                    me->GetMotionMaster()->MoveJump(-1679.089f,1348.42f,15.31f,25.0f, 15.0f);
                    AfterJump = true;
                    if (me->GetVehicleKit()->HasEmptySeat(1))
                    {
                        SetEscortPaused(true);
                        player->SetClientControl(me, 0);
                        break;
                    }
                    else
                    break;
                case 12:
                    player->ExitVehicle();
                    player->SetClientControl(me, 1);
                    break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Player* player = GetPlayerForEscort())
               player->FailQuest(QUEST_SAVE_KRENNAN_ARANAS);
        }

        void OnCharmed(bool /*apply*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            npc_escortAI::UpdateAI(diff);
            Player* player = GetPlayerForEscort();

            if (AfterJump && (me->IsWithinDist3d(-1679.089f, 1348.42f, 15.31f, 1.0f)))
            {
                Talk(0,player->GetGUID());
                AfterJump = false;
            }

            if (krennansay <=diff)
            {
                if (Creature *krennan = me->FindNearestCreature(3871227, 30, true))
                {
                    krennansay = urand(4000,7000);//Repeat every 4 to 7 seconds
                }
            }
            else
                krennansay -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_greymane_horseAI (creature);
    }
};

/*######
## npc_krennan_aranas_c2
######*/
class npc_krennan_aranas_c2 : public CreatureScript
{
public:
    npc_krennan_aranas_c2() : CreatureScript("npc_krennan_aranas_c2") { }

    struct npc_krennan_aranas_c2AI : public ScriptedAI
    {
        npc_krennan_aranas_c2AI(Creature* creature) : ScriptedAI(creature) {}

        bool Say;
        bool Move;
        bool Cast;
        bool KrennanDead;
        uint32 SayTimer;

        void AttackStart(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}
        void EnterEvadeMode() {}

        void Reset()
        {
            Say = false;
            Move = true;
            Cast = true;
            KrennanDead = false;
            SayTimer = 500;
        }

        void UpdateAI(const uint32 diff)
        {
            if (Creature *krennan = me->FindNearestCreature(3871227, 50))
            {
                if (!KrennanDead)
                {
                    krennan->ForcedDespawn(0);
                    KrennanDead = true;
                }
            }

            if (Creature *horse = me->FindNearestCreature(35905, 20.0f))//Jump onto horse in seat 2
            {
                if (Cast)
                {
                    DoCast(horse, 84275, true);
                }

                if (me->HasAura(84275))
                {
                    Cast = false;
                }
            }

            if (!me->HasAura(84275) && Move)
            {
                me->NearTeleportTo(KRENNAN_END_X, KRENNAN_END_Y, KRENNAN_END_Z, KRENNAN_END_O);
                Say = true;
                Move = false;
                SayTimer = 500;
            }

            if (Say && SayTimer <= diff)
            {
                DoScriptText(SAY_KRENNAN_C2, me);
                me->ForcedDespawn(6000);
                Say = false;
            }
            else
                SayTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_krennan_aranas_c2AI(creature);
    }
};

class spell_keg_placed : public SpellScriptLoader
{
    public:
        spell_keg_placed() : SpellScriptLoader("spell_keg_placed") {}

        class spell_keg_placed_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_keg_placed_AuraScript);

            uint32 tick, tickcount;

            void HandleEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                tick = urand(1, 4);
                tickcount = 0;
            }

            void HandlePeriodic(AuraEffect const* aurEff)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                {
                    if (tickcount > tick)
                    {
                        if (caster->GetTypeId() != TYPEID_PLAYER)
                            return;

                        caster->ToPlayer()->KilledMonsterCredit(36233, 0);
                        if (Unit* target = GetTarget())
                            target->Kill(target);
                    }
                    tickcount++;
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_keg_placed_AuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_keg_placed_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_keg_placed_AuraScript();
        }
};

void AddSC_gilneas()
{
    new npc_gilneas_city_guard_phase1();
    new npc_prince_liam_greymane_phase1();
    new npc_gilneas_city_guard_phase2();
    new npc_prince_liam_greymane_phase2();
    new npc_rampaging_worgen();
    new npc_rampaging_worgen2();
    new go_merchant_square_door();
    new npc_sergeant_cleese();
    new npc_bloodfang_worgen();
    new npc_frightened_citizen();
    new npc_gilnean_royal_guard();
    new npc_mariam_spellwalker();
    new npc_lord_darius_crowley_c2();
    new npc_lord_darius_crowley_c3();
    new npc_king_genn_greymane_c2();
    new spell_keg_placed();
    new npc_greymane_horse();
    new npc_krennan_aranas_c2();
}