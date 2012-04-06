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

//add here most rarely modified headers to speed up debug build compilation

#include "WorldSocket.h"        // must be first to make ACE happy with ACE includes in it
#include "Common.h"
#include "MapManager.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectDefines.h"
#include "Opcodes.h"
#include "SharedDefines.h"
#include "ObjectMgr.h"
#include "AchievementMgrBase.h"
#include "AchievementMgr.h"
#include "GuildAchievementMgr.h"
#include "SmartAI.h"
#include "SmartScript.h"
#include "SmartScriptMgr.h"
#include "CreatureAI.h"
#include "CreatureAIFactory.h"
#include "CreatureAIImpl.h"
#include "CreatureAIRegistry.h"
#include "CreatureAISelector.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "ScriptedGossip.h"
#include "ScriptedSimpleAI.h"
#include "CreatureEventAI.h"
#include "CreatureEventAIMgr.h"
#include "CombatAI.h"
#include "GameObjectAI.h"
#include "GuardAI.h"
#include "PassiveAI.h"
#include "PetAI.h"
#include "ReactorAI.h"
#include "TotemAI.h"
#include "UnitAI.h"
#include "AddonMgr.h"
#include "AccountMgr.h"
#include "AuctionHouseMgr.h"
#include "Calendar.h"
#include "UnitEvents.h"
#include "HostileRefManager.h"
#include "ThreatManager.h"
#include "DisableMgr.h"
#include "ScriptSystem.h"
#include "ConditionMgr.h"
#include "ScriptMgr.h"
#include "ScriptLoader.h"
