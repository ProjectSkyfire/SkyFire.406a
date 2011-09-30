/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
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

#include "bastion_of_twilight.h"
#include "ScriptPCH.h"

class instance_bastion_of_twilight : public InstanceMapScript
{
    public:
        instance_bastion_of_twilight() : InstanceMapScript("instance_bastion_of_twilight", 671) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_bastion_of_twilight_InstanceMapScript(map);
        }

        struct instance_bastion_of_twilight_InstanceMapScript : public InstanceScript
        {
            instance_bastion_of_twilight_InstanceMapScript(InstanceMap* map) : InstanceScript(map) { Initialize(); }

        private:
            uint8  EmeraldWhelpFlag;
            uint64 Encounter[MAX_ENCOUNTER];
            uint64 HalfusGUID;
            uint64 EmeraldWhelp[5];
            uint64 StormRiderGUID;
            uint64 TimeWardenGUID;
            uint64 SlateDragonGUID;
            uint64 NetherScionGUID;
            uint32 StormRiderEvent;
            uint32 TimeWardenEvent;
            uint32 SlateDragonEvent;
            uint32 NetherScionEvent;
            uint32 EmeraldWhelpEvent;

            void Initialize()
            {
                memset(&Encounter, 0, sizeof(Encounter));
                memset(&EmeraldWhelp, 0, sizeof(EmeraldWhelp));
                EmeraldWhelpFlag = 0;
                HalfusGUID = 0;
                StormRiderGUID = 0;
                TimeWardenGUID = 0;
                SlateDragonGUID = 0;
                NetherScionGUID = 0;
                TimeWardenEvent = 0;
                StormRiderEvent = 1;
                SlateDragonEvent = 1;
                NetherScionEvent = 1;
                EmeraldWhelpEvent = 0;
                for (int i = 0; i < 5; ++i)
                    EmeraldWhelp[i] = 0;
            }

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (Encounter[i] == IN_PROGRESS) return true;

                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case 44600:
                        HalfusGUID = creature->GetGUID();
                        break;
                    case 44645:
                        {
                            NetherScionGUID = creature->GetGUID();
                            if (NetherScionEvent == 1)
                                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        }
                        break;
                    case 44652:
                        {
                            SlateDragonGUID = creature->GetGUID();
                            if (SlateDragonEvent == 1)
                                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        }
                        break;
                    case 44650:
                        {
                            StormRiderGUID  = creature->GetGUID();
                            if (StormRiderEvent == 1)
                                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        }
                        break;
                    case 44797:
                        {
                            TimeWardenGUID  = creature->GetGUID();
                            if (TimeWardenEvent == 1)
                                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        }
                        break;
                    case 44641:
                        if (EmeraldWhelpFlag < 5)
                        {
                            EmeraldWhelp[EmeraldWhelpFlag] = creature->GetGUID();
                            ++EmeraldWhelpFlag;
                        }
                }
            }

            void OnGameObjectCreate(GameObject* go) {}

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_HALFUS: return HalfusGUID;
                }
                return 0;
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case DATA_HALFUS:                 return Encounter[0];
                    case DATA_THERALION_ANA_VALIONA:  return Encounter[1];
                    case DATA_ASCENDANT_COUNCIL:      return Encounter[2];
                    case DATA_CHOGALL:                return Encounter[3];
                    case DATA_SINESTRA:               return Encounter[4];
                    case DATA_STORM_RIDER:            return StormRiderEvent;
                    case DATA_THE_TIME_WARDEN:        return TimeWardenEvent;
                    case DATA_THE_SLATE_DRAGON:       return SlateDragonEvent;
                    case DATA_NETHER_SCION:           return NetherScionEvent;
                    case DATA_ORPHANED_EMERALD_WHELP: return EmeraldWhelpEvent;
                }
                return 0;
            }

            void ResetDragon(Creature* creature)
            {
                creature->setDeathState(ALIVE);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->GetMotionMaster()->MoveTargetedHome();
            }

            void SetData(uint32 Type, uint32 Data)
            {
                Encounter[Type] = Data;

                if (Type == DATA_HALFUS && Data == NOT_STARTED)
                {
                    if (NetherScionEvent == 1)
                        if (Creature* netherScion = instance->GetCreature(NetherScionGUID))
                            ResetDragon(netherScion);
                    if (SlateDragonEvent == 1)
                        if (Creature* slateDragon = instance->GetCreature(SlateDragonGUID))
                            ResetDragon(slateDragon);
                    if (StormRiderEvent == 1)
                        if (Creature* stormRider = instance->GetCreature(StormRiderGUID))
                            ResetDragon(stormRider);
                    if (TimeWardenEvent == 1)
                        if (Creature* timeWarden = instance->GetCreature(TimeWardenGUID))
                            ResetDragon(timeWarden);
                    if (EmeraldWhelpEvent == 1)
                        for (int i=0; i<5; ++i)
                            if (Creature* emeraldWhelp = instance->GetCreature(EmeraldWhelp[i]))
                                emeraldWhelp->AI()->Reset();
                }

                if (Data == DONE)
                {
                    RewardValorPoints();
                    SaveToDB();
                }
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "B T " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void RewardValorPoints()
            {
                Map::PlayerList const &PlList = instance->GetPlayers();

                if (PlList.isEmpty())
                    return;

                for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                    if (Player* player = i->getSource())
                        player->ModifyCurrency(396, 7000);
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

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'B' && dataHead2 == 'T')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        Encounter[i] = tmpState;
                    }
                } else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };
};

void AddSC_instance_bastion_of_twilight()
{
    new instance_bastion_of_twilight();
}