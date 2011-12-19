UPDATE `creature_template` SET `AIName`='SmartAI',`InhabitType`=4 WHERE `entry`=31689;
DELETE FROM `creature_template_addon` WHERE `entry`=31689;
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (31689,0,33554432,1,0, '59562 0');
DELETE FROM `smart_scripts` WHERE `entryorguid`=31689 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`)VALUES
(31689,0,0,0,22,0,100,0,78,5000,5000,0,5,66,0,0,0,0,0,1,0,0,0,0,0,0,0,'Salute - Salute'),
(31689,0,1,0,22,0,100,0,21,5000,5000,0,5,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cheer - Bow'),
(31689,0,2,0,22,0,100,0,101,5000,5000,0,5,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Wave - Wave'),
(31689,0,3,0,22,0,100,0,34,5000,5000,0,5,94,0,0,0,0,0,1,0,0,0,0,0,0,0,'Dance - Dance'),
(31689,0,4,0,22,0,100,0,328,5000,5000,0,5,11,0,0,0,0,0,1,0,0,0,0,0,0,0,'Flirt - Laugh'),
(31689,0,5,0,22,0,100,0,58,5000,5000,0,5,23,0,0,0,0,0,1,0,0,0,0,0,0,0,'Kiss - Flex'),
(31689,0,6,0,22,0,100,0,77,5000,5000,0,5,14,0,0,0,0,0,1,0,0,0,0,0,0,0,'Rude - Rude');

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (15872,15873,15874,15879,15880,15882);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (15872,15873,15874,15879,15880,15882);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (15872,15873,15874,15879,15880,15882);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(15879,0,0,0,1,0,100,1,0,0,0,0,33,15893,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15879,0,1,0,1,0,100,1,0,0,0,0,11,26344,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15880,0,0,0,1,0,100,1,0,0,0,0,33,15893,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15880,0,1,0,1,0,100,1,0,0,0,0,11,26345,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15882,0,0,0,1,0,100,1,0,0,0,0,33,15893,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15882,0,1,0,1,0,100,1,0,0,0,0,11,26347,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15872,0,0,0,1,0,100,1,0,0,0,0,33,15894,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15872,0,1,0,1,0,100,1,0,0,0,0,11,26344,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15873,0,0,0,1,0,100,1,0,0,0,0,33,15894,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15873,0,1,0,1,0,100,1,0,0,0,0,11,26347,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15874,0,0,0,1,0,100,1,0,0,0,0,33,15894,0,0,0,0,0,18,20,0,0,0,0,0,0, 'give credit'),
(15874,0,1,0,1,0,100,1,0,0,0,0,11,26345,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks');

UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry` IN (192708,192706,192871,192905,192710,192886,192869,192880,192713,192889,192890,192866,192891,192872,192881,192709,192883,192651,192711,192653,192887,192865,192874,192868,192867,192882,192707);
DELETE FROM `smart_scripts` WHERE `source_type`=1 AND `id`=0 AND `entryorguid` IN (192708,192706,192871,192905,192710,192886,192869,192880,192713,192889,192890,192866,192891,192872,192881,192709,192883,192651,192711,192653,192887,192865,192874,192868,192867,192882,192707);
INSERT INTO `smart_scripts`(`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(192708,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192706,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192871,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192905,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192710,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192886,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192869,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192880,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192713,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192889,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192890,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192866,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192891,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192872,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192881,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192709,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192883,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192651,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192711,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192653,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192887,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192865,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192874,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192868,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192867,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192882,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello'),
(192707,1,0,0,64,0,100,0,0,0,0,0,41,180000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dalaran Books: Despawn after 3 mins on gossip_hello');
SET @ENTRY := 23859;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,0,0,0,4,0,100,0,0,0,0,0,80,@ENTRY*100,0,2,0,0,0,1,0,0,0,0,0,0,0, 'Greer Orehammer - Script on Aggro'),
(@ENTRY,0,1,0,62,0,100,0,9546,1,0,0,52,745,0,0,0,0,0,0,0,0,0,0,0,0,0, 'Plague This Taxi Start'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Say text 0'),
(@ENTRY*100,9,1,0,0,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,7,0,0,0,0,0,0,0,'Summon Enraged Gryphon'),
(@ENTRY*100,9,2,0,0,0,100,0,0,0,0,0,12,9526,4,30000,0,0,0,7,0,0,0,0,0,0,0,'Summon Enraged Gryphon');
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(@ENTRY,0,0,'Guards!',0,0,100,0,0,0,'Greer Orehammer');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30273;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30273;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30273,0,0,0,6,0,100,0,0,0,0,0,85,56515,0x02,0,0,0,0,7,0,0,0,0,0,0,0, 'Cast Summon Freed Crusader on Death'),
(30273,0,1,0,6,0,100,0,0,0,0,0,33,30274,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Cast Summon Freed Crusader Quest Credit');
DELETE FROM `spell_scripts` WHERE `id`=56515;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(56515,0,0,15,56516,2,0,0,0,0,0);
UPDATE `creature_template` SET `AIName`= 'SmartAI', `minlevel`=1, `maxlevel`=1 WHERE `entry`=30268;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30268;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30268,0,0,0,6,0,100,0,0,0,0,0,12,30204,1,30000,0,0,0,1,0,0,0,0,0,0,0, 'Summon Forgotten Depths Ambusher');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30274;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30274;
DELETE FROM `smart_scripts` WHERE `entryorguid`=3027400;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30274,0,0,0,54,0,100,0,0,0,0,0,80,3027400,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Freed Crusader Start Script on Spawn'),
(3027400,9,0,0,0,0,100,0,0,0,0,0,11,58054,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Freed Crusader Blessing of Kings'),
(3027400,9,1,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Freed Crusader Speach'),
(3027400,9,2,0,0,0,100,0,0,0,0,0,11,58053,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Freed Crusader Holy Light'),
(3027400,9,3,0,0,0,100,0,4000,4000,0,0,53,1,30274,0,13008,0,0,1,0,0,0,0,0,0,0, 'Freed Crusader paths to Argeant Vanguard'),
(3027400,9,4,0,0,0,100,0,0,0,0,0,41,4000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Freed Crusader Despawn');
DELETE FROM `waypoints` WHERE `entry`=30274;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES 
(30274,1,6296.25,92.9397,390.701, 'send Freed Crusader here');
DELETE FROM `creature_text` WHERE `entry`=30274;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(30274,0,0, 'Thank you and farewell, friend. I must return to the Argent Vanguard.',0,0,100,0,0,0, 'Freed Crusader Speach');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30204;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30204;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30204,0,0,0,54,0,100,0,0,0,0,0,11,56418,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Forgotten Depths Ambusher - Emerge From Snow');

SET @ENTRY := 36879;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,5000,5000,10000,10000,11,69581,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Pustulant Flesh on Random Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,5000,5000,10000,10000,11,70273,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Pustulant Flesh on Random Target (Heroic)'),
(@ENTRY,0,2,0,0,0,100,6,8000,8000,8000,8000,11,70274,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Toxic Waste on Random Target'),
(@ENTRY,0,3,0,2,0,100,6,15,15,0,0,11,69582,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Blight Bomb self at 15pct Health');
SET @ENTRY := 37711;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,4000,6000,8000,12000,11,70393,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Devour Flesh on current Target');
SET @ENTRY := 37712;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,100,100,3000,3000,11,70386,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,100,100,3000,3000,11,70387,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Heroic)');
SET @ENTRY := 37713;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,10000,10000,10000,10000,11,70392,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Black Brand on current Target'),
(@ENTRY,0,1,0,0,0,100,6,6000,6000,13000,13000,11,70391,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Curse of Agony on Random Target');
SET @ENTRY := 36840;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,7000,7000,8000,8000,11,69603,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Blight on Random Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,7000,7000,8000,8000,11,70285,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Blight on Random Target (Heroic)');
SET @ENTRY := 36896;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,1000,1000,5000,5000,11,69520,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Gargoyle Strike on current Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,1000,1000,5000,5000,11,70275,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Gargoyle Strike on current Target (Heroic)'),
(@ENTRY,0,2,0,2,0,100,6,10,10,0,0,11,69575,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Stoneform self at 10pct Health');
SET @ENTRY := 37728;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,3000,3000,8000,8000,11,75330,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,3000,3000,8000,8000,11,75331,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Heroic)');
SET @ENTRY := 36842;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,100,100,3000,3000,11,69573,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Frostbolt on current Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,100,100,3000,3000,11,70277,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Frostbolt on current Target (Heroic)'),
(@ENTRY,0,2,0,0,0,100,2,9000,9000,15000,15000,11,69574,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Freezing Circle on current Target (Non-Heroic)'),
(@ENTRY,0,3,0,0,0,100,4,9000,9000,15000,15000,11,70276,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Freezing Circle on current Target (Heroic)');
SET @ENTRY := 36788;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,100,100,3000,3000,11,69577,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,100,100,3000,3000,11,70270,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Shadow Bolt on current Target (Heroic)'),
(@ENTRY,0,2,0,0,0,100,2,9000,9000,24000,24000,11,69578,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Conversion Beam on Random Target (Non-Heroic)'),
(@ENTRY,0,3,0,0,0,100,4,9000,9000,24000,24000,11,70269,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Conversion Beam on Random Target (Heroic)');
SET @ENTRY := 36841;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,5000,5000,7000,8000,11,69579,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Arcing Slice to current Target'),
(@ENTRY,0,1,0,0,0,100,6,15000,15000,22000,22000,11,61044,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Demoralizing Shout'),
(@ENTRY,0,2,0,0,0,100,6,22000,22000,25000,25000,11,69580,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Shield Block');
SET @ENTRY := 38487;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,5000,5000,7000,8000,11,69579,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Arcing Slice to current Target'),
(@ENTRY,0,1,0,0,0,100,6,15000,15000,22000,22000,11,61044,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Demoralizing Shout'),
(@ENTRY,0,2,0,0,0,100,6,22000,22000,25000,25000,11,69580,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast Shield Block');
SET @ENTRY := 31260;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,4000,4000,8000,8000,11,70292,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Glacial Strike on current Target'),
(@ENTRY,0,1,0,2,0,100,6,50,50,0,0,11,70291,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Frostblade on Random Target at 50pct Health');
SET @ENTRY := 37670;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,6,1000,1000,0,0,11,70306,0,0,0,0,0,2,0,0,0,0,0,0,0, 'Cast Frostblade self');
SET @ENTRY := 36892;
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`="" WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,2,4000,4000,8000,8000,11,69528,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Empowered Shadow Bolt on Random Target (Non-Heroic)'),
(@ENTRY,0,1,0,0,0,100,4,4000,4000,8000,8000,11,70281,0,0,0,0,0,5,0,0,0,0,0,0,0, 'Cast Empowered Shadow Bolt on Random Target (Heroic)');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25281;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25281);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(25281,0,0,0,1,0,100,0,6000,6000,6000,6000,11,45425,2,0,0,0,0,10,103993,24921,0,0,0,0,0,'Fire at target every 6 sec');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25282;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25282);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(25282,0,0,0,1,0,100,0,6000,6000,6000,6000,11,42611,2,0,0,0,0,10,103994,24921,0,0,0,0,0,'Fire at target every 6 sec');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=28801;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-107662);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-107662,0,0,0,1,0,100,0,12000,18000,12000,18000,11,54423,2,0,0,0,0,10,117888,29416,0,0,0,0,0,'Fire at target every 12-18 sec');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=16896;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-58449);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-58449,0,0,0,1,0,100,0,6000,6000,6000,6000,11,29120,2,0,0,0,0,10,58457,16898,0,0,0,0,0,'Fire at target every 6 sec');
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-58450);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-58450,0,0,0,1,0,100,0,4000,4000,6000,6000,11,29120,2,0,0,0,0,10,58461,16899,0,0,0,0,0,'Fire at target every 6 sec');
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-58451);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-58451,0,0,0,1,0,100,0,2000,2000,6000,6000,11,29120,2,0,0,0,0,10,58455,16897,0,0,0,0,0,'Fire at target every 6 sec');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30377;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (30377,3037700);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30377,0,0,0,1,0,100,0,30000,60000,240000,240000,80,3037700,0,0,0,0,0,0,0,0,0,0,0,0,0,'Load script every 4 min ooc'),
(3037700,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,9,28179,0,10,0,0,0,0,'Highlord Tirion Fordring Say text 0'),
(3037700,9,1,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 0'),
(3037700,9,2,0,0,0,100,0,12000,12000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 1'),
(3037700,9,3,0,0,0,100,0,12000,12000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 2'),
(3037700,9,4,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,9,28179,0,10,0,0,0,0,'Highlord Tirion Fordring Say text 1'),
(3037700,9,5,0,0,0,100,0,6000,6000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 3'),
(3037700,9,6,0,0,0,100,0,9000,9000,0,0,1,2,0,0,0,0,0,9,28179,0,10,0,0,0,0,'Highlord Tirion Fordring Say text 2'),
(3037700,9,7,0,0,0,100,0,9000,9000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 4'),
(3037700,9,8,0,0,0,100,0,3000,3000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 5'),
(3037700,9,9,0,0,0,100,0,9000,9000,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 6'),
(3037700,9,10,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 7'),
(3037700,9,11,0,0,0,100,0,11000,11000,0,0,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 8'),
(3037700,9,12,0,0,0,100,0,12000,12000,0,0,1,3,0,0,0,0,0,9,28179,0,10,0,0,0,0,'Highlord Tirion Fordring Say text 3'),
(3037700,9,13,0,0,0,100,0,13000,13000,0,0,1,9,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Ebon Watcher Say text 9');
DELETE FROM `creature_text` WHERE `entry` IN (28179,30377);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(28179,0,0,'The Lich King reacted swiftly to the breach. Faster than I anticipated.',0,0,100,1,0,0,'Highlord Tirion Fordring'),
(28179,1,0,'What would you have me do, Darion?',0,0,100,6,0,0,'Highlord Tirion Fordring'),
(28179,2,0,'Choose your words wisely, death knight. You stand amidst the company of the devoted.',0,0,100,1,0,0,'Highlord Tirion Fordring'),
(28179,3,0,'We will do this with honor, Darion. We will not sink to the levels of the Scourge to be victorious. To do so would make us no better than the monster that we fight to destroy!',0,0,100,1,0,0,'Highlord Tirion Fordring'),
(30377,0,0,'You are dealing with a being that holds within it the consciousness of the most cunning, intelligent, and ruthless individuals to ever live.',0,0,100,1,0,0,'The Ebon Watcher'),
(30377,1,0,'The Lich King is unlike any foe that you have ever faced, Highlord. Though you bested him upon the holy ground of Light\'s Hope Chapel, you tread now upon his domain.',0,0,100,1,0,0,'The Ebon Watcher'),
(30377,2,0,'You cannot win. Not like this...',0,0,100,274,0,0,'The Ebon Watcher'),
(30377,3,0,'Nothing. There is nothing that you can do while the Light binds you. It controls you wholly, shackling you to the ground with its virtues.',0,0,100,274,0,0,'The Ebon Watcher'),
(30377,4,0,'%s shakes his head.','2',0,100,0,0,0,'The Ebon Watcher'),
(30377,5,0,'Look upon the field, Highlord. The Lich King has halted your advance completely and won the upper hand!',0,0,100,25,0,0,'The Ebon Watcher'),
(30377,6,0,'The breach you created was sealed with Nerubian webbing almost as quickly as it was opened.',0,0,100,1,0,0,'The Ebon Watcher'),
(30377,7,0,'Your soldiers are being used as living shields to stave off artillery fire in the Valley of Echoes, allowing the forces of the Lich King to assault your base without impediment.',0,0,100,1,0,0,'The Ebon Watcher'),
(30377,8,0,'The Lich King knows your boundaries, Highlord. He knows that you will not fire on your own men. Do you not understand? He has no boundaries. No rules to abide.',0,0,100,1,0,0,'The Ebon Watcher'),
(30377,9,0,'Then you have lost, Highlord.',0,0,100,1,0,0,'The Ebon Watcher');
SET @Diver=31689; -- Gnome Diver
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Diver; -- Gnome Diver
REPLACE INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(28951,0,0,257,0, '60913 0 61354 0'), -- Breanni
(@Diver,0,33554432,1,0, '59562 0'); -- Gnome Diver
DELETE FROM `smart_scripts` WHERE `entryorguid`=@Diver AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`)VALUES
(@Diver,0,0,0,22,0,100,0,78,5000,5000,0,5,66,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Salute - Salute'),
(@Diver,0,1,0,22,0,100,0,21,5000,5000,0,5,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Cheer - Bow'),
(@Diver,0,2,0,22,0,100,0,101,5000,5000,0,5,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Wave - Wave'),
(@Diver,0,3,0,22,0,100,0,34,5000,5000,0,5,94,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Dance - Dance'),
(@Diver,0,4,0,22,0,100,0,328,5000,5000,0,5,11,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Flirt - Laugh'),
(@Diver,0,5,0,22,0,100,0,58,5000,5000,0,5,23,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Kiss - Flex'),
(@Diver,0,6,0,22,0,100,0,77,5000,5000,0,5,14,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Gnome Diver: Rude - Rude');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (15872,15873,15874,15879,15880,15882);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (15872,15873,15874,15879,15880,15882);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(15879,0,0,0,1,0,100,1,0,0,0,0,11,26344,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15880,0,0,0,1,0,100,1,0,0,0,0,11,26345,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15882,0,0,0,1,0,100,1,0,0,0,0,11,26347,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15872,0,0,0,1,0,100,1,0,0,0,0,11,26344,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15873,0,0,0,1,0,100,1,0,0,0,0,11,26347,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks'),
(15874,0,0,0,1,0,100,1,0,0,0,0,11,26345,2,0,0,0,0,1,0,0,0,0,0,0,0, 'cast fireworks');

SET @ENTRY := 24752; -- Rock Falcon SAI
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,9007,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'On gossip option Close Gossip'), -- Player needs to cast this on self "not working"
(@ENTRY,0,1,0,61,0,100,0,100,100,100,100,86,44363,0,7,0,0,0,7,0,0,0,0,0,0,0,'Player selfcast spell');
SET @ENTRY := 33303; -- NPC entry
SET @ERROR1 := 1334; -- Error Message 1
SET @ERROR2 := 1335; -- Error Message 2
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,75,45776,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Apply aura on spawn'),
(@ENTRY,0,1,0,8,0,100,0,62767,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On spell hit run script'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,28,45776,0,0,0,0,0,1,0,0,0,0,0,0,0,'Remove aura'),
(@ENTRY*100,9,1,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Face Player'),
(@ENTRY*100,9,2,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Say text 0'),
(@ENTRY*100,9,3,0,0,0,100,0,6000,6000,6000,6000,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Say text 1'),
(@ENTRY*100,9,4,0,0,0,100,0,5000,5000,5000,5000,66,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Reset Orientation'),
(@ENTRY*100,9,5,0,0,0,100,0,0,0,0,0,75,45776,0,0,0,0,0,1,0,0,0,0,0,0,0,'Replace Aura');
DELETE FROM `creature_text` WHERE `entry`=33303;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33303,0,0, 'Thank you, mortal, for freeing me from this curse. I beg you, take this blade.',0,0,100,1,0,0, 'Maiden of Winter''s Breath Lake'),
(33303,1,0, 'It has brought me naught but ill. Mayhap you can find someone who will contain its power.',0,0,100,1,0,0, 'Maiden of Winter''s Breath Lake');


DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=62767;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`COMMENT`) VALUES
(17,62767,19,33303,0,0,@ERROR1, 'Break Curse of Ice Required Target Maiden of Winter''s Breath Lake'),
(17,62767,1,45776,0,1,@ERROR2, 'Break Curse of Ice Required Target Needs Aura Ice Block');
DELETE FROM `trinity_string` WHERE `entry` IN (@ERROR1,@ERROR2);
INSERT INTO `trinity_string` (`entry`,`content_default`) VALUES
(@ERROR1, 'Requires Maiden of Winter''s Breath Lake'),
(@ERROR2, 'You can''t use that right now');
SET @ENTRY := 30224;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
UPDATE `smart_scripts` SET `target_type`=1, `comment`=  'The Ebon Watcher: Load script every 4 min ooc' WHERE `entryorguid`=30377 AND `source_type` =0 AND `id`=0;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,30000,60000,150000,150000,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Load script every 2.5 min ooc'),
(@ENTRY*100,9,0,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crusader Lord Dalfors text 0'),
(@ENTRY*100,9,1,0,0,0,100,0,6000,6000,0,0,1,0,0,0,0,0,0,9,30225,0,10,0,0,0,0,'Crusader Sunborn Say text 0'),
(@ENTRY*100,9,2,0,0,0,100,0,4000,4000,0,0,5,14,0,0,0,0,0,9,30225,0,10,0,0,0,0,'Crusader Sunborn emote');
DELETE FROM `creature_text` WHERE `entry` IN (30224,30225);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(30224,0,0, 'What''s on yer mind, lad?',0,0,100,6,0,0, 'Crusader Lord Dalfors'),
(30225,0,0, 'Eversong Woods, Dalfors. I''m thinking about how beautiful it was before Arthas cut a swathe of death through it...',0,0,100,1,0,0, 'Crusader Sunborn');
INSERT IGNORE INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(19,0,8871,0,4,1519,0,0,0,0,'The Lunar Festival: Stormwind'),
(19,0,8872,0,4,1657,0,0,0,0,'The Lunar Festival: Darnassus'),
(19,0,8870,0,4,1537,0,0,0,0,'The Lunar Festival: Ironforge'),
(19,0,8873,0,4,1637,0,0,0,0,'The Lunar Festival: Orgrimmar'),
(19,0,8874,0,4,1497,0,0,0,0,'The Lunar Festival: Undercity'),
(19,0,8875,0,4,1638,0,0,0,0,'The Lunar Festival: Thunder Bluff');
SET @Goodman := 27234; -- Blacksmith Goodman
SET @Zierhut := 27235; -- Lead Cannoneer Zierhut (npc)
SET @Mercer := 27236; -- Stable Master Mercer (npc)
SET @Jordan := 27237; -- Commander Jordan (npc)
SET @Rod := 37438; -- Rod of Compulsion (item)
SET @Compelled := 48714; -- Compelled (spell)
SET @DeathJordan := 48724; -- The Denouncement: Commander Jordan On Death
SET @DeathZierhut := 48726; -- The Denouncement: Lead Cannoneer Zierhut On Death
SET @DeathGoodman := 48728; -- The Denouncement: Blacksmith Goodman On Death
SET @DeathMercer := 48730; -- The Denouncement: Stable Master Mercer On Death
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry` IN (@Goodman,@Zierhut,@Mercer,@Jordan);
DELETE FROM `spell_scripts` WHERE `id` IN (@DeathJordan,@DeathZierhut,@DeathGoodman,@DeathMercer);
INSERT INTO `spell_scripts`(`id`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(@DeathJordan,0,15,48723,1,0,0,0,0,0),  -- cast "The Denouncement: Commander Jordan Kill Credit" on player
(@DeathZierhut,0,15,48725,1,0,0,0,0,0), -- cast "The Denouncement: Lead Cannoneer Zierhut Kill Credit" on player
(@DeathGoodman,0,15,48727,1,0,0,0,0,0), -- cast "The Denouncement: Blacksmith Goodman Kill Credit" on player
(@DeathMercer,0,15,48729,1,0,0,0,0,0);  -- cast "The Denouncement: Stable Master Mercer Kill Credit" on player
DELETE FROM `creature_text` WHERE `entry` IN (@Goodman,@Zierhut,@Mercer,@Jordan);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@Goodman,0,0, 'You are being misled! The Onslaught is all lies! The Scourge and the Forsaken are not our enemies! Wake up!',1,0,100,5,0,0, 'Blacksmith Goodman'),
(@Jordan,0,0, 'High general Abbendis personally told me that it was a mistake to come north and that we''re doomed! I urge you all to lay down your weapons and leave before it''s too late!',1,0,100,5,0,0, 'Commander Jordan'),
(@Zierhut,0,0, 'Renounce the Scarlet Onslaught! Don''t listen to the lies of the high general and the grand admiral any longer!',1,0,100,5,0,0, 'Lead Cannoneer Zierhut'),
(@Mercer,0,0, 'Abbendis is nothing but a harlot and Grand Admiral Westwind is selling her cheap like he sold us out!',1,0,100,5,0,0, 'Stable Master Mercer');
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@Goodman,@Zierhut,@Mercer,@Jordan);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@Goodman,0,0,0,8,0,100,0,@Compelled,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On spellhit set phase 2'),
(@Goodman,0,1,0,6,2,100,0,0,0,0,0,85,@DeathGoodman,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On death in phase 2 cast spell'),
(@Goodman,0,2,0,25,0,100,0,0,0,0,0,28,@Compelled,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On reset remove Compelled aura'),
(@Goodman,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On reset set phase 0'),
(@Goodman,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On death in phase 2 yell'),
(@Mercer,0,0,0,8,0,100,0,@Compelled,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Mercer: On spellhit set phase 2'),
(@Mercer,0,1,0,6,2,100,0,0,0,0,0,85,@DeathMercer,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Mercer: On death in phase 2 cast spell'),
(@Mercer,0,2,0,25,0,100,0,0,0,0,0,28,@Compelled,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Mercer: On reset remove Compelled aura'),
(@Mercer,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Mercer: On reset set phase 0'),
(@Mercer,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Mercer: On death in phase 2 yell'),
(@Zierhut,0,0,0,8,0,100,0,@Compelled,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Goodman: On spellhit set phase 2'),
(@Zierhut,0,1,0,6,2,100,0,0,0,0,0,85,@DeathZierhut,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Zierhut: On death in phase 2 cast spell'),
(@Zierhut,0,2,0,25,0,100,0,0,0,0,0,28,@Compelled,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Zierhut: On reset remove Compelled aura'),
(@Zierhut,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Zierhut: On reset set phase 0'),
(@Zierhut,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Zierhut: On death in phase 2 yell'),
(@Jordan,0,0,0,8,0,100,0,@Compelled,0,0,0,22,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Jordan: On spellhit set phase 2'),
(@Jordan,0,1,0,6,2,100,0,0,0,0,0,85,@DeathJordan,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Jordan: On death in phase 2 cast spell'),
(@Jordan,0,2,0,25,0,100,0,0,0,0,0,28,@Compelled,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Jordan: On reset remove Compelled aura'),
(@Jordan,0,3,0,25,0,100,0,0,0,0,0,22,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Jordan: On reset set phase 0'),
(@Jordan,0,4,0,6,2,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Denouncement/Jordan: On death in phase 2 yell');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25253;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-111383,-111377,-111378,-111382,-111379,-111380);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-111383,0,0,0,1,0,100,0,1000,2000,4000,5000,5,36,0,0,0,0,0,1,0,0,0,0,0,0,0,'Attack emote every 4-5 sec'),
(-111377,0,0,0,1,0,100,0,3000,4000,4000,5000,5,36,0,0,0,0,0,1,0,0,0,0,0,0,0,'Attack emote every 4-5 sec'),
(-111378,0,0,0,1,0,100,0,8000,8000,16000,16000,10,4,5,21,0,0,0,1,0,0,0,0,0,0,0,'Random cheer emote every 16 sec'),
(-111382,0,0,0,1,0,100,0,16000,16000,16000,16000,10,4,5,21,0,0,0,1,0,0,0,0,0,0,0,'Random cheer emote every 16 sec'),
(-111379,0,0,0,1,0,100,0,2000,2000,5000,5000,5,36,0,0,0,0,0,1,0,0,0,0,0,0,0,'Attack emote every 5 sec'),
(-111379,0,1,0,1,0,100,0,4000,4000,7000,7000,5,36,0,0,0,0,0,10,111376,25253,0,0,0,0,0,'Attack emote dueler 2 sec later sec'),
(-111380,0,0,0,1,0,100,0,5000,5000,5000,5000,5,36,0,0,0,0,0,1,0,0,0,0,0,0,0,'Attack emote every 5 sec'),
(-111380,0,1,0,1,0,100,0,7000,7000,7000,7000,5,36,0,0,0,0,0,10,111381,25253,0,0,0,0,0,'Attack emote dueler 2 sec later sec');
INSERT IGNORE INTO `conditions`(`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`Comment`) VALUES
(13,0,@DeathJordan,0,18,1,@Jordan,0,0, 'The Denouncement: Jordan target'),
(13,0,@DeathZierhut,0,18,1,@Zierhut,0,0, 'The Denouncement: Zierhut target'),
(13,0,@DeathGoodman,0,18,1,0,0,0, 'The Denouncement: Goodman target'),
(13,0,@DeathMercer,0,18,1,@Mercer,0,0, 'The Denouncement: Mercer'),
(18,0,@Rod,0,24,1,@Goodman,0,0, 'The Denouncement: Rod - Goodman target'),
(18,0,@Rod,0,24,1,@Zierhut,0,0, 'The Denouncement: Rod - Zierhut target'),
(18,0,@Rod,0,24,1,@Mercer,0,0, 'The Denouncement: Rod - Mercer target'),
(18,0,@Rod,0,24,1,@Jordan,0,0, 'The Denouncement: Rod - Jordan target');
DELETE FROM `creature_text` WHERE `entry`=36853;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(36853,0,0, 'You are fools to have come to this place! The icy winds of Northrend will consume your souls!',1,0,0,0,0,17007, 'Sindragosa - SAY_AGGRO'),
(36853,1,0, 'Suffer, mortals, as your pathetic magic betrays you!',1,0,0,0,0,17014, 'Sindragosa - SAY_UNCHAINED_MAGIC'),
(36853,2,0, '%s prepares to unleash a wave of blistering cold!',3,0,0,0,0,0, 'Sindragosa - EMOTE_WARN_BLISTERING_COLD'),
(36853,3,0, 'Can you feel the cold hand of death upon your heart?',1,0,0,0,0,17013, 'Sindragosa - SAY_BLISTERING_COLD'),
(36853,4,0, 'Aaah! It burns! What sorcery is this?!',1,0,0,0,0,17015, 'Sindragosa - SAY_RESPITE_FOR_A_TORMENTED_SOUL'),
(36853,5,0, 'Your incursion ends here! None shall survive!',1,0,0,0,0,17012, 'Sindragosa - SAY_AIR_PHASE'),
(36853,6,0, 'Now feel my master''s limitless power and despair!',1,0,0,0,0,17016, 'Sindragosa - SAY_PHASE_2'),
(36853,7,0, '%s fires a frozen orb towards $N!',3,0,0,0,0,0, 'Sindragosa - EMOTE_WARN_FROZEN_ORB'),
(36853,8,0, 'Perish!',1,0,0,0,0,17008, 'Sindragosa - SAY_KILL 1'),
(36853,8,1, 'A flaw of mortality...',1,0,0,0,0,17009, 'Sindragosa - SAY_KILL 2'),
(36853,9,0, 'Enough! I tire of these games!',1,0,0,0,0,17011, 'Sindragosa - SAY_BERSERK'),
(36853,10,0, 'Free...at last...',1,0,0,0,0,17010, 'Sindragosa - SAY_DEATH');
SET @ENTRY:=20561;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'On spawn set phase 1'),
(@ENTRY,0,1,0,8,1,100,0,35372,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On spell hit run script'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 'set phase 0'),
(@ENTRY*100,9,1,0,0,0,100,0,1000,1000,0,0,33,20561,0,0,0,0,0,7,0,0,0,0,0,0,0,'give quest credit'),
(@ENTRY*100,9,2,0,0,0,100,0,1000,1000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'despawn');
SET @ENTRY:=25321;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'On spawn set phase 1'),
(@ENTRY,0,1,0,8,1,100,0,45504,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On spell hit run script'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 'set phase 0'),
(@ENTRY*100,9,1,0,0,0,100,0,1000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say Text 0 random'),
(@ENTRY*100,9,2,0,0,0,100,0,1000,1000,0,0,33,25321,0,0,0,0,0,7,0,0,0,0,0,0,0,'give quest credit'),
(@ENTRY*100,9,3,0,0,0,100,0,1000,1000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'despawn');
DELETE FROM `creature_text` WHERE `entry`=25321;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(25321,0,0, 'Thank you for freeing me! May the tides always favor you.',0,0,100,1,0,0, 'Kaskala Craftman'),
(25321,0,1, 'Do not allow Kaskala to forget what has happened here.',0,0,100,1,0,0, 'Kaskala Craftman');
SET @ENTRY:=25322;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0, 'On spawn set phase 1'),
(@ENTRY,0,1,0,8,1,100,0,45504,0,0,0,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On spell hit run script'),
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 'set phase 0'),
(@ENTRY*100,9,1,0,0,0,100,0,1000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say Text 0 random'),
(@ENTRY*100,9,2,0,0,0,100,0,1000,1000,0,0,33,25322,0,0,0,0,0,7,0,0,0,0,0,0,0, 'give quest credit'),
(@ENTRY*100,9,3,0,0,0,100,0,1000,1000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'despawn');
DELETE FROM `creature_text` WHERE `entry`=25322;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES 
(25322,0,0, 'May the ancestors always aid you, $n, as you have aided me.',0,0,100,1,0,0, 'Kaskala Shaman'),
(25322,0,1, 'Thank you, $n. May the winds and seas always deliver you safely.',0,0,100,1,0,0, 'Kaskala Shaman');

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=32739; -- Baroness Zildjia
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=32736; -- Scribe Whitman
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=32741; -- Conjurer Weinhaus
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=32734; -- Arcanist Ginsberg
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=32735; -- Alchemist Burroughs
-- Talk events for Baroness Zildjia, Scribe Whitman and Conjurer Weinhaus
DELETE FROM `creature_text` WHERE `entry` IN (32739,32736,32741) AND `groupid`=0;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(32739,0,0, 'The view up here is amazing!',0,0,0,5,0,0, 'Baroness Zildjia'), -- Baroness Zildjia
(32739,0,1, 'Too bad I left my light feathers at home... Slow Fall would work perfect here!',0,0,0,1,0,0, 'Baroness Zildjia'), -- Baroness Zildjia
(32736,0,0, 'The view up here is amazing!',0,0,0,5,0,0, 'Scribe Whitman'), -- Scribe Whitman
(32736,0,1, 'Too bad I left my light feathers at home... Slow Fall would work perfect here!',0,0,0,1,0,0, 'Scribe Whitman'), -- Scribe Whitman
(32741,0,0, 'The view up here is amazing!',0,0,0,5,0,0, 'Conjurer Weinhaus'), -- Conjurer Weinhaus
(32741,0,1, 'Too bad I left my light feathers at home... Slow Fall would work perfect here!',0,0,0,1,0,0, 'Conjurer Weinhaus'); -- Conjurer Weinhaus
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (32739,32736,32741,32734,32735) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(32739,0,0,0,1,0,100,0,0,0,420000,1000000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Baroness Zildjia: Say rand text every 7-14 minutes'), -- Baroness Zildjia
(32736,0,0,0,1,0,100,0,0,0,300000,840000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Scribe Whitman: Say rand text every 5-14 minutes'), -- Scribe Whitman
(32741,0,0,0,1,0,100,0,0,0,400000,520000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Conjurer Weinhaus: Say rand text every 5-7 minutes'), -- Conjurer Weinhaus
(32734,0,0,0,1,0,100,0,0,0,5000,30000,10,274,1,11,0,0,0,1,0,0,0,0,0,0,0, 'Arcanist Ginsberg: Random emote every 5-30 seconds'), -- Arcanist Ginsberg
(32735,0,0,0,1,0,100,0,0,0,5000,30000,10,274,1,11,0,0,0,1,0,0,0,0,0,0,0, 'Alchemist Burroughs: Random emote every 5-30 seconds'); -- Alchemist Burroughs
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry` IN (25664,25665,25666);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25664,25665,25666);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(25664,0,0,0,8,0,100,0,45853,1,0,0,33,25664,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Mark Sinkhole Killcredit: South'),
(25665,0,0,0,8,0,100,0,45853,1,0,0,33,25665,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Mark Sinkhole Killcredit: NorthEast'),
(25666,0,0,0,8,0,100,0,45853,1,0,0,33,25666,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Mark Sinkhole Killcredit: NorthWest');

UPDATE `creature_template` SET `AIName`='AggressorAI' WHERE `entry`=27131;
DELETE FROM `conditions` WHERE `SourceEntry` =60089;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(17,0,60089,0,1,5487,0,0,0, '', 'Faerie Fire - Bear Form'),
(17,0,60089,1,1,9634,0,0,0, '', 'Faerie Fire - Dire Bear Form');
INSERT IGNORE INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,0,71322,0,18,1,38558,0,0, '', 'Blood-Queen Lana''thel - Annihilate Minchar');

UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry` IN (18714,18717,18716,18719,18715);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (18714,18717,18716,18719,18715);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(18714,0,0,0,19,0,100,0,10041,0,0,0,11,48917,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Neftis - On Quest Accept - Cast spell 48917 on player'),
(18714,0,1,0,20,0,100,0,10041,0,0,0,28,32756,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Neftis - On Quest Reward - Remove spell 32756 on player'),
(18714,0,2,0,62,0,100,0,7772,0,0,0,11,48917,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Neftis - On Gossip option - Cast spell 48917 on player'),
(18715,0,0,0,19,0,100,0,10040,0,0,0,11,48917,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Private Weeks - On Quest Accept - Cast spell 48917 on player'),
(18715,0,1,0,20,0,100,0,10040,0,0,0,28,32756,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Private Weeks - On Quest Reward - Remove spell 32756 on player'),
(18715,0,2,0,62,0,100,0,21253,0,0,0,11,48917,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Private Week - On Gossip option - Cast spell 48917 on player'),
(18717,0,0,0,62,0,100,0,7757,0,0,0,11,47069,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Who Are They - Shadowy Laborer - On Gossip option - Cast spell 47069 on player'),
(18716,0,0,0,62,0,100,0,7759,0,0,0,11,47068,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Who Are They - Shadowy Initiate - On Gossip option - Cast spell 47068 on player'),
(18719,0,0,0,62,0,100,0,7760,0,0,0,11,47070,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Who Are They - Shadowy Advisor - On Gossip option - Cast spell 47070 on player');
DELETE FROM `creature_text` WHERE `entry` IN (37119,37181,37183);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37119,0,0, 'This is our final stand. What happens here will echo through the ages. Regardless of outcome, they will know that we fought with honor. That we fought for the freedom and safety of our people!',1,0,0,22,0,16653, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_1'),
(37119,1,0, 'Remember, heroes, fear is your greatest enemy in these befouled halls. Steel your heart and your soul will shine brighter than a thousand suns. The enemy will falter at the sight of you. They will fall as the light of righteousness envelops them!',1,0,0,22,0,16654, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_2'),
(37119,2,0, 'Our march upon Icecrown Citadel begins now!',1,0,0,22,0,16655, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_3'),
(37119,3,0, 'ARTHAS! I swore that I would see you dead and the Scourge dismantled! I''m going to finish what I started at Light''s Hope!',1,0,0,22,0,16656, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_4'),
(37181,0,0, 'You now stand upon the hallowed ground of the Scourge. The Light won''t protect you here, paladin. Nothing will protect you...',1,0,0,0,0,17230, 'The Lich King - SAY_LK_INTRO_1'),
(37181,1,0, 'You could have been my greatest champion, Fordring: A force of darkness that would wash over this world and deliver it into a new age of strife.',1,0,0,0,0,17231, 'The Lich King - SAY_LK_INTRO_2'),
(37181,2,0, 'But that honor is no longer yours. Soon,I will have a new champion.',1,0,0,0,0,17232, 'The Lich King - SAY_LK_INTRO_3'),
(37181,3,0, 'The breaking of this one has been taxing. The atrocities I have committed upon his soul. He has resisted for so long, but he will bow down before his king soon.',1,0,0,0,0,17233, 'The Lich King - SAY_LK_INTRO_4'),
(37181,4,0, 'In the end, you will all serve me.',1,0,0,0,0,17234, 'The Lich King - SAY_LK_INTRO_5'),
(37183,0,0, 'NEVER! I... I will never... serve... you...',1,0,0,0,0,17078, 'Highlord Bolvar Fordragon - SAY_BOLVAR_INTRO_1');
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=37011; -- The Damned
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (-200966,-201066,37011);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(37011,0,0,0,6,0,100,1,0,0,0,0,11,70961,3,0,0,0,0,1,0,0,0,0,0,0,0, 'The Damned - Cast Shattered Bones on death'),
(37011,0,1,0,2,0,100,0,5,30,15000,20000,75,70960,0,0,0,0,0,1,0,0,0,0,0,0,0, 'The Damned - Cast Bone Flurry at 5-30%');
DELETE FROM `creature_text` WHERE `entry`=37187 AND `groupid` BETWEEN 15 AND 18;
DELETE FROM `creature_text` WHERE `entry`=37200 AND `groupid` BETWEEN 13 AND 15;
DELETE FROM `creature_text` WHERE `entry`=37119 AND `groupid` IN (4,5);
DELETE FROM `creature_text` WHERE `entry`=37181 AND `groupid`=2;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(37187,15,0, 'The paladin still lives? Is it possible, Highlord? Could he have survived?',0,0,0,6,0,17107, 'High Overlord Saurfang - SAY_SAURFANG_INTRO_1'),
(37187,16,0, 'Then we must save him! If we rescue Bolvar Fordragon, we may quell the unrest between the Alliance and the Horde.',0,0,0,5,0,17108, 'High Overlord Saurfang - SAY_SAURFANG_INTRO_2'),
(37187,17,0, 'Our mission is now clear: The Lich King will answer for his crimes and we will save Highlord Bolvar Fordragon!',0,0,0,15,0,17109, 'High Overlord Saurfang - SAY_SAURFANG_INTRO_3'),
(37187,18,0, 'Kor''kron, prepare Orgrim''s Hammer for its final voyage! Champions, our gunship will find a point to dock on the upper reaches of the citadel. Meet us there!',1,0,0,22,0,17110, 'High Overlord Saurfang - SAY_SAURFANG_INTRO_4'),
(37119,4,0, 'The power of the Light knows no bounds, Saurfang. His soul is under great strain, but he lives - for now.',0,0,0,1,0,16658, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_5'),
(37181,2,0, 'But that honor is no longer yours. Soon, I will have a new champion.',1,0,0,0,0,17232, 'The Lich King - SAY_LK_INTRO_3'),
(37200,13,0, 'Could it be, Lord Fordring? If Bolvar lives, mayhap there is hope fer peace between the Alliance and the Horde. We must reach the top o'' this cursed place and free the paladin!',0,0,0,6,0,16980, 'Muradin Bronzebeard - SAY_SAURFANG_INTRO_2'),
(37200,14,0, 'Prepare the Skybreaker fer an aerial assault on the citadel!',1,0,0,5,0,16981, 'Muradin Bronzebeard - SAY_SAURFANG_INTRO_3'),
(37200,15,0, 'Heroes, ye must fight yer way to a clear extraction point within Icecrown. We''ll try an'' rendezvous on the ramparts!',1,0,0,22,0,16982, 'Muradin Bronzebeard - SAY_SAURFANG_INTRO_4'),
(37119,5,0, 'By the Light, it must be so!',0,0,0,5,0,16657, 'Highlord Tirion Fordring - SAY_TIRION_INTRO_A_5');
UPDATE `creature_template` SET `AIName`='SmartAI',`InhabitType`=7,`flags_extra`=`flags_extra`|128 WHERE `entry`=38557;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=38558;
INSERT IGNORE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-93946,0,0,0,25,0,100,0,0,0,0,0,11,72302,3,0,0,0,0,10,@GUID,0,0,0,0,0,0, 'Minchar Beam Stalker - Channel beam'),
(-93947,0,0,0,25,0,100,0,0,0,0,0,11,72301,3,0,0,0,0,10,@GUID,0,0,0,0,0,0, 'Minchar Beam Stalker - Channel beam'),
(-93948,0,0,0,25,0,100,0,0,0,0,0,11,72304,3,0,0,0,0,10,@GUID,0,0,0,0,0,0, 'Minchar Beam Stalker - Channel beam'),
(-93949,0,0,0,25,0,100,0,0,0,0,0,11,72303,3,0,0,0,0,10,@GUID,0,0,0,0,0,0, 'Minchar Beam Stalker - Channel beam');

