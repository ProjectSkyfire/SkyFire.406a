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

/* ScriptData
Name: Gilneas City
%Complete: 10
Comment:
Category: Gilneas
EndScriptData */

/* ContentData
TODO
EndContentData */

#include "ScriptPCH.h"

//Phase 1
enum eGilneasCityPhase1
{
    //Quests
    QUEST_LOCKDOWN = 14078,

    //Spells
    SPELL_PHASE_2 = 59073,

    //Say
    SAY_PRINCE_LIAM_GREYMANE_1 = -1638000,
    SAY_PRINCE_LIAM_GREYMANE_2 = -1638001,
    SAY_PRINCE_LIAM_GREYMANE_3 = -1638002,
    DELAY_SAY_PRINCE_LIAM_GREYMANE = 20000, //20 seconds repetition time

    SAY_PANICKED_CITIZEN_1 = -1638016,
    SAY_PANICKED_CITIZEN_2 = -1638017,
    SAY_PANICKED_CITIZEN_3 = -1638018,
    SAY_PANICKED_CITIZEN_4 = -1638019,
    #define DELAY_EMOTE_PANICKED_CITIZEN urand(5000, 15000) //5-15 second time
    #define DELAY_SAY_PANICKED_CITIZEN urand(30000, 120000) //30sec - 1.5min

    SAY_GILNEAS_CITY_GUARD_GATE_1 = -1638022,
    SAY_GILNEAS_CITY_GUARD_GATE_2 = -1638023,
    SAY_GILNEAS_CITY_GUARD_GATE_3 = -1638024,
    #define DELAY_SAY_GILNEAS_CITY_GUARD_GATE urand(30000, 120000) //30sec - 1.5min
};
//Phase 2
enum eGilneasCityPhase2
{
    //Sounds
    SOUND_SWORD_FLESH = 143,
    SOUND_SWORD_PLATE = 147,
    DELAY_SOUND = 500,
    DELAY_ANIMATE = 2000,

    //Spells
    SPELL_PHASE_4 = 59074,

    //NPCs
    NPC_PRINCE_LIAM_GREYMANE = 34913,
    NPC_GILNEAS_CITY_GUARD = 34916,
    NPC_RAMPAGING_WORGEN_1 = 34884,
    NPC_RAMPAGING_WORGEN_2 = 35660,
    NPC_FRIGHTENED_CITIZEN_1 = 34981,
    NPC_FRIGHTENED_CITIZEN_2 = 35836,

    //Say
    YELL_PRINCE_LIAM_GREYMANE_1 = -1638025,
    YELL_PRINCE_LIAM_GREYMANE_2 = -1638026,
    YELL_PRINCE_LIAM_GREYMANE_3 = -1638027,
    YELL_PRINCE_LIAM_GREYMANE_4 = -1638028,
    YELL_PRINCE_LIAM_GREYMANE_5 = -1638029,
    DELAY_YELL_PRINCE_LIAM_GREYMANE = 2000,
};

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
        npc_prince_liam_greymane_phase1AI(Creature *c) : ScriptedAI(c) {}

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
                    switch(cSay)
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
## npc_panicked_citizen
######*/

uint32 guid_panicked_nextsay = 0; //GUID of the Panicked Citizen that will say random text, this is to prevent more than 1 npc speaking
uint32 tSay_panicked = DELAY_SAY_PANICKED_CITIZEN; //Time left to say
class npc_panicked_citizen : public CreatureScript
{
public:
    npc_panicked_citizen() : CreatureScript("npc_panicked_citizen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_panicked_citizenAI (creature);
    }

    struct npc_panicked_citizenAI : public ScriptedAI
    {
        npc_panicked_citizenAI(Creature *c) : ScriptedAI(c) {}

        uint32 tEmote; //Time left for doing an emote

        //Evade or Respawn
        void Reset()
        {
            if (me->GetPhaseMask() == 1)
            {
                tEmote = DELAY_EMOTE_PANICKED_CITIZEN; //Reset timer
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0); //Reset emote state
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //Out of combat and in Phase 1
            if (!me->getVictim() && me->GetPhaseMask() == 1)
            {
                //Timed emote
                if(tEmote <= diff)
                {
                    //Do random emote (1, 5, 18, 20, 430)
                    me->HandleEmoteCommand(RAND(
                        EMOTE_ONESHOT_TALK,
                        EMOTE_ONESHOT_EXCLAMATION,
                        EMOTE_ONESHOT_CRY,
                        EMOTE_ONESHOT_BEG,
                        EMOTE_ONESHOT_COWER));

                    tEmote = DELAY_EMOTE_PANICKED_CITIZEN; //Reset timer
                }
                else
                {
                    tEmote -= diff;
                }

                //Randomly select an NPC to say the next random text
                if(!guid_panicked_nextsay)
                {
                    if(urand(0,1))
                    {
                        guid_panicked_nextsay = me->GetGUIDLow();
                    }
                }

                //If this is the selected npc to say
                if(guid_panicked_nextsay == me->GetGUIDLow())
                {
                    //Timed say
                    if(tSay_panicked <= diff)
                    {
                        //Say random
                        DoScriptText(RAND(
                            SAY_PANICKED_CITIZEN_1,
                            SAY_PANICKED_CITIZEN_2,
                            SAY_PANICKED_CITIZEN_3,
                            SAY_PANICKED_CITIZEN_4),
                        me);

                        guid_panicked_nextsay = 0; //Reset Selected next NPC
                        tSay_panicked = DELAY_SAY_PANICKED_CITIZEN; //Reset timer
                    }
                    else
                    {
                        tSay_panicked -= diff;
                    }
                }
            }
        }
    };
};

/*######
## npc_panicked_citizen_2
######*/

enum ePanicked_citizen_2
{
    #define PATHS_COUNT_PANICKED_CITIZEN 8
};

struct Waypoint
{
    uint32 pathID;
    float x, y;
};

class npc_panicked_citizen_2 : public CreatureScript
{
public:
    npc_panicked_citizen_2() : CreatureScript("npc_panicked_citizen_2") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_panicked_citizen_2AI (creature);
    }

    struct npc_panicked_citizen_2AI : public ScriptedAI
    {
        npc_panicked_citizen_2AI(Creature *c) : ScriptedAI(c) {}

        bool running, onceRun;
        uint32 pathID, runDelay;
        Waypoint firstWaypoints[PATHS_COUNT_PANICKED_CITIZEN];

        void LoadWaypoints(Waypoint *waypoints)
        {
            QueryResult result[PATHS_COUNT_PANICKED_CITIZEN];
            result[0] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851000 and `point` = 1");
            result[1] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851001 and `point` = 1");
            result[2] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851002 and `point` = 1");
            result[3] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851003 and `point` = 1");
            result[4] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851004 and `point` = 1");
            result[5] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851005 and `point` = 1");
            result[6] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851006 and `point` = 1");
            result[7] = WorldDatabase.Query("SELECT `id`, `position_x`, `position_y` FROM waypoint_data WHERE id = 34851007 and `point` = 1");

            for (uint8 i = 0; i < PATHS_COUNT_PANICKED_CITIZEN; i ++)
            {
                Field* pFields = result[i]->Fetch();
                waypoints[i].pathID = pFields[0].GetUInt32();
                waypoints[i].x = pFields[1].GetFloat();
                waypoints[i].y = pFields[2].GetFloat();
            }
        }

        uint32 FindNearestPath(Waypoint *paths)
        {
            uint32 pathIDs[PATHS_COUNT_PANICKED_CITIZEN], nearestPathID;
            float distances[PATHS_COUNT_PANICKED_CITIZEN], minDist;

            for (uint8 i = 0; i < PATHS_COUNT_PANICKED_CITIZEN; i ++)
            {
                distances[i] = me->GetDistance2d(paths[i].x, paths[i].y);
                pathIDs[i] = paths[i].pathID;
            }
            for (uint8 i = 0; i < PATHS_COUNT_PANICKED_CITIZEN; i ++)
            {
                if (i == 0)
                {
                    minDist = distances[i];
                    nearestPathID = pathIDs[i];
                }
                else if (minDist > distances[i])
                {
                    minDist = distances[i];
                    nearestPathID = pathIDs[i];
                }
            }
            return nearestPathID;
        }

        void Reset()
        {
            me->Respawn(1);
        }

        void JustRespawned()
        {
            if (me->GetDefaultMovementType() == WAYPOINT_MOTION_TYPE)
            {
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                runDelay = urand(2000, 8000);
                running = true;
                onceRun = true;
            }
            else running = false;
        }

        void UpdateAI(const uint32 diff)
        {
            if (running)
            {
                if (runDelay <= diff && onceRun)
                {
                    LoadWaypoints(firstWaypoints);
                    pathID = FindNearestPath(firstWaypoints);
                    me->GetMotionMaster()->MovePath(pathID, false);
                    me->HandleEmoteCommand(EMOTE_ONESHOT_COWER);
                    onceRun = false;
                }
                else runDelay -= diff;
            }
        }
    };
};

/*######
## npc_lieutenant_walden
######*/

class npc_lieutenant_walden : public CreatureScript
{
public:
    npc_lieutenant_walden() : CreatureScript("npc_lieutenant_walden") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lieutenant_waldenAI (creature);
    }

    struct npc_lieutenant_waldenAI : public ScriptedAI
    {
        npc_lieutenant_waldenAI(Creature *c) : ScriptedAI(c) {}

        void sQuestReward(Player *player, const Quest *pQuest, uint32 data)
        {
            if (pQuest->GetQuestId() == QUEST_LOCKDOWN && player->GetPhaseMask() == 1)
                player->SetAuraStack(SPELL_PHASE_2, player, 1); //phaseshift
        }
    };
};

/*######
## npc_gilneas_city_guard_phase1
######*/
class npc_gilneas_city_guard_phase1 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase1() : CreatureScript("npc_gilneas_city_guard_phase1") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase1AI (creature);
    }

    struct npc_gilneas_city_guard_phase1AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase1AI(Creature *c) : ScriptedAI(c) {}

        uint32 tSay; //Time left for say

        //Evade or Respawn
        void Reset()
        {
            if (me->GetGUIDLow() == 3486400)
            {
                tSay = DELAY_SAY_GILNEAS_CITY_GUARD_GATE; //Reset timer
            }
        }

        void UpdateAI(const uint32 diff)
        {
            //Out of combat and
            if (me->GetGUIDLow() == 3486400)
            {
                //Timed say
                if(tSay <= diff)
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

/*######
## npc_gilneas_city_guard_phase2
######*/

class npc_gilneas_city_guard_phase2 : public CreatureScript
{
public:
    npc_gilneas_city_guard_phase2() : CreatureScript("npc_gilneas_city_guard_phase2") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_gilneas_city_guard_phase2AI (creature);
    }

    struct npc_gilneas_city_guard_phase2AI : public ScriptedAI
    {
        npc_gilneas_city_guard_phase2AI(Creature *c) : ScriptedAI(c) {}

        uint32 tAnimate, tSound, dmgCount, tSeek;
        bool playSnd;

        void Reset()
        {
            tAnimate = DELAY_ANIMATE;
            dmgCount = 0;
            tSound = DELAY_SOUND;
            playSnd = false;
            tSeek = urand(1000, 2000);
        }

        void DamageTaken(Unit * pWho, uint32 &uiDamage)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                pWho->AddThreat(me, 1.0f);
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
                dmgCount = 0;
            }
            else if (pWho->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
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
                playSnd = false;
            }

            if (playSnd == true) tSound -= diff;

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else if (me->getVictim()->isPet()) dmgCount = 0;
            else
            {
                if (tAnimate <= diff)
                {
                    me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                    playSnd = true;
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
    npc_prince_liam_greymane_phase2() : CreatureScript("npc_prince_liam_greymane_phase2") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_prince_liam_greymane_phase2AI (creature);
    }

    struct npc_prince_liam_greymane_phase2AI : public ScriptedAI
    {
        npc_prince_liam_greymane_phase2AI(Creature *c) : ScriptedAI(c) {}

        uint32 tAnimate, tSound, dmgCount, tYell, tSeek;
        bool playSnd, doYell;

        void Reset()
        {
            tAnimate = DELAY_ANIMATE;
            dmgCount = 0;
            tSound = DELAY_SOUND;
            playSnd = false;
            tSeek = urand(1000, 2000);
            doYell = true;
            tYell = DELAY_YELL_PRINCE_LIAM_GREYMANE;
        }

        void sGossipHello(Player *player)
        {
            if ((player->GetQuestStatus(14094) == QUEST_STATUS_REWARDED) && (player->GetPhaseMask() == 2))
                player->SetAuraStack(SPELL_PHASE_4, player, 1); //phaseshift
        }

        void DamageTaken(Unit * pWho, uint32 &uiDamage)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                pWho->AddThreat(me, 1.0f);
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
                dmgCount = 0;
            }
            else if (pWho->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
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
                if(doYell)
                {
                    //Yell Timer
                    if(tYell <= diff)
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
                    playSnd = false;
                }

                if (playSnd == true) tSound -= diff;

                //Attack
                if (dmgCount < 2)
                    DoMeleeAttackIfReady();
                else if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
                else if (me->getVictim()->isPet()) dmgCount = 0;
                else
                {
                    if (tAnimate <= diff)
                    {
                        me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);
                        playSnd = true;
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

enum eRampaging_worgen
{
    #define SPELL_ENRAGE 8599
    #define CD_ENRAGE 30000
};

class npc_rampaging_worgen : public CreatureScript
{
public:
    npc_rampaging_worgen() : CreatureScript("npc_rampaging_worgen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgenAI (creature);
    }

    struct npc_rampaging_worgenAI : public ScriptedAI
    {
        npc_rampaging_worgenAI(Creature *c) : ScriptedAI(c) {}

        uint32 tEnrage;
        uint32 dmgCount;
        uint32 tAnimate;
        uint32 tSound;
        bool playSound, willCastEnrage;

        void Reset()
        {
            tEnrage = 0;
            dmgCount = 0;
            tAnimate = DELAY_ANIMATE;
            tSound = DELAY_SOUND;
            playSound = false;
            willCastEnrage = urand(0, 1);
        }

        void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
        {
            if (target->GetEntry() == NPC_GILNEAS_CITY_GUARD || target->GetEntry() == NPC_PRINCE_LIAM_GREYMANE)
                dmgCount ++;
        }

        void DamageTaken(Unit * pWho, uint32 &uiDamage)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                me->getThreatManager().resetAllAggro();
                pWho->AddThreat(me, 1.0f);
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
                dmgCount = 0;
            }
            else if (pWho->isPet())
            {
                me->getThreatManager().resetAllAggro();
                me->AddThreat(pWho, 1.0f);
                me->AI()->AttackStart(pWho);
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
            if (playSound == true) tSound -= diff;

            if (tSound <= diff)
            {
                me->PlayDistanceSound(SOUND_SWORD_PLATE);
                tSound = DELAY_SOUND;
                playSound = false;
            }

            if (dmgCount < 2)
                DoMeleeAttackIfReady();
            else if (me->getVictim()->GetTypeId() == TYPEID_PLAYER) dmgCount = 0;
            else if (me->getVictim()->isPet()) dmgCount = 0;
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
    npc_rampaging_worgen2() : CreatureScript("npc_rampaging_worgen2") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rampaging_worgen2AI (creature);
    }

    struct npc_rampaging_worgen2AI : public ScriptedAI
    {
        npc_rampaging_worgen2AI(Creature *c) : ScriptedAI(c) {}

        uint16 tRun, tEnrage;
        bool onceRun, willCastEnrage;
        float x, y, z;

        void JustRespawned()
        {
            tEnrage = 0;
            tRun = 500;
            onceRun = true;
            x = me->m_positionX+cos(me->m_orientation)*8;
            y = me->m_positionY+sin(me->m_orientation)*8;
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
            else tRun -= diff;

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
            else tEnrage -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

/*######
## go_merchant_square_door
######*/

enum eMerchant_square_door
{
    #define SUMMON1_TTL 300000
    #define QUEST_EVAC_MERC_SQUA 14098
};

class go_merchant_square_door : public GameObjectScript
{
public:
    go_merchant_square_door() : GameObjectScript("go_merchant_square_door") { }

    float x, y, z, wx, wy, angle, tQuestCredit;
    bool opened;
    uint8 spawnKind;
    Player* aPlayer;
    GameObject* pGO;

    bool OnGossipHello(Player *player, GameObject *pGO)
    {
        if (player->GetQuestStatus(QUEST_EVAC_MERC_SQUA) == QUEST_STATUS_INCOMPLETE)
        {
            aPlayer = player;
            opened = 1;
            tQuestCredit = 2500;
            pGO->Use(player);
            spawnKind = urand(1, 3); //1,2=citizen, 3=citizen&worgen (66%,33%)
            angle=pGO->GetOrientation();
            x=pGO->GetPositionX()-cos(angle)*2;
            y=pGO->GetPositionY()-sin(angle)*2;
            z=pGO->GetPositionZ();
            wx = x-cos(angle)*2;
            wy = y-sin(angle)*2;

            if (spawnKind < 3)
            {
                if (Creature *spawnedCreature = pGO->SummonCreature(NPC_FRIGHTENED_CITIZEN_1,x,y,z,angle,TEMPSUMMON_TIMED_DESPAWN,SUMMON1_TTL))
                {
                    spawnedCreature->SetPhaseMask(6, 1);
                    spawnedCreature->Respawn(1);
                }
            }
            else
            {
                if (Creature *spawnedCreature = pGO->SummonCreature(NPC_FRIGHTENED_CITIZEN_2,x,y,z,angle,TEMPSUMMON_TIMED_DESPAWN,SUMMON1_TTL))
                {
                    spawnedCreature->SetPhaseMask(6, 1);
                    spawnedCreature->Respawn(1);
                }
            }
            return true;
        }
        return false;
    }

    void OnUpdate(GameObject *pGO, uint32 diff)
    {
        if (opened == 1)
        {
            if (tQuestCredit <= ((float)diff/8))
            {
                opened = 0;
                aPlayer->KilledMonsterCredit(35830, 0);
                if (spawnKind == 3)
                {
                    if (Creature *spawnedCreature = pGO->SummonCreature(NPC_RAMPAGING_WORGEN_2,wx,wy,z,angle,TEMPSUMMON_TIMED_DESPAWN,SUMMON1_TTL))
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
    }
};

/*######
## npc_frightened_citizen
######*/

enum eFrightened_citizen
{
    SAY_CITIZEN_1 = -1638003,
    SAY_CITIZEN_2 = -1638004,
    SAY_CITIZEN_3 = -1638005,
    SAY_CITIZEN_4 = -1638006,
    SAY_CITIZEN_5 = -1638007,
    SAY_CITIZEN_6 = -1638008,
    SAY_CITIZEN_7 = -1638009,
    SAY_CITIZEN_8 = -1638010,
    SAY_CITIZEN_1b = -1638011,
    SAY_CITIZEN_2b = -1638012,
    SAY_CITIZEN_3b = -1638013,
    SAY_CITIZEN_4b = -1638014,
    SAY_CITIZEN_5b = -1638015,
    #define PATHS_COUNT 2
};

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
    uint8 pointsCount[8];//pathID, pointsCount
    Point paths[8][10];//pathID, pointID, Point
};

class npc_frightened_citizen : public CreatureScript
{
public:
    npc_frightened_citizen() : CreatureScript("npc_frightened_citizen") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_frightened_citizenAI (creature);
    }

    struct npc_frightened_citizenAI : public ScriptedAI
    {
        npc_frightened_citizenAI(Creature *c) : ScriptedAI(c) {}

        uint16 tRun, tRun2, tSay;
        bool onceRun, onceRun2, onceGet, onceSay;
        float x, y, z;
        WayPointID nearestPointID;
        Paths paths;

        Paths LoadPaths()
        {
            Paths paths;
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
                    Field* pFields = result[i]->Fetch();
                    paths.paths[i][j].x = pFields[2].GetFloat();
                    paths.paths[i][j].y = pFields[3].GetFloat();
                    j++;
                }
                while (result[i]->NextRow());
            }

            return paths;
        }

        void MultiDistanceMeter(Point *p, uint8 pointsCount, float *dist)
        {
            for (uint8 i = 0; i <= (pointsCount-1); i++)
            {
                dist[i] = me->GetDistance2d(p[i].x, p[i].y);
            }
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
            paths = LoadPaths();
            tRun = 500;
            tRun2 = 2500;
            tSay = 1000;
            onceRun = onceRun2 = onceSay = onceGet = true;
            x = me->m_positionX+cos(me->m_orientation)*5;
            y = me->m_positionY+sin(me->m_orientation)*5;
            z = me->m_positionZ;
        }

        void UpdateAI(const uint32 diff)
        {
            if (tRun <= diff && onceRun)
            {
                me->GetMotionMaster()->MoveCharge(x, y, z, 8);
                onceRun = false;
            }
            else tRun -= diff;

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

// Quest: (14154) By the Skin of His Teeth
class npc_lord_darius_crowley : public CreatureScript
{
public:
    npc_lord_darius_crowley() : CreatureScript("npc_lord_darius_crowley") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14154)
        {
            CAST_AI(npc_lord_darius_crowley::npc_lord_darius_crowleyAI, creature->AI())->in_progress = true;
            CAST_AI(npc_lord_darius_crowley::npc_lord_darius_crowleyAI, creature->AI())->phase = 1;
            CAST_AI(npc_lord_darius_crowley::npc_lord_darius_crowleyAI, creature->AI())->m_player = player;
            creature->CastSpell(player, 66914, true);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lord_darius_crowleyAI (creature);
    }

    struct npc_lord_darius_crowleyAI : public ScriptedAI
    {
        npc_lord_darius_crowleyAI(Creature* c) : ScriptedAI(c), Summons(me) {}

        uint8 phase;
        uint32 phaseTime;
        bool in_progress;
        SummonList Summons;
        Player* m_player;

        void Reset()
        {
            phase = 1;
            phaseTime = 15000;
            Summons.DespawnAll();
            in_progress = false;
            m_player = NULL;
            me->CastSpell(me, 67503, true);
        }

        void EnterCombat(Unit* who)
        {
            me->CastSpell(who, 61044, true);
        }

        void JustSummoned(Creature *summoned)
        {
            summoned->AI()->AttackStart(m_player);
            Summons.Summon(summoned);
        }

        void SummonedCreatureDespawn(Creature* summoned)
        {
            Summons.Despawn(summoned);
        }

        void JustDied(Unit* /*killer*/)
        {
            if (m_player)
            {
                m_player->RemoveAurasDueToSpell(59073);
                m_player->FailQuest(66914);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (in_progress)
            {
                if (phaseTime <= diff)
                {
                    switch (phase)
                    {
                        case 1:
                            for (int i = 0; i < 8; i++)
                                me->SummonCreature(35456, me->GetPositionX()+10, me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                            me->SummonCreature(35167, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 2:
                            me->SummonCreature(35170, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 3:
                            for (int i = 0; i < 10; i++)
                                me->SummonCreature(35456, me->GetPositionX()+10, me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                            me->SummonCreature(35188, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 4:
                            me->SummonCreature(35188, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 5:
                            for (int i = 0; i < 7; i++)
                                me->SummonCreature(35456, me->GetPositionX()+10, me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                            me->SummonCreature(35167, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 6:
                            for (int i = 0; i < 7; i++)
                                me->SummonCreature(35456, me->GetPositionX()+10, me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                            me->SummonCreature(35188, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;

                        case 7:
                            me->SummonCreature(35170, -1672.92f, 1449.13f, 52.28f, 0, TEMPSUMMON_CORPSE_DESPAWN, 10000);
                        break;
                    }

                    phase++;
                    phaseTime = 15000;
                    if (phase>7)
                    {
                        phase = 1;
                        in_progress = false;
                    }
                } else phaseTime -= diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_josiah_avery : public CreatureScript
{
public:
    npc_josiah_avery() : CreatureScript("npc_josiah_avery") { }

    bool OnQuestComplete(Player* player, Creature* creature, const Quest *_Quest)
    {
        if (_Quest->GetQuestId() == 14159)
        {
            if (Creature *lorna = creature->FindNearestCreature(35378, 30))
                lorna->CastSpell(player, 67357, true);

            player->RemoveAurasDueToSpell(59073);
            player->CastSpell(player, 72870, true);

            DoScriptText(-1777004, player);
        }
        return true;
    }
};

// Quest:(14293) Save Krennan Aranas
class npc_king_genn_greymane : public CreatureScript
{
public:
    npc_king_genn_greymane() : CreatureScript("npc_king_genn_greymane") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 14293)
        {
            //player->CastSpell(player, 68232, true);
            //player->CastSpell(player, 43671, true);
            player->KilledMonsterCredit(35753, 0);
        }
        return true;
    }
};

class spell_rescue_krennan : public SpellScriptLoader
{
    public:
        spell_rescue_krennan() : SpellScriptLoader("spell_rescue_krennan") { }

        class spell_rescue_krennan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rescue_krennan_SpellScript)

            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit * caster = GetCaster())
                {
                    if (Creature *krennan = caster->FindNearestCreature(35905, 30))
                        krennan->DisappearAndDie();
                    else
                        return;

                    if (Creature *krennan = caster->FindNearestCreature(35907, 30))
                        caster->GetVehicle()->AddPassenger(krennan, 1, false);

                    if (caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    caster->ToPlayer()->KilledMonsterCredit(35753, 0);
                }
            }

            void Register()
            {
                OnEffect += SpellEffectFn(spell_rescue_krennan_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rescue_krennan_SpellScript();
        }
};

class npc_lord_darius_crowley_c2 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c2() : CreatureScript("npc_lord_darius_crowley_c2") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        for (int i = 0; i < 30; i++)
            player->KilledMonsterCredit(35582, 0);

        player->TeleportTo(654, -1533.76f, 1582.44f, 26.54f, 4.05f);
        return true;
    }
};

class npc_lord_darius_crowley_c3 : public CreatureScript
{
public:
    npc_lord_darius_crowley_c3() : CreatureScript("npc_lord_darius_crowley_c3") { }

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
            loc.m_orientation = 3.14f;

            player->SetHomebind(loc, 4786);
        }
        return true;
    }
};

class npc_king_genn_greymane_c2 : public CreatureScript
{
public:
    npc_king_genn_greymane_c2() : CreatureScript("npc_king_genn_greymane_c2") { }

    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest)
    {
        player->RemoveAurasDueToSpell(68630);
        player->RemoveAurasDueToSpell(76642);
        player->CastSpell(player, 68481, true);
        return true;
    }
};

class spell_keg_placed : public SpellScriptLoader
{
    public:
        spell_keg_placed() : SpellScriptLoader("spell_keg_placed") { }

        class spell_keg_placed_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_keg_placed_AuraScript);

            uint32 tick, tickcount;

            void HandleEffectApply(AuraEffect const * /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                tick = urand(1, 4);
                tickcount = 0;
            }

            void HandlePeriodic(AuraEffect const * aurEff)
            {
                PreventDefaultAction();
                if (Unit* caster = GetCaster())
                {
                    if (tickcount > tick)
                    {
                        if (caster->GetTypeId() != TYPEID_PLAYER)
                            return;

                        caster->ToPlayer()->KilledMonsterCredit(36233, 0);
                        if (Unit * target = GetTarget())
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
    new npc_gilneas_city_guard_phase2();
    new npc_prince_liam_greymane_phase1();
    new npc_prince_liam_greymane_phase2();
    new npc_rampaging_worgen();
    new npc_rampaging_worgen2();
    new go_merchant_square_door();
    new npc_frightened_citizen();
    new npc_panicked_citizen();
    new npc_panicked_citizen_2();
    new npc_lieutenant_walden();
    new npc_lord_darius_crowley();
    new npc_josiah_avery();
    new npc_king_genn_greymane();
    new spell_rescue_krennan();
    new npc_lord_darius_crowley_c2();
    new npc_lord_darius_crowley_c3();
    new npc_king_genn_greymane_c2();
    new spell_keg_placed();
}