/*
 * Copyright (C) 2011-2013 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2013 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Arlokk
SD%Complete: 95
SDComment: Wrong cleave and red aura is missing.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptPCH.h"
#include "zulgurub.h"

enum eYells
{
    SAY_AGGRO                   = -1309011,
    SAY_FEAST_PANTHER           = -1309012,
    SAY_DEATH                   = -1309013,
};

enum eSpells
{
    SPELL_SHADOWWORDPAIN        = 23952,
    SPELL_GOUGE                 = 24698,
    SPELL_MARK                  = 24210,
    SPELL_CLEAVE                = 26350,        //Perhaps not right. Not a red aura...
    SPELL_PANTHER_TRANSFORM     = 24190,

    MODEL_ID_NORMAL             = 15218,
    MODEL_ID_PANTHER            = 15215,
    MODEL_ID_BLANK              = 11686,

    NPC_ZULIAN_PROWLER          = 15101
};

class boss_arlokk : public CreatureScript
{
    public:
        boss_arlokk() : CreatureScript("boss_arlokk") {}

        struct boss_arlokkAI : public ScriptedAI
        {
            boss_arlokkAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            uint32 ShadowWordPain_Timer;
            uint32 Gouge_Timer;
            uint32 Mark_Timer;
            uint32 Cleave_Timer;
            uint32 Vanish_Timer;
            uint32 Visible_Timer;

            uint32 Summon_Timer;
            uint32 SummonCount;

            Unit* _pMarkedTarget;
            uint64 MarkedTargetGUID;

            bool _bIsPhaseTwo;
            bool _bIsVanished;

            void Reset()
            {
                ShadowWordPain_Timer     = 8000;
                Gouge_Timer              = 14000;
                Mark_Timer               = 35000;
                Cleave_Timer             = 4000;
                Vanish_Timer             = 60000;
                Visible_Timer            = 6000;

                Summon_Timer             = 5000;
                SummonCount              = 0;

                _bIsPhaseTwo             = false;
                _bIsVanished             = false;

                MarkedTargetGUID         = 0;

                me->SetDisplayId(MODEL_ID_NORMAL);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoScriptText(SAY_AGGRO, me);
            }

            void JustReachedHome()
            {
                if (instance)
                    instance->SetData(DATA_ARLOKK, NOT_STARTED);

                //we should be summoned, so despawn
                me->DespawnOrUnsummon();
            }

            void JustDied(Unit* /*killer*/)
            {
                DoScriptText(SAY_DEATH, me);

                me->SetDisplayId(MODEL_ID_NORMAL);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                if (instance)
                    instance->SetData(DATA_ARLOKK, DONE);
            }

            void DoSummonPhanters()
            {
                if (Unit* markedTarget = Unit::GetUnit(*me, MarkedTargetGUID))
                    DoScriptText(SAY_FEAST_PANTHER, me, markedTarget);

                me->SummonCreature(NPC_ZULIAN_PROWLER, -11532.7998f, -1649.6734f, 41.4800f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                me->SummonCreature(NPC_ZULIAN_PROWLER, -11532.9970f, -1606.4840f, 41.2979f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
            }

            void JustSummoned(Creature* summoned)
            {
                if (Unit* markedTarget = Unit::GetUnit(*me, MarkedTargetGUID))
                    summoned->AI()->AttackStart(markedTarget);

                ++SummonCount;
            }

            void UpdateAI(const uint32 Diff)
            {
                if (!UpdateVictim())
                    return;

                if (!_bIsPhaseTwo)
                {
                    if (ShadowWordPain_Timer <= Diff)
                    {
                        DoCast(me->getVictim(), SPELL_SHADOWWORDPAIN);
                        ShadowWordPain_Timer = 15000;
                    }
                    else
                        ShadowWordPain_Timer -= Diff;

                    if (Mark_Timer <= Diff)
                    {
                        Unit* markedTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);

                        if (markedTarget)
                        {
                            DoCast(markedTarget, SPELL_MARK);
                            MarkedTargetGUID = markedTarget->GetGUID();
                        }
                        else
                            sLog->outError("TSCR: boss_arlokk could not accuire MarkedTarget.");

                        Mark_Timer = 15000;
                    }
                    else
                        Mark_Timer -= Diff;
                }
                else
                {
                    //Cleave_Timer
                    if (Cleave_Timer <= Diff)
                    {
                        DoCast(me->getVictim(), SPELL_CLEAVE);
                        Cleave_Timer = 16000;
                    }
                    else
                        Cleave_Timer -= Diff;

                    //Gouge_Timer
                    if (Gouge_Timer <= Diff)
                    {
                        DoCast(me->getVictim(), SPELL_GOUGE);

                        DoModifyThreatPercent(me->getVictim(), -80);

                        Gouge_Timer = 17000+rand()%10000;
                    }
                    else
                        Gouge_Timer -= Diff;
                }

                if (SummonCount <= 30)
                {
                    if (Summon_Timer <= Diff)
                    {
                        DoSummonPhanters();
                        Summon_Timer = 5000;
                    }
                    else
                        Summon_Timer -= Diff;
                }

                if (Vanish_Timer <= Diff)
                {
                    //Invisble Model
                    me->SetDisplayId(MODEL_ID_BLANK);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                    me->AttackStop();
                    DoResetThreat();

                    _bIsVanished = true;

                    Vanish_Timer  = 45000;
                    Visible_Timer = 6000;
                }
                else
                    Vanish_Timer -= Diff;

                if (_bIsVanished)
                {
                    if (Visible_Timer <= Diff)
                    {
                        //The Panther Model
                        me->SetDisplayId(MODEL_ID_PANTHER);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                        const CreatureTemplate* cinfo = me->GetCreatureTemplate();
                        me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, (cinfo->mindmg +((cinfo->mindmg/100) * 35)));
                        me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, (cinfo->maxdmg +((cinfo->maxdmg/100) * 35)));
                        me->UpdateDamagePhysical(BASE_ATTACK);

                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            AttackStart(target);

                        _bIsPhaseTwo = true;
                        _bIsVanished = false;
                    }
                    else
                        Visible_Timer -= Diff;
                }
                else
                    DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_arlokkAI(creature);
        }
};

class go_gong_of_bethekk : public GameObjectScript
{
    public:
        go_gong_of_bethekk() : GameObjectScript("go_gong_of_bethekk") {}

        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            if (InstanceScript* instance = go->GetInstanceScript())
            {
                if (instance->GetData(DATA_ARLOKK) == DONE || instance->GetData(DATA_ARLOKK) == IN_PROGRESS)
                    return true;

                instance->SetData(DATA_ARLOKK, IN_PROGRESS);
                return true;
            }

            return true;
        }
};

void AddSC_boss_arlokk()
{
    new boss_arlokk();
    new go_gong_of_bethekk();
}
