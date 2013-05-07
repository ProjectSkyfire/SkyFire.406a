/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
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

#include "vortex_pinnacle.h"
#include "ScriptPCH.h"

#define MAX_ENCOUNTER 3

class instance_vortex_pinnacle : public InstanceMapScript
{
    public:
        instance_vortex_pinnacle() : InstanceMapScript("instance_vortex_pinnacle", 657) { }

        struct instance_vortex_pinnacle_InstanceMapScript : public InstanceScript
        {
            instance_vortex_pinnacle_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetBossNumber(MAX_ENCOUNTER);
                Initialize();
            }

            uint64 GrandVizierErtanGUID;
            uint64 AltairusGUID;
            uint64 AsaadGUID;

            void Initialize()
            {
                SetBossNumber(MAX_ENCOUNTER);
                GrandVizierErtanGUID    = 0;
                AltairusGUID            = 0;
                AsaadGUID               = 0;
            }

            void OnCreatureCreate(Creature* creature)
            {
                switch (creature->GetEntry())
                {
                    case BOSS_GRAND_VIZIER_ERTAN:
                        GrandVizierErtanGUID = creature->GetGUID();
                        break;
                    case BOSS_ALTAIRUS:
                        AltairusGUID = creature->GetGUID();
                        break;
                    case BOSS_ASAAD:
                        AsaadGUID = creature->GetGUID();
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
            }

            void OnGameObjectRemove(GameObject* go)
            {
            }

            bool SetBossState(uint32 data, EncounterState state)
            {
                if (!InstanceScript::SetBossState(data, state))
                    return false;

                return true;
            }

            uint64 GetData64(uint32 data)
            {
                switch (data)
                {
                    case DATA_GRAND_VIZIER_ERTAN:
                        return GrandVizierErtanGUID;
                    case DATA_ALTAIRUS:
                        return AltairusGUID;
                    case DATA_ASAAD:
                        return AsaadGUID;
                    default:
                        break;
                }
                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "V P " << GetBossSaveData();

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

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'V' && dataHead2 == 'P')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };
        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_vortex_pinnacle_InstanceMapScript(map);
        }
};

void AddSC_instance_vortex_pinnacle()
{
    new instance_vortex_pinnacle();
}
