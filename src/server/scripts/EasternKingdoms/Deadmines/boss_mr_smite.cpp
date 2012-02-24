/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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
#include "deadmines.h"

enum eSpels
{
    SPELL_TRASH             = 3391,
    SPELL_SMITE_STOMP       = 6432,
    SPELL_SMITE_SLAM        = 6435,
    SPELL_NIMBLE_REFLEXES   = 6264,

    EQUIP_SWORD             = 5191,
    EQUIP_MACE              = 7230,

    SAY_AGGRO               = -1036001
};

class boss_mr_smite : public CreatureScript
{
public:
    boss_mr_smite() : CreatureScript("boss_mr_smite") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_mr_smiteAI (creature);
    }

    struct boss_mr_smiteAI : public ScriptedAI
    {
        boss_mr_smiteAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 TrashTimer;
        uint32 SlamTimer;
        uint32 NimbleReflexesTimer;

        uint8 Health;

        uint32 Phase;
        uint32 Timer;

        void Reset()
        {
            TrashTimer = urand(5000, 9000);
            SlamTimer = 9000;
            NimbleReflexesTimer = urand(15500, 31600);

            Health = 0;

            Phase = 0;
            Timer = 0;

            SetEquipmentSlots(false, EQUIP_SWORD, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
        }

        void EnterCombat(Unit* /*who*/)
        {
           DoScriptText(SAY_AGGRO, me);
        }

        bool bCheckChances()
        {
            uint32 Chances = urand(0, 99);
            if (Chances <= 15)
                return false;
            else
                return true;
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;
            /* Start SkyFireAI */
            if (TrashTimer <= Diff)
            {
                if (bCheckChances())
                    DoCast(me, SPELL_TRASH);
                TrashTimer = urand(6000, 15500);
            } else TrashTimer -= Diff;

            if (SlamTimer <= Diff)
            {
                if (bCheckChances())
                    DoCast(me->getVictim(), SPELL_SMITE_SLAM);
                SlamTimer = 11000;
            } else SlamTimer -= Diff;

            if (NimbleReflexesTimer <= Diff)
            {
                if (bCheckChances())
                    DoCast(me, SPELL_NIMBLE_REFLEXES);
                NimbleReflexesTimer = urand(27300, 60100);
            } else NimbleReflexesTimer -= Diff;
        /*END SkyFireAI*/

            if ((Health == 0 && !HealthAbovePct(66)) || (Health == 1 && !HealthAbovePct(33)))
            {
                ++Health;
                DoCastAOE(SPELL_SMITE_STOMP, false);
                SetCombatMovement(false);
                if (instance)
                    if (GameObject* go = GameObject::GetGameObject((*me), instance->GetData64(DATA_SMITE_CHEST)))
                    {
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(1, go->GetPositionX() - 3.0f, go->GetPositionY(), go->GetPositionZ());
                    }
            }

            if (Phase)
            {
                if (Timer <= Diff)
                {
                    switch (Phase)
                    {
                        case 1:
                            me->HandleEmoteCommand(EMOTE_STATE_KNEEL); //doesn't work?
                            Timer = 1000;
                            Phase = 2;
                            break;
                        case 2:
                            if (Health == 1)
                                SetEquipmentSlots(false, EQUIP_SWORD, EQUIP_SWORD, EQUIP_NO_CHANGE);
                            else
                                SetEquipmentSlots(false, EQUIP_MACE, EQUIP_UNEQUIP, EQUIP_NO_CHANGE);
                            Timer = 500;
                            Phase = 3;
                            break;
                        case 3:
                            SetCombatMovement(true);
                            me->GetMotionMaster()->MoveChase(me->getVictim(), me->_CombatDistance);
                            Phase = 0;
                            break;
                    }
                } else Timer -= Diff;
            }

            DoMeleeAttackIfReady();
        }

        void MovementInform(uint32 Type, uint32 /*Id*/)
        {
            if (Type != POINT_MOTION_TYPE)
                return;

            Timer = 1500;
            Phase = 1;
        }
    };
};
void AddSC_boss_mr_smite()
{
    new boss_mr_smite();
}