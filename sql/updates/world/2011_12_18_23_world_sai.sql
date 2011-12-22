UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry` IN (17116,17240,17440);
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (17116,17240,17440);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(17116,0,0,0,64,0,100,0,0,0,0,0,33,17116,0,0,0,0,0,7,0,0,0,0,0,0,0, 'On gossip hello credit for quest 9663'),
(17240,0,0,0,64,0,100,0,0,0,0,0,33,17240,0,0,0,0,0,7,0,0,0,0,0,0,0, 'On gossip hello credit for quest 9663'),
(17440,0,0,0,64,0,100,0,0,0,0,0,33,17440,0,0,0,0,0,7,0,0,0,0,0,0,0, 'On gossip hello credit for quest 9663');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=27990;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (27990,2799000,2799001);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27990,0,0,0,62,0,100,0,10199,0,0,0,80,2799001,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On gossip option select run script'),
(27990,0,1,0,62,0,100,0,10199,1,0,0,80,2799000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On gossip option select run script'),
-- horde quest script
(2799000,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Turn off Gossip & Questgiver flags'),
(2799000,9,1,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn of Gossip & Questgiver flags for Alexstrasza'),
(2799000,9,2,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 0'),
(2799000,9,3,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 1'),
(2799000,9,4,0,0,0,100,0,0,0,0,0,45,0,1,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos start path'),
(2799000,9,5,0,0,0,100,0,4000,4000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 2'),
(2799000,9,6,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 3'),
(2799000,9,7,0,0,0,100,0,4000,4000,0,0,1,0,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 0'),
(2799000,9,8,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 1'),
(2799000,9,9,0,0,0,100,0,4000,4000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 4'),
(2799000,9,10,0,0,0,100,0,4000,4000,0,0,1,2,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 2'),
(2799000,9,11,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn Alexstrasza'),
(2799000,9,12,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Alexstrasza Say text 0'),
(2799000,9,13,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 3'),
(2799000,9,14,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos resume path'),
(2799000,9,15,0,0,0,100,0,0,0,0,0,45,0,2,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn Alexstrasza back'),
(2799000,9,16,0,0,0,100,0,1000,1000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 5'),
(2799000,9,17,0,0,0,100,0,4000,4000,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 6'),
(2799000,9,18,0,0,0,100,0,4000,4000,0,0,33,36715,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Give quest credit'),
(2799000,9,19,0,0,0,100,0,4000,4000,0,0,81,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Turn on Gossip & Questgiver flags'),
(2799000,9,20,0,0,0,100,0,0,0,0,0,81,3,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn on Gossip & Questgiver flags for Alexstrasza'),
-- alliance quest script
(2799001,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Turn off Gossip & Questgiver flags'),
(2799001,9,1,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn of Gossip & Questgiver flags for Alexstrasza'),
(2799001,9,2,0,0,0,100,0,2000,2000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 0'),
(2799001,9,3,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 1'),
(2799001,9,4,0,0,0,100,0,0,0,0,0,45,0,1,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos start path'),
(2799001,9,5,0,0,0,100,0,4000,4000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 2'),
(2799001,9,6,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 3'),
(2799001,9,7,0,0,0,100,0,4000,4000,0,0,1,0,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 0'),
(2799001,9,8,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 1'),
(2799001,9,9,0,0,0,100,0,4000,4000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 4'),
(2799001,9,10,0,0,0,100,0,4000,4000,0,0,1,2,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 2'),
(2799001,9,11,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn Alexstrasza'),
(2799001,9,12,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Alexstrasza Say text 0'),
(2799001,9,13,0,0,0,100,0,4000,4000,0,0,1,3,0,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos Say text 3'),
(2799001,9,14,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,9,38017,0,30,0,0,0,0, 'Kalecgos resume path'),
(2799001,9,15,0,0,0,100,0,0,0,0,0,45,0,2,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn Alexstrasza back'),
(2799001,9,16,0,0,0,100,0,1000,1000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 5'),
(2799001,9,17,0,0,0,100,0,4000,4000,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 7'),
(2799001,9,18,0,0,0,100,0,4000,4000,0,0,33,36715,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Give quest credit'),
(2799001,9,19,0,0,0,100,0,4000,4000,0,0,81,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Turn on Gossip & Questgiver flags'),
(2799001,9,20,0,0,0,100,0,0,0,0,0,81,3,0,0,0,0,0,9,26917,0,10,0,0,0,0, 'Turn on Gossip & Questgiver flags for Alexstrasza');
DELETE FROM `creature_text` WHERE `entry` IN (26917,27990,38017);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(26917,0,0,'Mortal champions have long used these weapons to combat evil. I see no reason to keep the swords from them in this battle.',0,0,100,1,0,0,'Alexstrasza the Life-Binder'),
(27990,0,0,'You''re too late, $n. Another visitor from Dalaran came asking after information about the same prismatic dragon blades.',0,0,100,1,0,0,'Krasus'),
(27990,1,0,'From your description, I''m certain the book I loaned our visitor could allow you to easily identify the weapon.',0,0,100,25,0,0,'Krasus'),
(27990,2,0,'I''m afraid you''ll have to ask the -- Well, perhaps Kalecgos can help.',0,0,100,1,0,0,'Krasus'),
(27990,3,0,'$n may have found the remains of a prismatic blade, Kalecgos. Will you offer your help to our visitor?',0,0,100,1,0,0,'Krasus'),
(27990,4,0,'You believe our allies will not be able to control the power of the swords?',0,0,100,1,0,0,'Krasus'),
(27990,5,0,'As will we all.',0,0,100,25,0,0,'Krasus'),
(27990,6,0,'Please, mortal, speak with Arcanist Tybalin in Dalaran. He may be able to negotiate with the Sunreavers for access to the book.',0,0,100,1,0,0,'Krasus'),
(27990,7,0,'Please, mortal, seek out Magister Hathorel in Dalaran. He might be able to negotiate with the Silver Covenant for access to the book.',0,0,100,1,0,0,'Krasus'),
(38017,0,0,'Are you certain you should be helping these mortals in their quest for the sword?',0,0,100,1,0,0,'Kalecgos'),
(38017,1,0,'These blades, Krasus... They were made long ago, when things were... different.',0,0,100,1,0,0,'Kalecgos'),
(38017,2,0,'Our enemies once turned our strongest weapon against us. What makes you think the prismatic blades will be any different?',0,0,100,1,0,0,'Kalecgos'),
(38017,3,0,'As you wish, my queen. I will not stand in their way, but I will keep a close watch.',0,0,100,16,0,0,'Kalecgos');
-- waypoints for Kalecgos
DELETE FROM `waypoints` WHERE `entry`=38017;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(38017,1,3541.156,276.041,342.721,'talk point'),
(38017,2,3545.989,287.278,342.721,'home point');
-- SAI for Kalecgos
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=38017;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=38017;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (3801700,3801701);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(38017,0,0,1,38,0,100,0,0,1,0,0,80,3801700,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On dataset 0 1 run script'),
(38017,0,1,1,38,0,100,0,0,2,0,0,80,3801701,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On dataset 0 2 run script'),
(38017,0,2,3,40,0,100,0,1,38017,0,0,54,30000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Pause at wp 1'),
(38017,0,3,0,61,0,100,0,0,0,0,0,66,0,0,0,0,0,0,9,27990,0,15,0,0,0,0, 'turn to Krasus'),
(38017,0,4,5,40,0,100,0,2,38017,0,0,55,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Stop at wp 2'),
(38017,0,5,0,61,0,100,0,0,0,0,0,66,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'turn to pos'),
(3801700,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'dataset 0 0'),
(3801700,9,1,0,0,0,100,0,0,0,0,0,53,0,38017,0,0,0,0,1,0,0,0,0,0,0,0, 'wp start'),
(3801701,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'dataset 0 0'),
(3801701,9,1,0,0,0,100,0,0,0,0,0,65,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'wp resume');
-- SAI for Alexstrasza
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=26917;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=26917;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(26917,0,0,1,38,0,100,0,0,1,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,1.6049, 'On dataset 0 1 turn'),
(26917,0,1,1,38,0,100,0,0,2,0,0,66,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'On dataset 0 2 turn');
-- Conversation between Sabetta Ward & Gavin Ward, Fort Wildervar "Sabetta Ward Envoker"
SET @ENTRY := 24532;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,10000,30000,150000,150000,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Load script every 2.5 min ooc'),
(@ENTRY*100,9,0,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sabetta Ward Say text 0'),
(@ENTRY*100,9,1,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,9,24531,0,10,0,0,0,0,'Gavin Ward Say text 0'),
(@ENTRY*100,9,2,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sabetta Ward Say text 1'),
(@ENTRY*100,9,3,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,9,24531,0,10,0,0,0,0,'Gavin Ward Say text 1'),
(@ENTRY*100,9,4,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Sabetta Ward Say text 2'),
(@ENTRY*100,9,5,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,9,24531,0,10,0,0,0,0,'Gavin Ward Say text 2');
-- NPC talk text insert from sniff
DELETE FROM `creature_text` WHERE `entry` IN (24531,24532);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(24532,0,0, 'And I don''t want our land to have any of those horrible wolves, or giants, or ugly rams!',0,7,100,1,0,0, 'Sabetta Ward'),
(24531,0,0, 'Yes, darling. You realize you''ll be eating dire ram mutton for dinner until the crops are planted...',0,7,100,1,0,0, 'Gavin Ward'),
(24532,1,0, 'I''d sooner butcher that mule of yours! Why did you bring that beast in here, anyway?',0,7,100,5,0,0, 'Sabetta Ward'),
(24531,1,0, 'I''d rather listen to his braying than yours, dear.',0,7,100,0,0,0, 'Gavin Ward'),
(24532,2,0, 'Remember, honey, we need to get a plot of land with a nice hot spring.',0,7,100,1,0,0, 'Sabetta Ward'),
(24531,2,0, 'Of course, darling.',0,7,100,1,0,0, 'Gavin Ward');

-- Conversation between Brune Grayblade & Eldrim Mounder <Blacksmith>, Fort Wildervar "Brune Grayblade Envoker"
SET @ENTRY := 24528;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,30000,60000,150000,150000,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Load script every 2.5 min ooc'),
(@ENTRY*100,9,0,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Brune Grayblade Say text 0'),
(@ENTRY*100,9,1,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,9,24052,0,10,0,0,0,0,'Eldrim Mounder Say text 0'),
(@ENTRY*100,9,2,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Brune Grayblade Say text 1'),
(@ENTRY*100,9,3,0,0,0,100,0,5000,5000,0,0,1,1,0,0,0,0,0,9,24052,0,10,0,0,0,0,'Eldrim Mounder Say text 1'),
(@ENTRY*100,9,4,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,9,24052,0,10,0,0,0,0,'Eldrim Mounder Say text 2'),
(@ENTRY*100,9,5,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Brune Grayblade Say text 2');
-- NPC talk text insert from sniff "5 sec between text 2 min between restart"
DELETE FROM `creature_text` WHERE `entry` IN (24528,24052);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(24528,0,0, 'How much''ll it cost me to get my mules shod?',0,7,100,6,0,0, 'Brune Grayblade'),
(24052,0,0, 'We don''t shoe no mules here. ''Sides, it''s strictly expedition business right now.',0,7,100,1,0,0, 'Eldrim Mounder'),
(24528,1,0, 'You don''t understand! If I''m not ready to go soon, all the good homesteading land will be taken!',0,7,100,1,0,0, 'Brune Grayblade'),
(24052,1,0, 'Not my problem! If yer so antsy to get yerself a house built, do it ''ere in the fort and quit yer whinin''!',0,7,100,274,0,0, 'Eldrim Mounder'),
(24052,2,0, 'Now, if you''d be so kind as to get your ass away from my forge...',0,7,100,25,0,0, 'Eldrim Mounder'),
(24528,2,0, 'That, sir, is a mule!',0,7,100,25,0,0, 'Brune Grayblade');
-- Creature Template Addon info
DELETE FROM `creature_template_addon` WHERE `entry` IN (24528,24052);
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(24528,0,0,256,0, ''),
(24052,0,0,257,0, '');
DELETE FROM `creature_text` WHERE `entry`=27656;
INSERT INTO `creature_text` (entry,groupid,id,text,type,comment) VALUES
(27656,0,0,'You brash interlopers are out of your element! I will ground you!',1,'Boss Eregos - Aggro'),
(27656,1,0,'Such insolence... such arrogance... must be PUNISHED!',1,'Boss Eregos - Enrage'),
(27656,2,0,'Savor this small victory, foolish little creatures. You and your dragon allies have won this battle. But we will win... the Nexus War.',1,'Boss Eregos - Death');
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
DELETE FROM `creature_text` WHERE `entry`=27447;
INSERT INTO `creature_text` (entry,groupid,id,TEXT,TYPE,LANGUAGE,sound) VALUES 
(27447,0,0,'There will be no mercy!',1,0,13649),
(27447,1,1,'Blast them! Destroy them!',1,0,13650),
(27447,2,2,'%s calls an Azure Ring Captain!',3,0,0),
(27447,3,3,'They are... too strong! Underestimated their... fortitude.',1,0,13655);
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30273;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30273;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30273,0,0,0,6,0,100,0,0,0,0,0,85,56515,0x02,0,0,0,0,7,0,0,0,0,0,0,0, 'Cast Summon Freed Crusader on Death'),
(30273,0,1,0,6,0,100,0,0,0,0,0,33,30274,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Cast Summon Freed Crusader Quest Credit');
UPDATE `creature_template` SET `AIName`= 'SmartAI', `minlevel`=1, `maxlevel`=1 WHERE `entry`=30268;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30268;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30268,0,0,0,6,0,100,0,0,0,0,0,12,30204,1,30000,0,0,0,1,0,0,0,0,0,0,0, 'Summon Forgotten Depths Ambusher');
-- Freeed Crusader
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
-- create path point location to send Freed Crusaders to
DELETE FROM `waypoints` WHERE `entry`=30274;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES 
(30274,1,6296.25,92.9397,390.701, 'send Freed Crusader here');
DELETE FROM `creature_text` WHERE `entry`=30274;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(30274,0,0, 'Thank you and farewell, friend. I must return to the Argent Vanguard.',0,0,100,0,0,0, 'Freed Crusader Speach');
-- Forgotten Depths Ambusher
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=30204;
DELETE FROM `smart_scripts` WHERE `entryorguid`=30204;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(30204,0,0,0,54,0,100,0,0,0,0,0,11,56418,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Forgotten Depths Ambusher - Emerge From Snow');
-- Cult Plaguebringer <Cult of the Damned> SAI (tested) 
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=24957;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=24957;
DELETE FROM `smart_scripts` WHERE `entryorguid`=24957;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(24957,0,0,0,1,0,100,0,1000,900000,500000,700000,11,45850,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Ghoul Summons OOC'),
(24957,0,2,0,0,0,30,0,1100,6300,8800,13800,11,50356,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Inject Plague on victim');
-- Cultist Necrolyte SAI (tested) 
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=25651;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (25651);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(25651,0,0,0,11,0,100,0,0,0,0,0,11,45104,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shadow Channelling on self when spawned'),
(25651,0,1,0,21,0,100,0,0,0,0,0,11,45104,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shadow Channelling on self when reach home home'),
(25651,0,2,0,0,0,30,0,1000,2000,6000,8000,11,18266,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Curse of Agony on victim'),
(25651,0,3,0,0,0,70,0,3000,4000,3000,4000,11,9613,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Shadow Bolt on victim');
-- Azure Front Channel Stalker SAI (tested working)
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=31400;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-112478,0,0,0,1,0,100,1,1000,1000,1000,1000,11,59044,2,0,0,0,0,10,111746,31400,0,0,0,0,0,'Cast Cosmetic - Crystalsong Tree Beam when spawned'),
(-112479,0,0,0,1,0,100,1,1000,1000,1000,1000,11,59044,2,0,0,0,0,10,111726,31400,0,0,0,0,0,'Cast Cosmetic - Crystalsong Tree Beam when spawned'),
(-112480,0,0,0,1,0,100,1,1000,1000,1000,1000,11,59044,2,0,0,0,0,10,111742,31400,0,0,0,0,0,'Cast Cosmetic - Crystalsong Tree Beam when spawned'),
(-112482,0,0,0,1,0,100,1,1000,1000,1000,1000,11,59044,2,0,0,0,0,10,203520,31400,0,0,0,0,0,'Cast Cosmetic - Crystalsong Tree Beam when spawned');
-- Wildhammer Scout SAI (tested)
-- Removes waypoint script error spamming at Wildhammer Stronghold
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=19384;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-74030,0,0,0,1,0,100,0,1000,2000,3000,6000,11,33808,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shoot Gun every 3-6 sec'),
(-74031,0,0,0,1,0,100,0,1000,2000,3000,6000,11,33808,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shoot Gun every 3-6 sec'),
(-74037,0,0,0,1,0,100,0,3000,5000,3000,5000,11,33805,2,0,0,0,0,9,19388,0,25,0,0,0,0,'Cast Throw Hammer every 3-5 sec'),
(-74038,0,0,0,1,0,100,0,3000,5000,3000,5000,11,33806,2,0,0,0,0,9,19388,0,25,0,0,0,0,'Cast Throw Hammer every 3-5 sec'),
(-74055,0,0,0,1,0,100,0,1000,2000,3000,6000,11,33808,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shoot Gun every 3-6 sec'),
(-74091,0,0,0,1,0,100,0,1000,2000,3000,6000,11,33808,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Shoot Gun every 3-6 sec');
-- Speech by Marrod Silvertongue, Fort Wildervar (Tested working)
SET @ENTRY := 24534;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@ENTRY*100;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,30000,50000,360000,360000,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Load script every 6 min ooc'),
(@ENTRY*100,9,0,0,0,0,100,0,8000,8000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 0'),
(@ENTRY*100,9,1,0,0,0,100,0,2000,2000,0,0,5,21,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,2,0,0,0,100,0,8000,8000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 1'),
(@ENTRY*100,9,3,0,0,0,100,0,2000,2000,0,0,5,21,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,4,0,0,0,100,0,8000,8000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 2'),
(@ENTRY*100,9,5,0,0,0,100,0,2000,2000,0,0,5,21,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,6,0,0,0,100,0,8000,8000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 3'),
(@ENTRY*100,9,7,0,0,0,100,0,2000,2000,0,0,5,21,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,8,0,0,0,100,0,8000,8000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 4'),
(@ENTRY*100,9,9,0,0,0,100,0,2000,2000,0,0,5,4,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,10,0,0,0,100,0,8000,8000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 5'),
(@ENTRY*100,9,11,0,0,0,100,0,2000,2000,0,0,5,4,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,12,0,0,0,100,0,8000,8000,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Marrod Silvertongue Say text 6'),
(@ENTRY*100,9,13,0,0,0,100,0,2000,2000,0,0,5,4,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote'),
(@ENTRY*100,9,14,0,0,0,100,0,3000,3000,0,0,5,4,0,0,0,0,0,9,24535,0,20,0,0,0,0,'Northrend Homesteader emote');
-- NPC talk text insert from sniff
DELETE FROM `creature_text` WHERE `entry` IN (24534);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(24534,0,0, 'Welcome to Fort Wildervar, brave homesteaders! There''s a whole continent out there just waiting to be claimed!',0,7,100,1,0,0, 'Marrod Silvertongue'),
(24534,1,0, 'True, Northrend is a hard land, but our people are strong, hardy, and equal to the task!',0,7,100,0,0,0, 'Marrod Silvertongue'),
(24534,2,0, 'We will win this land with the sword, and break it with the plow! You are the men and women who will be remembered for taming the wild continent!',0,7,100,1,0,0, 'Marrod Silvertongue'),
(24534,3,0, 'But, you will not be alone out there. My men and I have prepared pack mules carrying the supplies you''ll need most.',0,7,100,1,0,0, 'Marrod Silvertongue'),
(24534,4,0, 'Axes, picks, seed, nails, food, blankets, water... it''s all there, waiting for you. I think you''ll find my prices quite reasonable, too.',0,7,100,25,0,0, 'Marrod Silvertongue'),
(24534,5,0, 'There are more than enough to go around. Should you need other goods, don''t hesitate to ask!',0,7,100,1,0,0, 'Marrod Silvertongue'),
(24534,6,0, 'Now, my loyal custo... err, friends, go forth and conquer this land for our people!',0,7,100,274,0,0, 'Marrod Silvertongue');
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=12846 AND `type` in (16,18);
DELETE FROM `achievement_criteria_data` WHERE `criteria_id`=12859 AND `type` in (5,15,18);
INSERT INTO `achievement_criteria_data`(`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES 
(12846,16,335,0, ''),
(12859,5,26682,0, ''),
(12859,15,3,0, '');
DELETE FROM `creature_text` WHERE `entry` IN (38490,38494);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38490,0,0, '$n is infected with the Death Plague!',3,0,100,25,0,0, 'Rotting Frost Giant - Death Plague'),
(38494,0,0, '$n is infected with the Death Plague!',3,0,100,25,0,0, 'Rotting Frost Giant - Death Plague');
DELETE FROM `creature_text` WHERE `entry` IN (38472,38485);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(38472,0,0, 'Die, intruders! None shall interfere with the Cult''s plans!',1,0,0,0,0,0, 'Darnavan - SAY_DARNAVAN_AGGRO'),
(38472,1,0, 'Wh- where am I...? What a nightmare I have had... But this is no time to reflect, I have much information to report!',0,0,0,0,0,0, 'Darnavan - SAY_DARNAVAN_RESCUED'),
(38485,0,0, 'Die, intruders! None shall interfere with the Cult''s plans!',1,0,0,0,0,0, 'Darnavan - SAY_DARNAVAN_AGGRO'),
(38485,1,0, 'Wh- where am I...? What a nightmare I have had... But this is no time to reflect, I have much information to report!',0,0,0,0,0,0, 'Darnavan - SAY_DARNAVAN_RESCUED');
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=27006;
DELETE FROM `smart_scripts` WHERE `entryorguid`=27006;
DELETE FROM `creature_ai_scripts` WHERE `creature_id`=27006; 
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27006,0,0,0,0,0,100,0,5000,11000,16000,25000,11,52080,1,0,0,0,0,2,0,0,0,0,0,0,0,'Bonesunder - Cast Bonecrack');
-- Goramosh SAI
SET @ELMGUID := 113473;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=26349;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (26349);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(26349,0,0,0,1,0,100,1,1000,1000,1000,1000,11,46906,2,0,0,0,0,10,@ELMGUID,26298,0,0,0,0,0,'Cast Surge Needle Beam when spawned'),
(26349,0,1,0,21,0,100,0,0,0,0,0,11,46906,2,0,0,0,0,10,@ELMGUID,26298,0,0,0,0,0,'Cast Surge Needle Beam when reach home'),
(26349,0,2,0,2,0,100,1,0,50,0,0,11,20828,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Cone of Cold on victim at 50% health'),
(26349,0,3,0,0,0,100,0,3500,3500,3500,3500,11,9672,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Frost Bolt on victim');
-- Arcanimus SAI
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=26370;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (26370);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(26370,0,0,0,1,0,100,1,2000,2000,2000,2000,45,0,1,0,0,0,0,10,113473,26298,0,0,0,0,0, 'Set data 0 = 1 on bunny 2 sec after reset'),
(26370,0,1,0,1,0,100,1,0,0,0,0,11,46934,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - Add Cosmetic - Arcane Force Shield (Blue x2) Aura on spawn & reset'),
(26370,0,2,3,4,0,100,0,0,0,0,0,28,46934,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - Remove Cosmetic - Arcane Force Shield (Blue x2) Aura on aggro'),
(26370,0,3,0,61,0,100,0,0,0,0,0,28,46906,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - Remove Cosmetic - Surge Needle Beam on aggro'),
(26370,0,4,0,2,0,100,1,71,80,0,0,11,51820,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - at 80% health cast Arcane Explosion on self'),
(26370,0,5,0,2,0,100,1,41,60,0,0,11,51820,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - at 60% health cast Arcane Explosion on self'),
(26370,0,6,0,2,0,100,1,21,40,0,0,11,51820,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - at 40% health cast Arcane Explosion on self'),
(26370,0,7,0,2,0,100,1,1,20,0,0,11,51820,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Arcanimus - at 20% health cast Arcane Explosion on self');
-- ELM General Purpose Bunny (scale x0.01) Large SAI
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=26298;
REPLACE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-104147,0,0,0,11,0,100,0,0,0,0,0,11,32566,2,0,0,0,0,1,0,0,0,0,0,0,0,'Cast Purple Banish State aura on self when spawned'),
(-104147,0,1,2,38,0,100,0,0,1,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'reset data 0 = 0'),
(-104147,0,2,0,61,0,100,0,0,0,0,0,11,46906,2,0,0,0,0,10,96298,26370,0,0,0,0,0, 'cast Surge Needle Beam on Arcanimus');
UPDATE `creature_template` SET `flags_extra`=`flags_extra`|128 WHERE `entry`=38752;
UPDATE `creature_template` SET `AIName`='NullAI' WHERE `entry` IN(33742,33809,33942);
UPDATE `creature_template` SET `speed_run`=5.5/7, `modelid1`=1126, `modelid2`=11686, `flags_extra`= `flags_extra`|128 WHERE `entry` IN(33632,33802);
