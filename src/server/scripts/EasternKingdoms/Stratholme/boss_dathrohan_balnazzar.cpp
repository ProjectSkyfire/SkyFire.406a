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
SDName: Boss_Dathrohan_Balnazzar
SD%Complete: 95
SDComment: Possibly need to fix/improve summons after death
SDCategory: Stratholme
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    //Dathrohan spells
    SPELL_CRUSADERSHAMMER           = 17286,                //AOE stun
    SPELL_CRUSADERSTRIKE            = 17281,
    SPELL_HOLYSTRIKE                = 17284,                //weapon dmg +3

    //Transform
    SPELL_BALNAZZARTRANSFORM        = 17288,                //restore full HP/mana, trigger spell Balnazzar Transform Stun

    //Balnazzar spells
    SPELL_SHADOWSHOCK               = 17399,
    SPELL_MINDBLAST                 = 17287,
    SPELL_PSYCHICSCREAM             = 13704,
    SPELL_SLEEP                     = 12098,
    SPELL_MINDCONTROL               = 15690,

    NPC_DATHROHAN                   = 10812,
    NPC_BALNAZZAR                   = 10813,
    NPC_ZOMBIE                      = 10698                 //probably incorrect
};

struct SummonDef
{
    float _fX, _fY, _fZ, _fOrient;
};

SummonDef SummonPoint[]=
{
    {3444.156f, -3090.626f, 135.002f, 2.240f},                 //G1 front, left
    {3449.123f, -3087.009f, 135.002f, 2.240f},                 //G1 front, right
    {3446.246f, -3093.466f, 135.002f, 2.240f},                 //G1 back left
    {3451.160f, -3089.904f, 135.002f, 2.240f},                 //G1 back, right

    {3457.995f, -3080.916f, 135.002f, 3.784f},                 //G2 front, left
    {3454.302f, -3076.330f, 135.002f, 3.784f},                 //G2 front, right
    {3460.975f, -3078.901f, 135.002f, 3.784f},                 //G2 back left
    {3457.338f, -3073.979f, 135.002f, 3.784f}                   //G2 back, right
};

class boss_dathrohan_balnazzar : public CreatureScript
{
public:
    boss_dathrohan_balnazzar() : CreatureScript("boss_dathrohan_balnazzar") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_dathrohan_balnazzarAI (creature);
    }

    struct boss_dathrohan_balnazzarAI : public ScriptedAI
    {
        boss_dathrohan_balnazzarAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 CrusadersHammer_Timer;
        uint32 CrusaderStrike_Timer;
        uint32 MindBlast_Timer;
        uint32 HolyStrike_Timer;
        uint32 ShadowShock_Timer;
        uint32 PsychicScream_Timer;
        uint32 DeepSleep_Timer;
        uint32 MindControl_Timer;
        bool _bTransformed;

        void Reset()
        {
            CrusadersHammer_Timer = 8000;
            CrusaderStrike_Timer  = 12000;
            MindBlast_Timer       = 6000;
            HolyStrike_Timer      = 18000;
            ShadowShock_Timer     = 4000;
            PsychicScream_Timer   = 16000;
            DeepSleep_Timer       = 20000;
            MindControl_Timer     = 10000;
            _bTransformed = false;

            if (me->GetEntry() == NPC_BALNAZZAR)
                me->UpdateEntry(NPC_DATHROHAN);
        }

        void JustDied(Unit* /*Victim*/)
        {
            static uint32 Count = sizeof(SummonPoint)/sizeof(SummonDef);

            for (uint8 i=0; i<Count; ++i)
                me->SummonCreature(NPC_ZOMBIE,
                SummonPoint[i]._fX, SummonPoint[i]._fY, SummonPoint[i]._fZ, SummonPoint[i]._fOrient,
                TEMPSUMMON_TIMED_DESPAWN, HOUR*IN_MILLISECONDS);
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            //START NOT TRANSFORMED
            if (!_bTransformed)
            {
                //MindBlast
                if (MindBlast_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_MINDBLAST);
                    MindBlast_Timer = urand(15000, 20000);
                } else MindBlast_Timer -= Diff;

                //CrusadersHammer
                if (CrusadersHammer_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_CRUSADERSHAMMER);
                    CrusadersHammer_Timer = 12000;
                } else CrusadersHammer_Timer -= Diff;

                //CrusaderStrike
                if (CrusaderStrike_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_CRUSADERSTRIKE);
                    CrusaderStrike_Timer = 15000;
                } else CrusaderStrike_Timer -= Diff;

                //HolyStrike
                if (HolyStrike_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_HOLYSTRIKE);
                    HolyStrike_Timer = 15000;
                } else HolyStrike_Timer -= Diff;

                //BalnazzarTransform
                if (HealthBelowPct(40))
                {
                    if (me->IsNonMeleeSpellCasted(false))
                        me->InterruptNonMeleeSpells(false);

                    //restore hp, mana and stun
                    DoCast(me, SPELL_BALNAZZARTRANSFORM);
                    me->UpdateEntry(NPC_BALNAZZAR);
                    _bTransformed = true;
                }
            }
            else
            {
                //MindBlast
                if (MindBlast_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_MINDBLAST);
                    MindBlast_Timer = urand(15000, 20000);
                } else MindBlast_Timer -= Diff;

                //ShadowShock
                if (ShadowShock_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_SHADOWSHOCK);
                    ShadowShock_Timer = 11000;
                } else ShadowShock_Timer -= Diff;

                //PsychicScream
                if (PsychicScream_Timer <= Diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_PSYCHICSCREAM);

                    PsychicScream_Timer = 20000;
                } else PsychicScream_Timer -= Diff;

                //DeepSleep
                if (DeepSleep_Timer <= Diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        DoCast(target, SPELL_SLEEP);

                    DeepSleep_Timer = 15000;
                } else DeepSleep_Timer -= Diff;

                //MindControl
                if (MindControl_Timer <= Diff)
                {
                    DoCast(me->getVictim(), SPELL_MINDCONTROL);
                    MindControl_Timer = 15000;
                } else MindControl_Timer -= Diff;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_dathrohan_balnazzar()
{
    new boss_dathrohan_balnazzar();
}
