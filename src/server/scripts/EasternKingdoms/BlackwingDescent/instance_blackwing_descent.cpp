/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
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

#include "blackwing_descent.h"
#include "ScriptPCH.h"

class instance_blackwing_descent : public InstanceMapScript
{
    public:
        instance_blackwing_descent() : InstanceMapScript("instance_blackwing_descent", 669) { }

        struct instance_blackwing_descent_InstanceMapScript : public InstanceScript
        {
            instance_blackwing_descent_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
            }

            void OnCreatureCreate(Creature* creature)
            {
            }

            void OnGameObjectCreate(GameObject* go)
            {
            }

            uint64 GetData64(uint32 type)
            {
                return 0;
            }

            uint32 GetData(uint32 type)
            {
                return m_auiEncounter[type];
            }

            void SetData(uint32 uiType, uint32 uiData)
            {
                m_auiEncounter[uiType] = uiData;

                if (uiData == DONE)
                {
                    RewardValorPoints();
                    SaveToDB();
                }
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "B D " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void RewardValorPoints()
            {
                Map::PlayerList const &PlList = instance->GetPlayers();

                if (PlList.isEmpty())
                    return;

                for (Map::PlayerList::const_iterator i = PlList.begin(); i != PlList.end(); ++i)
                    if (Player* pPlayer = i->getSource())
                        pPlayer->ModifyCurrency(396, 7000);
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

                if (dataHead1 == 'B' && dataHead2 == 'D')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        m_auiEncounter[i] = tmpState;
                    }
                } else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

        private:
            uint32 m_auiEncounter[MAX_ENCOUNTER];
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_blackwing_descent_InstanceMapScript(map);
        }
};

void AddSC_instance_blackwing_descent()
{
    new instance_blackwing_descent();
}