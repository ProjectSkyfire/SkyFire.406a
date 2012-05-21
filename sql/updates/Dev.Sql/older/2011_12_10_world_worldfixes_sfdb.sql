
-- Fix quest-requirements for "A Meeting With Fate"
UPDATE quest_template SET RequiredRaces=690 WHERE entry=12755;

-- Fix tailoring quest "Cloth Scavenging"
UPDATE quest_template SET SkillOrClassMask=197, RequiredSkillValue=350 WHERE entry=13270;

-- Cleanup some spawns
DELETE FROM creature where guid IN (322816, 294962);

-- Set Tina Skyden's proper faction 
UPDATE creature_template SET faction_A=72, faction_H=72 WHERE entry=42426;

-- Fix many erroneus flight-masters' factions
UPDATE creature_template SET faction_A=210, faction_H=210 WHERE npcflag = (npcflag|8192) AND faction_a=72;

-- Cleanup some spawns
DELETE FROM creature where guid IN (322816, 294962);

-- Set Tina Skyden's proper faction 
UPDATE creature_template SET faction_A=72, faction_H=72 WHERE entry=42426;

-- Fix many erroneus flight-masters' factions
UPDATE creature_template SET faction_A=210, faction_H=210 WHERE npcflag = (npcflag|8192) AND faction_a=72;

-- Update High General Abbendis faction
UPDATE creature_template SET faction_A=66, faction_H=66 WHERE entry=29077;

-- Update "Tainted Arcane Wraith" for quest "Felendren the Banished"
UPDATE creature_template SET faction_A=14, faction_H=14 WHERE entry=15298;

-- Delete custom stuff from Landro: no more unoffy sells will be accomplished
UPDATE creature_template SET npcflag=1 WHERE entry=17249;
DELETE FROM npc_vendor WHERE entry=17249;

-- Fix Shazdar's items extended cost
DELETE FROM npc_vendor WHERE entry=49737;
INSERT INTO npc_vendor VALUES
(49737, 0, 62786, 0, 0, 0),
(49737, 0, 62787, 0, 0, 0),
(49737, 0, 62788, 0, 0, 0),
(49737, 0, 65406, 0, 0, 3322),
(49737, 0, 65407, 0, 0, 3322),
(49737, 0, 65408, 0, 0, 3322),
(49737, 0, 65409, 0, 0, 3322),
(49737, 0, 65410, 0, 0, 3322),
(49737, 0, 65411, 0, 0, 3322),
(49737, 0, 65412, 0, 0, 3322),
(49737, 0, 65413, 0, 0, 3322),
(49737, 0, 65414, 0, 0, 3322),
(49737, 0, 65415, 0, 0, 3322),
(49737, 0, 65416, 0, 0, 3322),
(49737, 0, 65417, 0, 0, 3322),
(49737, 0, 65418, 0, 0, 3322),
(49737, 0, 65419, 0, 0, 3322),
(49737, 0, 65420, 0, 0, 3322),
(49737, 0, 65421, 0, 0, 3322),
(49737, 0, 65422, 0, 0, 3322),
(49737, 0, 65423, 0, 0, 3322),
(49737, 0, 65424, 0, 0, 3322),
(49737, 0, 65425, 0, 0, 3322),
(49737, 0, 65426, 0, 0, 3322),
(49737, 0, 65427, 0, 0, 3322),
(49737, 0, 65428, 0, 0, 3322),
(49737, 0, 65429, 0, 0, 3322),
(49737, 0, 65430, 0, 0, 3322),
(49737, 0, 65431, 0, 0, 3322),
(49737, 0, 65432, 0, 0, 3023),
(49737, 0, 65433, 0, 0, 3023),
(49737, 0, 65513, 0, 0, 3024);

-- Update Rejuvenation training cost by Gart Mistrunner
UPDATE npc_trainer SET spellcost=60 WHERE spell=774 AND entry=3060;

-- Fix "Eitrigg" and templates and add their spawn locations
UPDATE creature_template SET minlevel=85, maxlevel=85, faction_A=76, faction_H=76 WHERE entry=48568;
UPDATE creature_template SET faction_A=189, faction_H=189, minlevel=85, maxlevel=85 WHERE entry=48109;
DELETE FROM creature WHERE id IN (48568, 48109);
INSERT INTO creature (id, map, spawnMask, phaseMask, modelid, equipment_id, position_x, position_y, position_z, 
orientation, spawntimesecs, spawndist, currentwaypoint, curhealth, curmana, DeathState, MovementType, 
npcflag, unit_flags, dynamicflags) VALUES
(48568, 0, 1, 1, 0, 0, -7917.25, -1868.87, 132.498, 3.98464, 300, 0, 0, 840, 0, 0, 0, 0, 0, 0),
(48109, 0, 1, 65534, 0, 0, -7947.22, -1927.15, 132.241, 0.45032, 300, 0, 0, 84, 0, 0, 0, 0, 0, 0);

-- Update Dual Talent Cost: 1000g -> 10g + fixed a little typo
UPDATE gossip_menu_option SET option_text="Purchase a Dual Talent Specialization" WHERE option_text="Purchase a Dual Talent Specialization.";
UPDATE gossip_menu_option SET box_money=100000 WHERE option_text="Purchase a Dual Talent Specialization" AND box_money=10000000;

-- Correct Frenzy Proc
DELETE FROM `spell_proc_event` WHERE `entry` = 20784;
INSERT INTO `spell_proc_event` VALUES
(20784,0x00,0,0x00000000,0x00000000,0x00000000,0x00000000,0x00000002,0,0,0);

-- Fix Goblin Quest: The Replacements
DELETE FROM `gameobject` WHERE `id`=201603;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(201603, 648, 1, 1, -8153.8, 1342.73, 22.7424, 5.96035, 0, 0, 0.160716, -0.987001, 300, 0, 1),
(201603, 648, 1, 1, -8084.37, 1481.35, 8.83228, 0.992712, 0, 0, 0.476225, 0.879324, 300, 0, 1),
(201603, 648, 1, 1, -8092.04, 1514.55, 8.99208, 1.82131, 0, 0, 0.789905, 0.613229, 300, 0, 1),
(201603, 648, 1, 1, -8248.27, 1513.22, 41.9297, 3.0858, 0, 0, 0.999611, 0.0278931, 300, 0, 1),
(201603, 648, 1, 1, -8235.23, 1490.32, 40.7525, 5.13569, 0, 0, 0.542785, -0.839872, 300, 0, 1),
(201603, 648, 1, 1, -8223.74, 1469.27, 39.6957, 5.46163, 0, 0, 0.399324, -0.91681, 300, 0, 1),
(201603, 648, 1, 1, -8263.78, 1459.77, 41.9269, 2.78735, 0, 0, 0.984355, 0.176199, 300, 0, 1),
(201603, 648, 1, 1, -8281.33, 1464.33, 43.1104, 2.8973, 0, 0, 0.992549, 0.121842, 300, 0, 1),
(201603, 648, 1, 1, -8252.64, 1437.37, 40.2229, 2.72373, 0, 0, 0.978254, 0.207413, 300, 0, 1),
(201603, 648, 1, 1, -8234.91, 1443.77, 39.9069, 6.08917, 0, 0, 0.0968577, -0.995298, 300, 0, 1),
(201603, 648, 1, 1, -8234.02, 1516.53, 40.6426, 1.73021, 0, 0, 0.761162, 0.648562, 300, 0, 1),
(201603, 648, 1, 1, -8260.23, 1538.11, 41.0158, 2.97899, 0, 0, 0.996697, 0.081212, 300, 0, 1),
(201603, 648, 1, 1, -8322.03, 1530.43, 47.4049, 2.97899, 0, 0, 0.996697, 0.081212, 300, 0, 1),
(201603, 648, 1, 1, -8363.38, 1502.63, 46.2952, 0.469642, 0, 0, 0.232669, 0.972556, 300, 0, 1),
(201603, 648, 1, 1, -8330.75, 1500.44, 46.4421, 5.52368, 0, 0, 0.37069, -0.928756, 300, 0, 1);

-- spell_proc_event improved steady shot, master marksman, arcane concentration(clearcasting),rude interruption, Bloodsurge, invocation
DELETE FROM `spell_proc_event` WHERE `entry` IN ('34485','34486','34487','46913','46914','46915','53221','53222','53224','61216','61221','84722','84723');
INSERT INTO `spell_proc_event` VALUES (34485, 0, 9, 0, 1, 0, 0, 0, 0, 20, 0);
INSERT INTO `spell_proc_event` VALUES (34486, 0, 9, 0, 1, 0, 0, 0, 0, 40, 0);
INSERT INTO `spell_proc_event` VALUES (34487, 0, 9, 0, 1, 0, 0, 0, 0, 60, 0);
INSERT INTO `spell_proc_event` VALUES (46913, 0, 4, 0, 1024, 0, 0, 0, 0, 10, 0);
INSERT INTO `spell_proc_event` VALUES (46914, 0, 4, 0, 1024, 0, 0, 0, 0, 20, 0);
INSERT INTO `spell_proc_event` VALUES (46915, 0, 4, 0, 1024, 0, 0, 0, 0, 30, 0);
INSERT INTO `spell_proc_event` VALUES (53221, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (53222, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (53224, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (61216, 0, 4, 2056, 0, 0, 4112, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (61221, 0, 4, 2056, 0, 0, 4112, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (84722, 0, 3, 16384, 0, 0, 0, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (84723, 0, 3, 16384, 0, 0, 0, 0, 0, 100, 0);

-- Plate Specialization
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87509','87510','87511');
INSERT INTO `spell_learn_spell` VALUES (87509, 86526, 1);
INSERT INTO `spell_learn_spell` VALUES (87510, 86524, 1);
INSERT INTO `spell_learn_spell` VALUES (87511, 86525, 1);

-- Mail Specialization
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87506','87507');
INSERT INTO `spell_learn_spell` VALUES (87506, 86528, 1);
INSERT INTO `spell_learn_spell` VALUES (87507, 86529, 1);

-- Leather Specializations
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87504','87505');
INSERT INTO `spell_learn_spell` VALUES (87504, 86531, 1);
INSERT INTO `spell_learn_spell` VALUES (87505, 86530, 1);

-- Blackrock Caverns Mobs
update creature_template set health_mod=15, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=530, maxdmg=713, attackpower=827, baseattacktime=2000 where entry in (39708,39980,39982,39985,39978,39985,40004,40019,40017,40021,50284);
update creature_template SET `Health_mod`=22.8152 WHERE entry in (39665, 39698);
update creature_template set health_mod=45.05232558139535, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=545, maxdmg=723, attackpower=839, dmg_multiplier=7.5, baseattacktime=2000 where entry in (39987,39994,40023);
update creature_template set health_mod=3, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=470, maxdmg=650, attackpower=750, baseattacktime=2000 where entry in (40084);
update creature set spawnMask = '3' where map = '645';

-- -------------- --
--    RAIDS SAI   --
-- -------------- --

-- Baradin 10 Normal
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47901;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47120;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=47901 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=47120 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(47901, 0, 0, 0, 0, 0, 100, 30, 2000, 2400, 25000, 27000, 11, 89348, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Demon unit'),
(47901, 0, 1, 0, 0, 0, 100, 30, 4500, 4500, 50000, 51000, 11, 89354, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Demon unit'),
(47120, 0, 0, 0, 2, 0, 100, 30, 0, 2, 95000, 96000, 11, 47008, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Argaloth'),
(47120, 0, 1, 0, 0, 0, 100, 30, 5000, 6000, 40000, 41000, 11, 88942, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Argaloth'),
(47120, 0, 2, 0, 0, 0, 100, 30, 7000, 7000, 32000, 33000, 11, 88954, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Argaloth'),
(47120, 0, 3, 0, 0, 0, 100, 30, 15000, 19000, 50000, 54000, 11, 88972, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Argaloth');

-- Twilight Bastion 10 Normal
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45267 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44600 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44687 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45993 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45992 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43686 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43687 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43689 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43688 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43735 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43324 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45213 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(45267, 0, 0, 0, 0, 0, 100, 30, 5000, 6000, 14500, 15600, 11, 84838, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Cast Twist Phase'),
(45267, 0, 1, 0, 0, 0, 100, 30, 2000, 5000, 20000, 25000, 11, 95440, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast shadow bolt'),
(45267, 0, 2, 0, 0, 0, 100, 30, 8500, 8500, 31000, 32000, 11, 61394, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Cast frost'),
(44600, 0, 0, 0, 2, 0, 100, 30, 1, 3, 65000, 66000, 11, 26662, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44600, 0, 1, 0, 0, 0, 100, 30, 20000, 25000, 65000, 66000, 11, 83703, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44600, 0, 2, 0, 0, 0, 100, 30, 29000, 29000, 32000, 34000, 11, 84030, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44600, 0, 3, 0, 0, 0, 100, 30, 34000, 34000, 54000, 55000, 11, 83908, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44600, 0, 4, 0, 0, 0, 100, 30, 1500, 1500, 70000, 80000, 11, 83952, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44600, 0, 5, 0, 2, 0, 100, 30, 10, 20, 52000, 54000, 11, 83710, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Halfus Wyrmbreaker'),
(44687, 0, 0, 0, 0, 0, 100, 30, 2500, 2500, 45000, 46000, 11, 83956, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Proto-Behemoth'),
(44687, 0, 1, 0, 0, 0, 100, 30, 6000, 6400, 32000, 33000, 11, 83706, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Proto-Behemoth'),
(44687, 0, 2, 0, 0, 0, 100, 30, 2600, 2900, 45000, 46000, 11, 83707, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Proto-Behemoth'),
(44687, 0, 3, 0, 0, 0, 100, 30, 44000, 46000, 56000, 59000, 11, 86058, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Proto-Behemoth'),
(44687, 0, 4, 0, 0, 0, 100, 30, 55000, 55000, 60000, 62000, 11, 84106, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Proto-Behemoth'),
(45993, 0, 0, 0, 2, 0, 100, 30, 0, 1, 25000, 26000, 11, 47008, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Theralion'),
(45993, 0, 1, 0, 0, 0, 100, 30, 15000, 16000, 30000, 32000, 11, 86505, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Theralion'),
(45993, 0, 2, 0, 0, 0, 100, 30, 40000, 40000, 54000, 55000, 11, 86622, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Theralion'),
(45993, 0, 3, 0, 0, 0, 100, 30, 20000, 22000, 42000, 44000, 11, 86369, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Theralion'),
(45993, 0, 4, 0, 0, 0, 100, 30, 25000, 30000, 65000, 70000, 11, 86408, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Theralion'),
(45992, 0, 0, 0, 2, 0, 100, 30, 0, 1, 90000, 91000, 11, 47008, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(45992, 0, 1, 0, 0, 0, 100, 30, 3000, 6000, 45000, 48000, 11, 86840, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(45992, 0, 2, 0, 0, 0, 100, 30, 12000, 12000, 55000, 56000, 11, 86788, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(45992, 0, 3, 0, 0, 0, 100, 30, 32000, 38000, 60000, 66000, 11, 86013, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(43686, 0, 0, 0, 0, 0, 100, 30, 200, 200, 95000, 96000, 11, 82639, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ignacious'),
(43686, 0, 1, 0, 0, 0, 100, 30, 15000, 15000, 44000, 45000, 11, 82857, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ignacious'),
(43686, 0, 2, 0, 0, 0, 100, 30, 25000, 27000, 65000, 67000, 11, 82631, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ignacious'),
(43686, 0, 3, 0, 0, 0, 100, 30, 15000, 15000, 47000, 48000, 11, 82660, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ignacious'),
(43686, 0, 4, 0, 2, 0, 100, 30, 0, 5, 40000, 50000, 12, 43688, 8, 0, 43688, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ignacious'),
(43687, 0, 0, 0, 0, 0, 100, 30, 5000, 8500, 35000, 39000, 11, 82746, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Feludius'),
(43687, 0, 1, 0, 0, 0, 100, 30, 11000, 13000, 42000, 44000, 11, 82752, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Feludius'),
(43687, 0, 2, 0, 0, 0, 100, 30, 32400, 32400, 60000, 61000, 11, 82772, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Feludius'),
(43687, 0, 3, 0, 0, 0, 100, 30, 45100, 45100, 70000, 71000, 11, 82665, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Feludius'),
(43687, 0, 4, 0, 2, 0, 100, 30, 0, 5, 30000, 40000, 12, 43689, 8, 0, 43689, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Feludius'),
(43689, 0, 0, 0, 0, 0, 100, 30, 6000, 7000, 25000, 26000, 11, 83718, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Terrastra'),
(43689, 0, 1, 0, 0, 0, 100, 30, 12000, 15000, 35000, 38000, 11, 83565, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Terrastra'),
(43689, 0, 2, 0, 0, 0, 100, 30, 24000, 24000, 65000, 66000, 11, 82285, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Terrastra'),
(43688, 0, 0, 0, 0, 0, 100, 30, 14000, 19000, 40000, 45000, 11, 83070, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43688, 0, 1, 0, 0, 0, 100, 30, 22400, 22400, 50000, 51000, 11, 83099, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43688, 0, 2, 0, 0, 0, 100, 30, 1200, 1600, 70000, 74000, 11, 83067, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43688, 0, 3, 0, 0, 0, 100, 30, 30000, 34000, 38000, 42000, 11, 83087, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43688, 0, 4, 0, 0, 0, 100, 30, 45000, 45000, 70000, 71000, 11, 82285, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43688, 0, 5, 0, 2, 0, 100, 30, 0, 5, 30000, 40000, 12, 43735, 8, 0, 43735, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arion'),
(43735, 0, 0, 0, 0, 0, 100, 30, 50000, 50000, 90000, 91000, 11, 84918, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Elementium Monstrosity'),
(43735, 0, 1, 0, 0, 0, 100, 30, 20000, 24000, 50000, 54000, 11, 84913, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Elementium Monstrosity'),
(43324, 0, 0, 0, 2, 0, 100, 30, 0, 1, 95000, 95000, 11, 64238, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(43324, 0, 1, 0, 0, 0, 100, 30, 2600, 4800, 30000, 34000, 11, 82299, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(43324, 0, 2, 0, 0, 0, 100, 30, 15000, 17000, 40000, 42000, 11, 82524, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(43324, 0, 3, 0, 0, 0, 100, 30, 12000, 12000, 26000, 27000, 11, 82361, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(43324, 0, 4, 0, 0, 0, 100, 30, 5000, 7000, 60000, 62000, 11, 81628, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(43324, 0, 5, 0, 0, 0, 100, 30, 7000, 7000, 61000, 63000, 12, 43622, 7, 0, 43622, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chogall'),
(45213, 0, 0, 0, 2, 0, 100, 30, 1, 5, 950000, 960000, 11, 87299, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sinestra'),
(45213, 0, 1, 0, 0, 0, 100, 30, 40000, 44000, 80000, 82000, 11, 90125, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sinestra'),
(45213, 0, 2, 0, 0, 0, 100, 30, 1200, 1200, 15000, 16000, 11, 89421, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Sinestra'),
(45213, 0, 3, 0, 0, 0, 100, 30, 70000, 71000, 120000, 121000, 11, 86227, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sinestra'),
(45213, 0, 4, 0, 0, 0, 100, 30, 71000, 72000, 130000, 131000, 11, 87945, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sinestra'),
(45213, 0, 5, 0, 0, 0, 100, 30, 12000, 14000, 25000, 27000, 11, 89280, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sinestra');

UPDATE `creature_template` SET `unit_flags` = 4, `AIName` = 'SmartAI' WHERE `entry` = 45213;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43324;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `rank` = 3, `mindmg` = 1129, `maxdmg` = 3940, `baseattacktime` = 2400, `AIName` = 'SmartAI' WHERE `entry` = 43735;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43688;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43689;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43687;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43686;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45992;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45993;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44687;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44600;

DELETE FROM `creature_loot_template` WHERE (`entry`=41570);
INSERT INTO `creature_loot_template` VALUES
(41570, 60226, 44, 0, 0, 1, 1),
(41570, 60227, 26, 0, 0, 1, 1),
(41570, 60228, 41, 0, 0, 1, 1),
(41570, 60229, 6, 0, 0, 1, 1),
(41570, 60230, 32, 0, 0, 1, 1),
(41570, 60231, 26, 0, 0, 1, 1),
(41570, 60232, 56, 0, 0, 1, 1),
(41570, 60233, 53, 0, 0, 1, 1),
(41570, 60234, 24, 0, 0, 1, 1),
(41570, 60235, 6, 0, 0, 1, 1),
(41570, 60236, 9, 0, 0, 1, 1),
(41570, 60237, 50, 0, 0, 1, 1),
(41570, 60238, 6, 0, 0, 1, 1);

-- Stonecore 5 Normal
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43438;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43214;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42188;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42333;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42499;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=43438 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43214 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42188 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42333 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42499 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(43438, 0, 0, 0, 0, 0, 100, 30, 5000, 5000, 44000, 45000, 11, 82415, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'corborus'),
(43438, 0, 1, 0, 0, 0, 100, 30, 14000, 20000, 60000, 66000, 11, 86881, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'corborus'),
(43214, 0, 0, 0, 0, 0, 100, 30, 15000, 15000, 23000, 24000, 11, 80807, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Slabhide'),
(42188, 0, 0, 0, 0, 0, 100, 30, 15000, 18000, 30000, 33000, 11, 78807, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 1, 0, 0, 0, 100, 30, 2000, 2000, 12000, 13000, 11, 31589, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 2, 0, 2, 0, 100, 30, 1, 3, 50000, 51000, 11, 80467, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 3, 0, 0, 0, 100, 30, 14000, 14000, 15000, 16000, 11, 55095, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 4, 0, 0, 0, 100, 30, 25000, 29000, 55000, 59000, 11, 78903, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 5, 0, 0, 0, 100, 30, 12000, 12000, 43000, 44000, 11, 78859, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42188, 0, 6, 0, 0, 0, 100, 30, 43000, 43000, 22000, 23000, 11, 78939, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ozruk'),
(42333, 0, 0, 0, 0, 0, 100, 30, 25000, 27000, 30000, 32000, 11, 79050, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 1, 0, 0, 0, 100, 30, 14000, 14000, 45000, 46000, 11, 79002, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 2, 0, 0, 0, 100, 30, 2000, 2000, 21000, 22000, 11, 79345, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 3, 0, 0, 0, 100, 30, 14000, 14000, 19000, 20000, 11, 79340, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42333, 0, 4, 0, 0, 0, 100, 30, 45000, 47000, 34000, 36000, 11, 79351, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Azil'),
(42499, 0, 0, 0, 0, 0, 100, 0, 1, 1, 500, 600, 11, 83587, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Gravity Wall');

-- blackwing Descent 10 Normal
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42802;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41378;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41570;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43296;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42649;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42800;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42178;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42179;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42180;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42166;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41376;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41442;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41918;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42987;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42321;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43361;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42897;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=42802 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41378 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41570 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43296 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42649 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42800 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42178 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42179 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42180 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42166 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41376 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41442 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41918 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42987 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42321 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43361 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42897 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(42802, 0, 0, 0, 0, 0, 100, 2, 4500, 4500, 15000, 16000, 11, 80391, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Slayer'),
(42802, 0, 1, 0, 0, 0, 100, 2, 7000, 7000, 8000, 8100, 11, 80392, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Slayer'),
(42802, 0, 2, 0, 0, 0, 100, 2, 2500, 2500, 11000, 12000, 11, 80390, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Slayer'),
(41378, 0, 0, 0, 2, 0, 100, 2, 1, 3, 25000, 29000, 11, 64238, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 1, 0, 0, 0, 100, 2, 12000, 12000, 15000, 17000, 11, 77760, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 2, 0, 0, 0, 100, 2, 99000, 99000, 150000, 155000, 11, 77912, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 3, 0, 0, 0, 100, 2, 21000, 21000, 23000, 23000, 11, 78225, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 4, 0, 0, 0, 100, 2, 90000, 90000, 91000, 92000, 11, 77699, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 5, 0, 0, 0, 100, 2, 9500, 9500, 16000, 16200, 11, 77786, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41378, 0, 6, 0, 0, 0, 100, 2, 15000, 19000, 23000, 25900, 11, 77896, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Maloriak'),
(41570, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 11000, 13000, 11, 91931, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'magmaw'),
(41570, 0, 1, 0, 0, 0, 100, 2, 4000, 4000, 5000, 5000, 11, 77971, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'magmaw'),
(41570, 0, 3, 0, 0, 0, 100, 2, 4000, 4000, 14000, 15000, 12, 42321, 6, 1000, 42321, 1, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'magmaw'),
(41570, 0, 4, 0, 0, 0, 100, 2, 9000, 9000, 15000, 15000, 11, 78068, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Magmaw'),
(43296, 0, 0, 0, 2, 0, 100, 2, 1, 2, 90000, 120000, 11, 26662, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chimaeron'),
(43296, 0, 1, 0, 0, 0, 100, 2, 12000, 12000, 15000, 16000, 11, 82935, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Chimaeron'),
(43296, 0, 2, 0, 0, 0, 100, 2, 19000, 24000, 25000, 29000, 11, 82848, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chimaeron'),
(43296, 0, 3, 0, 0, 0, 100, 2, 2000, 2000, 28000, 28200, 11, 82881, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Chimaeron'),
(43296, 0, 4, 0, 2, 0, 100, 2, 1, 3, 90000, 95000, 11, 82890, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Chimaeron'),
(42649, 0, 0, 0, 0, 0, 100, 2, 8000, 8000, 11000, 12000, 11, 80051, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Chainwielder'),
(42649, 0, 1, 0, 0, 0, 100, 2, 4000, 4000, 10000, 11000, 11, 79580, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Chainwielder'),
(42649, 0, 2, 0, 0, 0, 100, 2, 1000, 1000, 20000, 21000, 11, 79589, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakonid Chainwielder'),
(42800, 0, 0, 0, 0, 0, 100, 2, 8000, 8000, 10000, 11000, 11, 81056, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Golem sentry'),
(42800, 0, 1, 0, 0, 0, 100, 2, 15000, 15000, 23000, 24000, 11, 81055, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Golem Sentry'),
(42178, 0, 0, 0, 0, 0, 100, 2, 1, 200, 60000, 65000, 11, 78740, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42178, 0, 1, 0, 0, 0, 100, 2, 15000, 15000, 20000, 22000, 11, 79501, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42178, 0, 2, 0, 0, 0, 100, 2, 16000, 16500, 21000, 21500, 11, 79505, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42178, 0, 3, 0, 0, 0, 100, 2, 6000, 8600, 17500, 19000, 11, 79023, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42178, 0, 4, 0, 0, 0, 100, 2, 40000, 40000, 50000, 51000, 11, 79582, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42178, 0, 5, 0, 2, 0, 100, 2, 1, 10, 2000, 3000, 11, 78746, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Magmatron'),
(42179, 0, 0, 0, 0, 0, 100, 2, 1, 100, 60000, 61000, 11, 78740, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Electron'),
(42179, 0, 1, 0, 0, 0, 100, 2, 20000, 20000, 24000, 26000, 11, 79900, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Electron'),
(42179, 0, 2, 0, 0, 0, 100, 2, 8000, 8000, 12000, 14000, 11, 79888, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Electron'),
(42179, 0, 3, 0, 0, 0, 100, 2, 19000, 19000, 22000, 25000, 11, 79879, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Electron'),
(42180, 0, 0, 0, 0, 0, 100, 2, 1, 100, 60000, 61000, 11, 78740, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Toxitron'),
(42180, 0, 1, 0, 0, 0, 100, 2, 5000, 5000, 7000, 7200, 11, 80011, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Toxitron'),
(42180, 0, 2, 0, 0, 0, 100, 2, 5000, 5000, 7000, 7200, 11, 80053, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Toxitron'),
(42180, 0, 3, 0, 0, 0, 100, 2, 10000, 10000, 14000, 16000, 11, 80157, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Toxitron'),
(42180, 0, 4, 0, 0, 0, 100, 2, 15000, 15000, 17000, 19000, 11, 79835, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Toxitron'),
(42166, 0, 0, 0, 0, 0, 100, 2, 1, 100, 60000, 61000, 11, 78740, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arcanotron'),
(42166, 0, 1, 0, 0, 0, 100, 2, 8000, 8000, 11000, 12000, 11, 79710, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Arcanotron'),
(42166, 0, 2, 0, 0, 0, 100, 2, 20000, 20000, 21000, 23000, 11, 79729, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arcanotron'),
(42166, 0, 3, 0, 0, 0, 100, 2, 22000, 22000, 60000, 65000, 11, 79735, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arcanotron'),
(41376, 0, 0, 0, 2, 0, 100, 2, 1, 3, 690000, 690000, 11, 26662, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41376, 0, 1, 0, 0, 0, 100, 2, 12000, 12000, 16000, 17500, 11, 78684, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41376, 0, 2, 0, 0, 0, 100, 2, 8000, 8000, 25000, 27800, 11, 77826, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41376, 0, 3, 0, 0, 0, 100, 2, 5000, 5000, 32000, 34900, 11, 79353, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41376, 0, 4, 0, 0, 0, 100, 2, 45000, 45000, 72000, 78000, 11, 77827, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41376, 0, 5, 0, 0, 0, 100, 2, 75000, 75000, 76000, 79000, 11, 78621, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nefarian'),
(41442, 0, 0, 0, 0, 0, 100, 2, 2500, 2700, 14000, 16000, 11, 78098, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Atramedes'),
(41442, 0, 1, 0, 0, 0, 100, 2, 5000, 5000, 7000, 7100, 11, 78353, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Atramedes'),
(41442, 0, 2, 0, 0, 0, 100, 2, 6500, 6500, 8000, 8100, 11, 78221, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Atramedes'),
(41442, 0, 3, 0, 0, 0, 100, 2, 9800, 9800, 12000, 12000, 11, 77612, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Atramedes'),
(41442, 0, 4, 0, 0, 0, 100, 2, 12000, 12000, 12500, 12600, 11, 77672, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Atramedes'),
(41918, 0, 0, 0, 0, 0, 100, 2, 5000, 7000, 14000, 14500, 11, 81586, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Animated Bone Warrior'),
(41918, 0, 1, 0, 0, 0, 100, 2, 2000, 2000, 3500, 3600, 11, 61394, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Animated Bone Warrior'),
(41918, 0, 2, 0, 0, 0, 100, 2, 3400, 3400, 3500, 3500, 11, 79330, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Animated Bone Warrior'),
(42897, 0, 0, 0, 0, 0, 100, 2, 100, 4000, 5000, 6000, 11, 80092, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Poison Bomb'),
(42321, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 25000, 30000, 11, 78941, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Lava Parasite'),
(43361, 0, 0, 0, 0, 0, 100, 2, 200, 200, 4000, 5000, 11, 81060, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Flash Bomb');

-- Added 4 mobs with SmartAI (3 in Twilight highlands and 1 in Deepholm)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 50089;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 50085;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 50086;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43358;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=50089 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=50085 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=50086 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43358 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(50089, 0, 0, 0, 0, 0, 100, 0, 45000, 48000, 60000, 63000, 11, 93610, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Julak Doom'),
(50089, 0, 1, 0, 0, 0, 100, 0, 22000, 22000, 30000, 31000, 11, 93611, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Julak Doom'),
(50085, 0, 0, 0, 0, 0, 100, 0, 20000, 23000, 45000, 48000, 11, 77703, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Overlord Sunderfury'),
(50085, 0, 1, 0, 0, 0, 100, 0, 5000, 9000, 12000, 17000, 11, 80819, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Overlord Sunderfury'),
(50085, 0, 2, 0, 0, 0, 100, 0, 300, 300, 60000, 61000, 11, 35915, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Overlord Sunderfury'),
(50086, 0, 0, 0, 0, 0, 100, 0, 5000, 8000, 30000, 33000, 11, 79857, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Tarvus the Vile'),
(50086, 0, 1, 0, 0, 0, 100, 0, 200, 200, 24000, 24500, 11, 78472, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Tarvus the Vile'),
(50086, 0, 2, 0, 0, 0, 100, 0, 500, 500, 12000, 13000, 11, 84867, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Tarvus the Vile'),
(43358, 0, 0, 0, 0, 0, 100, 0, 2000, 7000, 32000, 37000, 11, 35235, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Feldspar the Eternal'),
(43358, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 10000, 11000, 11, 29326, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Feldspar the Eternal'),
(43358, 0, 2, 0, 0, 0, 100, 0, 1100, 1100, 11000, 12000, 11, 32076, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Feldspar the Eternal');

-- Grim Batol SmartAI (only bosses 5 Normal)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39625;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40177;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40319;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40320;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40484;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39625 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40177 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40319 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40320 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40484 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39625, 0, 0, 0, 2, 0, 100, 6, 1, 5, 15000, 18000, 11, 74853, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'General Umbriss'),
(39625, 0, 1, 0, 0, 0, 100, 6, 10000, 13000, 25000, 28000, 11, 74670, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'General Umbriss'),
(39625, 0, 2, 0, 0, 0, 100, 6, 20000, 23000, 30000, 33000, 11, 74634, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'General Umbriss'),
(39625, 0, 3, 0, 0, 0, 100, 6, 4000, 4000, 20000, 21000, 11, 74846, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'General Umbriss'),
(40177, 0, 0, 0, 0, 0, 100, 6, 1000, 3000, 60000, 62000, 11, 75000, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40177, 0, 1, 0, 0, 0, 100, 6, 3100, 3200, 63000, 64000, 11, 74981, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40177, 0, 2, 0, 0, 0, 100, 6, 15000, 17000, 30000, 33000, 11, 74976, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40177, 0, 3, 0, 2, 0, 100, 6, 30, 60, 25000, 27000, 11, 74908, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40177, 0, 4, 0, 0, 0, 100, 6, 21000, 22000, 34000, 35000, 11, 74984, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40177, 0, 5, 0, 0, 0, 100, 6, 26000, 26000, 40000, 41000, 11, 75056, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Throngus'),
(40319, 0, 0, 0, 2, 0, 100, 6, 5, 10, 26000, 27000, 11, 76303, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drahga'),
(40319, 0, 1, 0, 0, 0, 100, 6, 2000, 4000, 12000, 14000, 11, 75245, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Drahga'),
(40320, 0, 0, 0, 0, 0, 100, 6, 3000, 5000, 12000, 14000, 11, 75321, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(40320, 0, 1, 0, 2, 0, 100, 6, 1, 5, 20000, 21000, 11, 75328, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valiona'),
(40484, 0, 0, 0, 0, 0, 100, 6, 20000, 20000, 40000, 41000, 11, 75792, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'erudax'),
(40484, 0, 1, 0, 0, 0, 100, 6, 10000, 11000, 43000, 44000, 11, 75789, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'erudax'),
(40484, 0, 2, 0, 2, 0, 100, 6, 5, 10, 10000, 14000, 11, 79466, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'erudax'),
(40484, 0, 3, 0, 0, 0, 100, 6, 32000, 37000, 45000, 50000, 11, 75664, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'erudax');

-- SmartAI Vortex Pinnacle (All bosses) 5 Normal
-- SmartAI Throne of the Tides (Ozumat not working) 5 Normal
-- SmartAI for npc Canyon Ettin
-- Vortex Pinnacle 
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43878;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43873;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43875;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=43878 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43873 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43875 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(43878, 0, 0, 0, 0, 0, 100, 6, 1000, 3000, 7000, 9000, 11, 86331, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Grand Vizier Ertan'),
(43873, 0, 0, 0, 0, 0, 100, 6, 1000, 2000, 9000, 10000, 11, 88357, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Altairus'),
(43875, 0, 0, 0, 0, 0, 100, 6, 5000, 8000, 19000, 22000, 11, 87622, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Asaad'),
(43875, 0, 1, 0, 0, 0, 100, 6, 12000, 14000, 26000, 28000, 11, 87618, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Asaad'),
(43875, 0, 2, 0, 0, 0, 100, 6, 25000, 40000, 50000, 90000, 11, 86930, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Asaad');

-- Throne of the Tides 
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40825;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40765;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40586;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=40825 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40765 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40586 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(40825, 0, 0, 0, 0, 0, 100, 6, 5000, 5000, 35000, 36000, 11, 76170, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'runak Stonespeaker'),
(40825, 0, 1, 0, 0, 0, 100, 6, 3000, 3000, 20000, 21000, 11, 76165, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'runak Stonespeaker'),
(40825, 0, 2, 0, 0, 0, 100, 6, 9000, 10000, 31000, 32000, 11, 84931, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'runak Stonespeaker'),
(40825, 0, 3, 0, 0, 0, 100, 6, 12000, 15000, 11000, 14000, 11, 76171, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'runak Stonespeaker'),
(40765, 0, 0, 0, 2, 0, 100, 6, 1, 5, 12000, 45000, 11, 76100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Ulthok'),
(40765, 0, 1, 0, 0, 0, 100, 6, 7000, 7000, 17000, 18000, 11, 76094, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Commander Ulthok'),
(40765, 0, 2, 0, 0, 0, 100, 6, 21000, 22000, 24000, 25000, 11, 76026, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Commander Ulthok'),
(40765, 0, 3, 0, 0, 0, 100, 6, 10000, 12000, 35000, 37000, 11, 76047, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Ulthok'),
(40586, 0, 0, 0, 0, 0, 100, 6, 20000, 23000, 30000, 33000, 11, 76008, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Lady Naz jar'),
(40586, 0, 1, 0, 0, 0, 100, 6, 12000, 12000, 22000, 23000, 11, 76001, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Lady Naz jar'),
(40586, 0, 2, 0, 0, 0, 100, 6, 100, 100, 25000, 26000, 11, 75722, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Lady Naz jar'),
(40586, 0, 3, 0, 0, 0, 100, 6, 45000, 60000, 55000, 70000, 11, 75683, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lady Naz jar');

-- Canyon Ettin
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43094;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=43094 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(43094, 0, 0, 0, 0, 0, 100, 0, 5000, 8000, 15000, 18000, 11, 88421, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Canyon Ettin');

-- SmartAI Lost city Tol'Vir (5 Normal)
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 44577;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44819;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 43614;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 49045;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 43612;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=44577 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44819 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43614 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=49045 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43612 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(44577, 0, 0, 0, 0, 0, 100, 6, 100, 100, 40000, 41000, 11, 83113, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'General Husam'),
(44577, 0, 1, 0, 0, 0, 100, 6, 2000, 7000, 21000, 26000, 11, 83445, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'General Husam'),
(44819, 0, 0, 0, 0, 0, 100, 6, 8000, 8000, 25000, 26000, 11, 84982, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Siamat'),
(44819, 0, 1, 0, 0, 0, 100, 6, 14000, 20000, 34000, 40000, 11, 83066, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Siamat'),
(44819, 0, 2, 0, 0, 0, 100, 6, 2500, 2500, 11000, 12000, 11, 91853, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Siamat'),
(44819, 0, 3, 0, 2, 0, 100, 6, 1, 5, 40000, 41000, 11, 84589, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Siamat'),
(43614, 0, 0, 0, 0, 0, 100, 6, 200, 200, 30000, 31000, 11, 81630, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'lockmaw'),
(43614, 0, 1, 0, 0, 0, 100, 6, 9000, 9000, 15000, 16000, 11, 81690, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'lockmaw'),
(43614, 0, 2, 0, 2, 0, 100, 6, 1, 5, 20000, 21000, 11, 81706, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'lockmaw'),
(49045, 0, 0, 0, 2, 0, 100, 6, 1, 5, 20000, 21000, 11, 91415, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'augh'),
(49045, 0, 1, 0, 0, 0, 100, 6, 2000, 10000, 30000, 40000, 11, 91408, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'augh'),
(49045, 0, 2, 0, 0, 0, 100, 6, 12000, 12000, 14000, 15000, 11, 90026, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'augh'),
(49045, 0, 3, 0, 0, 0, 100, 6, 24000, 25000, 19000, 20000, 11, 89989, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'augh'),
(43612, 0, 0, 0, 0, 0, 100, 6, 200, 200, 14000, 15000, 11, 82622, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'High Prophet Barim'),
(43612, 0, 1, 0, 0, 0, 100, 6, 10000, 10000, 18000, 19000, 11, 82506, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Prophet Barim'),
(43612, 0, 2, 0, 2, 0, 100, 6, 5, 10, 24000, 25000, 11, 82320, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Prophet Barim'),
(43612, 0, 3, 0, 2, 0, 100, 6, 5, 10, 27000, 28000, 28, 82320, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'High Prophet Barim');

-- SmartAI Blackrock Caverns (5 Normal)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39665;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39679;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39698;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39700;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39705;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40817;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39665 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39679 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39698 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39700 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39705 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40817 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39665, 0, 0, 0, 2, 0, 100, 6, 5, 10, 20000, 22000, 11, 82137, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Romogg Bonecrusher'),
(39665, 0, 1, 0, 0, 0, 100, 6, 30000, 43000, 50000, 73000, 11, 75543, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Romogg Bonecrusher'),
(39665, 0, 2, 0, 0, 0, 100, 6, 20000, 20000, 24000, 25000, 11, 75441, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Romogg Bonecrusher'),
(39665, 0, 3, 0, 0, 0, 100, 6, 5000, 5000, 12000, 13000, 11, 75571, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Romogg Bonecrusher'),
(39665, 0, 4, 0, 0, 0, 100, 6, 8000, 9000, 15000, 16000, 11, 75272, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Romogg Bonecrusher'),
(39679, 0, 0, 0, 2, 0, 100, 6, 10, 20, 20000, 21000, 11, 75817, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Corla Herald of Twilight'),
(39679, 0, 1, 0, 2, 0, 100, 6, 30, 50, 20000, 21000, 11, 75732, 1, 0, 0, 0, 0, 11, 50284, 20, 0, 0, 0, 0, 0, 'Corla Herald of Twilight'),
(39679, 0, 2, 0, 0, 0, 100, 6, 4000, 6000, 26000, 28000, 11, 75823, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Corla Herald of Twilight'),
(39679, 0, 3, 0, 0, 0, 100, 6, 10000, 11000, 14000, 15000, 11, 75610, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Corla Herald of Twilight'),
(39698, 0, 0, 0, 0, 0, 100, 6, 2000, 4000, 6000, 8000, 11, 15284, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Karsh Steelbender'),
(39698, 0, 1, 0, 2, 0, 100, 6, 5, 10, 30000, 32000, 11, 75842, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Karsh Steelbender'),
(39698, 0, 2, 0, 2, 0, 100, 6, 2, 7, 25000, 26000, 11, 75846, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Karsh Steelbender'),
(39700, 0, 0, 0, 0, 0, 100, 6, 200, 1000, 20000, 21000, 11, 76030, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Beauty'),
(39700, 0, 1, 0, 2, 0, 100, 6, 1, 5, 18000, 19000, 11, 82395, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Beauty'),
(39700, 0, 2, 0, 0, 0, 100, 6, 5000, 5000, 12000, 14000, 11, 76032, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Beauty'),
(39700, 0, 3, 0, 0, 0, 100, 6, 10000, 11000, 22000, 23000, 11, 76031, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Beauty'),
(39700, 0, 4, 0, 2, 0, 100, 6, 20, 40, 15000, 16000, 11, 76028, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Beauty'),
(39705, 0, 0, 0, 0, 0, 100, 6, 8000, 8000, 14000, 15000, 11, 76188, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ascendant Lord Obsidius'),
(39705, 0, 1, 0, 0, 0, 100, 6, 40000, 50000, 60000, 66000, 11, 82393, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascendant Lord Obsidius'),
(39705, 0, 2, 0, 0, 0, 100, 6, 30000, 35000, 70000, 75000, 11, 76274, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ascendant Lord Obsidius'),
(40817, 0, 0, 0, 0, 0, 100, 6, 200, 5000, 6000, 14000, 11, 76189, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Shadow of Obsidius');

-- SmartAI Halls of Origination (5 Normal)
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 39425;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 39428;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `ScriptName` = '' WHERE `entry` = 39788;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39378;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39732;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39731;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39587;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39425 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39428 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39788 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39378 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39732 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39731 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39587 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39425, 0, 0, 0, 0, 0, 100, 6, 1000, 2000, 5000, 10000, 11, 75592, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Temple Guardian Anhuur'),
(39425, 0, 1, 0, 0, 0, 100, 6, 30000, 50000, 60000, 80000, 11, 75322, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Temple Guardian Anhuur'),
(39425, 0, 2, 0, 2, 0, 100, 6, 10, 20, 0, 0, 11, 74938, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Temple Guardian Anhuur not working'),
(39428, 0, 0, 0, 0, 0, 100, 6, 10000, 15000, 30000, 35000, 11, 77370, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Earthrager Ptah'),
(39428, 0, 1, 0, 0, 0, 100, 6, 2000, 4000, 8000, 10000, 11, 83650, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Earthrager Ptah'),
(39788, 0, 0, 0, 0, 0, 100, 6, 5000, 8000, 14000, 17000, 11, 76184, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anraphet'),
(39788, 0, 1, 0, 0, 0, 100, 6, 10000, 10000, 20000, 21000, 11, 75609, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anraphet'),
(39788, 0, 2, 0, 0, 0, 100, 6, 12000, 12000, 24000, 25000, 11, 75623, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anraphet'),
(39788, 0, 3, 0, 0, 0, 100, 6, 28000, 28000, 32000, 33000, 11, 77437, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Anraphet'),
(39788, 0, 4, 0, 0, 0, 100, 6, 2000, 2000, 26500, 27000, 11, 75604, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Anraphet'),
(39378, 0, 0, 0, 0, 0, 100, 6, 5000, 5000, 15000, 16000, 11, 76355, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rajh'),
(39378, 0, 1, 0, 0, 0, 100, 6, 1000, 3000, 21000, 23000, 11, 87653, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Rajh'),
(39378, 0, 2, 0, 0, 0, 100, 6, 8000, 8000, 12000, 13000, 11, 73872, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Rajh'),
(39732, 0, 0, 0, 0, 0, 100, 6, 1000, 3000, 7000, 9000, 11, 77069, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Setesh'),
(39732, 0, 1, 0, 0, 0, 100, 6, 10000, 10000, 16000, 17000, 11, 76681, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Setesh'),
(39732, 0, 2, 0, 0, 0, 100, 6, 5000, 5000, 13000, 14000, 11, 76870, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Setesh'),
(39731, 0, 0, 0, 0, 0, 100, 6, 5000, 7000, 15000, 17000, 11, 75790, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Ammunae'),
(39731, 0, 1, 0, 0, 0, 100, 6, 10000, 12000, 20000, 22000, 11, 76043, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ammunae'),
(39731, 0, 2, 0, 0, 0, 100, 6, 34000, 40000, 50000, 56700, 11, 79767, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ammunae'),
(39587, 0, 0, 0, 0, 0, 100, 6, 5000, 5000, 10000, 11000, 11, 74365, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Isiset'),
(39587, 0, 1, 0, 0, 0, 100, 6, 12000, 12000, 45000, 46000, 11, 74133, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Isiset'),
(39587, 0, 2, 0, 0, 0, 100, 6, 15000, 18000, 20000, 23000, 11, 74136, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Isiset');

-- SmartAI The Vortex Pinnacle 5 normal - all mobs scripted
-- Added skin loot for mob - Young Storm Dragon
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45912;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45704;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45915;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45924;
UPDATE `creature_template` SET `skinloot` = 45919, `AIName` = 'SmartAI' WHERE `entry` = 45919;

DELETE FROM `skinning_loot_template` WHERE (`entry`=45919);
INSERT INTO `skinning_loot_template` VALUES
(45919, 52976, 89, 1, 0, 1, 9),
(45919, 52979, 54, 1, 0, 1, 8);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45922;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45926;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45935;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45930;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45928;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45932;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=45912 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45704 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45915 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45924 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45919 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45922 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45926 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45935 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45930 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45928 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=45932 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(45912, 0, 0, 0, 0, 0, 100, 2, 1200, 3000, 10000, 12000, 11, 88029, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Wild Vortex'),
(45912, 0, 1, 0, 0, 0, 100, 2, 5000, 8000, 13000, 16000, 11, 88032, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Wild Vortex'),
(45912, 0, 2, 0, 0, 0, 100, 30, 200, 800, 6500, 6600, 11, 61394, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Wild Vortex'),
(45912, 0, 3, 0, 0, 0, 100, 30, 15000, 17000, 18000, 20000, 11, 88010, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Wild Vortex'),
(45915, 0, 0, 0, 0, 0, 100, 30, 12000, 20000, 22000, 30000, 11, 88055, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Armored Mistral'),
(45915, 0, 1, 0, 0, 0, 100, 30, 4000, 8000, 13000, 17000, 11, 88061, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Armored Mistral'),
(45915, 0, 2, 0, 2, 0, 100, 30, 0, 20, 1000, 1800, 11, 88058, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Armored Mistral'),
(45704, 0, 0, 0, 0, 0, 100, 30, 100, 300, 90000, 91000, 11, 85467, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Lurking Tempest'),
(45704, 0, 1, 0, 0, 0, 100, 30, 1000, 3000, 6000, 8000, 11, 89105, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Lurking Tempest'),
(45924, 0, 0, 0, 0, 0, 100, 30, 15000, 20000, 35000, 40000, 11, 88170, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Turbulent Squall'),
(45924, 0, 1, 0, 0, 0, 100, 30, 3000, 3000, 22000, 23000, 11, 88175, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Turbulent Squall'),
(45924, 0, 2, 0, 0, 0, 100, 30, 7000, 7000, 12000, 13000, 11, 88171, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Turbulent Squall'),
(45919, 0, 0, 0, 0, 0, 100, 30, 4000, 8000, 20000, 24000, 11, 88194, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Young Storm Dragon'),
(45919, 0, 1, 0, 2, 0, 100, 30, 0, 45, 12000, 13000, 11, 88192, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Young Storm Dragon'),
(45919, 0, 2, 0, 2, 0, 100, 30, 0, 20, 16000, 18000, 11, 88201, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Young Storm Dragon'),
(45922, 0, 0, 0, 0, 0, 100, 30, 5000, 6000, 6000, 7000, 11, 88182, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Empyrean Assassin'),
(45922, 0, 1, 0, 2, 0, 100, 30, 0, 40, 8000, 10000, 11, 88186, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Empyrean Assassin'),
(45926, 0, 0, 0, 0, 0, 100, 30, 5000, 5000, 10000, 11000, 11, 58127, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Servant of Asaad'),
(45926, 0, 1, 0, 0, 0, 100, 30, 2000, 2000, 4000, 4100, 11, 87771, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Servant of Asaad'),
(45926, 0, 2, 0, 2, 0, 100, 30, 10, 40, 16000, 17000, 11, 87772, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Servant of Asaad'),
(45935, 0, 0, 0, 0, 0, 100, 30, 1000, 4000, 5000, 8000, 11, 88959, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Temple Adept'),
(45935, 0, 1, 0, 2, 0, 100, 30, 10, 50, 7000, 11000, 11, 87779, 1, 0, 0, 0, 0, 11, 0, 40, 0, 0, 0, 0, 0, 'Temple Adept'),
(45935, 0, 2, 0, 0, 0, 100, 30, 20000, 20000, 40000, 41000, 11, 87780, 1, 0, 0, 0, 0, 11, 0, 40, 0, 0, 0, 0, 0, 'Temple Adept'),
(45930, 0, 0, 0, 0, 0, 100, 30, 100, 300, 9000, 10000, 11, 87768, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Minister of Air'),
(45930, 0, 1, 0, 0, 0, 100, 30, 3000, 4000, 6000, 7000, 11, 87762, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Minister of Air'),
(45928, 0, 0, 0, 0, 0, 100, 30, 500, 1000, 10000, 11000, 11, 87759, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Executor of the Caliph'),
(45928, 0, 1, 0, 0, 0, 100, 30, 2000, 2500, 5000, 6000, 11, 76622, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Executor of the Caliph'),
(45928, 0, 2, 0, 0, 0, 100, 30, 4000, 4000, 7000, 8000, 11, 78660, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Executor of the Caliph'),
(45928, 0, 3, 0, 2, 0, 100, 30, 20, 50, 13000, 14000, 11, 87761, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Executor of the Caliph'),
(45932, 0, 0, 0, 0, 0, 100, 30, 1000, 6000, 6000, 10000, 11, 87854, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Skyfall Star');

-- SmartAI Tol Barad (4 NPC)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47591;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47676;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47659;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 47304;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=47591 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=47676 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=47659 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=47304 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(47591, 0, 0, 0, 0, 0, 100, 0, 1000, 1500, 3000, 4000, 11, 13445, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Baradin Crocolisk'),
(47591, 0, 1, 0, 0, 0, 100, 0, 3000, 5000, 5000, 7000, 11, 3604, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Baradin Crocolisk'),
(47676, 0, 0, 0, 0, 0, 100, 0, 200, 2000, 2000, 4000, 11, 32919, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Baradin Fox'),
(47659, 0, 0, 0, 0, 0, 100, 0, 100, 500, 20000, 22000, 11, 78894, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Apprehensive Worker'),
(47659, 0, 1, 0, 2, 0, 100, 0, 5, 30, 12000, 14000, 11, 79561, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Apprehensive Worker'),
(47304, 0, 0, 0, 2, 0, 100, 0, 5, 20, 25000, 26000, 11, 79871, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Largo'),
(47304, 0, 1, 0, 0, 0, 100, 0, 12000, 20000, 30000, 38000, 11, 78828, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Largo'),
(47304, 0, 2, 0, 0, 0, 100, 0, 8000, 8000, 22000, 23000, 11, 80983, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Commander Largo'),
(47304, 0, 3, 0, 0, 0, 100, 0, 300, 2000, 3000, 5000, 11, 32736, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Commander Largo');

-- SmartAI mob 19384 - He have flag smartAI but no have events + WP fix console flood error
DELETE FROM `smart_scripts` WHERE (`entryorguid`=19384 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(19384, 0, 0, 0, 1, 0, 100, 0, 1000, 2000, 3000, 6000, 11, 33806, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast 33806');
DELETE FROM `waypoint_data` WHERE `id` IN (691220,691230,691240,691250,691260,691270);
DELETE FROM `waypoint_scripts` WHERE `id` BETWEEN 190 AND 214;

-- SmartAI mob 40845 works
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40845 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(40845, 0, 0, 0, 0, 0, 100, 0, 500, 1000, 4000, 6000, 11, 18543, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Pyrendius');

-- SmartAI Stonecore mobs + pickpocket loot
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42808;
UPDATE `creature_template` SET `pickpocketloot` = 43537, `AIName` = 'SmartAI' WHERE `entry` = 43537;
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 43537;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=43537);
INSERT INTO `pickpocketing_loot_template` VALUES
(43537, 63348, 25, 0, 0, 1, 1),
(43537, 63291, 23, 0, 0, 1, 1),
(43537, 63349, 20, 0, 0, 1, 1),
(43537, 63317, 19, 0, 0, 1, 1),
(43537, 58269, 16, 0, 0, 1, 1),
(43537, 63310, 11, 0, 0, 1, 1),
(43537, 63300, 7, 0, 0, 1, 1),
(43537, 63316, 1.4, 0, 0, 1, 1),
(43537, 63318, 0.9, 0, 0, 1, 1);

UPDATE `creature_template` SET `pickpocketloot` = 42696, `AIName` = 'SmartAI' WHERE `entry` = 42696;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=42696);
INSERT INTO `pickpocketing_loot_template` VALUES
(42696, 63348, 23, 0, 0, 1, 1),
(42696, 63291, 22, 0, 0, 1, 1),
(42696, 63349, 22, 0, 0, 1, 1),
(42696, 63317, 22, 0, 0, 1, 1),
(42696, 58269, 17, 0, 0, 1, 1),
(42696, 63310, 10, 0, 0, 1, 1),
(42696, 63300, 8, 0, 0, 1, 1),
(42696, 63316, 1.6, 0, 0, 1, 1),
(42696, 63318, 1.1, 0, 0, 1, 1);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43662;
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 43391;
UPDATE `creature_template` SET `pickpocketloot` = 43430, `AIName` = 'SmartAI' WHERE `entry` = 43430;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=43430);
INSERT INTO `pickpocketing_loot_template` VALUES
(43430, 63349, 23, 0, 0, 1, 1),
(43430, 63291, 22, 0, 0, 1, 1),
(43430, 63348, 22, 0, 0, 1, 1),
(43430, 63317, 20, 0, 0, 1, 1),
(43430, 58269, 19, 0, 0, 1, 1),
(43430, 63310, 12, 0, 0, 1, 1),
(43430, 63300, 8, 0, 0, 1, 1),
(43430, 63316, 2, 0, 0, 1, 1),
(43430, 63318, 0.8, 0, 0, 1, 1);

UPDATE `creature_template` SET `skinloot` = 42808 WHERE `entry` = 42808;

DELETE FROM `skinning_loot_template` WHERE (`entry`=42808);
INSERT INTO `skinning_loot_template` VALUES
(42808, 52976, 85, 1, 0, 1, 9),
(42808, 52977, 44, 1, 0, 1, 12);

UPDATE `creature_template` SET `pickpocketloot` = 42691, `AIName` = 'SmartAI' WHERE `entry` = 42691;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=42691);
INSERT INTO `pickpocketing_loot_template` VALUES
(42691, 63317, 23, 0, 0, 1, 1),
(42691, 63291, 22, 0, 0, 1, 1),
(42691, 63348, 22, 0, 0, 1, 1),
(42691, 63349, 21, 0, 0, 1, 1),
(42691, 58269, 17, 0, 0, 1, 1),
(42691, 63310, 11, 0, 0, 1, 1),
(42691, 63300, 7, 0, 0, 1, 1),
(42691, 63316, 2, 0, 0, 1, 1),
(42691, 63318, 1.2, 0, 0, 1, 1);

UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `unit_class` = 2 WHERE `entry` = 43014;
UPDATE `creature_template` SET `pickpocketloot` = 42695 WHERE `entry` = 42695;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=42695);
INSERT INTO `pickpocketing_loot_template` VALUES
(42695, 63349, 24, 0, 0, 1, 1),
(42695, 63291, 22, 0, 0, 1, 1),
(42695, 63348, 22, 0, 0, 1, 1),
(42695, 63317, 22, 0, 0, 1, 1),
(42695, 58269, 17, 0, 0, 1, 1),
(42695, 63310, 10, 0, 0, 1, 1),
(42695, 63300, 9, 0, 0, 1, 1),
(42695, 63318, 1.8, 0, 0, 1, 1),
(42695, 63316, 0.2, 0, 0, 1, 1),
(42695, 55536, 0.2, 0, 0, 1, 1),
(42695, 62116, 0.2, 0, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=42789);
INSERT INTO `creature_loot_template` VALUES
(42789, 52325, 33.5, 1, 0, 2, 6),
(42789, 55822, 3.1, 1, 0, 1, 1),
(42789, 55823, 2.6, 1, 0, 1, 1),
(42789, 55824, 2.9, 1, 0, 1, 1),
(42789, 52506, 7, 1, 0, 1, 1);

UPDATE `creature_template` SET `pickpocketloot` = 42789 WHERE `entry` = 42789;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=42789);
INSERT INTO `pickpocketing_loot_template` VALUES
(42789, 63317, 78, 0, 0, 1, 1),
(42789, 63348, 33, 0, 0, 1, 1),
(42789, 58269, 22, 0, 0, 1, 1),
(42789, 63291, 22, 0, 0, 1, 1);

UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 42789;
UPDATE `creature_template` SET `pickpocketloot` = 42692, `AIName` = 'SmartAI' WHERE `entry` = 42692;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=42692);
INSERT INTO `pickpocketing_loot_template` VALUES
(42692, 63348, 24, 0, 0, 1, 1),
(42692, 63291, 22, 0, 0, 1, 1),
(42692, 63349, 22, 0, 0, 1, 1),
(42692, 58269, 20, 0, 0, 1, 1),
(42692, 63317, 19, 0, 0, 1, 1),
(42692, 63310, 11, 0, 0, 1, 1),
(42692, 63300, 8, 0, 0, 1, 1),
(42692, 63316, 1.4, 0, 0, 1, 1),
(42692, 63318, 1.2, 0, 0, 1, 1);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42789;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=42808 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43537 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42696 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43662 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43430 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42691 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42789 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42692 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(42808, 0, 0, 0, 0, 0, 100, 30, 1000, 3000, 5000, 10000, 11, 79922, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Flayer'),
(43537, 0, 0, 0, 0, 0, 100, 30, 4000, 6000, 12000, 14000, 11, 81576, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Earthshaper'),
(43537, 0, 1, 0, 0, 0, 100, 30, 2000, 2700, 8000, 9000, 11, 81530, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Earthshaper'),
(43537, 0, 2, 0, 0, 0, 100, 30, 15000, 25000, 26000, 36000, 11, 81463, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Earthshaper'),
(43537, 0, 3, 0, 2, 0, 100, 30, 5, 20, 22000, 22000, 11, 81459, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Earthshaper'),
(42696, 0, 0, 0, 2, 0, 100, 30, 1, 10, 20000, 23000, 11, 80158, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Warbringer'),
(42696, 0, 1, 0, 0, 0, 100, 30, 1000, 3000, 6000, 9000, 11, 15496, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Warbringer'),
(43662, 0, 0, 0, 0, 0, 100, 30, 100, 400, 1500, 2500, 11, 81711, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Unbound Earth Rager'),
(43430, 0, 0, 0, 0, 0, 100, 30, 500, 1000, 40000, 41000, 11, 81574, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Berserker'),
(43430, 0, 1, 0, 0, 0, 100, 30, 4000, 10000, 12000, 18000, 11, 81568, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Berserker'),
(42691, 0, 0, 0, 0, 0, 100, 30, 100, 2100, 5000, 7000, 11, 80279, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Rift Conjurer'),
(42691, 0, 1, 0, 0, 0, 100, 30, 4000, 7000, 14000, 17000, 11, 80308, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Rift Conjurer'),
(42789, 0, 0, 0, 0, 0, 100, 30, 2000, 2000, 5000, 6000, 11, 80151, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Magmalord'),
(42789, 0, 1, 0, 0, 0, 100, 30, 3000, 10000, 13000, 24000, 11, 80038, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Magmalord'),
(42692, 0, 0, 0, 0, 0, 100, 30, 5000, 5000, 6000, 6100, 11, 80221, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Bruiser'),
(42692, 0, 1, 0, 0, 0, 100, 30, 800, 1400, 10000, 11000, 11, 80180, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Bruiser'),
(42692, 0, 2, 0, 0, 0, 100, 30, 3000, 4000, 8000, 8100, 11, 80195, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Stonecore Bruiser');

- SmartAI Throne of the tides Mobs + PickpocketLoot + hp fix + mana fix
UPDATE `creature_template` SET `pickpocketloot` = 40577, `AIName` = 'SmartAI' WHERE `entry` = 40577;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=40577);
INSERT INTO `pickpocketing_loot_template` VALUES 
(40577, 58263, 27, 0, 0, 1, 1),
(40577, 63349, 26, 0, 0, 1, 1),
(40577, 63312, 25, 0, 0, 1, 1),
(40577, 63293, 22, 0, 0, 1, 1),
(40577, 63327, 16, 0, 0, 1, 1),
(40577, 63300, 11, 0, 0, 1, 1),
(40577, 63321, 11, 0, 0, 1, 1);

UPDATE `creature_template` SET `pickpocketloot` = 40935, `AIName` = 'SmartAI' WHERE `entry` = 40935;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=40935);
INSERT INTO `pickpocketing_loot_template` VALUES 
(40935, 63293, 26, 0, 0, 1, 1),
(40935, 58263, 25, 0, 0, 1, 1),
(40935, 63312, 25, 0, 0, 1, 1),
(40935, 63349, 24, 0, 0, 1, 1),
(40935, 63300, 9, 0, 0, 1, 1),
(40935, 63327, 9, 0, 0, 1, 1),
(40935, 63321, 2, 0, 0, 1, 1),
(40935, 55670, 0.19, 0, 0, 1, 1);

UPDATE `creature_template` SET `unit_class` = 2, `pickpocketloot` = 40943, `AIName` = 'SmartAI' WHERE `entry` = 40943;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=40943);
INSERT INTO `pickpocketing_loot_template` VALUES 
(40943, 63312, 29, 0, 0, 1, 1),
(40943, 58263, 25, 0, 0, 1, 1),
(40943, 63293, 25, 0, 0, 1, 1),
(40943, 63349, 19, 0, 0, 1, 1),
(40943, 63327, 10, 0, 0, 1, 1),
(40943, 63300, 7, 0, 0, 1, 1),
(40943, 63321, 1.5, 0, 0, 1, 1),
(40943, 63342, 0.5, 0, 0, 1, 1),
(40943, 17058, 0.15, 0, 0, 1, 1);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40936;
UPDATE `creature_template` SET `AIName` = 'SmartAI', `Health_mod` = 0.27199 WHERE `entry` = 40923;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40925;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44648;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44841;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI', `Mana_mod` = 2 WHERE `entry` = 44715;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 44752;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40788;
UPDATE `creature_template` SET `lootid` = 39960, `pickpocketloot` = 39960 WHERE `entry` = 39960;

DELETE FROM `creature_loot_template` WHERE (`entry`=39960);
INSERT INTO `creature_loot_template` VALUES 
(39960, 63312, 100, 0, 0, 1, 1);

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=39960);
INSERT INTO `pickpocketing_loot_template` VALUES 
(39960, 58263, 28, 0, 0, 1, 1),
(39960, 63312, 26, 0, 0, 1, 1),
(39960, 63293, 25, 0, 0, 1, 1),
(39960, 63349, 20, 0, 0, 1, 1),
(39960, 63327, 13, 0, 0, 1, 1),
(39960, 63321, 4, 0, 0, 1, 1),
(39960, 63300, 3, 0, 0, 1, 1);

UPDATE `creature_template` SET `pickpocketloot` = 39616, `AIName` = 'SmartAI' WHERE `entry` = 39616;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=39616);
INSERT INTO `pickpocketing_loot_template` VALUES 
(39616, 63293, 27, 0, 0, 1, 1),
(39616, 63312, 27, 0, 0, 1, 1),
(39616, 63349, 26, 0, 0, 1, 1),
(39616, 58263, 21, 0, 0, 1, 1),
(39616, 63327, 12, 0, 0, 1, 1),
(39616, 63300, 9, 0, 0, 1, 1),
(39616, 63321, 1, 0, 0, 1, 1),
(39616, 63342, 0.3, 0, 0, 1, 1);

UPDATE `creature_template` SET `unit_class` = 2, `pickpocketloot` = 41139, `AIName` = 'SmartAI', `Mana_mod` = 2 WHERE `entry` = 41139;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=41139);
INSERT INTO `pickpocketing_loot_template` VALUES 
(41139, 63349, 28, 0, 0, 1, 1),
(41139, 63293, 24, 0, 0, 1, 1),
(41139, 63312, 23, 0, 0, 1, 1),
(41139, 58263, 17, 0, 0, 1, 1),
(41139, 63327, 10, 0, 0, 1, 1),
(41139, 63300, 9, 0, 0, 1, 1),
(41139, 63321, 0.5, 0, 0, 1, 1),
(41139, 63342, 0.3, 0, 0, 1, 1);

UPDATE `creature_template` SET `unit_class` = 2, `pickpocketloot` = 40634, `AIName` = 'SmartAI', `Mana_mod` = 2 WHERE `entry` = 40634;

DELETE FROM `pickpocketing_loot_template` WHERE (`entry`=40634);
INSERT INTO `pickpocketing_loot_template` VALUES 
(40634, 63293, 28, 0, 0, 1, 1),
(40634, 63349, 25, 0, 0, 1, 1),
(40634, 58263, 24, 0, 0, 1, 1),
(40634, 63312, 23, 0, 0, 1, 1),
(40634, 63327, 12, 0, 0, 1, 1),
(40634, 63300, 9, 0, 0, 1, 1),
(40634, 63321, 1.2, 0, 0, 1, 1);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40633;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=40577 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40935 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40943 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40936 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40923 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40925 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44648 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44841 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44715 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=44752 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40788 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39616 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41139 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40634 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40633 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(40577, 0, 0, 0, 0, 0, 100, 30, 500, 1000, 4000, 8000, 11, 76721, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Sentinel'),
(40935, 0, 0, 0, 0, 0, 100, 30, 200, 1000, 5000, 6000, 11, 76516, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Gilgoblin Hunter'),
(40935, 0, 1, 0, 0, 0, 100, 30, 2000, 2000, 3000, 4000, 11, 76520, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Gilgoblin Hunter'),
(40943, 0, 0, 0, 0, 0, 100, 30, 2000, 4000, 6000, 8000, 11, 76535, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Gilgoblin Aquamage'),
(40943, 0, 1, 0, 0, 0, 100, 30, 5000, 7000, 10000, 12000, 11, 76560, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gilgoblin Aquamage'),
(40936, 0, 0, 0, 0, 0, 100, 30, 5000, 10000, 15000, 25000, 11, 76590, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Faceless Watcher'),
(40936, 0, 1, 0, 0, 0, 100, 30, 11000, 14000, 15000, 25000, 11, 76590, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Faceless Watcher'),
(40923, 0, 0, 0, 0, 0, 100, 30, 100, 500, 600, 900, 11, 76363, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Unstable Corruption'),
(40925, 0, 0, 0, 0, 0, 100, 30, 1000, 3000, 4500, 6500, 11, 76634, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Tainted Sentry'),
(44648, 0, 0, 0, 0, 0, 100, 30, 1000, 6000, 7000, 12000, 11, 83985, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Unyielding Behemoth'),
(44841, 0, 0, 0, 0, 0, 100, 30, 6000, 6000, 15000, 16000, 11, 83971, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Blight Beast'),
(44715, 0, 0, 0, 0, 0, 100, 30, 2000, 4000, 6000, 8000, 11, 83914, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Vicious Mindlasher'),
(44715, 0, 1, 0, 0, 0, 100, 30, 7000, 10000, 10000, 13000, 11, 83915, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Vicious Mindlasher'),
(44752, 0, 0, 0, 0, 0, 100, 30, 100, 100, 30000, 31000, 11, 83463, 1, 0, 0, 0, 0, 11, 40792, 100, 0, 0, 0, 0, 0, 'Faceless Sapper'),
(40788, 0, 0, 0, 0, 0, 100, 30, 5000, 5000, 10000, 11000, 11, 76207, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Mindbender Ghursha'),
(40788, 0, 1, 0, 2, 0, 100, 30, 5, 20, 15000, 17000, 11, 76307, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mindbender Ghursha'),
(40788, 0, 2, 0, 2, 0, 100, 30, 5, 10, 13000, 14000, 11, 76339, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mindbender Ghursha'),
(39616, 0, 0, 0, 0, 0, 100, 30, 2000, 3000, 4000, 5000, 11, 76807, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Invader'),
(39616, 0, 1, 0, 2, 0, 100, 30, 10, 50, 8000, 10000, 11, 76790, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Invader'),
(41139, 0, 0, 0, 0, 0, 100, 30, 15000, 17000, 18000, 20000, 11, 76820, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Spiritmender'),
(41139, 0, 1, 0, 0, 0, 100, 30, 4000, 6000, 8000, 10000, 11, 76815, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Spiritmender'),
(41139, 0, 2, 0, 2, 0, 100, 30, 10, 40, 13000, 15000, 11, 76813, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Spiritmender'),
(40634, 0, 0, 0, 0, 0, 100, 30, 4000, 6000, 8000, 10000, 11, 75813, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Tempest Witch'),
(40634, 0, 1, 0, 0, 0, 100, 30, 1000, 2000, 6000, 7000, 11, 75992, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Tempest Witch'),
(40633, 0, 0, 0, 2, 0, 100, 30, 20, 60, 10000, 12000, 11, 75998, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Honor Guard'),
(40633, 0, 1, 0, 0, 0, 100, 30, 500, 1500, 4000, 5500, 11, 75907, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Nazjar Honor Guard');

-- Smart AI Gilneas Start zone mobs
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 35118;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 35660;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 35505;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 35463;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 51277;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 35627;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 36057;
UPDATE `creature_template` SET `minlevel` = 4, `maxlevel` = 5, `unit_class` = 2 WHERE `entry` = 36057;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 34884;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=35118 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=35660 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=35505 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=35463 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=51277 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=35627 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=36057 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=34884 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES (35118, 0, 0, 0, 2, 0, 100, 0, 5, 10, 2000, 3000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Worgen'),
(35660, 0, 0, 0, 2, 0, 100, 0, 5, 10, 2000, 3000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rampaging Worgen'),
(35505, 0, 0, 0, 2, 0, 100, 0, 5, 20, 7000, 8000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Ripper'),
(35463, 0, 0, 0, 2, 0, 100, 0, 5, 20, 7000, 8000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Lurker'),
(35463, 0, 1, 0, 0, 0, 100, 0, 100, 500, 20000, 21000, 11, 80515, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Lurker'),
(35463, 0, 2, 0, 0, 0, 100, 0, 1, 400, 15000, 16000, 11, 5916, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Lurker'),
(51277, 0, 0, 0, 2, 0, 100, 0, 5, 20, 7000, 8000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Bloodfang Stalker'),
(35627, 0, 0, 0, 2, 0, 100, 0, 5, 20, 7000, 8000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Frenzied Stalker'),
(36057, 0, 0, 0, 0, 0, 100, 0, 100, 400, 600, 800, 11, 59146, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Northgate Rebel'),
(36057, 0, 1, 0, 0, 0, 100, 0, 800, 1000, 1200, 1400, 11, 21390, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Northgate Rebel'),
(36057, 0, 2, 0, 0, 0, 100, 0, 1300, 2000, 2200, 2900, 11, 15496, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Northgate Rebel'),
(36057, 0, 3, 0, 2, 0, 100, 0, 40, 70, 3000, 3400, 11, 61044, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Northgate Rebel'),
(34884, 0, 0, 0, 2, 0, 100, 0, 5, 20, 7000, 8000, 11, 8599, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Rampaging Worgen');

-- SmartAI Grim Batol all MOBS 5Normal/5Heroic
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45467;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39855;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39854;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39900;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39961;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41073;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39381;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI' WHERE `entry` = 39890;
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 48595;
UPDATE `creature_template` SET `Mana_mod` = 10 WHERE `entry` = 39890;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI' WHERE `entry` = 39962;
UPDATE `creature_template` SET `difficulty_entry_1` = 48597 WHERE `entry` = 39962;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39414;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39415;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI', `Mana_mod` = 10 WHERE `entry` = 39954;
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 48669;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40167;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40166;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39909;
UPDATE `creature_template` SET `minlevel` = 83, `maxlevel` = 85, `exp` = 2, `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 41040;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39892;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39956;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI', `Mana_mod` = 10 WHERE `entry` = 40268;
UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 48744;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI' WHERE `entry` = 40270;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40269;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40291;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 39870;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40272;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40273;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 40290;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=45467 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39855 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39854 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39900 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39961 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41073 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39381 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39890 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39962 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39414 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39415 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39954 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40167 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40166 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(45467, 0, 0, 0, 0, 0, 100, 4, 14000, 15000, 20000, 22000, 11, 90179, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Trogg Dweller'),
(45467, 0, 1, 0, 0, 0, 100, 4, 500, 1500, 4000, 5000, 11, 90212, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Trogg Dweller'),
(45467, 0, 2, 0, 0, 0, 100, 2, 500, 1500, 4000, 5000, 11, 76507, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Trogg Dweller'),
(39855, 0, 0, 0, 2, 0, 100, 2, 20, 50, 16000, 17000, 11, 76340, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39855, 0, 1, 0, 0, 0, 100, 2, 1000, 5000, 10000, 14000, 11, 76370, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39855, 0, 2, 0, 0, 0, 100, 2, 6000, 9000, 15000, 18000, 11, 76369, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39855, 0, 3, 0, 2, 0, 100, 4, 20, 50, 16000, 17000, 11, 90844, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39855, 0, 4, 0, 0, 0, 100, 4, 1000, 5000, 10000, 14000, 11, 90300, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39855, 0, 5, 0, 0, 0, 100, 4, 6000, 9000, 15000, 18000, 11, 90303, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39854, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 12000, 14000, 11, 76394, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Guardian'),
(39854, 0, 1, 0, 0, 0, 100, 6, 3000, 5000, 8000, 10000, 11, 76378, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Guardian'),
(39854, 0, 2, 0, 0, 0, 100, 4, 1000, 2000, 12000, 14000, 11, 90659, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Guardian'),
(39900, 0, 0, 0, 2, 0, 100, 6, 20, 70, 4000, 5000, 11, 76014, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Rock Elemental'),
(39961, 0, 0, 0, 0, 0, 100, 4, 1000, 3000, 5000, 7000, 11, 90490, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Water Spirit'),
(41073, 0, 0, 0, 0, 0, 100, 2, 1000, 3000, 6000, 7600, 11, 76727, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Armsmaster'),
(41073, 0, 1, 0, 0, 0, 100, 6, 8000, 15000, 15500, 20000, 11, 76729, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Armsmaster'),
(41073, 0, 2, 0, 0, 0, 100, 4, 1000, 3000, 6000, 7600, 11, 90526, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Armsmaster'),
(39381, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 6000, 7000, 11, 76409, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Guardian'),
(39381, 0, 1, 0, 0, 0, 100, 4, 5000, 5000, 6000, 7000, 11, 90312, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Guardian'),
(39890, 0, 0, 0, 0, 0, 100, 2, 5000, 5000, 6000, 7000, 11, 76603, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Earthshaper'),
(39890, 0, 1, 0, 2, 0, 100, 2, 5, 30, 8000, 8100, 11, 76596, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Earthshaper'),
(39890, 0, 2, 0, 0, 0, 100, 6, 10000, 15000, 40000, 45000, 11, 74552, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Earthshaper'),
(39890, 0, 3, 0, 0, 0, 100, 4, 5000, 5000, 6000, 7000, 11, 90487, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Earthshaper'),
(39890, 0, 4, 0, 2, 0, 100, 4, 5, 30, 8000, 8100, 11, 90486, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Earthshaper'),
(39962, 0, 0, 0, 0, 0, 100, 2, 5000, 7000, 16000, 18000, 11, 76720, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Stormbreaker'),
(39962, 0, 1, 0, 0, 0, 100, 6, 10000, 15000, 40000, 45000, 11, 76561, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Stormbreaker'),
(39962, 0, 2, 0, 0, 0, 100, 4, 5000, 7000, 16000, 18000, 11, 90522, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Stormbreaker'),
(39962, 0, 3, 0, 0, 0, 100, 4, 2000, 4000, 8000, 10000, 11, 90491, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Stormbreaker'),
(39414, 0, 0, 0, 0, 0, 100, 6, 1000, 1000, 6000, 7000, 11, 76557, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ascended Windwalker'),
(39415, 0, 0, 0, 0, 0, 100, 2, 2000, 4000, 16000, 18000, 11, 76517, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Flameseeker'),
(39415, 0, 1, 0, 0, 0, 100, 2, 6000, 14000, 20000, 28000, 11, 76514, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Flameseeker'),
(39415, 0, 2, 0, 0, 0, 100, 4, 2000, 4000, 16000, 18000, 11, 90693, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Flameseeker'),
(39415, 0, 3, 0, 0, 0, 100, 4, 6000, 14000, 20000, 28000, 11, 90692, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Flameseeker'),
(39954, 0, 0, 0, 0, 0, 100, 2, 1000, 3000, 8000, 10000, 11, 76416, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Shadow Weaver'),
(39954, 0, 1, 0, 0, 0, 100, 4, 1000, 3000, 8000, 10000, 11, 90668, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Shadow Weaver'),
(39954, 0, 2, 0, 0, 0, 100, 4, 6000, 6000, 14000, 15000, 11, 90673, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Shadow Weaver'),
(39954, 0, 3, 0, 0, 0, 100, 4, 16000, 21000, 50000, 55000, 11, 76418, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Shadow Weaver'),
(40167, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 6000, 7000, 11, 76715, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Beguiler'),
(40167, 0, 1, 0, 0, 0, 100, 2, 3000, 5000, 9000, 11000, 11, 76711, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Beguiler'),
(40167, 0, 2, 0, 0, 0, 100, 4, 3000, 5000, 9000, 11000, 11, 90715, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Beguiler'),
(40167, 0, 3, 0, 0, 0, 100, 4, 1000, 2000, 6000, 7000, 11, 90712, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Beguiler'),
(40167, 0, 4, 0, 0, 0, 100, 4, 4000, 5500, 11000, 13000, 11, 90719, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Beguiler'),
(40166, 0, 0, 0, 0, 0, 100, 2, 1000, 3000, 5000, 7000, 11, 76703, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Gronn Brute'),
(40166, 0, 1, 0, 0, 0, 100, 4, 1000, 3000, 5000, 7000, 11, 90710, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Gronn Brute');

DELETE FROM `smart_scripts` WHERE (`entryorguid`=39909 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39892 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39956 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40268 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40270 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40269 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40291 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39870 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40273 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40272 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=40290 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(39909, 0, 0, 0, 0, 0, 100, 2, 2000, 6000, 9000, 13000, 11, 76620, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Warlord'),
(39909, 0, 1, 0, 0, 0, 100, 2, 15000, 21000, 25000, 31000, 11, 76626, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Warlord'),
(39909, 0, 2, 0, 0, 0, 100, 4, 15000, 21000, 25000, 31000, 11, 90695, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Warlord'),
(39909, 0, 3, 0, 0, 0, 100, 4, 2000, 6000, 9000, 13000, 11, 90697, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Warlord'),
(39892, 0, 0, 0, 0, 0, 100, 6, 200, 1000, 4000, 5000, 11, 90846, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Burning Ember'),
(39956, 0, 0, 0, 0, 0, 100, 2, 1000, 3000, 5000, 7000, 11, 76411, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Enforcer'),
(39956, 0, 1, 0, 0, 0, 100, 2, 3100, 3100, 7100, 7200, 11, 76415, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Enforcer'),
(39956, 0, 2, 0, 0, 0, 100, 4, 1000, 3000, 5000, 7000, 11, 90665, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Enforcer'),
(39956, 0, 3, 0, 0, 0, 100, 4, 3100, 3100, 7100, 7200, 11, 90666, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Enforcer'),
(40268, 0, 0, 0, 0, 0, 100, 2, 1000, 2000, 8000, 8500, 11, 76825, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40268, 0, 1, 0, 0, 0, 100, 6, 9000, 9000, 16000, 17000, 11, 76823, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40268, 0, 2, 0, 0, 0, 100, 6, 10000, 10000, 17000, 18000, 11, 76822, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40268, 0, 3, 0, 0, 0, 100, 2, 3000, 5000, 20000, 22000, 11, 76826, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40268, 0, 4, 0, 0, 0, 100, 4, 1000, 2000, 8000, 8500, 11, 90841, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40268, 0, 5, 0, 0, 0, 100, 4, 3000, 5000, 20000, 22000, 11, 90839, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight War-Mage'),
(40270, 0, 0, 0, 0, 0, 100, 2, 2000, 4000, 9000, 11000, 11, 76579, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Thundercaller'),
(40270, 0, 1, 0, 0, 0, 100, 2, 5000, 7000, 12000, 14000, 11, 76578, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Thundercaller'),
(40270, 0, 2, 0, 0, 0, 100, 6, 15000, 20000, 45000, 50000, 11, 75096, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Thundercaller'),
(40270, 0, 3, 0, 0, 0, 100, 4, 2000, 4000, 9000, 11000, 11, 90858, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Thundercaller'),
(40270, 0, 4, 0, 0, 0, 100, 4, 5000, 7000, 12000, 14000, 11, 90856, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Thundercaller'),
(40269, 0, 0, 0, 0, 0, 100, 2, 100, 400, 4000, 5000, 11, 90852, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Enslaved Thunder Spirit'),
(40291, 0, 0, 0, 2, 0, 100, 2, 20, 50, 16000, 17000, 11, 76340, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(40291, 0, 1, 0, 0, 0, 100, 2, 1000, 5000, 10000, 14000, 11, 76370, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(40291, 0, 2, 0, 0, 0, 100, 2, 6000, 9000, 15000, 18000, 11, 76369, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(40291, 0, 3, 0, 2, 0, 100, 4, 20, 50, 16000, 17000, 11, 90844, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(40291, 0, 4, 0, 0, 0, 100, 4, 1000, 5000, 10000, 14000, 11, 90300, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(40291, 0, 5, 0, 0, 0, 100, 4, 6000, 9000, 15000, 18000, 11, 90303, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Azureborne Seer'),
(39870, 0, 0, 0, 0, 0, 100, 2, 1000, 3000, 6000, 8000, 11, 76765, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Firecatcher'),
(39870, 0, 1, 0, 0, 0, 100, 2, 5000, 10000, 15000, 20000, 11, 76766, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Firecatcher'),
(39870, 0, 2, 0, 0, 0, 100, 6, 11000, 16000, 40000, 45000, 11, 74551, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Firecatcher'),
(39870, 0, 3, 0, 0, 0, 100, 4, 1000, 3000, 6000, 8000, 11, 90849, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Twilight Firecatcher'),
(39870, 0, 4, 0, 0, 0, 100, 4, 5000, 10000, 15000, 20000, 11, 90851, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Twilight Firecatcher'),
(40273, 0, 0, 0, 0, 0, 100, 6, 19000, 19000, 30000, 31000, 11, 76097, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Waterlasher'),
(40273, 0, 1, 0, 0, 0, 100, 2, 5000, 5000, 8000, 9000, 11, 76794, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Waterlasher'),
(40273, 0, 2, 0, 0, 0, 100, 2, 12000, 18000, 22000, 28000, 11, 76797, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Waterlasher'),
(40273, 0, 3, 0, 0, 0, 100, 4, 5000, 5000, 8000, 9000, 11, 90870, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Waterlasher'),
(40273, 0, 4, 0, 0, 0, 100, 4, 12000, 18000, 22000, 28000, 11, 90868, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Waterlasher'),
(40272, 0, 0, 0, 0, 0, 100, 6, 5000, 5000, 9000, 10000, 11, 76093, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40272, 0, 1, 0, 0, 0, 100, 2, 1000, 3000, 4000, 6000, 11, 76792, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40272, 0, 2, 0, 0, 0, 100, 2, 100, 900, 7000, 8000, 11, 76779, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40272, 0, 3, 0, 0, 0, 100, 4, 1000, 3000, 4000, 6000, 11, 90867, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40272, 0, 4, 0, 0, 0, 100, 4, 100, 900, 7000, 8000, 11, 90866, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40272, 0, 5, 0, 2, 0, 100, 4, 10, 40, 11000, 12000, 11, 76086, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Ascended Rockbreaker'),
(40290, 0, 0, 0, 0, 0, 100, 2, 10000, 12000, 30000, 31000, 11, 76314, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer'),
(40290, 0, 1, 0, 0, 0, 100, 2, 6000, 6000, 11000, 12000, 11, 76335, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer'),
(40290, 0, 2, 0, 0, 0, 100, 2, 15000, 25000, 40000, 50000, 11, 76332, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer'),
(40290, 0, 3, 0, 0, 0, 100, 4, 10000, 12000, 30000, 31000, 11, 90308, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer'),
(40290, 0, 4, 0, 0, 0, 100, 4, 6000, 6000, 11000, 12000, 11, 90652, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer'),
(40290, 0, 5, 0, 0, 0, 100, 4, 15000, 25000, 40000, 50000, 11, 90653, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Crimsonborne Seer');

UPDATE `creature_template` SET `minlevel` = 84, `maxlevel` = 85, `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 48597;
UPDATE `creature_template` SET `mindmg` = 725, `maxdmg` = 959, `unit_class` = 2 WHERE `entry` = 48597;
UPDATE `creature_template` SET `exp` = 2, `minrangedmg` = 439, `maxrangedmg` = 695, `rangedattackpower` = 165 WHERE `entry` = 48597;

-- SmartAI Hyjal 2 mobs + Fix mana mod + redone Forgemaster Pyrendius
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41029 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=41255 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=39446 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(41029, 0, 0, 0, 4, 0, 100, 1, 0, 0, 0, 0, 11, 78114, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast Twilight Charge on Aggro'),
(41029, 0, 1, 0, 0, 0, 100, 0, 5000, 9000, 13000, 16000, 11, 78121, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast Twilight Blast'),
(41029, 0, 2, 0, 0, 0, 100, 0, 10000, 10000, 18000, 19000, 11, 78113, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Twilight Dragon'),
(41255, 0, 0, 0, 0, 0, 100, 0, 1000, 4000, 7000, 10000, 11, 78129, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Sethria'),
(41255, 0, 1, 0, 0, 0, 100, 0, 6000, 7000, 12000, 13000, 11, 78143, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sethria'),
(41255, 0, 2, 0, 0, 0, 100, 0, 14000, 16000, 21000, 23000, 11, 78160, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Sethria'),
(39446, 0, 0, 0, 0, 0, 100, 0, 8000, 8000, 18000, 21000, 11, 37776, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Cast Blood Howl'),
(39446, 0, 1, 0, 0, 0, 100, 0, 100, 200, 10000, 11000, 11, 74061, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Cast Fear');

UPDATE `creature_template` SET `unit_class` = 2 WHERE `entry` = 41030;
UPDATE `creature_template` SET `unit_class` = 2, `AIName` = 'SmartAI' WHERE `entry` = 41255;
UPDATE `creature_template` SET `unit_class` = 2, `Mana_mod` = 2 WHERE `entry` = 39643;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=40845 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(40845, 0, 0, 0, 0, 0, 100, 0, 500, 1000, 4000, 6000, 11, 18543, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Forgemaster Pyrendius');

-- Westfall SmartAI Small pack (4 mobs) tested
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 573;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=462);
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 462;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42677;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=573);
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 42669;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=42677 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=462 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=573 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42669 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(42677, 0, 0, 0, 0, 0, 100, 0, 1000, 2000, 8000, 8000, 11, 80146, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Moonbrook Thug'),
(462, 0, 0, 0, 0, 0, 100, 0, 1000, 2000, 5000, 6000, 11, 13443, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Vultros'),
(573, 0, 0, 0, 0, 0, 100, 0, 2000, 2000, 14000, 14000, 11, 7342, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Foe Reaper 4000'),
(573, 0, 1, 0, 2, 0, 100, 0, 10, 40, 16000, 19000, 11, 80572, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Foe Reaper 4000'),
(42669, 0, 0, 0, 2, 0, 100, 0, 5, 30, 7000, 10000, 11, 80570, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Chasm Slime');

-- Duskwood SmartAI Small pack (3 mobs)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 45619;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43761;

DELETE FROM `creature` WHERE `id`=1200;
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=522);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 522;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=45619 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=522 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43761 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(45619, 0, 0, 0, 0, 0, 100, 0, 1000, 2000, 5000, 7000, 11, 16856, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Morbidius'),
(522, 0, 0, 0, 2, 0, 100, 0, 5, 50, 25000, 25000, 11, 3547, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'MorLadim'),
(522, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 5000, 6000, 11, 79961, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'MorLadim'),
(43761, 0, 0, 0, 0, 0, 100, 0, 3000, 5500, 15000, 15500, 11, 3108, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel'),
(43761, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 12000, 14000, 11, 3109, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel'),
(43761, 0, 2, 0, 4, 0, 100, 0, 0, 0, 0, 0, 11, 8909, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Morbent Fel');

-- SmartAI Shatterspear champion - Removed EventAI because no events here - Empty (Console Errors)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 32858;

DELETE FROM `smart_scripts` WHERE (`entryorguid`=32858 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(32858, 0, 0, 0, 0, 0, 100, 0, 1000, 3000, 7000, 9000, 11, 37704, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Shatterspear Champion');

-- SmartAI Blackwing Descent Mobs 10/25 normal/heroic scripts
-- Skin loot for dragons
-- Added spawn location for npc 41440 and smartai
-- Loot fix 10 normal for npc 43126
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 41440;
UPDATE `creature_template` SET `skinloot` = 42764, `AIName` = 'SmartAI' WHERE `entry` = 42764;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 41440;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 43126;

DELETE FROM `skinning_loot_template` WHERE (`entry`=42764);
INSERT INTO `skinning_loot_template` VALUES
(42764, 52976, 88, 0, 0, 1, 7),
(42764, 52979, 58, 0, 0, 1, 7);

UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 46083;
UPDATE `creature_template` SET `skinloot` = 42767, `AIName` = 'SmartAI' WHERE `entry` = 42767;

DELETE FROM `skinning_loot_template` WHERE (`entry`=42767);
INSERT INTO `skinning_loot_template` VALUES
(42767, 52976, 89, 0, 0, 1, 7),
(42767, 52979, 57, 0, 0, 1, 6);

UPDATE `creature_template` SET `skinloot` = 42768, `AIName` = 'SmartAI' WHERE `entry` = 42768;

DELETE FROM `skinning_loot_template` WHERE (`entry`=42768);
INSERT INTO `skinning_loot_template` VALUES
(42768, 52976, 85, 0, 0, 1, 11),
(42768, 52979, 56, 0, 0, 1, 7);

DELETE FROM `creature_loot_template` WHERE (`entry`=43126);
INSERT INTO `creature_loot_template` VALUES
(43126, 53010, 36, 1, 0, 1, 6),
(43126, 68198, 10, 1, 0, 1, 2),
(43126, 58268, 5, 1, 0, 1, 1),
(43126, 59461, 3, 1, 0, 1, 1),
(43126, 58256, 3, 1, 0, 1, 1),
(43126, 68197, 3, 1, 0, 1, 2),
(43126, 59463, 2, 1, 0, 1, 1),
(43126, 59462, 1.9, 1, 0, 1, 1),
(43126, 59460, 1.8, 1, 0, 1, 1),
(43126, 68601, 1.8, 1, 0, 1, 1);

DELETE FROM `smart_scripts` WHERE (`entryorguid`=41440 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42764 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=46083 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42767 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=42768 AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=43126 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(41440, 0, 0, 0, 0, 0, 100, 30, 200, 1000, 6000, 7000, 11, 39700, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Aberration'),
(42764, 0, 0, 0, 0, 0, 100, 30, 5000, 10000, 20000, 25000, 11, 79921, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Pyrecraw'),
(42764, 0, 1, 0, 0, 0, 100, 6, 2000, 3000, 6000, 7000, 11, 80127, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Pyrecraw'),
(42764, 0, 2, 0, 0, 0, 100, 24, 2000, 3000, 6000, 7000, 11, 91902, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Pyrecraw'),
(46083, 0, 0, 0, 0, 0, 100, 30, 7000, 9000, 16000, 18000, 11, 80329, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 1, 0, 0, 0, 100, 6, 500, 1000, 60000, 61000, 11, 79904, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 2, 0, 0, 0, 100, 30, 23000, 25000, 30000, 32000, 11, 80341, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 3, 0, 0, 0, 100, 6, 4000, 6000, 15000, 17000, 11, 80345, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 4, 0, 0, 0, 100, 6, 8000, 10000, 19000, 21000, 11, 80336, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 5, 0, 2, 0, 100, 6, 5, 30, 23000, 25000, 11, 80332, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 6, 0, 2, 0, 100, 24, 5, 30, 23000, 25000, 11, 91907, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 7, 0, 0, 0, 100, 24, 8000, 10000, 19000, 21000, 11, 91896, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 8, 0, 0, 0, 100, 24, 4000, 6000, 15000, 17000, 11, 95060, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 9, 0, 0, 0, 100, 24, 500, 1000, 60000, 61000, 11, 91904, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 10, 0, 0, 0, 20, 30, 100, 900, 70000, 70000, 11, 80372, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 11, 0, 0, 0, 20, 30, 100, 900, 70000, 70000, 11, 80369, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 12, 0, 0, 0, 20, 30, 100, 900, 70000, 70000, 11, 80368, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 13, 0, 0, 0, 20, 30, 100, 900, 70000, 70000, 11, 80371, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(46083, 0, 14, 0, 0, 0, 20, 30, 100, 900, 70000, 70000, 11, 80370, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drakeadon Mongrel'),
(42767, 0, 0, 0, 0, 0, 100, 30, 6000, 8000, 20000, 22000, 11, 80295, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Ivoroc'),
(42767, 0, 1, 0, 0, 0, 100, 30, 10000, 15000, 30000, 35000, 11, 79921, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Ivoroc'),
(42768, 0, 0, 0, 2, 0, 100, 30, 5, 10, 50000, 50000, 11, 80084, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, ''),
(42768, 0, 1, 0, 0, 0, 100, 6, 8000, 9000, 15000, 16000, 11, 80130, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(42768, 0, 2, 0, 0, 0, 100, 6, 6000, 6000, 17000, 18000, 11, 80270, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(42768, 0, 3, 0, 0, 0, 100, 6, 1000, 5000, 20000, 25000, 11, 80145, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(42768, 0, 4, 0, 0, 0, 100, 24, 1000, 5000, 20000, 25000, 11, 91909, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(42768, 0, 5, 0, 0, 0, 100, 24, 6000, 6000, 17000, 18000, 11, 91908, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(42768, 0, 6, 0, 0, 0, 100, 24, 8000, 9000, 15000, 16000, 11, 91901, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Maimgor'),
(43126, 0, 0, 0, 0, 0, 100, 30, 500, 500, 30000, 30000, 11, 80645, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 1, 0, 0, 0, 100, 2, 1000, 1000, 28000, 28000, 11, 80718, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 2, 0, 0, 0, 100, 30, 5000, 10000, 20000, 25000, 11, 80652, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 3, 0, 0, 0, 100, 6, 3000, 3000, 17000, 17000, 11, 80648, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 4, 0, 2, 0, 100, 30, 30, 50, 26000, 26000, 11, 80655, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 5, 0, 0, 0, 100, 30, 30000, 50000, 70000, 90000, 11, 80727, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 6, 0, 0, 0, 100, 6, 7000, 7000, 14000, 14000, 11, 80649, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 7, 0, 0, 0, 100, 6, 4000, 4500, 13000, 13500, 11, 80646, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 8, 0, 2, 0, 100, 6, 5, 10, 31000, 32000, 11, 80747, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 9, 0, 0, 0, 100, 24, 3000, 3000, 17000, 17000, 11, 91890, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 10, 0, 0, 0, 100, 24, 4000, 4500, 13000, 13500, 11, 91891, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 11, 0, 2, 0, 100, 24, 5, 10, 31000, 32000, 11, 95537, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 12, 0, 4, 0, 100, 30, 0, 0, 0, 0, 11, 80871, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 13, 0, 4, 0, 35, 30, 0, 0, 0, 0, 11, 80762, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 14, 0, 4, 0, 35, 30, 0, 0, 0, 0, 11, 80770, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan'),
(43126, 0, 15, 0, 4, 0, 35, 30, 0, 0, 0, 0, 11, 80766, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Spirit of Thaurissan');

DELETE FROM `creature` WHERE `id`=41440;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(6657290, 41440, 669, 1, 1, 0, 0, -78.6178, -473.454, 73.7118, 2.20538, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657292, 41440, 669, 1, 1, 0, 0, -83.4519, -478.074, 73.7118, 1.99463, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657294, 41440, 669, 1, 1, 0, 0, -83.4794, -470.541, 73.2104, 1.8173, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657296, 41440, 669, 1, 1, 0, 0, -92.1432, -472.68, 72.8516, 1.54132, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657298, 41440, 669, 1, 1, 0, 0, -85.3816, -488.867, 73.2129, 1.8173, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657354, 41440, 669, 1, 1, 0, 0, -110.886, -474.556, 73.4552, 1.10477, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657352, 41440, 669, 1, 1, 0, 0, -117.671, -430.39, 73.2881, 1.28541, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657350, 41440, 669, 1, 1, 0, 0, -101.274, -445.764, 73.6697, 2.07321, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657348, 41440, 669, 1, 1, 0, 0, -80.5363, -453.174, 73.5578, 2.11335, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657346, 41440, 669, 1, 1, 0, 0, -103.247, -423.063, 73.0187, 1.33057, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657344, 41440, 669, 1, 1, 0, 0, -88.5244, -430.705, 73.2581, 2.24883, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657342, 41440, 669, 1, 1, 0, 0, -98.9911, -436.654, 73.4546, 1.63666, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657340, 41440, 669, 1, 1, 0, 0, -134.267, -441.216, 73.4243, 0.271812, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657338, 41440, 669, 1, 1, 0, 0, -114.805, -439.717, 73.5125, 1.05961, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657336, 41440, 669, 1, 1, 0, 0, -105.511, -449.205, 73.2843, 1.96783, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657334, 41440, 669, 1, 1, 0, 0, -90.5349, -442.496, 73.5317, 1.7621, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657332, 41440, 669, 1, 1, 0, 0, -78.4927, -428.741, 73.2492, 2.50976, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657330, 41440, 669, 1, 1, 0, 0, -79.6861, -443.507, 73.4658, 2.54488, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657328, 41440, 669, 1, 1, 0, 0, -92.0497, -453.237, 73.7451, 2.0983, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657326, 41440, 669, 1, 1, 0, 0, -74.7544, -458.79, 73.7118, 2.05314, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657324, 41440, 669, 1, 1, 0, 0, -84.0625, -464.576, 73.459, 1.96282, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657322, 41440, 669, 1, 1, 0, 0, -101.805, -468.764, 73.4549, 1.01947, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657320, 41440, 669, 1, 1, 0, 0, -126.707, -482.5, 73.2141, 5.98798, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657318, 41440, 669, 1, 1, 0, 0, -141.46, -459.994, 73.3562, 1.09975, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657316, 41440, 669, 1, 1, 0, 0, -129.05, -432.054, 73.2812, 0.387221, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657314, 41440, 669, 1, 1, 0, 0, -122.979, -444.711, 73.5722, 1.19509, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657312, 41440, 669, 1, 1, 0, 0, -110.228, -459.361, 73.455, 1.63666, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657310, 41440, 669, 1, 1, 0, 0, -115.056, -469.405, 73.4577, 0.964272, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657308, 41440, 669, 1, 1, 0, 0, -123.783, -457.652, 73.7617, 0.698328, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657306, 41440, 669, 1, 1, 0, 0, -133.246, -445.83, 73.4751, 0.613025, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657304, 41440, 669, 1, 1, 0, 0, -136.225, -466.301, 73.7117, 1.52627, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657302, 41440, 669, 1, 1, 0, 0, -135.01, -479.772, 73.7117, 1.58147, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0),
(6657300, 41440, 669, 1, 1, 0, 0, -126.315, -470.177, 73.2099, 1.68684, 300, 0, 0, 169907, 0, 0, 0, 0, 0, 0);

-- Lost ScriptNames
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('50524','67533','50053','70701','56641','1120','80398','79513');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(50524,'spell_dk_runic_power_feed'),
(67533,'spell_item_red_rider_air_rifle'),
(50053,'spell_varos_centrifuge_shield'),
(70701,'spell_putricide_expunged_gas'),
(56641,'spell_hun_steady_shot'),
(1120, 'spell_warl_drain_soul'),
(80398,'spell_warlock_dark_intent'),
(79513,'item_tiki_torch');

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (5369,5423);
INSERT INTO `areatrigger_scripts` (`entry`,`ScriptName`) VALUES
(5369, 'at_RX_214_repair_o_matic_station'),
(5423, 'at_RX_214_repair_o_matic_station');

UPDATE `creature_template` SET `ScriptName` = 'npc_lord_darius_crowley' WHERE `entry` = '35077';
UPDATE `creature_template` SET `ScriptName` = 'npc_josiah_avery' WHERE `entry` = '35369';
UPDATE `creature_template` SET `ScriptName` = 'npc_eye_of_acherus' WHERE `entry` = '28511';
UPDATE `creature_template` SET `ScriptName` = 'npc_prospector_anvilward' WHERE `entry` = '15420';
UPDATE `creature_template` SET `ScriptName`='mob_shattered_rumbler' WHERE `entry`=17157;
UPDATE `creature_template` SET `ScriptName`='mob_lump' WHERE `entry`=18351;
UPDATE `creature_template` SET `ScriptName`='npc_altruis_the_sufferer' WHERE `entry`=18417;
UPDATE `creature_template` SET `ScriptName`='npc_lantresor_of_the_blade' WHERE `entry`=18261;
UPDATE `creature_template` SET `ScriptName`='mob_sparrowhawk' WHERE `entry`=22979;
UPDATE `creature_template` SET `ScriptName`='npc_azure_ring_captain' WHERE `entry`=27638;
UPDATE `creature_template` SET `ScriptName`='npc_jungle_punch_target' WHERE `entry` IN(27986,28047,28568);
UPDATE `creature_template` SET `ScriptName`='npc_brunnhildar_prisoner' WHERE `entry`=29639;

