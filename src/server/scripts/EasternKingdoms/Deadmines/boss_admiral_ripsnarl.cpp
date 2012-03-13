/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2010-2011 MigCore <http://wow-mig.ru/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

 /* GetPlay team (c)    //then remove this!
    Admiral Ripsnarl   
    %: 10
 */ 
 
#include "ScriptPCH.h"
#include "deadmines.h"


enum Yells
{
    SAY_AGGRO     = "Ah.. Fresh meat!"
    SAY_SPELL_1   = "Do you feel that chill running up your spine? .. The fog is rolling in."
    SAY_SPELL_2   = "I can smell your fear.."
    SAY_VANISH    = "I will rip your heart from your chest!
    SAY_KILL      = "Your blood only increases my hunger!"
    SAY_DEATH     = "You will.. not find her.. until it is too late..
};

enum Spells
{
    SPELL_GO_F_T    = 88836,
    SPELL_GO_F_T_H  = 91863,
    SPELL_SWIPE     = 88839,
    SPELL_SWIPE_H   = 91859,
    SPELL_T_F_B_A   = 88736,
    SPELL_VANISH    = 29448, /*Karazhan-Moroes lol */
};

enum Events
{
    EVENT_CLAVE         = 1,
    EVENT_STEALTH       = 2,
    EVENT_JUMP          = 3,
    EVENT_RES_ATTACK    = 4,
    EVENT_VANISH        = 5,
    EVENT_CHARGE        = 6,
};

enum Phases
{
    PHASE_ONE           = 1,
    PHASE_TWO           = 2,
    PHASE_THREE         = 3,
    PHASE_FOUR          = 4,
    
    PHASE_ONE_MASK      = 1 << PHASE_ONE,
    PHASE_TWO_MASK      = 1 << PHASE_TWO,
    PHASE_THREE_MASK    = 1 << PHASE_THREE,
    PHASE_FOUR_MASK     = 1 << PHASE_FOUR,
};

enum MiscData
{
    POINT_JUMP          = 0,
};

Position const jumpOne   = {-63.6682f, -838.3784f, 41.2662f, 1.6932f};
Position const jumpTwo   = {-55.6585f, -821.7366f, 41.9944f, 2.8006f};
Position const jumpThree = {-68.6040f, -806.9727f, 40.7819f, 4.8088f};

class boss_admiral_ripsnarl : public CreatureScript
{
  public:
      boss_admiral_ripsnarl() : CreatureScript("boss_admiral_ripsnarl") { }

      struct boss_admiral_ripsnarlAI : public BossAI
      {
          boss_admiral_ripsnarlAI(Creature* creature) : BossAI(creature)
          {
                DoCast(me, SPELL_T_F_B_A, true);
          }
          
          void InitializeAI()
          {
              if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(FoSScriptName))
                  me->IsAIEnabled = false;
              else if (!me->isDead())
                  Reset();

          void Reset() 
          {
              events.Reset();
              events.SetPhase(PHASE_ONE);

              instance->SetBossState(DATA_RIPSNARL, NOT_STARTED);
          }

          void EnterCombat(Unit* /*who*/)
          {
              DoScriptText(SAY_AGGRO, me);
              DoCast(me, SPELL_PERMAFROST);
              events.ScheduleEvent(EVENT_CLAVE, urand(2000, 5000));

              instance->SetBossState(DATA_RIPSNARL, IN_PROGRESS);
          }          
                   
          void KilledUnit(Unit* who)
          {
              if (who->GetTypeId() == TYPEID_PLAYER)
                  DoScriptText(SAY_KILL, me);
          }
          
          void JustDied(Unit* /*killer*/)
          {
                DoScriptText(SAY_DEATH, me);

                instance->SetBossState(DATA_RIPSNARL, DONE);
          }
          
          void DamageTaken(Unit* /*attacker*/, uint32& /*uidamage*/)
          {
                if (events.GetPhaseMask() & PHASE_ONE_MASK && !HealthAbovePct(75))
                {
                    events.SetPhase(PHASE_TWO);
                    events.DelayEvents(3000);
                    //DoCast(me, SPELL_VANISH);
                    events.ScheduleEvent(EVENT_JUMP, 1500);
                    return;
                }

                if (events.GetPhaseMask() & PHASE_TWO_MASK && !HealthAbovePct(50))
                {
                    events.SetPhase(PHASE_THREE);
                    events.DelayEvents(3000);
                    //DoCast(me, SPELL_VANISH);
                    events.ScheduleEvent(EVENT_JUMP, 1500);
                    return;
                    
                if (events.GetPhaseMask() & PHASE_TWO_THREE && !HealthAbovePct(25))
                {
                    events.SetPhase(PHASE_FOUR);
                    events.DelayEvents(3000);
                    //DoCast(me, SPELL_VANISH);
                    events.ScheduleEvent(EVENT_JUMP, 1500);
                    return;
                }
          }
          
          void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE || id != POINT_JUMP)
                    return;

                if (events.GetPhaseMask() & PHASE_TWO_MASK)
                    me->RemoveAurasDueToSpell(SPELL_VANISH);
                if (events.GetPhaseMask() & PHASE_THREE_MASK)
                    me->RemoveAurasDueToSpell(SPELL_VANISH);
                if (events.GetPhaseMask() & PHASE_FOUR_MASK)
                    me->RemoveAurasDueToSpell(SPELL_VANISH);

                events.ScheduleEvent(EVENT_RESUME_ATTACK, 3000);
            }

          void UpdateAI(const uint32 diff)
          {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CLAVE:
                            DoCast(target, SPELL_SWIPE_H);
                            events.ScheduleEvent(EVENT_CLAVE, urand(2000, 5000));
                            break;
                        /*case EVENT_CHARGE
                            DoCast(me, EVENT_CHARGE);
                            events.ScheduleEvent(EVENT_CHARGE, 40000, 0, PHASE_TWO);
                            break;*/
                        case EVENT_CHARGE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                DoCast(target, SPELL_GO_F_T_H);
                            events.ScheduleEvent(SPELL_GO_F_T_H, urand(20000, 23000));
                            break;
                        case EVENT_JUMP:
                            me->AttackStop();
                            if (events.GetPhaseMask() & PHASE_TWO_MASK)
                                me->GetMotionMaster()->MoveJump(jumpOne.GetPositionX(), jumpOne.GetPositionY(), jumpOne.GetPositionZ(), 25.0f, 15.0f);
                            else if (events.GetPhaseMask() & PHASE_THREE_MASK)
                                me->GetMotionMaster()->MoveJump(jumpTwo.GetPositionX(), jumpTwo.GetPositionY(), jumpTwo.GetPositionZ(), 25.0f, 15.0f);
                            else if (events.GetPhaseMask() & PHASE_FOUR_MASK)
                                me->GetMotionMaster()->MoveJump(jumpThree.GetPositionX(), jumpThree.GetPositionY(), jumpThree.GetPositionZ(), 25.0f, 15.0f);
                            break;
                        case EVENT_RESUME_ATTACK:
                            if (events.GetPhaseMask() & PHASE_TWO_MASK)
                                events.ScheduleEvent(EVENT_CHARGE, 20000, 0, PHASE_TWO);
                            else if (events.GetPhaseMask() & PHASE_THREE_MASK)
                                events.ScheduleEvent(EVENT_CHARGE, 18000, 0, PHASE_THREE);
                            else if (events.GetPhaseMask() & PHASE_FOUR_MASK)
                                events.ScheduleEvent(EVENT_CHARGE, 19000, 0, PHASE_FOUR);
                            AttackStart(me->getVictim());
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
      };
      
      CreatureAI* GetAI(Creature* creature) const
      {
          return new boss_admiral_ripsnarlAI (creature);
      }
};

void AddSC_boss_admiral_ripsnarl()
{
    new boss_admiral_ripsnarl();
}