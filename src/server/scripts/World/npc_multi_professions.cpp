/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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
Name: Npc_Multi_Professions Trainer
%Complete: 0
Comment: Provides support for multi-profession trainer new to cataclysm
Category: NPCs
EndScriptData */

#include "ScriptPCH.h"

/*
INSERT INTO `script_texts` VALUES ('0', '-2000000', 'I can teach you the basics of any gathering profession, but that's all. To learn more than an apprentice's skills, youu'll need to visit a specialist dedicated to only one profession. You can learn up to two professions: Two gathering, two production, or one of each. Secondary skills like Archaelogy, cooking, First Aid, and Fishing don't count twards your two professions; you can learn as many of those as you like.', null, null, null, null, null, null, null, null, '0', '1', '0', '0', 'INTRO0');
INSERT INTO `script_texts` VALUES ('0', '-2000001', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO1');
INSERT INTO `script_texts` VALUES ('0', '-2000002', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO2');
INSERT INTO `script_texts` VALUES ('0', '-2000003', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO3');
INSERT INTO `script_texts` VALUES ('0', '-2000004', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO4');
INSERT INTO `script_texts` VALUES ('0', '-2000005', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO5');
INSERT INTO `script_texts` VALUES ('0', '-2000006', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO6');
INSERT INTO `script_texts` VALUES ('0', '-2000007', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO7');
INSERT INTO `script_texts` VALUES ('0', '-2000008', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO8');
INSERT INTO `script_texts` VALUES ('0', '-2000009', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO9');
INSERT INTO `script_texts` VALUES ('0', '-2000010', 'Reserved', null, null, null, null, null, null, null, null, '16261', '1', '0', '0', 'INTRO10');
*/

enum eEnums          // Text placeholder
{
    SAY_INTRO0       = -2000000,
    SAY_INTRO1       = -2000001,
    SAY_INTRO2       = -2000002,
    SAY_INTRO3       = -2000003,
    SAY_INTRO4       = -2000004,
    SAY_INTRO5       = -2000005,
    SAY_INTRO6       = -2000006,
    SAY_INTRO7       = -2000007,
    SAY_INTRO8       = -2000008,
    SAY_INTRO9       = -2000009,
    SAY_INTRO10      = -2000010
};