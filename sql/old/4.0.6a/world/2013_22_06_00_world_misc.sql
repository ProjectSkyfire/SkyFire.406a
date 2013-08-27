-- Credits to Kiper and Bastek.
-- Some fix for Gart Mistrunner and quest Rejuvenating Touch 
UPDATE quest_template SET ReqCreatureOrGOCount1 = 2, ReqSpellCast1 = 774 WHERE entry = 27067;
UPDATE npc_trainer SET spell = 774, reqlevel = 8 WHERE entry = 3060 AND spell = 5185;

-- Centaur Bracers quest items drop fix
DELETE FROM `creature_loot_template` WHERE item=5030; 
INSERT  INTO `creature_loot_template` VALUES 
(3272,5030,-4,1,0,1,1),
(3273,5030,-4,1,0,1,1),
(3274,5030,-1,1,0,1,1),
(3275,5030,-80,1,0,1,1),
(3394,5030,-3,1,0,1,1),
(3395,5030,-3,1,0,1,1),
(3396,5030,-21,1,0,1,1),
(3397,5030,-20,1,0,1,1),
(44170,5030,-36,1,0,1,1),
(5837,5030,-7,1,0,1,1),
(5838,5030,-4,1,0,1,1),
(5841,5030,-6,1,0,1,1),
(9456,5030,-4,1,0,1,1),
(9523,5030,-99,1,0,1,1),
(9524,5030,-90,1,0,1,1);

-- Poison Water quest items drop fix
DELETE FROM creature_loot_template WHERE entry IN (2958, 2956, 2957) AND item IN (4758, 4759);
INSERT INTO creature_loot_template VALUES
(2958, 4758, -40, 1, 0, 1, 1),
(2956, 4759, -51, 1, 0, 1, 1),
(2957, 4759, -6, 1, 0, 1, 1);

-- The Rod of Lianthe drop fix
DELETE FROM creature_loot_template WHERE entry IN (19792, 19796, 19806) AND item = 31316;
INSERT INTO creature_loot_template VALUES
(19792, 31316, -6, 1, 0, 1, 1),
(19796, 31316, -6, 1, 0, 1, 1),
(19806, 31316, -5, 1, 0, 1, 1);

-- Fix quest Curtail the Darktail
DELETE FROM conditions WHERE SourceEntry=78838 AND SourceTypeOrReferenceId=13;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, ConditionValue3, ErrorTextId, ScriptName, COMMENT)VALUES
(13,0,78838,0,18,1,42235,0,0,0,'Enohar''s Explosive Arrow can hit only Darktail Bonepicker.');

-- Fix quest False Idols
UPDATE `quest_template` SET `ReqCreatureOrGOId1`=-203289,`ReqCreatureOrGOCount1`=1 WHERE `entry`=25705;

UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry`=203289;
DELETE FROM `smart_scripts` WHERE `entryorguid`=203289 AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(203289,1,0,0,64,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Azsh''ir Idol - On GossipHello - despawn');

-- Fix quest The Holy Water of Clarity
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=759 AND `item`=58811;
UPDATE `gameobject_loot_template` SET `ChanceOrQuestChance`=-100 WHERE `entry`=759 AND `item`=60386;

-- Fix quest Cozzle's Plan
DELETE FROM gameobject_loot_template WHERE item=5852;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(20691,5852,100,1,0,1,1);

-- Fix quest The Defense of Grom'gol: Murloc Menace 
UPDATE `creature_template` SET `KillCredit1`=42621 WHERE `entry` IN (4460,4458,4461,4457,4459);

-- Fix quest Zul'Mamwe Mambo
UPDATE `creature_template` SET `KillCredit1`=43024 WHERE `entry` IN (1059,783,782,42858,781,672,784,669,670);

-- Fix quest Latent Disease
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=1815;
DELETE FROM `smart_scripts` WHERE `entryorguid`=1815 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(1815,0,0,0,6,0,100,0,0,0,0,0,11,83105,2,0,0,0,0,1,0,0,0,0,0,0,0,'Diseased Black Bear - On Death - Cast Latent Disease: Summon Plague Tangle');

 UPDATE `gameobject_template` SET `flags`=0 WHERE `entry`=205060;
 
 -- Ancient Shadowmoon Spirit quests
UPDATE quest_template SET NextQuestId = 10635 WHERE entry = 10634;
UPDATE quest_template SET NextQuestId = 10636, PrevQuestId = 10634 WHERE entry = 10635;
UPDATE quest_template SET NextQuestId = 10637, PrevQuestId = 10635 WHERE entry = 10636;
UPDATE quest_template SET RequiredRaces = 690 WHERE entry = 10639;
UPDATE quest_template SET RequiredRaces = 1101 WHERE entry = 10645;

-- Fix quest The Spiders Have to Go(27980)
UPDATE `creature_template` SET `KillCredit1`=5857 WHERE `entry` IN (5858);

-- Fix quest Aberrant Flora (24855)
UPDATE `creature_template` SET `KillCredit1`=38358 WHERE `entry` IN (6510,6511,6509,6512);
