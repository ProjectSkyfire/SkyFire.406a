/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

 /* ScriptData
 SFName: boss_Lich_king
 SF%Complete: 0%
 SFComment: new script for tc implementation.
 SFCategory: Halls of Reflection
 EndScriptData */

#include "ScriptPCH.h"
#include "halls_of_reflection.h"
#include "ScriptedEscortAI.h"

enum
{
    SPELL_WINTER                       = 69780,
    SPELL_FURY_OF_FROSTMOURNE          = 70063,
    SPELL_SOUL_REAPER                  = 73797,
    SPELL_RAISE_DEAD                   = 69818,
    SPELL_ICE_PRISON                   = 69708,
    SPELL_DARK_ARROW                   = 70194,
    SPELL_HARVEST_SOUL                 = 70070,

    //Raging gnoul
    SPELL_EMERGE_VISUAL                = 50142,
    SPELL_GNOUL_JUMP                   = 70150,

    //Witch Doctor
    SPELL_COURSE_OF_DOOM               = 70144,
    H_SPELL_COURSE_OF_DOOM             = 70183,
    SPELL_SHADOW_BOLT_VOLLEY           = 70145,
    H_SPELL_SHADOW_BOLT_VOLLEY         = 70184,
    SPELL_SHADOW_BOLT                  = 70080,
    H_SPELL_SHADOW_BOLT                = 70182,

    //Lumbering Abomination
    SPELL_ABON_STRIKE                  = 40505,
    SPELL_VOMIT_SPRAY                  = 70176,
    H_SPELL_VOMIT_SPRAY                = 70181,

    SAY_LICH_KING_WALL_01              = -1594486,
    SAY_LICH_KING_WALL_02              = -1594491,
    SAY_LICH_KING_GNOUL                = -1594482,
    SAY_LICH_KING_ABON                 = -1594483,
    SAY_LICH_KING_WINTER               = -1594481,
    SAY_LICH_KING_END_DUN              = -1594504,
    SAY_LICH_KING_WIN                  = -1594485,
};

class boss_lich_king_hor : public CreatureScript
{
public:
    boss_lich_king_hor() : CreatureScript("boss_lich_king_hor") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lich_king_horAI(creature);
    }

    struct boss_lich_king_horAI : public npc_escortAI
    {
        boss_lich_king_horAI(Creature* creature) : npc_escortAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        uint32 Step;
        uint32 StepTimer;
        uint32 Wall;
        bool StartEscort;
        bool NonFight;
        float walkSpeed;

        void Reset()
        {
            if (!instance)
                return;

            NonFight    = false;
            StartEscort = false;
            walkSpeed   = 1.0f;
            Wall        = 0;
        }

        void JustDied(Unit* killer) { }

        void WaypointReached(uint32 i)
        {
            if (instance->GetData(DATA_ICE_WALL_1) == IN_PROGRESS)
            {
                Wall = 1;
                SetEscortPaused(true);
            }

            if (instance->GetData(DATA_ICE_WALL_2) == IN_PROGRESS)
            {
                Wall = 2;
                SetEscortPaused(true);
            }

            if (instance->GetData(DATA_ICE_WALL_3) == IN_PROGRESS)
            {
                Wall = 3;
                SetEscortPaused(true);
            }

            if (instance->GetData(DATA_ICE_WALL_4) == IN_PROGRESS)
            {
                Wall = 4;
                SetEscortPaused(true);
            }

            switch (i)
            {
                case 66:
                    SetEscortPaused(true);
                    instance->SetData(DATA_LICHKING_EVENT, SPECIAL);
                    DoScriptText(SAY_LICH_KING_END_DUN, me);
                    if (Creature* lider = ((Creature*)Unit::GetUnit((*me), instance->GetData64(DATA_ESCAPE_LIDER))))
                        me->CastSpell(lider, SPELL_HARVEST_SOUL, false);
                    me->setActive(false);
                    break;
            }
        }

        void AttackStart(Unit* who)
        {
            if (!instance || !who)
                return;

            if (NonFight)
                return;

            if (instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS || who->GetTypeId() == TYPEID_PLAYER)
                return;

            npc_escortAI::AttackStart(who);
        }

        void JustSummoned(Creature* summoned)
        {
            if (!instance || !summoned)
                return;

            summoned->SetInCombatWithZone();
            summoned->setActive(true);

            instance->SetData(DATA_SUMMONS, 1);
            if (Unit* lider = Unit::GetUnit((*me), instance->GetData64(DATA_ESCAPE_LIDER)))
            {
                summoned->GetMotionMaster()->MoveChase(lider);
                summoned->AddThreat(lider, 100.0f);
            }
        }

        void CallGuard(uint32 GuardID)
        {
            me->SummonCreature(GuardID,(me->GetPositionX()-5)+rand()%10, (me->GetPositionY()-5)+rand()%10, me->GetPositionZ(),4.17f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000);
        }

        void Wall01()
        {
            switch (Step)
            {
                case 0:
                    instance->SetData(DATA_SUMMONS, 3);
                    DoScriptText(SAY_LICH_KING_WALL_01, me);
                    StepTimer = 2000;
                    ++Step;
                    break;
                case 1:
                    DoCast(me, SPELL_RAISE_DEAD);
                    DoScriptText(SAY_LICH_KING_GNOUL, me);
                    StepTimer = 7000;
                    ++Step;
                    break;
                case 2:
                    DoCast(me, SPELL_WINTER);
                    DoScriptText(SAY_LICH_KING_WINTER, me);
                    me->SetSpeed(MOVE_WALK, walkSpeed, true);
                    StepTimer = 1000;
                    ++Step;
                    break;
                case 3:
                    StepTimer = 2000;
                    ++Step;
                    break;
                case 4:
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    instance->SetData(DATA_ICE_WALL_1, DONE);
                    StepTimer = 100;
                    Step      = 0;
                    Wall      = 0;
                    SetEscortPaused(false);
                    break;
            }
        }

        void Wall02()
        {
            switch (Step)
            {
                case 0:
                    instance->SetData(DATA_SUMMONS, 3);
                    DoScriptText(SAY_LICH_KING_GNOUL, me);
                    DoCast(me, SPELL_RAISE_DEAD);
                    StepTimer = 6000;
                    ++Step;
                    break;
                case 1:
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_ABON);
                    instance->SetData(DATA_ICE_WALL_2, DONE);
                    StepTimer = 5000;
                    Step      = 0;
                    Wall      = 0;
                    SetEscortPaused(false);
                    break;
            }
        }

        void Wall03()
        {
            switch (Step)
            {
                case 0:
                    instance->SetData(DATA_SUMMONS, 3);
                    DoCast(me, SPELL_RAISE_DEAD);
                    DoScriptText(SAY_LICH_KING_GNOUL, me);
                    StepTimer = 6000;
                    ++Step;
                    break;
                case 1:
                    DoScriptText(SAY_LICH_KING_ABON, me);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_ABON);
                    CallGuard(NPC_ABON);
                    instance->SetData(DATA_ICE_WALL_3, DONE);
                    StepTimer = 5000;
                    Step      = 0;
                    Wall      = 0;
                    SetEscortPaused(false);
                    break;
            }
        }

        void Wall04()
        {
            switch (Step)
            {
                case 0:
                    instance->SetData(DATA_SUMMONS, 3);
                    DoCast(me, SPELL_RAISE_DEAD);
                    DoScriptText(SAY_LICH_KING_GNOUL, me);
                    StepTimer = 6000;
                    ++Step;
                    break;
                case 1:
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_ABON);
                    CallGuard(NPC_ABON);
                    StepTimer = 15000;
                    ++Step;
                    break;
                case 2:
                    DoScriptText(SAY_LICH_KING_ABON, me);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    CallGuard(NPC_RISEN_WITCH_DOCTOR);
                    instance->SetData(DATA_ICE_WALL_4, DONE);
                    Wall = 0;
                    SetEscortPaused(false);
                    ++Step;
                    break;
            }
        }

        void UpdateEscortAI(const uint32 diff)
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_LICHKING_EVENT) == NOT_STARTED || instance->GetData(DATA_LICHKING_EVENT) == FAIL)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }

            if (me->isInCombat() && instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS)
            {
                npc_escortAI::EnterEvadeMode();
            }

            // Start chase for leader
            if (instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS && StartEscort != true)
            {
                StartEscort = true;
                me->RemoveAurasDueToSpell(SPELL_ICE_PRISON);
                me->RemoveAurasDueToSpell(SPELL_DARK_ARROW);
                me->setActive(true);
                NonFight = true;
                me->AttackStop();
                me->SetSpeed(MOVE_WALK, 2.5f, true);
                Start(false, false);
                Step = 0;
                StepTimer = 100;
            }

            // Leader caught, wipe
            if (Creature* lider = ((Creature*)Unit::GetUnit((*me), instance->GetData64(DATA_ESCAPE_LIDER))))
            {
                if (lider->IsWithinDistInMap(me, 2.0f) && instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS)
                {
                    me->setActive(false);
                    SetEscortPaused(false);
                    me->StopMoving();
                    DoScriptText(SAY_LICH_KING_WIN, me);
                    me->CastSpell(me, SPELL_FURY_OF_FROSTMOURNE, false);
                    me->DealDamage(lider, lider->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }

            if (Wall == 1)
            {
                if (StepTimer < diff)
                    Wall01();
                else
                    StepTimer -= diff;
            }

            if (Wall == 2)
            {
                if (StepTimer < diff)
                    Wall02();
                else
                    StepTimer -= diff;
            }

            if (Wall == 3)
            {
                if (StepTimer < diff)
                    Wall03();
                else
                    StepTimer -= diff;
            }

            if (Wall == 4)
            {
                if (StepTimer < diff)
                    Wall04();
                else
                    StepTimer -= diff;
            }
            return;
        }
    };
};

class npc_raging_gnoul : public CreatureScript
{
public:
    npc_raging_gnoul() : CreatureScript("npc_raging_gnoul") { }

    struct npc_raging_gnoulAI : public ScriptedAI
    {
        npc_raging_gnoulAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            me->setActive(true);
            Reset();
        }

        InstanceScript* instance;
        uint32 EmergeTimer;
        bool Emerge;
        bool Jumped;
        uint64 LiderGUID;

        void Reset()
        {
            DoCast(me, SPELL_EMERGE_VISUAL);
            EmergeTimer = 4000;
            Emerge = false;
            Jumped = false;
        }

        void JustDied(Unit* killer)
        {
            if (!instance)
                return;

            instance->SetData(DATA_SUMMONS, 0);
        }

        void AttackStart(Unit* who)
        {
            if (!who)
                return;

            if (Emerge == false)
                return;

            ScriptedAI::AttackStart(who);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS)
            {
                LiderGUID = instance->GetData64(DATA_ESCAPE_LIDER);
                Creature* lider = ((Creature*)Unit::GetUnit((*me), LiderGUID));

                if (Emerge != true)
                {
                    if (EmergeTimer < diff)
                    {
                        //me->RemoveFlag(SPLINEFLAG_WALKING | MOVEMENTFLAG_WALKING, true);
                        Emerge = true;
                        LiderGUID = instance->GetData64(DATA_ESCAPE_LIDER);
                        if (lider)
                        {
                            DoResetThreat();
                            me->AI()->AttackStart(lider);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveChase(lider);
                        }
                    }
                    else
                        EmergeTimer -= diff;
                }

                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f))
                {
                    if (!Jumped && me->IsWithinDistInMap(target, 30.0f) && !me->IsWithinDistInMap(target, 5.0f))
                    {
                        Jumped = true;
                        DoCast(target, SPELL_GNOUL_JUMP);
                    }
                }
            }
            else if (instance->GetData(DATA_LICHKING_EVENT) == FAIL || instance->GetData(DATA_LICHKING_EVENT) == NOT_STARTED)
                me->DespawnOrUnsummon();

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_raging_gnoulAI(creature);
    }
};

class npc_risen_witch_doctor : public CreatureScript
{
public:
    npc_risen_witch_doctor() : CreatureScript("npc_risen_witch_doctor") { }

    struct npc_risen_witch_doctorAI : public ScriptedAI
    {
        npc_risen_witch_doctorAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            me->setActive(true);
            Reset();
        }

        InstanceScript* instance;
        uint32 EmergeTimer;
        bool Emerge;
        uint64 LiderGUID;
        uint32 BoltTimer;
        uint32 BoltVolleyTimer;
        uint32 CurseTimer;

        void Reset()
        {
            DoCast(me, SPELL_EMERGE_VISUAL);
            EmergeTimer = 5000;
            BoltTimer = 6000;
            BoltVolleyTimer = 15000;
            CurseTimer = 7000;
            Emerge = false;
        }

        void JustDied(Unit* killer)
        {
            if (!instance)
                return;

            instance->SetData(DATA_SUMMONS, 0);
        }

        void AttackStart(Unit* who)
        {
            if (!who)
                return;

            if (Emerge == false)
                return;

            ScriptedAI::AttackStart(who);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance)
                return;

            if (instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS)
            {
                if (Emerge != true)
                {
                    if (EmergeTimer < diff)
                    {
                        Emerge = true;
                        LiderGUID = instance->GetData64(DATA_ESCAPE_LIDER);
                        if (Creature* lider = ((Creature*)Unit::GetUnit((*me), LiderGUID)))
                        {
                            DoResetThreat();
                            me->AI()->AttackStart(lider);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MoveChase(lider);
                        }
                    }
                    else
                        EmergeTimer -= diff;
                }

                if (CurseTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        DoCast(target, SPELL_COURSE_OF_DOOM);
                    CurseTimer = urand(10000, 15000);
                } else CurseTimer -= diff;

                if (BoltTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                        DoCast(target, SPELL_SHADOW_BOLT);
                    BoltTimer = urand(2000, 3000);
                } else BoltTimer -= diff;

                if (BoltVolleyTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                        DoCast(target, SPELL_SHADOW_BOLT_VOLLEY);
                    BoltVolleyTimer = urand(15000, 22000);
                } else BoltVolleyTimer -= diff;
            }
            else if (instance->GetData(DATA_LICHKING_EVENT) == FAIL || instance->GetData(DATA_LICHKING_EVENT) == NOT_STARTED)
                me->DespawnOrUnsummon();

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_risen_witch_doctorAI(creature);
    }
};

class npc_abon : public CreatureScript
{
public:
    npc_abon() : CreatureScript("npc_abon") { }

    struct npc_abonAI : public ScriptedAI
    {
        npc_abonAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = (InstanceScript*)creature->GetInstanceScript();
            me->setActive(true);
            Reset();
        }

        InstanceScript* instance;
        uint64 LiderGUID;
        bool Walk;
        uint32 StrikeTimer;
        uint32 VomitTimer;

        void Reset()
        {
            Walk = false;
            VomitTimer = 15000;
            StrikeTimer = 6000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!instance) return;

            if (instance->GetData(DATA_LICHKING_EVENT) == IN_PROGRESS)
            {
                if (Walk != true)
                {
                    Walk = true;
                    LiderGUID = instance->GetData64(DATA_ESCAPE_LIDER);
                    if (Creature* lider = ((Creature*)Unit::GetUnit((*me), LiderGUID)))
                    {
                        DoResetThreat();
                        me->AI()->AttackStart(lider);
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MoveChase(lider);
                    }
                }

                if (StrikeTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                        DoCast(target, SPELL_ABON_STRIKE);
                    StrikeTimer = urand(7000, 9000);
                } else StrikeTimer -= diff;

                if (VomitTimer < diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                        DoCast(target, SPELL_VOMIT_SPRAY);
                    VomitTimer = urand(15000, 20000);
                } else VomitTimer -= diff;
            }
            else if (instance->GetData(DATA_LICHKING_EVENT) == FAIL || instance->GetData(DATA_LICHKING_EVENT) == NOT_STARTED)
                me->DespawnOrUnsummon();
            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* killer)
        {
            if (!instance)
                return;

            instance->SetData(DATA_SUMMONS, 0);
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_abonAI(creature);
    }
};

void AddSC_boss_lich_king_hr()
{
    new boss_lich_king_hor();
    new npc_raging_gnoul();
    new npc_risen_witch_doctor();
    new npc_abon();
}
