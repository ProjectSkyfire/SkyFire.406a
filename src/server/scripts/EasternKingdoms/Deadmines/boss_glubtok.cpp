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

/* TODO:
ScriptData
SDName:
SD%Complete:
SDComment:
EndScriptData */

#include "ScriptPCH.h"
#include "deadmines.h"

enum eSpels
{
    SPELL_ARCANE_POWER      = 88009,
    SPELL_FIST_OF_FLAME     = 87859,
    SPELL_FIST_OF_FROST     = 87861,
    SPELL_FIRE_BLOSSOM      = 88129,
    SPELL_FIRE_BLOSSOM_H    = 91286,
    SPELL_FROST_BLOSSOM     = 88169,
    SPELL_FROST_BLOSSOM_H   = 91287
};

class boss_glubtok : public CreatureScript
{
public:
    boss_glubtok() : CreatureScript("boss_glubtok") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_glubtokAI (creature);
    }

    struct boss_glubtokAI : public ScriptedAI
    {
        boss_glubtokAI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        uint32 uiTrashTimer;
        uint32 uiSlamTimer;
        uint32 uiNimbleReflexesTimer;

        uint8 uiHealth;

        uint32 uiPhase;
        uint32 uiTimer;
        // TODO: MAKE THE CORRECT SCRIPT :)
    };
};

void AddSC_boss_glubtok()
{
    new boss_glubtok();
}