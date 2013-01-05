/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Karazhan
SD%Complete: 70
SDComment: Instance Script for Karazhan to help in various encounters. TODO: GameObject visibility for Opera event.
SDCategory: Karazhan
EndScriptData */

#include "ScriptPCH.h"
#include "karazhan.h"

#define MAX_ENCOUNTER      12

/*
0  - Attumen + Midnight (optional)
1  - Moroes
2  - Maiden of Virtue (optional)
3  - Hyakiss the Lurker /  Rokad the Ravager  / Shadikith the Glider
4  - Opera Event
5  - Curator
6  - Shade of Aran (optional)
7  - Terestian Illhoof (optional)
8  - Netherspite (optional)
9  - Chess Event
10 - Prince Malchezzar
11 - Nightbane
*/

class instance_karazhan : public InstanceMapScript
{
public:
    instance_karazhan() : InstanceMapScript("instance_karazhan", 532) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_karazhan_InstanceMapScript(map);
    }

    struct instance_karazhan_InstanceMapScript : public InstanceScript
    {
        instance_karazhan_InstanceMapScript(Map* map) : InstanceScript(map) {}

        uint32 Encounter[MAX_ENCOUNTER];
        std::string strSaveData;

        uint32 OperaEvent;
        uint32 OzDeathCount;

        uint64 CurtainGUID;
        uint64 _StageDoorLeftGUID;
        uint64 _StageDoorRightGUID;
        uint64 KilrekGUID;
        uint64 TerestianGUID;
        uint64 MoroesGUID;
        uint64 LibraryDoor;                                     // Door at Shade of Aran
        uint64 MassiveDoor;                                     // Door at Netherspite
        uint64 SideEntranceDoor;                                // Side Entrance
        uint64 GamesmansDoor;                                   // Door before Chess
        uint64 GamesmansExitDoor;                               // Door after Chess
        uint64 NetherspaceDoor;                                // Door at Malchezaar
        uint64 MastersTerraceDoor[2];
        uint64 ImageGUID;
        uint64 DustCoveredChest;

        void Initialize()
        {
            memset(&Encounter, 0, sizeof(Encounter));

            // 1 - OZ, 2 - HOOD, 3 - RAJ, this never gets altered.
            OperaEvent      = urand(1, 3);
            OzDeathCount    = 0;

            CurtainGUID         = 0;
            _StageDoorLeftGUID   = 0;
            _StageDoorRightGUID  = 0;

            KilrekGUID      = 0;
            TerestianGUID   = 0;
            MoroesGUID      = 0;

            LibraryDoor         = 0;
            MassiveDoor         = 0;
            SideEntranceDoor    = 0;
            GamesmansDoor       = 0;
            GamesmansExitDoor   = 0;
            NetherspaceDoor     = 0;
            MastersTerraceDoor[0]= 0;
            MastersTerraceDoor[1]= 0;
            ImageGUID = 0;
            DustCoveredChest    = 0;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (Encounter[i] == IN_PROGRESS)
                    return true;

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case 17229:   KilrekGUID =    creature->GetGUID();      break;
                case 15688:   TerestianGUID = creature->GetGUID();      break;
                case 15687:   MoroesGUID =    creature->GetGUID();      break;
            }
        }

        void SetData(uint32 type, uint32 Data)
        {
            switch (type)
            {
                case TYPE_ATTUMEN:              Encounter[0] = Data; break;
                case TYPE_MOROES:
                    if (Encounter[1] == DONE)
                        break;
                    Encounter[1] = Data;
                    break;
                case TYPE_MAIDEN:               Encounter[2] = Data; break;
                case TYPE_OPTIONAL_BOSS:        Encounter[3] = Data; break;
                case TYPE_OPERA:
                    Encounter[4] = Data;
                    if (Data == DONE)
                        UpdateEncounterState(ENCOUNTER_CREDIT_KILL_CREATURE, 16812, NULL);
                    break;
                case TYPE_CURATOR:              Encounter[5] = Data; break;
                case TYPE_ARAN:                 Encounter[6] = Data; break;
                case TYPE_TERESTIAN:            Encounter[7] = Data; break;
                case TYPE_NETHERSPITE:          Encounter[8] = Data; break;
                case TYPE_CHESS:
                    if (Data == DONE)
                        DoRespawnGameObject(DustCoveredChest, DAY);
                    Encounter[9]  = Data;
                    break;
                case TYPE_MALCHEZZAR:           Encounter[10] = Data; break;
                case TYPE_NIGHTBANE:
                    if (Encounter[11] != DONE)
                        Encounter[11] = Data;
                    break;
                case DATA_OPERA_OZ_DEATHCOUNT:
                    if (Data == SPECIAL)
                        ++OzDeathCount;
                    else if (Data == IN_PROGRESS)
                        OzDeathCount = 0;
                    break;
            }

            if (Data == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << Encounter[0] << ' ' << Encounter[1] << ' ' << Encounter[2] << ' '
                    << Encounter[3] << ' ' << Encounter[4] << ' ' << Encounter[5] << ' ' << Encounter[6] << ' '
                    << Encounter[7] << ' ' << Encounter[8] << ' ' << Encounter[9] << ' ' << Encounter[10] << ' ' << Encounter[11];

                strSaveData = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

         void SetData64(uint32 identifier, uint64 data)
         {
             switch (identifier)
             {
             case DATA_IMAGE_OF_MEDIVH: ImageGUID = data;
             }
         }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case 183932:   CurtainGUID = go->GetGUID(); break;
                case 184278:
                    _StageDoorLeftGUID = go->GetGUID();
                    if (Encounter[4] == DONE)
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
                case 184279:
                    _StageDoorRightGUID = go->GetGUID();
                    if (Encounter[4] == DONE)
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
                case 184517:   LibraryDoor          = go->GetGUID();         break;
                case 185521:   MassiveDoor          = go->GetGUID();         break;
                case 184276:   GamesmansDoor        = go->GetGUID();         break;
                case 184277:   GamesmansExitDoor    = go->GetGUID();         break;
                case 185134:   NetherspaceDoor      = go->GetGUID();         break;
                case 184274:   MastersTerraceDoor[0] = go->GetGUID();        break;
                case 184280:   MastersTerraceDoor[1] = go->GetGUID();        break;
                case 184275:
                    SideEntranceDoor = go->GetGUID();
                    if (Encounter[4] == DONE)
                        go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                    else
                        go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                    break;
                case 185119: DustCoveredChest = go->GetGUID(); break;
            }

            switch (OperaEvent)
            {
                //TODO: Set Object visibilities for Opera based on performance
                case EVENT_OZ:
                    break;

                case EVENT_HOOD:
                    break;

                case EVENT_RAJ:
                    break;
            }
        }

        std::string GetSaveData()
        {
            return strSaveData;
        }

        uint32 GetData(uint32 Data)
        {
            switch (Data)
            {
                case TYPE_ATTUMEN:              return Encounter[0];
                case TYPE_MOROES:               return Encounter[1];
                case TYPE_MAIDEN:               return Encounter[2];
                case TYPE_OPTIONAL_BOSS:        return Encounter[3];
                case TYPE_OPERA:                return Encounter[4];
                case TYPE_CURATOR:              return Encounter[5];
                case TYPE_ARAN:                 return Encounter[6];
                case TYPE_TERESTIAN:            return Encounter[7];
                case TYPE_NETHERSPITE:          return Encounter[8];
                case TYPE_CHESS:                return Encounter[9];
                case TYPE_MALCHEZZAR:           return Encounter[10];
                case TYPE_NIGHTBANE:            return Encounter[11];
                case DATA_OPERA_PERFORMANCE:    return OperaEvent;
                case DATA_OPERA_OZ_DEATHCOUNT:  return OzDeathCount;
            }

            return 0;
        }

        uint64 GetData64(uint32 Data)
        {
            switch (Data)
            {
                case DATA_KILREK:                   return KilrekGUID;
                case DATA_TERESTIAN:                return TerestianGUID;
                case DATA_MOROES:                   return MoroesGUID;
                case DATA_GO_STAGEDOORLEFT:         return _StageDoorLeftGUID;
                case DATA_GO_STAGEDOORRIGHT:        return _StageDoorRightGUID;
                case DATA_GO_CURTAINS:              return CurtainGUID;
                case DATA_GO_LIBRARY_DOOR:          return LibraryDoor;
                case DATA_GO_MASSIVE_DOOR:          return MassiveDoor;
                case DATA_GO_SIDE_ENTRANCE_DOOR:    return SideEntranceDoor;
                case DATA_GO_GAME_DOOR:             return GamesmansDoor;
                case DATA_GO_GAME_EXIT_DOOR:        return GamesmansExitDoor;
                case DATA_GO_NETHER_DOOR:           return NetherspaceDoor;
                case DATA_MASTERS_TERRACE_DOOR_1:   return MastersTerraceDoor[0];
                case DATA_MASTERS_TERRACE_DOOR_2:   return MastersTerraceDoor[1];
                case DATA_IMAGE_OF_MEDIVH:          return ImageGUID;
            }

            return 0;
        }

        void Load(const char* chrIn)
        {
            if (!chrIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(chrIn);
            std::istringstream loadStream(chrIn);

            loadStream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3]
                >> Encounter[4] >> Encounter[5] >> Encounter[6] >> Encounter[7]
                >> Encounter[8] >> Encounter[9] >> Encounter[10] >> Encounter[11];
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (Encounter[i] == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
                    Encounter[i] = NOT_STARTED;
            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_karazhan()
{
    new instance_karazhan();
}
