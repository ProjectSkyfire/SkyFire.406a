/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 *
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScriptPCH.h"
#include "the_stonecore.h"

#define MAX_ENCOUNTER     4

class instance_the_stonecore : public InstanceMapScript
{
public:
    instance_the_stonecore() : InstanceMapScript("instance_the_stonecore", 725) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_the_stonecore_InstanceMapScript(map);
    }

    struct instance_the_stonecore_InstanceMapScript : public InstanceScript
    {
        instance_the_stonecore_InstanceMapScript(Map* map) : InstanceScript(map) {};

        uint64 uiCorborus;
        uint64 uiSlabhide;
        uint64 uiOzruk;
        uint64 uiHighPriestessAzil;
        uint32 uiTeamInInstance;
        uint32 uiEncounter[MAX_ENCOUNTER];

        void Initialize()
        {
             for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                 uiEncounter[i] = NOT_STARTED;

             uiCorborus = 0;
             uiSlabhide = 0;
             uiOzruk = 0;
             uiHighPriestessAzil = 0;
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;

             return false;
        }

        void OnCreatureCreate(Creature* pCreature, bool /*add*/)
        {
            Map::PlayerList const &players = instance->GetPlayers();

            if (!players.isEmpty())
            {
                if (Player* pPlayer = players.begin()->getSource())
                    uiTeamInInstance = pPlayer->GetTeam();
            }

            switch(pCreature->GetEntry())
            {
                case BOSS_CORBORUS:
                    uiCorborus = pCreature->GetGUID();
                    break;
                case BOSS_SLABHIDE:
                    uiSlabhide = pCreature->GetGUID();
                    break;
                case BOSS_OZRUK:
                    uiOzruk = pCreature->GetGUID();
                    break;
                case BOSS_HIGH_PRIESTESS_AZIL:
                    uiHighPriestessAzil = pCreature->GetGUID();
                    break;
            }
        }

        uint64 GetData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_CORBORUS:                    return uiCorborus;
                case DATA_SLABHIDE:                    return uiSlabhide;
                case DATA_OZRUK:                    return uiOzruk;
                case DATA_HIGH_PRIESTESS_AZIL:        return uiHighPriestessAzil;
            }

            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case DATA_CORBORUS_EVENT:
                    uiEncounter[0] = data;
                    break;
                case DATA_SLABHIDE_EVENT:
                    uiEncounter[1] = data;
                    break;
                case DATA_OZRUK_EVENT:
                    uiEncounter[2] = data;
                    break;
                case DATA_HIGH_PRIESTESS_AZIL_EVENT:
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
                case DATA_CORBORUS_EVENT:                return uiEncounter[0];
                case DATA_SLABHIDE_EVENT:                return uiEncounter[1];
                case DATA_OZRUK_EVENT:                    return uiEncounter[2];
                case DATA_HIGH_PRIESTESS_AZIL_EVENT:    return uiEncounter[3];
            }

            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;

            std::ostringstream saveStream;
            saveStream << "P S " << uiEncounter[0] << " " << uiEncounter[1]  << " " << uiEncounter[2]  << " " << uiEncounter[3];

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

            if (dataHead1 == 'P' && dataHead2 == 'S')
            {
                uiEncounter[0] = data0;
                uiEncounter[1] = data1;
                uiEncounter[2] = data2;
                uiEncounter[3] = data3;

                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        uiEncounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_the_stonecore()
{
    new instance_the_stonecore();
}