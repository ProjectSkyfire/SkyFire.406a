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
#include "gnomeregan.h"

#define    MAX_ENCOUNTER  1

class instance_gnomeregan : public InstanceMapScript
{
public:
    instance_gnomeregan() : InstanceMapScript("instance_gnomeregan", 90) {}

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_gnomeregan_InstanceMapScript(map);
    }

    struct instance_gnomeregan_InstanceMapScript : public InstanceScript
    {
        instance_gnomeregan_InstanceMapScript(Map* map) : InstanceScript(map) {}

        uint32 Encounter[MAX_ENCOUNTER];

        uint64 CaveInLeftGUID;
        uint64 CaveInRightGUID;

        uint64 BastmasterEmiShortfuseGUID;

        void Initialize()
        {
            memset(&Encounter, 0, sizeof(Encounter));

            CaveInLeftGUID                = 0;
            CaveInRightGUID               = 0;

            BastmasterEmiShortfuseGUID    = 0;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> Encounter[0];

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (Encounter[i] == IN_PROGRESS)
                    Encounter[i] = NOT_STARTED;
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_BLASTMASTER_EMI_SHORTFUSE: BastmasterEmiShortfuseGUID = creature->GetGUID(); break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_CAVE_IN_LEFT:
                    CaveInLeftGUID = go->GetGUID();
                    if (Encounter[0] == DONE || Encounter[0] == NOT_STARTED)
                        HandleGameObject(0, false, go);
                    break;
                case GO_CAVE_IN_RIGHT:
                    CaveInRightGUID = go->GetGUID();
                    if (Encounter[0] == DONE || Encounter[0] == NOT_STARTED)
                        HandleGameObject(0, false, go);
                    break;
            }
        }

        void SetData(uint32 Type, uint32 Data)
        {
            switch (Type)
            {
                case TYPE_EVENT:
                    Encounter[0] = Data;
                    if (Data == DONE)
                        SaveToDB();
                    break;
            }
        }

        uint32 GetData(uint32 Type)
        {
            switch (Type)
            {
                case TYPE_EVENT:    return Encounter[0];
            }
            return 0;
        }

        uint64 GetData64(uint32 Type)
        {
            switch (Type)
            {
                case DATA_GO_CAVE_IN_LEFT:              return CaveInLeftGUID;
                case DATA_GO_CAVE_IN_RIGHT:             return CaveInRightGUID;
                case DATA_NPC_BASTMASTER_EMI_SHORTFUSE: return BastmasterEmiShortfuseGUID;
            }

            return 0;
        }
    };
};

void AddSC_instance_gnomeregan()
{
    new instance_gnomeregan();
}
