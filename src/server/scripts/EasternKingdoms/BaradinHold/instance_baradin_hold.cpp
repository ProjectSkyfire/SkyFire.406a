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

#include"ScriptPCH.h"
#include"baradin_hold.h"

class instance_baradin_hold: public InstanceMapScript
{
public:
    instance_baradin_hold() : InstanceMapScript("instance_baradin_hold", 757) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_baradin_hold_InstanceMapScript(map);
    }

    struct instance_baradin_hold_InstanceMapScript: public InstanceScript
    {
        instance_baradin_hold_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
        {
            SetBossNumber(MAX_ENCOUNTER);
        }

        /*
        void Initialize()
        {
            memset(&guid, 0, sizeof(guid));
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case CREATURE_ARGALOTH: guid[DATA_ARGALOTH] = creature->GetGUID(); break;
            case CREATURE_OCCUTHAR: guid[DATA_OCCUTHAR] = creature->GetGUID(); break;
            }
        }

        uint64 GetData64(uint32 identifier) { return guid[identifier]; }

    private:
        uint64 guid[MAX_ENCOUNTER];
    */
    };
};

void AddSC_instance_baradin_hold()
{
    new instance_baradin_hold();
}
