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

/* ScriptData
SDName: Boss_Onyxia
SD%Complete: 95
SDComment: <Known bugs>
               Ground visual for Deep Breath effect;
               Not summoning whelps on phase 3 (lacks info)
           </Known bugs>
SDCategory: Onyxia's Lair
EndScriptData */

#include "ScriptPCH.h"
#include "onyxias_lair.h"

enum eYells
{
    SAY_AGGRO                   = -1249000,
    SAY_KILL                    = -1249001,
    SAY_PHASE_2_TRANS           = -1249002,
    SAY_PHASE_3_TRANS           = -1249003,
    EMOTE_BREATH                = -1249004,
};

enum eSpells
{
    // Phase 1 spells
    SPELL_WING_BUFFET           = 18500,
    SPELL_FLAME_BREATH          = 18435,
    SPELL_CLEAVE                = 68868,
    SPELL_TAIL_SWEEP            = 68867,

    // Phase 2 spells
    SPELL_DEEP_BREATH           = 23461,
    SPELL_FIREBALL              = 18392,

    //Not much choise about these. We have to make own defintion on the direction/start-end point
    SPELL_BREATH_NORTH_TO_SOUTH = 17086,                    // 20x in "array"
    SPELL_BREATH_SOUTH_TO_NORTH = 18351,                    // 11x in "array"

    SPELL_BREATH_EAST_TO_WEST   = 18576,                    // 7x in "array"
    SPELL_BREATH_WEST_TO_EAST   = 18609,                    // 7x in "array"

    SPELL_BREATH_SE_TO_NW       = 18564,                    // 12x in "array"
    SPELL_BREATH_NW_TO_SE       = 18584,                    // 12x in "array"
    SPELL_BREATH_SW_TO_NE       = 18596,                    // 12x in "array"
    SPELL_BREATH_NE_TO_SW       = 18617,                    // 12x in "array"

    //SPELL_BREATH                = 21131,                  // 8x in "array", different initial cast than the other arrays

    // Phase 3 spells
    SPELL_BELLOWING_ROAR         = 18431,
};

struct sOnyxMove
{
    uint32 locId;
    uint32 locIdEnd;
    uint32 spellId;
    float fX, fY, fZ;
};

static sOnyxMove aMoveData[]=
{
    {0, 1, SPELL_BREATH_WEST_TO_EAST,   -33.5561f, -182.682f, -56.9457f}, //west
    {1, 0, SPELL_BREATH_EAST_TO_WEST,   -31.4963f, -250.123f, -55.1278f}, //east
    {2, 4, SPELL_BREATH_NW_TO_SE,         6.8951f, -180.246f, -55.896f}, //north-west
    {3, 5, SPELL_BREATH_NE_TO_SW,        10.2191f, -247.912f, -55.896f}, //north-east
    {4, 2, SPELL_BREATH_SE_TO_NW,       -63.5156f, -240.096f, -55.477f}, //south-east
    {5, 3, SPELL_BREATH_SW_TO_NE,       -58.2509f, -189.020f, -55.790f}, //south-west
    {6, 7, SPELL_BREATH_SOUTH_TO_NORTH, -65.8444f, -213.809f, -55.2985f}, //south
    {7, 6, SPELL_BREATH_NORTH_TO_SOUTH,  22.8763f, -217.152f, -55.0548f}, //north
};

const Position MiddleRoomLocation = {-23.6155f, -215.357f, -55.7344f, 0.0f};

const Position Phase2Location = {-80.924f, -214.299f, -82.942f, 0.0f};

static Position aSpawnLocations[3]=
{
    //Whelps
    {-30.127f, -254.463f, -89.440f, 0.0f},
    {-30.817f, -177.106f, -89.258f, 0.0f},
    //Lair Guard
    {-145.950f, -212.831f, -68.659f, 0.0f}
};

class boss_onyxia : public CreatureScript
{
public:
    boss_onyxia() : CreatureScript("boss_onyxia") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_onyxiaAI (creature);
    }

    struct boss_onyxiaAI : public ScriptedAI
    {
        boss_onyxiaAI(Creature* creature) : ScriptedAI(creature), Summons(me)
        {
            instance = creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        SummonList Summons;

        uint32 phase;

        uint32 flameBreathTimer;
        uint32 cleaveTimer;
        uint32 tailSweepTimer;
        uint32 wingBuffetTimer;

        uint32 movePoint;
        uint32 movementTimer;
        sOnyxMove* _pPointData;

        uint32 fireballTimer;
        uint32 whelpTimer;
        uint32 lairGuardTimer;
        uint32 deepBreathTimer;

        uint32 bellowingRoarTimer;

        uint8 SummonWhelpCount;
        bool _bIsMoving;

        void Reset()
        {
            if (!IsCombatMovementAllowed())
                SetCombatMovement(true);

            phase = PHASE_START;

            flameBreathTimer = urand(10000, 20000);
            tailSweepTimer = urand(15000, 20000);
            cleaveTimer = urand(2000, 5000);
            wingBuffetTimer = urand(10000, 20000);

            movePoint = urand(0, 5);
            movementTimer = 14000;
            _pPointData = GetMoveData();

            fireballTimer = 15000;
            whelpTimer = 60000;
            lairGuardTimer = 60000;
            deepBreathTimer = 85000;

            bellowingRoarTimer = 30000;

            Summons.DespawnAll();
            SummonWhelpCount = 0;
            _bIsMoving = false;

            if (instance)
            {
                instance->SetData(DATA_ONYXIA, NOT_STARTED);
                instance->SetData(DATA_ONYXIA_PHASE, phase);
                instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT,  ACHIEV_TIMED_START_EVENT);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            me->SetInCombatWithZone();

            if (instance)
            {
                instance->SetData(DATA_ONYXIA, IN_PROGRESS);
                instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT,  ACHIEV_TIMED_START_EVENT);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
                instance->SetData(DATA_ONYXIA, DONE);

            Summons.DespawnAll();
        }

        void JustSummoned(Creature* summoned)
        {
            summoned->SetInCombatWithZone();
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                summoned->AI()->AttackStart(target);

            switch (summoned->GetEntry())
            {
                case NPC_WHELP:
                    ++SummonWhelpCount;
                    break;
                case NPC_LAIRGUARD:
                    summoned->setActive(true);
                    break;
            }
            Summons.Summon(summoned);
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            Summons.Despawn(summon);
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(SAY_KILL, me);
        }

        void SpellHit(Unit* /*pCaster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_BREATH_EAST_TO_WEST ||
                spell->Id == SPELL_BREATH_WEST_TO_EAST ||
                spell->Id == SPELL_BREATH_SE_TO_NW ||
                spell->Id == SPELL_BREATH_NW_TO_SE ||
                spell->Id == SPELL_BREATH_SW_TO_NE ||
                spell->Id == SPELL_BREATH_NE_TO_SW)
            {
                _pPointData = GetMoveData();
                movePoint = _pPointData->locIdEnd;

                me->SetSpeed(MOVE_FLIGHT, 1.5f);
                me->GetMotionMaster()->MovePoint(8, MiddleRoomLocation);
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                    case 8:
                        _pPointData = GetMoveData();
                        if (_pPointData)
                        {
                            me->SetSpeed(MOVE_FLIGHT, 1.0f);
                            me->GetMotionMaster()->MovePoint(_pPointData->locId, _pPointData->fX, _pPointData->fY, _pPointData->fZ);
                        }
                        break;
                    case 9:
                        me->GetMotionMaster()->MoveChase(me->getVictim());
                        bellowingRoarTimer = 1000;
                        break;
                    case 10:
                        me->SetFlying(true);
                        me->GetMotionMaster()->MovePoint(11, Phase2Location.GetPositionX(), Phase2Location.GetPositionY(), Phase2Location.GetPositionZ()+25);
                        me->SetSpeed(MOVE_FLIGHT, 1.0f);
                        DoScriptText(SAY_PHASE_2_TRANS, me);
                        if (instance)
                            instance->SetData(DATA_ONYXIA_PHASE, phase);
                        whelpTimer = 5000;
                        lairGuardTimer = 15000;
                        break;
                    case 11:
                        if (_pPointData)
                            me->GetMotionMaster()->MovePoint(_pPointData->locId, _pPointData->fX, _pPointData->fY, _pPointData->fZ);
                        me->GetMotionMaster()->Clear(false);
                        me->GetMotionMaster()->MoveIdle();

                        break;

                    default:
                        _bIsMoving = false;
                        break;
                }
            }
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spell)
        {
            //Workaround - Couldn't find a way to group this spells (All Eruption)
            if (((spell->Id >= 17086 && spell->Id <= 17095) ||
                (spell->Id == 17097) ||
                (spell->Id >= 18351 && spell->Id <= 18361) ||
                (spell->Id >= 18564 && spell->Id <= 18576) ||
                (spell->Id >= 18578 && spell->Id <= 18607) ||
                (spell->Id == 18609) ||
                (spell->Id >= 18611 && spell->Id <= 18628) ||
                (spell->Id >= 21132 && spell->Id <= 21133) ||
                (spell->Id >= 21135 && spell->Id <= 21139) ||
                (spell->Id >= 22191 && spell->Id <= 22202) ||
                (spell->Id >= 22267 && spell->Id <= 22268)) &&
                (target->GetTypeId() == TYPEID_PLAYER))
            {
                if (instance)
                {
                    instance->SetData(DATA_SHE_DEEP_BREATH_MORE, FAIL);
                }
            }
        }

        sOnyxMove* GetMoveData()
        {
            uint32 maxCount = sizeof(aMoveData)/sizeof(sOnyxMove);

            for (uint32 i = 0; i < maxCount; ++i)
            {
                if (aMoveData[i].locId == movePoint)
                    return &aMoveData[i];
            }

            return NULL;
        }

        void SetNextRandomPoint()
        {
            uint32 maxCount = sizeof(aMoveData)/sizeof(sOnyxMove);

            uint32 iTemp = rand()%(maxCount-1);

            if (iTemp >= movePoint)
                ++iTemp;

            movePoint = iTemp;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            //Common to PHASE_START && PHASE_END
            if (phase == PHASE_START || phase == PHASE_END)
            {
                //Specific to PHASE_START || PHASE_END
                if (phase == PHASE_START)
                {
                    if (HealthBelowPct(60))
                    {
                        SetCombatMovement(false);
                        phase = PHASE_BREATH;
                        me->GetMotionMaster()->MovePoint(10, Phase2Location);
                        return;
                    }
                }
                else
                {
                    if (bellowingRoarTimer <= diff)
                    {
                        DoCastVictim(SPELL_BELLOWING_ROAR);
                        // Eruption
                        GameObject* floor = NULL;
                        SkyFire::GameObjectInRangeCheck check(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 15);
                        SkyFire::GameObjectLastSearcher<SkyFire::GameObjectInRangeCheck> searcher(me, floor, check);
                        me->VisitNearbyGridObject(30, searcher);
                        if (instance && floor)
                            instance->SetData64(DATA_FLOOR_ERUPTION_GUID, floor->GetGUID());
                        bellowingRoarTimer = 30000;
                    }
                    else
                        bellowingRoarTimer -= diff;
                }

                if (flameBreathTimer <= diff)
                {
                    DoCastVictim(SPELL_FLAME_BREATH);
                    flameBreathTimer = urand(10000, 20000);
                }
                else
                    flameBreathTimer -= diff;

                if (tailSweepTimer <= diff)
                {
                    DoCastAOE(SPELL_TAIL_SWEEP);
                    tailSweepTimer = urand(15000, 20000);
                }
                else
                    tailSweepTimer -= diff;

                if (cleaveTimer <= diff)
                {
                    DoCastVictim(SPELL_CLEAVE);
                    cleaveTimer = urand(2000, 5000);
                }
                else
                    cleaveTimer -= diff;

                if (wingBuffetTimer <= diff)
                {
                    DoCastVictim(SPELL_WING_BUFFET);
                    wingBuffetTimer = urand(15000, 30000);
                }
                else
                    wingBuffetTimer -= diff;

                DoMeleeAttackIfReady();
            }
            else
            {
                if (HealthBelowPct(40))
                {
                    phase = PHASE_END;
                    if (instance)
                        instance->SetData(DATA_ONYXIA_PHASE, phase);
                    DoScriptText(SAY_PHASE_3_TRANS, me);

                    SetCombatMovement(true);
                    me->SetFlying(false);
                    _bIsMoving = false;
                    me->GetMotionMaster()->MovePoint(9, me->GetHomePosition());
                    return;
                }

                if (deepBreathTimer <= diff)
                {
                    if (!_bIsMoving)
                    {
                        if (me->IsNonMeleeSpellCasted(false))
                            me->InterruptNonMeleeSpells(false);

                        DoScriptText(EMOTE_BREATH, me);
                        DoCast(me, _pPointData->spellId);
                        deepBreathTimer = 70000;
                    }
                }
                else
                    deepBreathTimer -= diff;

                if (movementTimer <= diff)
                {
                    if (!_bIsMoving)
                    {
                        SetNextRandomPoint();
                        _pPointData = GetMoveData();

                        if (!_pPointData)
                            return;

                        me->GetMotionMaster()->MovePoint(_pPointData->locId, _pPointData->fX, _pPointData->fY, _pPointData->fZ);
                        _bIsMoving = true;
                        movementTimer = 25000;
                    }
                }
                else
                    movementTimer -= diff;

                if (fireballTimer <= diff)
                {
                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_FIREBALL);

                        fireballTimer = 8000;
                    }
                }
                else
                    fireballTimer -= diff;

                if (lairGuardTimer <= diff)
                {
                    me->SummonCreature(NPC_LAIRGUARD, aSpawnLocations[2].GetPositionX(), aSpawnLocations[2].GetPositionY(), aSpawnLocations[2].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN);
                    lairGuardTimer = 30000;
                }
                else
                    lairGuardTimer -= diff;

                if (whelpTimer <= diff)
                {
                    me->SummonCreature(NPC_WHELP, aSpawnLocations[0].GetPositionX(), aSpawnLocations[0].GetPositionY(), aSpawnLocations[0].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN);
                    me->SummonCreature(NPC_WHELP, aSpawnLocations[1].GetPositionX(), aSpawnLocations[1].GetPositionY(), aSpawnLocations[1].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN);
                    if (SummonWhelpCount >= RAID_MODE(20, 40))
                    {
                        SummonWhelpCount = 0;
                        whelpTimer = 90000;
                    }
                    else
                        whelpTimer = 500;
                }
                else
                    whelpTimer -= diff;
            }
        }
    };
};

void AddSC_boss_onyxia()
{
    new boss_onyxia();
}
