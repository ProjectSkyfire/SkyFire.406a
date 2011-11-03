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

class instance_ruby_sanctum : public InstanceMapScript
{
public:
    instance_ruby_sanctum() : InstanceMapScript("instance_ruby_sanctum", 724) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_ruby_sanctum_InstanceMapScript(map);
    }

    struct instance_ruby_sanctum_InstanceMapScript : public InstanceScript
    {
        instance_ruby_sanctum_InstanceMapScript(Map* map) : InstanceScript(map) {Initialize();};

        std::string strSaveData;

        //Creatures GUID
        uint32 Encounter[MAX_ENCOUNTERS+1];

        uint32 EventTimer;
        uint32 HalionEvent;

        uint32 OrbDirection;
        uint32 OrbNState;
        uint32 OrbSState;

        uint64 Halion_pGUID;
        uint64 Halion_tGUID;
        uint64 HalionControlGUID;
        uint64 RagefireGUID;
        uint64 ZarithianGUID;
        uint64 BaltharusGUID;
        uint64 CloneGUID;
        uint64 XerestraszaGUID;

        uint64 OrbNGUID;
        uint64 OrbSGUID;
        uint64 OrbFocusGUID;
        uint64 OrbCarrierGUID;

        //object GUID
        uint64 HalionPortal1GUID;
        uint64 HalionPortal2GUID;
        uint64 HalionPortal3GUID;
        uint64 HalionFireWallSGUID;
        uint64 HalionFireWallMGUID;
        uint64 HalionFireWallLGUID;
        uint64 BaltharusTargetGUID;

        uint64 FireFieldGUID;
        uint64 FlameWallsGUID;
        uint64 FlameRingGUID;

        void Initialize()
        {
            for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                Encounter[i] = NOT_STARTED;

            EventTimer = 1000;

            Halion_pGUID = 0;
            Halion_tGUID = 0;
            RagefireGUID = 0;
            ZarithianGUID = 0;
            BaltharusGUID = 0;
            CloneGUID = 0;
            HalionPortal1GUID = 0;
            HalionPortal2GUID = 0;
            HalionPortal3GUID = 0;
            XerestraszaGUID = 0;
            HalionFireWallSGUID = 0;
            HalionFireWallMGUID = 0;
            HalionFireWallLGUID = 0;
            BaltharusTargetGUID = 0;
            OrbDirection = 0;
            OrbNGUID = 0;
            OrbSGUID = 0;
            OrbFocusGUID = 0;
            OrbNState = NOT_STARTED;
            OrbSState = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i = 1; i < MAX_ENCOUNTERS ; ++i)
                if (Encounter[i] == IN_PROGRESS)
                    return true;

            return false;
        }

        void OpenDoor(uint64 guid)
        {
            if(!guid)
                return;

            GameObject* go = instance->GetGameObject(guid);
            if(go)
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
        }

        void CloseDoor(uint64 guid)
        {
            if(!guid)
                return;

            GameObject* go = instance->GetGameObject(guid);
            if(go)
                go->SetGoState(GO_STATE_READY);
        }

        void OpenAllDoors()
        {
            if (Encounter[TYPE_RAGEFIRE] == DONE &&
                Encounter[TYPE_BALTHARUS] == DONE &&
                Encounter[TYPE_XERESTRASZA] == DONE)
                     OpenDoor(FlameWallsGUID);
            else CloseDoor(FlameWallsGUID);
        }

        void UpdateWorldState(bool command, uint32 value)
        {
            Map::PlayerList const &players = instance->GetPlayers();

            if (command)
            {
                for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                {
                    if(Player* player = i->getSource())
                    {
                        if(player->isAlive())
                        {
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
                            if (player->HasAura(74807))
                            {
                                player->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_T, 100 - value);
                            }
                            else
                            {
                                player->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_R, value);
                            }
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,1);
                        }
                    }
                }
            }
            else
            {
                for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                {
                    if(Player* player = i->getSource())
                    {
                        if(player->isAlive())
                        {
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
                        }
                    }
                }
            }
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case NPC_HALION_REAL: Halion_pGUID = creature->GetGUID();break;
                case NPC_HALION_TWILIGHT: Halion_tGUID = creature->GetGUID(); break;
                case NPC_HALION_CONTROL: HalionControlGUID = creature->GetGUID(); break;
                case NPC_RAGEFIRE: RagefireGUID = creature->GetGUID(); break;
                case NPC_ZARITHIAN: ZarithianGUID = creature->GetGUID(); break;
                case NPC_BALTHARUS: BaltharusGUID = creature->GetGUID(); break;
                case NPC_BALTHARUS_TARGET: BaltharusTargetGUID = creature->GetGUID(); break;
                case NPC_CLONE: CloneGUID = creature->GetGUID(); break;
                case NPC_XERESTRASZA: XerestraszaGUID = creature->GetGUID(); break;
                case NPC_SHADOW_PULSAR_N: OrbNGUID = creature->GetGUID(); break;
                case NPC_SHADOW_PULSAR_S: OrbSGUID = creature->GetGUID(); break;
                case NPC_ORB_ROTATION_FOCUS: OrbFocusGUID = creature->GetGUID(); break;
                case NPC_ORB_CARRIER: OrbCarrierGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch(go->GetEntry())
            {
                case GO_HALION_PORTAL_1: HalionPortal1GUID = go->GetGUID(); break;
                case GO_HALION_PORTAL_2: HalionPortal2GUID = go->GetGUID(); break;
                case GO_HALION_PORTAL_3: HalionPortal3GUID = go->GetGUID(); break;
                case GO_FLAME_WALLS: FlameWallsGUID = go->GetGUID(); break;
                case GO_FLAME_RING: FlameRingGUID = go->GetGUID(); break;
                case GO_FIRE_FIELD: FireFieldGUID = go->GetGUID(); break;
            }
            OpenAllDoors();
        }

        void SetData(uint32 Type, uint32 Data)
        {
            switch(Type)
            {
                case TYPE_EVENT: Encounter[Type] = Data; Data = NOT_STARTED; break;
                case TYPE_RAGEFIRE: Encounter[Type] = Data;
                                           OpenAllDoors();
                                        break;
                case TYPE_BALTHARUS: Encounter[Type] = Data;
                                           OpenAllDoors();
                                        break;
                case TYPE_XERESTRASZA: Encounter[Type] = Data;
                                        if (Data == IN_PROGRESS)
                                           OpenDoor(FireFieldGUID);
                                        else if (Data == NOT_STARTED)
                                        {
                                           CloseDoor(FireFieldGUID);
                                           OpenAllDoors();
                                        }
                                        else if (Data == DONE)
                                        {
                                           OpenAllDoors();
                                           if (Encounter[TYPE_ZARITHRIAN] == DONE)
                                           {
                                               Encounter[TYPE_EVENT] = 200;
                                               EventTimer = 30000;
                                           };
                                        }
                                        break;
                case TYPE_ZARITHRIAN: Encounter[Type] = Data;
                                        if (Data == DONE)
                                        {
                                           OpenDoor(FlameWallsGUID);
                                           Encounter[TYPE_EVENT] = 200;
                                           EventTimer = 30000;
                                        }
                                        else if (Data == IN_PROGRESS)
                                           CloseDoor(FlameWallsGUID);
                                        else if (Data == FAIL)
                                           OpenDoor(FlameWallsGUID);
                                        break;
                case TYPE_HALION: Encounter[Type] = Data;
                                        if (Data == IN_PROGRESS)
                                        {
                                            CloseDoor(FlameRingGUID);
                                        }
                                        else
                                        {
                                              OpenDoor(FlameRingGUID);
                                        }
                                        break;
                case TYPE_HALION_EVENT: HalionEvent = Data; Data = NOT_STARTED; break;
                case TYPE_EVENT_TIMER: EventTimer = Data; Data = NOT_STARTED; break;

                case DATA_ORB_DIRECTION: OrbDirection = Data; Data = NOT_STARTED; break;
                case DATA_ORB_N: OrbNState = Data; Data = NOT_STARTED; break;
                case DATA_ORB_S: OrbSState = Data; Data = NOT_STARTED; break;
                case TYPE_COUNTER:
                                    if (Data == COUNTER_OFF)
                                    {
                                        UpdateWorldState(false,0);
                                    }
                                    else
                                    {
                                        UpdateWorldState(true,Data);
                                    }
                                    Data = NOT_STARTED;
                                    break;
            }

            if (Data == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;

                for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                    saveStream << Encounter[i] << " ";

                strSaveData = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        std::string GetSaveData()
        {
            return strSaveData;
        }

        uint32 GetData(uint32 Type)
        {
            switch(Type)
            {
                case TYPE_RAGEFIRE: return Encounter[Type];
                case TYPE_BALTHARUS: return Encounter[Type];
                case TYPE_XERESTRASZA: return Encounter[Type];
                case TYPE_ZARITHRIAN: return Encounter[Type];
                case TYPE_HALION: return Encounter[Type];

                case TYPE_EVENT: return Encounter[Type];

                case TYPE_HALION_EVENT: return HalionEvent;

                case TYPE_EVENT_TIMER: return EventTimer;
                case TYPE_EVENT_NPC: switch (Encounter[TYPE_EVENT])
                                         {
                                              case 10:
                                              case 20:
                                              case 30:
                                              case 40:
                                              case 50:
                                              case 60:
                                              case 70:
                                              case 80:
                                              case 90:
                                              case 100:
                                              case 110:
                                              case 200:
                                              case 210:
                                                     return NPC_XERESTRASZA;
                                                     break;
                                              default:
                                                     break;
                                         };
                                         return 0;

                case DATA_ORB_DIRECTION: return OrbDirection;
                case DATA_ORB_N: return OrbNState;
                case DATA_ORB_S: return OrbSState;
            }
            return 0;
        }

        uint64 GetData64(uint32 Data)
        {
            switch(Data)
            {
                case NPC_BALTHARUS: return BaltharusGUID;
                case NPC_CLONE: return CloneGUID;
                case NPC_ZARITHIAN: return ZarithianGUID;
                case NPC_RAGEFIRE: return RagefireGUID;
                case NPC_HALION_REAL: return Halion_pGUID;
                case NPC_HALION_TWILIGHT: return Halion_tGUID;
                case NPC_HALION_CONTROL: return HalionControlGUID;
                case NPC_XERESTRASZA: return XerestraszaGUID;
                case NPC_BALTHARUS_TARGET: return BaltharusTargetGUID;

                case GO_FLAME_WALLS: return FlameWallsGUID;
                case GO_FLAME_RING: return FlameRingGUID;
                case GO_FIRE_FIELD: return FireFieldGUID;

                case GO_HALION_PORTAL_1: return HalionPortal1GUID;
                case GO_HALION_PORTAL_2: return HalionPortal2GUID;
                case GO_HALION_PORTAL_3: return HalionPortal3GUID;

                case NPC_SHADOW_PULSAR_N: return OrbNGUID;
                case NPC_SHADOW_PULSAR_S: return OrbSGUID;
                case NPC_ORB_ROTATION_FOCUS: return OrbFocusGUID;
                case NPC_ORB_CARRIER: return OrbCarrierGUID;
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

            for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                loadStream >> Encounter[i];

                if (Encounter[i] == IN_PROGRESS
                    || Encounter[i] == FAIL)
                    Encounter[i] = NOT_STARTED;
            }

            Encounter[TYPE_XERESTRASZA] = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
            OpenAllDoors();
        }
    };
};

void AddSC_instance_ruby_sanctum()
{
    new instance_ruby_sanctum();
}