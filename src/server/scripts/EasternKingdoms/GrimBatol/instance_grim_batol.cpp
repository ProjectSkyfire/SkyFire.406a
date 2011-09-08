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

#include "ScriptPCH.h"
#include "grim_batol.h"

#define ENCOUNTERS 4

/* Boss Encounters
   General Umbriss
   Forgemaster Throngus
   Drahga Shadowburner
   Erudax
 */

class instance_grim_batol : public InstanceMapScript
{
public:
    instance_grim_batol() : InstanceMapScript("instance_grim_batol", 670) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_grim_batol_InstanceMapScript(map);
    }

    struct instance_grim_batol_InstanceMapScript: public InstanceScript
    {
        instance_grim_batol_InstanceMapScript(InstanceMap* map) : InstanceScript(map) {}

        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiGeneralUmbriss;
        uint64 uiForgemasterThrongus;
        uint64 uiDrahgaShadowburner;
        uint64 uiErudax;
        uint64 uiTeamInInstance;

        void Initialize()
        {
            uiGeneralUmbriss = 0;
            uiForgemasterThrongus = 0;
            uiDrahgaShadowburner = 0;
            uiErudax = 0;

            for(uint8 i=0 ; i<ENCOUNTERS; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i=0; i < ENCOUNTERS; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }
            return false;
        }

        void OnCreatureCreate(Creature* pCreature, bool )
        {
            switch(pCreature->GetEntry())
            {
                 case BOSS_GENERAL_UMBRISS:
                     uiGeneralUmbriss = pCreature->GetGUID();
                     break;
                 case BOSS_FORGEMASTER_THRONGUS:
                     uiForgemasterThrongus = pCreature->GetGUID();
                     break;
                 case BOSS_DRAHGA_SHADOWBURNER:
                     uiDrahgaShadowburner = pCreature->GetGUID();
                     break;
                 case BOSS_ERUDAX:
                     uiErudax = pCreature->GetGUID();
                     break;
            }
        }

        uint64 getData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_GENERAL_UMBRISS:
                    return uiGeneralUmbriss;
                case DATA_FORGEMASTER_THRONGUS:
                    return uiForgemasterThrongus;
                case DATA_DRAHGA_SHADOWBURNER:
                    return uiDrahgaShadowburner;
                case DATA_ERUDAX:
                    return uiErudax;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case DATA_GENERAL_UMBRISS_EVENT:
                    uiEncounter[0] = data;
                    break;
                case DATA_FORGEMASTER_THRONGUS_EVENT:
                    uiEncounter[1] = data;
                    break;
                case DATA_DRAHGA_SHADOWBURNER_EVENT:
                    uiEncounter[2] = data;
                    break;
                case DATA_ERUDAX_EVENT:
                    uiEncounter[3] = data;
                    break;
            }

           if (data == DONE)
               SaveToDB();
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case DATA_GENERAL_UMBRISS_EVENT:
                    return uiEncounter[0];
                case DATA_FORGEMASTER_THRONGUS_EVENT:
                    return uiEncounter[1];
                case DATA_DRAHGA_SHADOWBURNER_EVENT:
                    return uiEncounter[2];
                case DATA_ERUDAX_EVENT:
                    return uiEncounter[3];
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "G B" << uiEncounter[0] << " " << uiEncounter[1]  << " " << uiEncounter[2]  << " " << uiEncounter[3];
            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
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
            uint16 data0, data1, data2, data3;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3;

            if (dataHead1 == 'G' && dataHead2 == 'B')
            {
                uiEncounter[0] = data0;
                uiEncounter[1] = data1;
                uiEncounter[2] = data2;
                uiEncounter[3] = data3;

                for(uint8 i=0; i < ENCOUNTERS; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        uiEncounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_grim_batol()
{
    new instance_grim_batol();
}