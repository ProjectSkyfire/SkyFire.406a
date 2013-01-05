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
#include "onyxias_lair.h"

class instance_onyxias_lair : public InstanceMapScript
{
public:
    instance_onyxias_lair() : InstanceMapScript("instance_onyxias_lair", 249) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_onyxias_lair_InstanceMapScript(map);
    }

    struct instance_onyxias_lair_InstanceMapScript : public InstanceScript
    {
        instance_onyxias_lair_InstanceMapScript(Map* map) : InstanceScript(map) {}

        //Eruption is a BFS graph problem
        //One map to remember all floor, one map to keep floor that still need to erupt and one queue to know what needs to be removed
        std::map<uint64, uint32> FloorEruptionGUID[2];
        std::queue<uint64> FloorEruptionGUIDQueue;

        uint64 OnyxiasGUID;
        uint32 OnyxiaLiftoffTimer;
        uint32 ManyWhelpsCounter;
        uint32 EruptTimer;

        uint8  Encounter[MAX_ENCOUNTER];

        bool   _bAchievManyWhelpsHandleIt;
        bool   _bAchievSheDeepBreathMore;

        void Initialize()
        {
            memset(&Encounter, 0, sizeof(Encounter));

            OnyxiasGUID = 0;
            OnyxiaLiftoffTimer = 0;
            ManyWhelpsCounter = 0;
            _bAchievManyWhelpsHandleIt = false;
            _bAchievSheDeepBreathMore = true;

            EruptTimer = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_ONYXIA:
                    OnyxiasGUID = creature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* go)
        {
            if ((go->GetGOInfo()->displayId == 4392 || go->GetGOInfo()->displayId == 4472) && go->GetGOInfo()->trap.spellId == 17731)
            {
                FloorEruptionGUID[0].insert(std::make_pair(go->GetGUID(), 0));
                return;
            }

            switch (go->GetEntry())
            {
                case GO_WHELP_SPAWNER:
                    Position goPos;
                    go->GetPosition(&goPos);
                    if (Creature* temp = go->SummonCreature(NPC_WHELP, goPos, TEMPSUMMON_CORPSE_DESPAWN))
                    {
                        temp->SetInCombatWithZone();
                        ++ManyWhelpsCounter;
                    }
                    break;
            }
        }

        void OnGameObjectRemove(GameObject* go)
        {
            if ((go->GetGOInfo()->displayId == 4392 || go->GetGOInfo()->displayId == 4472) && go->GetGOInfo()->trap.spellId == 17731)
            {
                FloorEruptionGUID[0].erase(go->GetGUID());
                return;
            }
        }

        void FloorEruption(uint64 floorEruptedGUID)
        {
            if (GameObject* floorEruption = instance->GetGameObject(floorEruptedGUID))
            {
                // THIS GOB IS A TRAP - What shall i do? =(
                // Cast it spell? Copyed Heigan method
                floorEruption->SendCustomAnim(floorEruption->GetGoAnimProgress());
                floorEruption->CastSpell(NULL, Difficulty(instance->GetSpawnMode()) == RAID_DIFFICULTY_10MAN_NORMAL ? 17731 : 69294);                                  // floorEruption->GetGOInfo()->trap.spellId

                // Get all immediatly nearby floors
                std::list<GameObject*> nearFloorList;
                SkyFire::GameObjectInRangeCheck check(floorEruption->GetPositionX(), floorEruption->GetPositionY(), floorEruption->GetPositionZ(), 15);
                SkyFire::GameObjectListSearcher<SkyFire::GameObjectInRangeCheck> searcher(floorEruption, nearFloorList, check);
                floorEruption->VisitNearbyGridObject(999, searcher);
                // remove all that are not present on FloorEruptionGUID[1] and update treeLen on each GUID
                for (std::list<GameObject*>::const_iterator itr = nearFloorList.begin(); itr != nearFloorList.end(); ++itr)
                {
                    if (((*itr)->GetGOInfo()->displayId == 4392 || (*itr)->GetGOInfo()->displayId == 4472) && (*itr)->GetGOInfo()->trap.spellId == 17731)
                    {
                        uint64 nearFloorGUID = (*itr)->GetGUID();
                        if (FloorEruptionGUID[1].find(nearFloorGUID) != FloorEruptionGUID[1].end() && (*FloorEruptionGUID[1].find(nearFloorGUID)).second == 0)
                        {
                            (*FloorEruptionGUID[1].find(nearFloorGUID)).second = (*FloorEruptionGUID[1].find(floorEruptedGUID)).second+1;
                            FloorEruptionGUIDQueue.push(nearFloorGUID);
                        }
                    }
                }
            }
            FloorEruptionGUID[1].erase(floorEruptedGUID);
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_ONYXIA:
                    Encounter[0] = data;
                    if (data == IN_PROGRESS)
                        SetData(DATA_SHE_DEEP_BREATH_MORE, IN_PROGRESS);
                    break;
                case DATA_ONYXIA_PHASE:
                    if (data == PHASE_BREATH) //Used to mark the liftoff phase
                    {
                        _bAchievManyWhelpsHandleIt = false;
                        ManyWhelpsCounter = 0;
                        OnyxiaLiftoffTimer = 10 * IN_MILLISECONDS;
                    }
                    break;
                case DATA_SHE_DEEP_BREATH_MORE:
                    if (data == IN_PROGRESS)
                    {
                        _bAchievSheDeepBreathMore = true;
                    }
                    else if (data == FAIL)
                    {
                        _bAchievSheDeepBreathMore = false;
                    }
                    break;
            }

            if (type < MAX_ENCOUNTER && data == DONE)
                SaveToDB();
        }

        void SetData64(uint32 type, uint64 data)
        {
            switch (type)
            {
                case DATA_FLOOR_ERUPTION_GUID:
                    FloorEruptionGUID[1] = FloorEruptionGUID[0];
                    FloorEruptionGUIDQueue.push(data);
                    EruptTimer = 2500;
                    break;
            }
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
                case DATA_ONYXIA:
                    return Encounter[0];
            }

            return 0;
        }

        uint64 GetData64(uint32 data)
        {
            switch (data)
            {
                case DATA_ONYXIA_GUID:
                    return OnyxiasGUID;
            }

            return 0;
        }

        void Update(uint32 diff)
        {
            if (GetData(DATA_ONYXIA) == IN_PROGRESS)
            {
                if (OnyxiaLiftoffTimer && OnyxiaLiftoffTimer <= diff)
                {
                    OnyxiaLiftoffTimer = 0;
                    if (ManyWhelpsCounter >= 50)
                        _bAchievManyWhelpsHandleIt = true;
                } else OnyxiaLiftoffTimer -= diff;
            }

            if (!FloorEruptionGUIDQueue.empty())
            {
                if (EruptTimer <= diff)
                {
                    uint32 treeHeight = 0;
                    do
                    {
                        treeHeight = (*FloorEruptionGUID[1].find(FloorEruptionGUIDQueue.front())).second;
                        FloorEruption(FloorEruptionGUIDQueue.front());
                        FloorEruptionGUIDQueue.pop();
                    } while (!FloorEruptionGUIDQueue.empty() && (*FloorEruptionGUID[1].find(FloorEruptionGUIDQueue.front())).second == treeHeight);
                    EruptTimer = 1000;
                }
                else
                    EruptTimer -= diff;
            }
        }

        bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target*/ = NULL, uint32 /*miscvalue1*/ = 0)
        {
            switch (criteria_id)
            {
                case ACHIEV_CRITERIA_MANY_WHELPS_10_PLAYER:  // Criteria for achievement 4403: Many Whelps! Handle It! (10 player) Hatch 50 eggs in 10s
                case ACHIEV_CRITERIA_MANY_WHELPS_25_PLAYER:  // Criteria for achievement 4406: Many Whelps! Handle It! (25 player) Hatch 50 eggs in 10s
                    return _bAchievManyWhelpsHandleIt;
                case ACHIEV_CRITERIA_DEEP_BREATH_10_PLAYER:  // Criteria for achievement 4404: She Deep Breaths More (10 player) Everybody evade Deep Breath
                case ACHIEV_CRITERIA_DEEP_BREATH_25_PLAYER:  // Criteria for achievement 4407: She Deep Breaths More (25 player) Everybody evade Deep Breath
                    return _bAchievSheDeepBreathMore;
            }
            return false;
        }
    };
};

void AddSC_instance_onyxias_lair()
{
    new instance_onyxias_lair();
}
