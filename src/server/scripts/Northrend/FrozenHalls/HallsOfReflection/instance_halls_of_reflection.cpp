/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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
#include "halls_of_reflection.h"

/* Halls of Reflection encounters:
0- Falric
1- Marwyn
2- Frostworn General
3- The Lich King
*/

enum eEnum
{
    ENCOUNTER_WAVE_MERCENARY                      = 6,
    ENCOUNTER_WAVE_FOOTMAN                        = 10,
    ENCOUNTER_WAVE_RIFLEMAN                       = 6,
    ENCOUNTER_WAVE_PRIEST                         = 6,
    ENCOUNTER_WAVE_MAGE                           = 6,
};

enum Events
{
    EVENT_NONE,
    EVENT_NEXT_WAVE,
    EVENT_START_LICH_KING,
};

static Position PriestSpawnPos[ENCOUNTER_WAVE_PRIEST] =
{
    {5277.74f, 2016.88f, 707.778f, 5.96903f},
    {5295.88f, 2040.34f, 707.778f, 5.07891f},
    {5320.37f, 1980.13f, 707.778f, 2.00713f},
    {5280.51f, 1997.84f, 707.778f, 0.296706f},
    {5302.45f, 2042.22f, 707.778f, 4.90438f},
    {5306.57f, 1977.47f, 707.778f, 1.50098f},
};

static Position MageSpawnPos[ENCOUNTER_WAVE_MAGE] =
{
    {5312.75f, 2037.12f, 707.778f, 4.59022f},
    {5309.58f, 2042.67f, 707.778f, 4.69494f},
    {5275.08f, 2008.72f, 707.778f, 6.21337f},
    {5279.65f, 2004.66f, 707.778f, 0.069813f},
    {5275.48f, 2001.14f, 707.778f, 0.174533f},
    {5316.7f, 2041.55f, 707.778f, 4.50295f},
};

static Position MercenarySpawnPos[ENCOUNTER_WAVE_MERCENARY] =
{
    {5302.25f, 1972.41f, 707.778f, 1.37881f},
    {5311.03f, 1972.23f, 707.778f, 1.64061f},
    {5277.36f, 1993.23f, 707.778f, 0.401426f},
    {5318.7f, 2036.11f, 707.778f, 4.2237f},
    {5335.72f, 1996.86f, 707.778f, 2.74017f},
    {5299.43f, 1979.01f, 707.778f, 1.23918f},
};

static Position FootmenSpawnPos[ENCOUNTER_WAVE_FOOTMAN] =
{
    {5306.06f, 2037, 707.778f, 4.81711f},
    {5344.15f, 2007.17f, 707.778f, 3.15905f},
    {5337.83f, 2010.06f, 707.778f, 3.22886f},
    {5343.29f, 1999.38f, 707.778f, 2.9147f},
    {5340.84f, 1992.46f, 707.778f, 2.75762f},
    {5325.07f, 1977.6f, 707.778f, 2.07694f},
    {5336.6f, 2017.28f, 707.778f, 3.47321f},
    {5313.82f, 1978.15f, 707.778f, 1.74533f},
    {5280.63f, 2012.16f, 707.778f, 6.05629f},
    {5322.96f, 2040.29f, 707.778f, 4.34587f},
};

static Position RiflemanSpawnPos[ENCOUNTER_WAVE_RIFLEMAN] =
{
    {5343.47f, 2015.95f, 707.778f, 3.49066f},
    {5337.86f, 2003.4f, 707.778f, 2.98451f},
    {5319.16f, 1974, 707.778f, 1.91986f},
    {5299.25f, 2036, 707.778f, 5.02655f},
    {5295.64f, 1973.76f, 707.778f, 1.18682f},
    {5282.9f, 2019.6f, 707.778f, 5.88176f},
};

class instance_halls_of_reflection : public InstanceMapScript
{
public:
    instance_halls_of_reflection() : InstanceMapScript("instance_halls_of_reflection", 668) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_halls_of_reflection_InstanceMapScript(map);
    }

    struct instance_halls_of_reflection_InstanceMapScript : public InstanceScript
    {
        instance_halls_of_reflection_InstanceMapScript(Map* map) : InstanceScript(map) {};

        uint64 Falric;
        uint64 Marwyn;
        uint64 LichKing;
        uint64 JainaPart1;
        uint64 SylvanasPart1;
        uint64 Loralen;
        uint64 Koreln;
        uint64 Lider;

        uint64 Gunship;
        uint64 Chest;
        uint64 uiPortal;

        uint64 Frostmourne;
        uint64 FrontDoor;
        uint64 FrostwornDoor;
        uint64 ArthasDoor;
        uint64 RunDoor;
        uint64 Wall[4];
        uint64 WallID[4];
        uint64 CaveDoor;

        uint32 Encounter[MAX_ENCOUNTER];
        uint32 TeamInInstance;
        uint32 WaveCount;
        uint32 IntroDone;
        uint32 Summons;
        uint32 DataPhase;

        EventMap events;

        void Initialize()
        {
            events.Reset();

            Falric = 0;
            Marwyn = 0;
            LichKing = 0;
            JainaPart1 = 0;
            SylvanasPart1 = 0;
            Koreln = 0;
            Loralen = 0;
            Lider = 0;

            Gunship = 0;
            Chest = 0;
            uiPortal = 0;

            Frostmourne = 0;
            ArthasDoor = 0;
            FrostwornDoor = 0;
            FrontDoor = 0;
            CaveDoor = 0;
            TeamInInstance = 0;
            WaveCount = 0;
            IntroDone = 0;

            for (uint8 i = 0; i < 4; ++i)
            {
                Wall[i] = 0;
                WallID[i] = 0;
            }

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                Encounter[i] = NOT_STARTED;
        }

        void OpenDoor(uint64 guid)
        {
            if (!guid) return;
            GameObject* go = instance->GetGameObject(guid);
            if (go) go->SetGoState(GO_STATE_ACTIVE);
        }

        void CloseDoor(uint64 guid)
        {
            if (!guid) return;
            GameObject* go = instance->GetGameObject(guid);
            if (go) go->SetGoState(GO_STATE_READY);
        }

        void OnCreatureCreate(Creature* creature)
        {
            Map::PlayerList const &players = instance->GetPlayers();
            if (!players.isEmpty())
                if (Player* player = players.begin()->getSource())
                    TeamInInstance = player->GetTeam();

            switch (creature->GetEntry())
            {
                case NPC_FALRIC:
                    Falric = creature->GetGUID();
                    break;
                case NPC_MARWYN:
                    Marwyn = creature->GetGUID();
                    break;
                case NPC_LICH_KING_EVENT:
                    break;
                case NPC_JAINA_PART1:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_SYLVANAS_PART1, HORDE);
                    JainaPart1 = creature->GetGUID();
                    SylvanasPart1 = creature->GetGUID();
                    break;
                case NPC_KORELN:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_LORALEN, HORDE);
                    Koreln = creature->GetGUID();
                    Loralen = creature->GetGUID();
                    break;
                case NPC_SYLVANAS_PART1:
                    SylvanasPart1 = creature->GetGUID();
                    break;
                case NPC_FROSTWORN_GENERAL:
                    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    break;
                case NPC_JAINA_OUTRO:
                    if (TeamInInstance == HORDE)
                        creature->UpdateEntry(NPC_SYLVANA_OUTRO, HORDE);
                    creature->SetHealth(252000);
                    Lider = creature->GetGUID();
                    break;
                case BOSS_LICH_KING:
                    creature->SetHealth(20917000);
                    LichKing = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            // TODO: init state depending on encounters
            switch (go->GetEntry())
            {
                case GO_FROSTMOURNE:
                    Frostmourne = go->GetGUID();
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, false, go);
                    break;
                case GO_FROSTMOURNE_ALTAR:
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, true, go);
                    break;
                case GO_FRONT_DOOR:
                    FrontDoor = go->GetGUID();
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                    OpenDoor(FrontDoor);
                    break;
                case GO_FROSTWORN_DOOR:
                    FrostwornDoor = go->GetGUID();
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

                    if (Encounter[1] == DONE)
                        OpenDoor(FrostwornDoor);
                    else
                        CloseDoor(FrostwornDoor);
                    break;
                case GO_RUN_DOOR:
                    RunDoor = go->GetGUID();
                    break;
                case GO_ARTHAS_DOOR:
                    ArthasDoor = go->GetGUID();
                    break;
                case GO_ICE_WALL_1:
                    WallID[0] = go->GetGUID();
                    break;
                case GO_ICE_WALL_2:
                    WallID[1] = go->GetGUID();
                    break;
                case GO_ICE_WALL_3:
                    WallID[2] = go->GetGUID();
                    break;
                case GO_ICE_WALL_4:
                    WallID[3] = go->GetGUID();
                    break;
                case GO_CAVE:
                    CaveDoor = go->GetGUID();
                    break;
                case GO_CAPTAIN_CHEST_1:
                    go->SetPhaseMask(2, true);
                    if (!instance->IsHeroic() && TeamInInstance == HORDE)
                        Chest = go->GetGUID();
                    break;
                case GO_CAPTAIN_CHEST_3:
                    go->SetPhaseMask(2, true);
                    if (instance->IsHeroic() && TeamInInstance == HORDE)
                        Chest = go->GetGUID();
                    break;
                case GO_CAPTAIN_CHEST_2:
                    go->SetPhaseMask(2, true);
                    if (!instance->IsHeroic() && TeamInInstance == ALLIANCE)
                        Chest = go->GetGUID();
                    break;
                case GO_CAPTAIN_CHEST_4:
                    go->SetPhaseMask(2, true);
                    if (instance->IsHeroic() && TeamInInstance == ALLIANCE)
                        Chest = go->GetGUID();
                    break;
                case GO_SKYBREAKER:
                    go->SetPhaseMask(2, true);
                    if (TeamInInstance == ALLIANCE)
                        Gunship = go->GetGUID();
                    break;
                case GO_ORGRIM_HAMMER:
                    go->SetPhaseMask(2, true);
                    if (TeamInInstance == HORDE)
                        Gunship = go->GetGUID();
                    break;
                case GO_PORTAL:
                    go->SetPhaseMask(2, true);
                    uiPortal = go->GetGUID();
                    break;
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            if (type == DATA_WAVE_COUNT && data == SPECIAL)
            {
                CloseDoor(FrontDoor);
                events.ScheduleEvent(EVENT_NEXT_WAVE, 10000);
                return;
            }

            if (WaveCount && data == NOT_STARTED)
                DoWipe();

            switch (type)
            {
                case DATA_INTRO_EVENT:
                    IntroDone = data;
                    break;
                case DATA_FALRIC_EVENT:
                    Encounter[0] = data;
                    if (data == DONE)
                        events.ScheduleEvent(EVENT_NEXT_WAVE, 60000);
                    break;
                case DATA_MARWYN_EVENT:
                    Encounter[1] = data;
                    if (data == DONE)
                    {
                        OpenDoor(FrostwornDoor);
                        OpenDoor(FrontDoor);
                    }
                    break;
                case DATA_FROSWORN_EVENT:
                    Encounter[2] = data;
                    if (data == DONE)
                    {
                        OpenDoor(ArthasDoor);
                        SetData(DATA_PHASE, 3);
                        instance->SummonCreature(BOSS_LICH_KING, OutroSpawns[0]);
                        instance->SummonCreature(NPC_JAINA_OUTRO, OutroSpawns[1]);
                    }
                    break;
                case DATA_LICHKING_EVENT:
                    Encounter[3] = data;
                    if (data == IN_PROGRESS)
                    {
                        OpenDoor(RunDoor);

                        if (instance->IsHeroic())
                            DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_NOT_RETREATING_EVENT);
                    }
                    if (data == FAIL)
                    {
                        for (uint8 i = 0; i<4; i++)
                            OpenDoor(WallID[i]);

                        CloseDoor(RunDoor);

                        if (Creature* lichKing = instance->GetCreature(LichKing))
                            lichKing->DespawnOrUnsummon(10000);
                        if (Creature* lider = instance->GetCreature(Lider))
                            lider->DespawnOrUnsummon(10000);

                        DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_NOT_RETREATING_EVENT);
                        DoCastSpellOnPlayers(5); // Kill all players

                        SetData(DATA_PHASE, 3);
                        instance->SummonCreature(BOSS_LICH_KING, OutroSpawns[0]);
                        instance->SummonCreature(NPC_JAINA_OUTRO, OutroSpawns[1]);
                    }
                    if (data == DONE)
                    {
                        if (GameObject* chest = instance->GetGameObject(Chest))
                            chest->SetPhaseMask(1, true);
                        if (GameObject* portal = instance->GetGameObject(uiPortal))
                            portal->SetPhaseMask(1, true);

                        /*DoCompleteAchievement(ACHIEV_HALLS_OF_REFLECTION_N);
                        if (instance->IsHeroic())
                        {
                            DoCompleteAchievement(ACHIEV_HALLS_OF_REFLECTION_H);
                            DoCastSpellOnPlayers(SPELL_ACHIEV_CHECK);
                            DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_NOT_RETREATING_EVENT);
                        }*/
                    }
                    break;
                case DATA_SUMMONS:
                    if (data == 3) Summons = 0;
                    else if (data == 1) ++Summons;
                    else if (data == 0) --Summons;
                    data = NOT_STARTED;
                    break;
                case DATA_ICE_WALL_1:
                    Wall[0] = data;
                    break;
                case DATA_ICE_WALL_2:
                    Wall[1] = data;
                    break;
                case DATA_ICE_WALL_3:
                    Wall[2] = data;
                    break;
                case DATA_ICE_WALL_4:
                    Wall[3] = data;
                    break;
                case DATA_PHASE:
                    DataPhase = data;
                    break;
            }

            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
                case DATA_INTRO_EVENT:          return IntroDone;
                case DATA_TEAM_IN_INSTANCE:     return TeamInInstance;

                case DATA_FALRIC_EVENT:         return Encounter[0];
                case DATA_MARWYN_EVENT:         return Encounter[1];
                case DATA_WAVE_COUNT:           return WaveCount;

                case DATA_FROSWORN_EVENT:       return Encounter[2];

                case DATA_LICHKING_EVENT:       return Encounter[3];
                case DATA_ICE_WALL_1:           return Wall[0];
                case DATA_ICE_WALL_2:           return Wall[1];
                case DATA_ICE_WALL_3:           return Wall[2];
                case DATA_ICE_WALL_4:           return Wall[3];
                case DATA_SUMMONS:              return Summons;

                case DATA_PHASE:                return DataPhase;
            }

            return 0;
        }

        uint64 GetData64(uint32 identifier)
        {
            switch (identifier)
            {
                case DATA_FALRIC:               return Falric;
                case DATA_MARWYN:               return Marwyn;
                case DATA_LICHKING:             return LichKing;
                case DATA_ESCAPE_LIDER:         return Lider;
                case DATA_FROSTMOURNE:          return Frostmourne;
                case DATA_FRONT_DOOR:           return FrontDoor;
                case DATA_FROSTWORN_DOOR:       return FrostwornDoor;
                case DATA_ARTHAS_DOOR:          return ArthasDoor;
                case GO_ICE_WALL_1:             return WallID[0];
                case GO_ICE_WALL_2:             return WallID[1];
                case GO_ICE_WALL_3:             return WallID[2];
                case GO_ICE_WALL_4:             return WallID[3];
                case GO_CAVE:                   return CaveDoor;
                case GO_CAPTAIN_CHEST_1:
                case GO_CAPTAIN_CHEST_2:
                case GO_CAPTAIN_CHEST_3:
                case GO_CAPTAIN_CHEST_4:        return Chest;
                case GO_SKYBREAKER:
                case GO_ORGRIM_HAMMER:          return Gunship;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "H R 1 " << Encounter[0] << " " << Encounter[1] << " " << Encounter[2] << " " << Encounter[3] << " " << IntroDone;

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;
            uint16 version;
            uint16 data0, data1, data2, data3, data4;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> version >> data0 >> data1 >> data2 >> data3 >> data4;

            if (dataHead1 == 'H' && dataHead2 == 'R')
            {
                Encounter[0] = data0;
                Encounter[1] = data1;
                Encounter[2] = data2;
                Encounter[3] = data3;
                IntroDone = data4;

                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (Encounter[i] == IN_PROGRESS)
                        Encounter[i] = NOT_STARTED;

                OpenDoor(FrontDoor);
                if (Encounter[1] == DONE)
                    OpenDoor(FrostwornDoor);
                if (Encounter[2] == DONE)
                    OpenDoor(ArthasDoor);
            } else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void AddWave()
        {
            DoUpdateWorldState(WORLD_STATE_HOR, 1);
            DoUpdateWorldState(WORLD_STATE_HOR_WAVE_COUNT, WaveCount);

            switch (WaveCount)
            {
                case 1:
                case 2:
                case 3:
                case 4:
                    if (Creature* falric = instance->GetCreature(Falric))
                        SpawnWave(falric);
                    break;
                case 5:
                    if (GetData(DATA_FALRIC_EVENT) == DONE)
                        events.ScheduleEvent(EVENT_NEXT_WAVE, 10000);
                    else if (Creature* falric = instance->GetCreature(Falric))
                        if (falric->AI())
                            falric->AI()->DoAction(ACTION_ENTER_COMBAT);
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                    if (Creature* marwyn  = instance->GetCreature(Marwyn))
                        SpawnWave(marwyn);
                    break;
                case 10:
                    if (GetData(DATA_MARWYN_EVENT) != DONE) // wave should not have been started if DONE. Check anyway to avoid bug exploit!
                        if (Creature* marwyn = instance->GetCreature(Marwyn))
                            if (marwyn->AI())
                                marwyn->AI()->DoAction(ACTION_ENTER_COMBAT);
                    break;
            }
        }

        // Wipe has been detected. Perform cleanup and reset.
        void DoWipe()
        {
            if (GetData(DATA_MARWYN_EVENT) != DONE) {
                SetData(DATA_WAVE_COUNT, FAIL);
                WaveCount = 0;
                events.Reset();
                DoUpdateWorldState(WORLD_STATE_HOR, 1);
                DoUpdateWorldState(WORLD_STATE_HOR_WAVE_COUNT, WaveCount);
                OpenDoor(FrontDoor);

            // TODO
            // in case of wipe, the event is normally restarted by jumping into the center of the room.
            // As I can't find a trigger area there, just respawn Jaina/Sylvanas so the event may be restarted.
            if (Creature* falric = instance->GetCreature(Falric))
                falric->SetVisible(false);
            if (Creature* marwyn = instance->GetCreature(Marwyn))
                marwyn->SetVisible(false);
            }
        }

        // spawn a wave on behalf of the summoner.
        void SpawnWave(Creature* summoner)
        {
            uint32 index;

            summoner->SetVisible(true);

            // TODO: do composition at random. # of spawn also depends on WaveCount
            // As of now, it is just one of each.
            index = urand(0, ENCOUNTER_WAVE_MERCENARY -1);
            summoner->SummonCreature(NPC_WAVE_MERCENARY, MercenarySpawnPos[index], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);

            index = urand(0, ENCOUNTER_WAVE_FOOTMAN -1);
            summoner->SummonCreature(NPC_WAVE_FOOTMAN, FootmenSpawnPos[index], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);

            index = urand(0, ENCOUNTER_WAVE_RIFLEMAN -1);
            summoner->SummonCreature(NPC_WAVE_RIFLEMAN, RiflemanSpawnPos[index], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);

            index = urand(0, ENCOUNTER_WAVE_PRIEST -1);
            summoner->SummonCreature(NPC_WAVE_PRIEST, PriestSpawnPos[index], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);

            index = urand(0, ENCOUNTER_WAVE_MAGE -1);
            summoner->SummonCreature(NPC_WAVE_MAGE, MageSpawnPos[index], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0);
        }

        void Update(uint32 diff)
        {
            if (!instance->HavePlayers())
                return;

            events.Update(diff);

            switch (events.ExecuteEvent())
            {
                case EVENT_NEXT_WAVE:
                    WaveCount++;
                    AddWave();
                    break;
            }
        }
    };
};

void AddSC_instance_halls_of_reflection()
{
    new instance_halls_of_reflection();
}
