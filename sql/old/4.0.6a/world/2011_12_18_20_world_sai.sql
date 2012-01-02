-- SAI for Chief Engineer Galpen Rolltie
SET @ENTRY := 26600;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100,@ENTRY*100+1,@ENTRY*100+2);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
-- AI
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - On spawn - Start WP movement'),
(@ENTRY,0,1,2,40,0,100,0,1,@ENTRY,0,0,54,16000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 1 - pause path'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 1 - STATE_WORK_MINING'),
(@ENTRY,0,3,4,40,0,100,0,7,@ENTRY,0,0,54,9000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 7 - pause path'),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 7 - STATE_WORK_MINING'),
(@ENTRY,0,5,6,40,0,100,0,15,@ENTRY,0,0,54,14000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 15 - pause path'),
(@ENTRY,0,6,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Chief Engineer Galpen Rolltie - Reach wp 15 - STATE_WORK_MINING');
-- Waypoints for Chief Engineer Galpen Rolltie from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4138.141,5318.302,28.81850, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,2,4140.475,5319.229,29.29604, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,3,4141.725,5323.979,29.04604, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,4,4139.975,5327.229,29.29604, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,5,4136.975,5328.229,29.29604, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,6,4134.975,5327.229,29.29604, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,7,4135.308,5325.655,28.77358, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,8,4135.063,5327.819,29.27233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,9,4140.063,5327.819,29.27233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,10,4143.313,5325.319,29.27233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,11,4141.313,5317.819,29.77233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,12,4137.063,5314.819,29.02233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,13,4132.313,5316.569,29.02233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,14,4130.313,5319.819,29.27233, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,15,4131.816,5320.484,28.77108, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,16,4130.521,5321.019,29.24854, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,17,4131.021,5317.769,29.24854, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,18,4133.771,5315.769,28.99854, 'Chief Engineer Galpen Rolltie'),
(@ENTRY,19,4136.725,5316.553,28.72600, 'Chief Engineer Galpen Rolltie');


-- Pathing for Willis Wobblewheel SAI
SET @ENTRY := 26599;
-- SAI for Willis Wobblewheel
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100,@ENTRY*100+1);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Willis Wobblewheel - On spawn - Start WP movement'),
(@ENTRY,0,1,2,40,0,100,0,1,@ENTRY,0,0,54,17000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Willis Wobblewheel - Reach wp 1 - pause path'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Willis Wobblewheel - Reach wp 1 - STATE_WORK_MINING'),
(@ENTRY,0,3,4,40,0,100,0,3,@ENTRY,0,0,54,16000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Willis Wobblewheel - Reach wp 3 - pause path'),
(@ENTRY,0,4,5,61,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,5.288348, 'Willis Wobblewheel - Reach wp 3 - turn to'),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Willis Wobblewheel - Reach wp 1 - STATE_USESTANDING');
-- Waypoints for Willis Wobblewheel from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4137.04,5285.097,25.23916, 'Willis Wobblewheel'),
(@ENTRY,2,4135.779,5282.234,25.11416, 'Willis Wobblewheel'),
(@ENTRY,3,4135.004,5281.168,25.11416, 'Willis Wobblewheel'),
(@ENTRY,4,4135.779,5282.234,25.11416, 'Willis Wobblewheel');

-- Pathing for Fizzcrank Watcher Rupert Keeneye SAI
SET @ENTRY := 26634;
-- SAI for Fizzcrank Watcher Rupert Keeneye
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100,@ENTRY*100+1);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Watcher Rupert Keeneye - On spawn - Start WP movement'),
(@ENTRY,0,1,0,40,0,100,0,2,@ENTRY,0,0,54,30000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Watcher Rupert Keeneye - Reach wp 2 - pause path'),
(@ENTRY,0,2,3,40,0,100,0,6,@ENTRY,0,0,54,30000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Watcher Rupert Keeneye - Reach wp 6 - pause path'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0.8901179, 'Fizzcrank Watcher Rupert Keeneye - Reach wp 6 - turn to');
-- Waypoints for Fizzcrank Watcher Rupert Keeneye from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4186.929,5321.105,58.13441, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,2,4185.132,5318.713,58.1639, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,3,4186.515,5316.936,58.15049, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,4,4186.929,5321.105,58.13441, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,5,4191.268,5319.607,58.12418, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,6,4189.929,5324.715,58.08976, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,7,4184.381,5325.549,58.05596, 'Fizzcrank Watcher Rupert Keeneye'),
(@ENTRY,8,4183.354,5318.837,58.1593, 'Fizzcrank Watcher Rupert Keeneye');

-- Pathing for Fizzcrank Engineering Crew SAI
SET @ENTRY := 26645;
SET @PATH2 := @ENTRY;
-- SAI for Fizzcrank Engineering Crew
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT IGNORE INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-117070,0,0,0,11,0,100,0,0,0,0,0,53,0,@PATH2,1,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - On spawn - Start WP movement'),
(-117070,0,1,2,40,0,100,0,5,@PATH2,0,0,54,20000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 5 - pause path'),
(-117070,0,2,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 5 - STATE_USESTANDING'),
(-117070,0,3,4,40,0,100,0,10,@PATH2,0,0,54,23000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 10 - pause path'),
(-117070,0,4,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 10 - STATE_WORK_MINING'),
(-117070,0,5,6,40,0,100,0,18,@PATH2,0,0,54,25000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 18 - pause path'),
(-117070,0,6,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 18 - STATE_WORK_MINING'),
(-117070,0,7,8,40,0,100,0,24,@PATH2,0,0,54,25000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 24 - pause path'),
(-117070,0,8,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Engineering Crew - Reach wp 24 - STATE_USESTANDING');
-- Waypoints for Fizzcrank Engineering Crew from sniff
DELETE FROM `waypoints` WHERE `entry` IN (@PATH,@PATH2);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@PATH2,1,4147.00,5327.734,29.32715, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,2,4149.25,5326.734,29.07715, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,3,4151.50,5329.484,29.32715, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,4,4150.25,5330.734,29.32715, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,5,4148.829,5329.599,28.9719, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,6,4150.054,5331.477,29.32324, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,7,4152.054,5333.477,29.07324, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,8,4150.804,5335.727,29.07324, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,9,4147.554,5336.477,29.07324, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,10,4143.779,5335.355,28.67457, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,11,4146.732,5336.823,29.20758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,12,4150.982,5335.573,29.20758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,13,4153.232,5331.323,28.95758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,14,4150.482,5326.823,28.70758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,15,4144.732,5324.573,29.45758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,16,4141.482,5326.823,29.20758, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,17,4139.686,5329.791,28.74058, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,18,4141.878,5331.735,28.69350, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,19,4141.274,5330.552,29.18795, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,20,4141.774,5328.302,29.18795, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,21,4142.774,5326.052,29.18795, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,22,4145.524,5326.052,29.43795, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,23,4146.774,5328.052,29.18795, 'Fizzcrank Engineering Crew wp 2'),
(@PATH2,24,4145.670,5329.370,28.68240, 'Fizzcrank Engineering Crew wp 2');

-- Pathing for Fizzcrank bomber Entry: 25765
SET @NPC := 95549;
SET @PATH := @NPC;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=4235.847,`position_y`=5353.55,`position_z`=81.03476 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`bytes2`,`mount`,`auras`) VALUES (@NPC,@PATH,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,4222.374,5370.328,72.03476,0,1,0,100,0),
(@PATH,2,4193.999,5364.787,66.81252,0,1,0,100,0),
(@PATH,3,4161.166,5319.937,66.81252,0,1,0,100,0),
(@PATH,4,4149.038,5289.545,66.81252,0,1,0,100,0),
(@PATH,5,4158.851,5255.303,66.81252,0,1,0,100,0),
(@PATH,6,4193.628,5230.504,79.17356,0,1,0,100,0),
(@PATH,7,4259.787,5211.473,79.20131,0,1,0,100,0),
(@PATH,8,4293.693,5221.593,80.20133,0,1,0,100,0),
(@PATH,9,4296.654,5282.716,82.20137,0,1,0,100,0),
(@PATH,10,4261.68,5314.814,89.8682,0,1,0,100,0),
(@PATH,11,4224.254,5366.333,98.86811,0,1,0,100,0),
(@PATH,12,4174.309,5345.78,98.86811,0,1,0,100,0),
(@PATH,13,4150.472,5287.501,98.86811,0,1,0,100,0),
(@PATH,14,4188.47,5251.628,102.757,0,1,0,100,0),
(@PATH,15,4241.055,5236.796,102.757,0,1,0,100,0),
(@PATH,16,4280.259,5260.132,105.6182,0,1,0,100,0),
(@PATH,17,4271.736,5301.975,105.6182,0,1,0,100,0),
(@PATH,18,4235.847,5353.55,81.03476,0,1,0,100,0);

-- Rig Hauler AC-9 SAI
SET @ENTRY := 25766;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,0,5000,10000,210000,210000,80,@ENTRY*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Rig Hauler AC-9 - OOC 3.5 min - start script 1'),
(@ENTRY,0,1,0,40,0,100,0,1,@ENTRY,0,0,45,0,1,0,0,0,0,11,25765,20,0,0,0,0,0, 'Rig Hauler AC-9 - Reach wp 1 - dataset 0 1 nearest Fizzcrank Bomber'),
(@ENTRY,0,2,3,40,0,100,0,5,@ENTRY,0,0,54,5000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Rig Hauler AC-9 - Reach wp 5 - pause wp'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,92,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Rig Hauler AC-9 - Reach wp 5 - INTERRUPT_SPELL'),
(@ENTRY,0,4,0,40,0,100,0,6,@ENTRY,0,0,45,0,1,0,0,0,0,10,106069,15214,0,0,0,0,0, 'Rig Hauler AC-9 - Reach wp 6 - dataset 0 1 Invisable Stalker'),
(@ENTRY,0,5,0,40,0,100,0,25,@ENTRY,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,2.740167, 'Rig Hauler AC-9 - Reach wp 25 - turn to'),
-- Script
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,12,25765,3,360000,0,0,0,8,0,0,0,4165.76,5354.39,30.1116,2.35619, 'Rig Hauler AC-9 - script - summon 25765'),
(@ENTRY*100,9,1,0,0,0,100,0,6000,6000,0,0,11,45967,0,0,0,0,0,11,25765,10,0,0,0,0,0, 'Rig Hauler AC-9 - script - cast 45967'),
(@ENTRY*100,9,2,0,0,0,100,0,3000,3000,0,0,53,0,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0, 'Rig Hauler AC-9 - script - Start WP movement');
-- Waypoints for Rig Hauler AC-9 from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4149.316,5357.732,29.11953, 'Rig Hauler AC-9'),
(@ENTRY,2,4136.816,5345.482,29.11953, 'Rig Hauler AC-9'),
(@ENTRY,3,4125.566,5333.982,29.11953, 'Rig Hauler AC-9'),
(@ENTRY,4,4115.297,5323.852,28.67458, 'Rig Hauler AC-9'),
(@ENTRY,5,4108.158,5316.849,28.75930, 'Rig Hauler AC-9'),
(@ENTRY,6,4111.660,5313.279,28.75930, 'Rig Hauler AC-9'),
(@ENTRY,7,4112.747,5314.946,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,8,4116.997,5314.946,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,9,4118.997,5316.946,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,10,4125.247,5323.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,11,4127.247,5325.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,12,4129.497,5326.696,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,13,4131.497,5328.446,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,14,4133.497,5328.446,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,15,4134.747,5329.446,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,16,4135.747,5333.696,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,17,4141.997,5337.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,18,4143.997,5341.946,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,19,4145.997,5344.946,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,20,4147.247,5346.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,21,4150.247,5348.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,22,4152.247,5350.196,29.16189, 'Rig Hauler AC-9'),
(@ENTRY,23,4162.747,5356.196,29.66189, 'Rig Hauler AC-9'),
(@ENTRY,24,4166.997,5358.696,30.41189, 'Rig Hauler AC-9'),
(@ENTRY,25,4170.335,5359.113,30.06447, 'Rig Hauler AC-9');

-- Fizzcrank Bomber SAI
SET @ENTRY := 25765;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,38,0,100,0,0,1,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Bomber - on dataset 0 1 - dataset 0 0'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,53,0,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Bomber - on dataset 0 1 - Start WP movement'),
(@ENTRY,0,2,3,40,0,100,0,22,@ENTRY,0,0,54,45000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Bomber - Reach wp 22 - pause wp'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Bomber - Reach wp 22 - Set Speed run'),
(@ENTRY,0,4,5,40,0,100,0,74,@ENTRY,0,0,11,47460,3,0,0,0,0,11,26817,5,0,0,0,0,0, 'Fizzcrank Bomber - Reach wp 74 - cast 47460 on Fizzcrank fighter'),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Bomber - Reach wp 74 - despawn');
-- Waypoints for Fizzcrank Bomber from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4164.758,5354.723,30.19215, 'Fizzcrank Bomber wp 1'),
(@ENTRY,2,4162.034,5355.368,30.09748, 'Fizzcrank Bomber wp 1'),
(@ENTRY,3,4159.190,5355.827,30.01153, 'Fizzcrank Bomber wp 1'),
(@ENTRY,4,4156.273,5356.132,29.94405, 'Fizzcrank Bomber wp 1'),
(@ENTRY,5,4154.659,5355.736,29.91132, 'Fizzcrank Bomber wp 1'),
(@ENTRY,6,4152.153,5354.786,29.86976, 'Fizzcrank Bomber wp 1'),
(@ENTRY,7,4149.633,5353.545,29.83581, 'Fizzcrank Bomber wp 1'),
(@ENTRY,8,4147.138,5352.081,29.80874, 'Fizzcrank Bomber wp 1'),
(@ENTRY,9,4144.689,5350.449,29.78749, 'Fizzcrank Bomber wp 1'),
(@ENTRY,10,4142.290,5348.694,29.77098, 'Fizzcrank Bomber wp 1'),
(@ENTRY,11,4139.963,5346.840,29.76581, 'Fizzcrank Bomber wp 1'),
(@ENTRY,12,4137.673,5344.909,29.76182, 'Fizzcrank Bomber wp 1'),
(@ENTRY,13,4135.418,5342.924,29.75874, 'Fizzcrank Bomber wp 1'),
(@ENTRY,14,4133.194,5340.901,29.75638, 'Fizzcrank Bomber wp 1'),
(@ENTRY,15,4130.993,5338.848,29.75706, 'Fizzcrank Bomber wp 1'),
(@ENTRY,16,4128.794,5336.785,29.75758, 'Fizzcrank Bomber wp 1'),
(@ENTRY,17,4126.612,5334.716,29.75798, 'Fizzcrank Bomber wp 1'),
(@ENTRY,18,4124.430,5332.629,29.75829, 'Fizzcrank Bomber wp 1'),
(@ENTRY,19,4121.542,5329.849,29.75858, 'Fizzcrank Bomber wp 1'),
(@ENTRY,20,4118.184,5326.597,29.75881, 'Fizzcrank Bomber wp 1'),
(@ENTRY,21,4116.024,5324.498,29.75892, 'Fizzcrank Bomber wp 1'),
(@ENTRY,22,4113.869,5322.398,29.75901, 'Fizzcrank Bomber wp 1'),
(@ENTRY,23,4090.109,5298.56,29.70082, 'Fizzcrank Bomber wp 1'),
(@ENTRY,24,4079.459,5287.617,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,25,4066.779,5274.603,31.53571, 'Fizzcrank Bomber wp 1'),
(@ENTRY,26,4041.215,5249.248,31.45236, 'Fizzcrank Bomber wp 1'),
(@ENTRY,27,4020.432,5218.824,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,28,4002.392,5190.421,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,29,4000.105,5146.331,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,30,3993.002,5119.754,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,31,3976.405,5093.208,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,32,3983.637,5055.651,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,33,3990.106,5011.049,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,34,3992.433,4984.051,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,35,3988.744,4946.948,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,36,3975.796,4912.274,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,37,3958.111,4895.366,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,38,3928.622,4858.76,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,39,3921.781,4825.03,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,40,3935.435,4790.436,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,41,3966.323,4756.983,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,42,3987.75,4763.042,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,43,4025.366,4755.083,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,44,4050.189,4787.045,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,45,4082.41,4825.174,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,46,4084.739,4845.887,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,47,4082.781,4879.066,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,48,4075.255,4897.705,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,49,4063.763,4936.532,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,50,4066.78,4968.409,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,51,4082.993,4997.696,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,52,4110.507,5030.572,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,53,4141.148,5060.043,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,54,4164.455,5087.176,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,55,4189.664,5124.69,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,56,4214.33,5154.247,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,57,4237.962,5194.166,29.8968, 'Fizzcrank Bomber wp 1'),
(@ENTRY,58,4228.307,5238.578,42.11903, 'Fizzcrank Bomber wp 1'),
(@ENTRY,59,4200.375,5271.218,46.75792, 'Fizzcrank Bomber wp 1'),
(@ENTRY,60,4211.719,5318.444,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,61,4229.69,5356.218,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,62,4229.779,5396.165,53.08044, 'Fizzcrank Bomber wp 1'),
(@ENTRY,63,4231.299,5419.959,53.71933, 'Fizzcrank Bomber wp 1'),
(@ENTRY,64,4228.378,5466.135,57.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,65,4249.183,5490.759,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,66,4282.767,5500.858,48.85822, 'Fizzcrank Bomber wp 1'),
(@ENTRY,67,4300.521,5486.341,48.386, 'Fizzcrank Bomber wp 1'),
(@ENTRY,68,4291.369,5470.349,48.91378, 'Fizzcrank Bomber wp 1'),
(@ENTRY,69,4277.046,5454.25,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,70,4253.641,5434.851,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,71,4227.768,5423.928,47.13599, 'Fizzcrank Bomber wp 1'),
(@ENTRY,72,4204.012,5411.217,37.52486, 'Fizzcrank Bomber wp 1'),
(@ENTRY,73,4194.847,5402.538,32.41374, 'Fizzcrank Bomber wp 1'),
(@ENTRY,74,4178.285,5386.063,30.94151, 'Fizzcrank Bomber wp 1');

-- Invisable Stalker SAI
SET @ENTRY := 15214;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` in (-112623,-112625);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(-112623,0,0,1,38,0,100,0,0,1,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Invisable Stalker - on dataset 0 1 - dataset 0 0'),
(-112625,0,1,0,61,0,100,0,0,0,0,0,11,47453,3,0,0,0,0,11,25766,200,0,0,0,0,0, 'Invisable Stalker - on dataset 0 1 - Cast 47453 on Rig Hauler AC-9');

-- Fizzcrank Fighter SAI
SET @ENTRY := 26817;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Fighter - on spawn - start wp'),
(@ENTRY,0,1,0,1,0,100,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Fighter - on spawn - say text 0'),
(@ENTRY,0,2,0,40,0,100,0,15,@ENTRY,0,0,11,43671,3,0,0,0,0,11,25765,20,0,0,0,0,0, 'Fizzcrank Fighter - Reach wp 15 - cast 43671 on Fizzcrank Bomber');
-- NPC talk text for Fizzcrank Fighter
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I''ll blast those gnomish wannabes back to the scrap heap!',0,7,100,0,0,0, 'Fizzcrank Fighter'),
(@ENTRY,0,1, 'You''re sending me back there?!',0,7,100,0,0,0, 'Fizzcrank Fighter');
-- Waypoints for Fizzcrank Fighter from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4176.501,5280.566,27.17445, 'Fizzcrank Fighter'),
(@ENTRY,2,4167.001,5282.066,27.17445, 'Fizzcrank Fighter'),
(@ENTRY,3,4164.751,5282.566,26.92445, 'Fizzcrank Fighter'),
(@ENTRY,4,4162.655,5282.681,26.48916, 'Fizzcrank Fighter'),
(@ENTRY,5,4158.462,5280.628,26.26419, 'Fizzcrank Fighter'),
(@ENTRY,6,4155.712,5279.378,25.76419, 'Fizzcrank Fighter'),
(@ENTRY,7,4154.958,5278.939,24.86416, 'Fizzcrank Fighter'),
(@ENTRY,8,4147.710,5281.817,24.86416, 'Fizzcrank Fighter'),
(@ENTRY,9,4144.757,5295.502,25.61416, 'Fizzcrank Fighter'),
(@ENTRY,10,4142.652,5300.067,26.94346, 'Fizzcrank Fighter'),
(@ENTRY,11,4137.876,5308.749,27.94350, 'Fizzcrank Fighter'),
(@ENTRY,12,4135.610,5310.586,28.93834, 'Fizzcrank Fighter'),
(@ENTRY,13,4131.433,5312.564,28.75930, 'Fizzcrank Fighter'),
(@ENTRY,14,4123.820,5317.622,28.75930, 'Fizzcrank Fighter'),
(@ENTRY,15,4115.430,5321.649,28.75930, 'Fizzcrank Fighter');

-- Pathing for Crafty Wobblesprocket SAI
SET @ENTRY := 25477;
UPDATE `creature` SET `spawndist`=0,`MovementType`=0,`position_x`=4172.788,`position_y`=5254.925,`position_z`=26.12851 WHERE `guid`=108021;
-- SAI for Crafty Wobblesprocket
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100,@ENTRY*100+1);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Crafty Wobblesprocket - On spawn - Start WP movement'),
(@ENTRY,0,1,2,40,0,100,0,1,@ENTRY,0,0,54,45000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Crafty Wobblesprocket - Reach wp 1 - pause path'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,17,69,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Crafty Wobblesprocket - Reach wp 1 - STATE_USESTANDING'),
(@ENTRY,0,3,4,40,0,100,0,6,@ENTRY,0,0,54,35000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Crafty Wobblesprocket - Reach wp 6 - pause path'),
(@ENTRY,0,4,5,61,0,100,0,0,0,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,0.4712389, 'Crafty Wobblesprocket - Reach wp 6 - turn to'),
(@ENTRY,0,5,0,61,0,100,0,0,0,0,0,17,233,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Crafty Wobblesprocket - Reach wp 6 - STATE_WORK_MINING');
-- Waypoints for Crafty Wobblesprocket from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4179.099,5251.51,26.37851, 'Crafty Wobblesprocket'),
(@ENTRY,2,4177.94,5250.202,26.87851, 'Crafty Wobblesprocket'),
(@ENTRY,3,4181.048,5243.429,24.87851, 'Crafty Wobblesprocket'),
(@ENTRY,4,4182.067,5222.448,25.00868, 'Crafty Wobblesprocket'),
(@ENTRY,5,4193.037,5217.233,25.13368, 'Crafty Wobblesprocket'),
(@ENTRY,6,4193.037,5217.233,25.13368, 'Crafty Wobblesprocket'),
(@ENTRY,7,4190.718,5217.938,25.25868, 'Crafty Wobblesprocket'),
(@ENTRY,8,4176.049,5229.444,24.50868, 'Crafty Wobblesprocket'),
(@ENTRY,9,4166.732,5248.798,24.75351, 'Crafty Wobblesprocket'),
(@ENTRY,10,4172.788,5254.925,26.12851, 'Crafty Wobblesprocket');


-- SAI for Fizzcrank Airstrip Survivor
SET @ENTRY := 25783;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,0,0,0,0,11,34427,3,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Airstrip Survivor - on spawn - cast 34427 on self'),
(@ENTRY,0,1,0,1,0,100,1,1000,1000,1000,1000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Airstrip Survivor - on spawn - say text 0'),
(@ENTRY,0,2,3,38,0,100,0,0,1,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Airstrip Survivor - on dataset 0 1 - dataset 0 0'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,53,0,@ENTRY,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Airstrip Survivor - on dataset 0 1 - Start WP movement'),
(@ENTRY,0,4,0,40,0,100,0,6,@ENTRY,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Airstrip Survivor - Reach wp 6 - despawn');
-- Waypoints for Fizzcrank Airstrip Survivor from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,4168.529,5251.933,24.87851, 'Fizzcrank Airstrip Survivor'),
(@ENTRY,2,4156.656,5256.007,24.62325, 'Fizzcrank Airstrip Survivor'),
(@ENTRY,3,4151.527,5268.997,25.36416, 'Fizzcrank Airstrip Survivor'),
(@ENTRY,4,4159.549,5281.078,26.23916, 'Fizzcrank Airstrip Survivor'),
(@ENTRY,5,4173.898,5280.844,26.69306, 'Fizzcrank Airstrip Survivor'),
(@ENTRY,6,4179.473,5282.701,26.69306, 'Fizzcrank Airstrip Survivor');
-- NPC talk text for Fizzcrank Survivor
DELETE FROM `creature_text` WHERE `entry`=@ENTRY;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@ENTRY,0,0, 'I''m flesh and blood again. That''s all that matters!',0,7,100,5,0,0, 'Fizzcrank Survivor');


-- Jean Pierre Poulain SAI
SET @ENTRY  := 34244;
SET @GOSSIP := 10478;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,@GOSSIP,0,0,0,11,64795,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Jean Pierre Poulain - On gossip option select - cast spell');
-- Fizzcrank Fullthrottle SAI
SET @ENTRY  := 25590;
SET @GOSSIP := 9171;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,15,11708,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Fizzcrank Fullthrottle - On gossip option select - quest complete'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Fizzcrank Fullthrottle - On gossip option select - close gossip');
-- Keeper Remulos SAI
SET @ENTRY  := 11832;
SET @GOSSIP := 10215;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,62,0,100,0,@GOSSIP,0,0,0,11,57413,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Keeper Remulos - On gossip option select - cast spell'),
(@ENTRY,0,1,2,62,0,100,0,@GOSSIP,1,0,0,11,57670,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Keeper Remulos - On gossip option select - cast spell'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Keeper Remulos - On gossip option select - close gossip');
-- Fizzcrank Recon Pilot SAI
SET @ENTRY  := 25841;
SET @GOSSIP := 9190;
SET @SCRIPT := 50028;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,11,46362,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - On gossip option select - close gossip'),
(@ENTRY,0,2,0,11,0,100,0,0,0,0,0,81,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - On spawn - set gossip flag'),
(@ENTRY,0,3,4,8,0,100,0,46362,0,0,0,11,46362,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - On spellhit - cast spell on envoker'),
(@ENTRY,0,4,0,61,0,100,0,0,0,0,0,23,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - On spellhit - set phase 1'),
(@ENTRY,0,5,0,1,1,100,0,3000,3000,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Fizzcrank Recon Pilot - OOC - wait 3 sec despawn (Phase 1)');
-- Glodrak Huntsniper SAI
SET @ENTRY  := 24657;
SET @GOSSIP := 9016;
SET @SCRIPT := 10603;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,11,66592,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Glodrak Huntsniper - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Glodrak Huntsniper - On gossip option select - close gossip');
-- Goldark Snipehunter SAI
SET @ENTRY  := 23486;
SET @GOSSIP := 9006;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,11,66592,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Goldark Snipehunter - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Goldark Snipehunter - On gossip option select - close gossip');

-- Pol Amberstill & Driz Tumblequick SAI
SET @ENTRY   := 24468;
SET @ENTRY1  := 24510;
SET @GOSSIP  := 8958;
SET @GOSSIP1 := 8958;
SET @SCRIPT  := 8958;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry` IN (@ENTRY,@ENTRY1);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@ENTRY,@ENTRY1);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
-- Pol Amberstill
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,6,0,0,11,44262,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Pol Amberstill - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Pol Amberstill - On gossip option select - close gossip'),
(@ENTRY,0,2,3,62,0,100,0,@GOSSIP1,0,0,0,11,44262,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Pol Amberstill - On gossip option select - cast spell'),
(@ENTRY,0,3,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Pol Amberstill - On gossip option select - close gossip'),
-- Driz Tumblequick
(@ENTRY1,0,0,1,62,0,100,0,@GOSSIP,6,0,0,11,44262,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Driz Tumblequick - On gossip option select - cast spell'),
(@ENTRY1,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Driz Tumblequick - On gossip option select - close gossip'),
(@ENTRY1,0,2,3,62,0,100,0,@GOSSIP1,0,0,0,11,44262,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Driz Tumblequick - On gossip option select - cast spell'),
(@ENTRY1,0,3,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Driz Tumblequick - On gossip option select - close gossip');
-- Steel Gate Chief Archaeologist SAI
SET @ENTRY  := 24399;
SET @GOSSIP := 8954;
SET @SCRIPT := 24399;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,11,43533,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Steel Gate Chief Archaeologist - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Steel Gate Chief Archaeologist - On gossip option select - close gossip');

-- Drakuru SAI
SET @ENTRY := 26423;
SET @GOSSIP := 9615;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,33,27921,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Drakuru - On gossip option select - killcredit'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Drakuru - On gossip option select - close gossip');

-- Dread Captain DeMeza SAI
SET @ENTRY := 28048;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,9647,0,0,0,11,50517,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Dread Captain DeMeza - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Dread Captain DeMeza - On gossip option select - close gossip');
-- Scourge Deathspeaker SAI 
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=27615;
DELETE FROM `smart_scripts` WHERE `entryorguid`=27615;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(27615,0,0,1,1,0,100,1,1000,1000,1000,1000,11,49119,2,0,0,0,0,10,101497,27452,0,0,0,0,0,'Scourge Deathspeaker - Spawn & reset - channel Fire Beam'),
(27615,0,1,0,61,0,100,1,0,0,0,0,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scourge Deathspeaker - Spawn & reset - Prevent Combat Movement'),
(27615,0,2,3,4,0,100,1,0,0,0,0,11,52282,2,0,0,0,0,2,0,0,0,0,0,0,0,'Scourge Deathspeaker - On aggro - Cast Fireball'),
(27615,0,3,0,61,0,100,1,0,0,0,0,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - On aggro - Set phase 1'),
(27615,0,4,0,9,1,100,0,3000,3000,3400,4800,11,52282,1,0,0,0,0,2,0,0,0,0,0,0,0,'Scourge Deathspeaker - in combat - Cast Fireball (phase 1)'),
(27615,0,5,0,9,1,100,0,35,80,1000,1000,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 35 Yards - Start Combat Movement (phase 1)'),
(27615,0,6,0,9,1,100,0,5,15,1000,1000,21,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 15 Yards - Prevent Combat Movement (phase 1)'),
(27615,0,7,0,9,1,100,0,0,5,1000,1000,21,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Scourge Deathspeaker - Below 5 Yards - Start Combat Movement (phase 1)'),
(27615,0,8,0,3,1,100,1,0,7,0,0,22,2,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - Mana at 7% - Set Phase 2 (phase 1)'),
(27615,0,9,0,0,2,100,1,0,0,0,0,21,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - In combat - Allow Combat Movement (phase 2)'),
(27615,0,10,0,3,2,100,1,15,100,100,100,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - Mana above 15% - Set Phase 1 (phase 2)'),
(27615,0,11,0,2,0,100,1,0,30,120000,130000,11,52281,0,0,0,0,0,2,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 15% HP - Cast Flame of the Seer'),
(27615,0,12,0,2,0,100,1,0,15,0,0,22,3,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 15% HP - Set Phase 3'),
(27615,0,13,0,2,4,100,1,0,15,0,0,21,1,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 15% HP - Allow Combat Movement (phase 3)'),
(27615,0,14,15,2,4,100,1,0,15,0,0,25,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'Scourge Deathspeaker - At 15% HP - Flee (phase 3)'),
(27615,0,15,0,61,4,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Scourge Deathspeaker - At 15% HP - Say text0 (Phase 3)');

-- NPC talk text insert
DELETE FROM `creature_text` WHERE `entry` IN (27615);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(27615,0,0, '%s attempts to run away in fear!',2,0,100,0,0,0, 'Scourge Deathspeaker');

-- SET InhabitType for Invisible Stalker Grizzly Hills
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=27452;

-- SAI for Dark Conclave Ritualist
SET @ENTRY := 22138;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,1,0,100,1,1000,1000,1000,1000,11,38469,0,0,0,0,0,19,22139,0,0,0,0,0,0,'Dark Conclave Ritualist - OOC - Dark Conclave Ritualist Channel');


-- SAI add animation to GameObject Smoke Beacon
SET @ENTRY := 184661;
UPDATE `gameobject_template` SET `AIName`= 'SmartGameObjectAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=1 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,1,0,0,1,0,100,0,0,0,1000,1000,93,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'GameObject Smoke Beacon - On Spawn - Do Custom Animation');

-- SAI for Zeth'Gor Quest Credit Marker, They Must Burn, Tower South
SET @ENTRY := 21182;
UPDATE `creature_template` SET `minlevel`=1,`maxlevel`=1,`flags_extra`=`flags_extra`&~2,`InhabitType`=4,`AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Spawn - Start WP movement'),
(@ENTRY,0,1,2,8,0,100,0,36374,0,0,0,45,0,1,0,0,0,0,10,78738,21173,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On spell hit - Call Griphonriders'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,11,34386,2,0,0,0,0,1,0,0,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On spell hit - Spawn fire');

-- Waypoints for Zeth'Gor Quest Credit Marker, They Must Burn, Tower South from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,-1156.975,2109.627,83.51005,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 1'),
(@ENTRY,2,-1152.303,2112.098,90.67654,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 2'),
(@ENTRY,3,-1150.817,2103.74,89.81573,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 3'),
(@ENTRY,4,-1153.965,2107.031,97.06559,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 4'),
(@ENTRY,5,-1156.105,2107.421,93.06557,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 5'),
(@ENTRY,6,-1152.167,2107.406,83.17665,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 6'),
(@ENTRY,7,-1150.145,2102.392,75.23684,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 7'),
(@ENTRY,8,-1158.784,2102.993,76.98234,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 8'),
(@ENTRY,9,-1158.344,2112.019,79.20454,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 9'),
(@ENTRY,10,-1148.166,2113.343,77.0103,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 10'),
(@ENTRY,11,-1148.897,2102.624,69.67694,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 11'),
(@ENTRY,12,-1157.054,2104.975,82.9548,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South WP 12');
-- Update Creature
UPDATE `creature` SET `curhealth`=1,`spawndist`=0,`MovementType`=0,`position_x`=-1157.054,`position_y`=2104.975,`position_z`=82.9548,`orientation`=1.186824 WHERE `guid`=74299;

-- SAI for Zeth'Gor Quest Credit Marker, They Must Burn, Tower North
SET @ENTRY := 22401;
UPDATE `creature_template` SET `minlevel`=1,`maxlevel`=1,`flags_extra`=`flags_extra`&~2,`InhabitType`=4,`AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North - On Spawn - Start WP movement'),
(@ENTRY,0,1,2,8,0,100,0,36374,0,0,0,45,0,2,0,0,0,0,10,74239,21173,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North - On spell hit - Call Griphonriders'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,11,34386,2,0,0,0,0,1,0,0,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North - On spell hit - Spawn fire');

-- Waypoints for Zeth'Gor Quest Credit Marker, They Must Burn, Tower North from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,-821.9919,2034.883,55.01843,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North WP 1'),
(@ENTRY,2,-820.9771,2027.591,63.68367,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North WP 2'),
(@ENTRY,3,-825.2185,2034.113,65.86314,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North WP 3'),
(@ENTRY,4,-816.8493,2028.659,49.75199,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North WP 4'),
(@ENTRY,5,-825.249,2026.351,46.58422,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North WP 5');
-- Update Creature
UPDATE `creature` SET `curhealth`=1,`spawndist`=0,`MovementType`=0,`position_x`=-825.249,`position_y`=2026.351,`position_z`=46.58422,`orientation`=1.186824 WHERE `guid`=78735;

-- SAI for Zeth'Gor Quest Credit Marker, They Must Burn, Tower Forge
SET @ENTRY := 22402;
UPDATE `creature_template` SET `minlevel`=1,`maxlevel`=1,`flags_extra`=`flags_extra`&~2,`InhabitType`=4,`AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge - On Spawn - Start WP movement'),
(@ENTRY,0,1,2,8,0,100,0,36374,0,0,0,45,0,3,0,0,0,0,10,74239,21173,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge - On spell hit - Call Griphonriders'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,11,34386,2,0,0,0,0,1,0,0,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge - On spell hit - Spawn fire');

-- Waypoints for Zeth'Gor Quest Credit Marker, They Must Burn, Tower Forge from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,-897.1001,1917.556,93.73737,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 1'),
(@ENTRY,2,-903.386,1919.14,76.0997,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 2'),
(@ENTRY,3,-898.1819,1920.161,82.67819,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 3'),
(@ENTRY,4,-901.2836,1920.168,92.57269,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 4'),
(@ENTRY,5,-894.9478,1924.78,75.48938,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 5'),
(@ENTRY,6,-894.4704,1919.866,93.71019,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge WP 6');
-- Update Creature
UPDATE `creature` SET `curhealth`=1,`spawndist`=0,`MovementType`=0,`position_x`=-894.4704,`position_y`=1919.866,`position_z`=93.71019,`orientation`=1.186824 WHERE `guid`=78736;

-- SAI for Zeth'Gor Quest Credit Marker, They Must Burn, Tower Foothill
SET @ENTRY := 22403;
UPDATE `creature_template` SET `minlevel`=1,`maxlevel`=1,`flags_extra`=`flags_extra`&~2,`flags_extra`=`flags_extra`|128,`InhabitType`=4,`AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,11,0,100,0,0,0,0,0,53,0,@ENTRY,1,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill - On Spawn - Start WP movement'),
(@ENTRY,0,1,2,8,0,100,0,36374,0,0,0,45,0,4,0,0,0,0,10,74239,21173,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill - On spell hit - Call Griphonriders'),
(@ENTRY,0,2,0,61,0,100,0,0,0,0,0,11,34386,2,0,0,0,0,1,0,0,0,0,0,0,0,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill - On spell hit - Spawn fire');

-- Waypoints for Zeth'Gor Quest Credit Marker, They Must Burn, Tower Foothill from sniff
DELETE FROM `waypoints` WHERE `entry`=@ENTRY;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@ENTRY,1,-978.3713,1883.556,104.3167,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 1'),
(@ENTRY,2,-974.3038,1878.926,109.6782,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 2'),
(@ENTRY,3,-974.1463,1874.819,121.9402,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 3'),
(@ENTRY,4,-982.4401,1875.441,100.4122,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 4'),
(@ENTRY,5,-975.1263,1882.178,118.0354,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 5'),
(@ENTRY,6,-979.3693,1876.667,121.5866,'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill WP 6');
-- Update Creature
UPDATE `creature` SET `curhealth`=1,`spawndist`=0,`MovementType`=0,`position_x`=-979.3693,`position_y`=1876.667,`position_z`=121.5866,`orientation`=1.186824 WHERE `guid`=78737;

-- SAI for Zeth'Gor Quest Credit Marker, They Must Burn
SET @ENTRY  := 21173; -- Zeth'Gor Quest Credit Marker, They Must Burn
SET @ENTRY1 := 21170; -- Honor Hold Gryphon Brigadier, South
SET @ENTRY2 := 22404; -- Honor Hold Gryphon Brigadier, North
SET @ENTRY3 := 22405; -- Honor Hold Gryphon Brigadier, Forge
SET @ENTRY4 := 22406; -- Honor Hold Gryphon Brigadier, Foothills
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid` IN (@ENTRY*100, (@ENTRY*100)+1, (@ENTRY*100)+2, (@ENTRY*100)+3);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
-- AI
(@ENTRY,0,0,0,38,0,100,0,0,1,0,0,80,(@ENTRY*100)+0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On dataset - load script'),
(@ENTRY,0,1,0,38,0,100,0,0,2,0,0,80,(@ENTRY*100)+1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower North - On dataset - load script'),
(@ENTRY,0,2,0,38,0,100,0,0,3,0,0,80,(@ENTRY*100)+2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Forge - On dataset - load script'),
(@ENTRY,0,3,0,38,0,100,0,0,4,0,0,80,(@ENTRY*100)+3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower Foothill - On dataset - load script'),
-- Script 0
(@ENTRY*100,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Reset data 0'),
(@ENTRY*100,9,1,0,0,0,100,0,1000,1000,0,0,11,36302,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,2,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,@ENTRY1,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,3,0,0,0,100,0,0,0,0,0,11,36302,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,4,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,19,@ENTRY1,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,5,0,0,0,100,0,0,0,0,0,11,36302,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,6,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY1,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,7,0,0,0,100,0,0,0,0,0,11,36302,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
(@ENTRY*100,9,8,0,0,0,100,0,3000,3000,0,0,45,0,4,0,0,0,0,19,@ENTRY1,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, South'),
-- Script 1
((@ENTRY*100)+1,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Reset data 0'),
((@ENTRY*100)+1,9,1,0,0,0,100,0,0,0,0,0,11,39106,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,2,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,@ENTRY2,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,3,0,0,0,100,0,0,0,0,0,11,39106,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,4,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,19,@ENTRY2,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,5,0,0,0,100,0,0,0,0,0,11,39106,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,6,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY2,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,7,0,0,0,100,0,0,0,0,0,11,39106,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
((@ENTRY*100)+1,9,8,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY2,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, North'),
-- Script 2
((@ENTRY*100)+2,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Reset data 0'),
((@ENTRY*100)+2,9,1,0,0,0,100,0,0,0,0,0,11,39107,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,2,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,@ENTRY3,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,3,0,0,0,100,0,0,0,0,0,11,39107,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,4,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,19,@ENTRY3,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,5,0,0,0,100,0,0,0,0,0,11,39107,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,6,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY3,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,7,0,0,0,100,0,0,0,0,0,11,39107,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
((@ENTRY*100)+2,9,8,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY3,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Forge'),
-- Script 3
((@ENTRY*100)+3,9,0,0,0,0,100,0,0,0,0,0,45,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Reset data 0'),
((@ENTRY*100)+3,9,1,0,0,0,100,0,0,0,0,0,11,39108,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,2,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,@ENTRY4,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,3,0,0,0,100,0,0,0,0,0,11,39108,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,4,0,0,0,100,0,3000,3000,0,0,45,0,2,0,0,0,0,19,@ENTRY4,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,5,0,0,0,100,0,0,0,0,0,11,39108,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,6,0,0,0,100,0,3000,3000,0,0,45,0,3,0,0,0,0,19,@ENTRY4,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,7,0,0,0,100,0,0,0,0,0,11,39108,0,0,0,0,0,1,0,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill'),
((@ENTRY*100)+3,9,8,0,0,0,100,0,3000,3000,0,0,45,0,1,0,0,0,0,19,@ENTRY4,0,0,0,0,0,0, ' Summon Honor Hold Gryphon Brigadier, Foothill');

-- SAI for Honor Hold Gryphon Brigadier, South
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY1;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY1,0,0,0,11,0,100,0,0,0,0,0,11,36350,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Spawn - Add aura'),
(@ENTRY1,0,1,0,38,0,100,0,0,1,0,0,53,1,@ENTRY1*100,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY1,0,2,0,38,0,100,0,0,2,0,0,53,1,(@ENTRY1*100)+1,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY1,0,3,0,38,0,100,0,0,3,0,0,53,1,(@ENTRY1*100)+2,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY1,0,4,0,38,0,100,0,0,4,0,0,53,1,(@ENTRY1*100)+3,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY1,0,5,0,40,0,100,0,10,@ENTRY1*100,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY1,0,6,0,40,0,100,0,10,(@ENTRY1*100)+1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY1,0,7,0,40,0,100,0,11,(@ENTRY1*100)+2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY1,0,8,0,40,0,100,0,11,(@ENTRY1*100)+3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn');

-- SAI for Honor Hold Gryphon Brigadier, North
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY2;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY2;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY2,0,0,0,11,0,100,0,0,0,0,0,11,36350,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Spawn - Add aura'),
(@ENTRY2,0,1,0,38,0,100,0,0,1,0,0,53,1,@ENTRY2*100,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY2,0,2,0,38,0,100,0,0,2,0,0,53,1,(@ENTRY2*100)+1,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY2,0,3,0,38,0,100,0,0,3,0,0,53,1,(@ENTRY2*100)+2,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY2,0,4,0,38,0,100,0,0,4,0,0,53,1,(@ENTRY2*100)+3,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY2,0,5,0,40,0,100,0,12,@ENTRY2*100,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY2,0,6,0,40,0,100,0,11,(@ENTRY2*100)+1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY2,0,7,0,40,0,100,0,12,(@ENTRY2*100)+2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY2,0,8,0,40,0,100,0,12,(@ENTRY2*100)+3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn');

-- SAI for Honor Hold Gryphon Brigadier, Forge
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY3;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY3;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY3,0,0,0,11,0,100,0,0,0,0,0,11,36350,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Spawn - Add aura'),
(@ENTRY3,0,1,0,38,0,100,0,0,1,0,0,53,1,@ENTRY3*100,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY3,0,2,0,38,0,100,0,0,2,0,0,53,1,(@ENTRY3*100)+1,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY3,0,3,0,38,0,100,0,0,3,0,0,53,1,(@ENTRY3*100)+2,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY3,0,4,0,38,0,100,0,0,4,0,0,53,1,(@ENTRY3*100)+3,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY3,0,5,0,40,0,100,0,13,@ENTRY3*100,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY3,0,6,0,40,0,100,0,13,(@ENTRY3*100)+1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY3,0,7,0,40,0,100,0,12,(@ENTRY3*100)+2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY3,0,8,0,40,0,100,0,14,(@ENTRY3*100)+3,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn');

-- SAI for Honor Hold Gryphon Brigadier, Foothill
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY4;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY4;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY4,0,0,0,11,0,100,0,0,0,0,0,11,36350,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Spawn - Add aura'),
(@ENTRY4,0,1,0,38,0,100,0,0,1,0,0,53,1,@ENTRY4*100,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY4,0,2,0,38,0,100,0,0,2,0,0,53,1,(@ENTRY4*100)+1,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY4,0,3,0,38,0,100,0,0,3,0,0,53,1,(@ENTRY4*100)+2,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On data set - Start WP movement'),
(@ENTRY4,0,4,0,40,0,100,0,15,@ENTRY4*100,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY4,0,5,0,40,0,100,0,15,(@ENTRY4*100)+1,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn'),
(@ENTRY4,0,6,0,40,0,100,0,15,(@ENTRY4*100)+2,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Zeth''Gor Quest Credit Marker, They Must Burn, Tower South - On Reach WP - Despawn');

-- Honor Hold Gryphon Brigadier, South Pathing
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY1*100, (@ENTRY1*100)+1, (@ENTRY1*100)+2, (@ENTRY1*100)+3);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
-- Honor Hold Gryphon Brigadier, South Path 1
(@ENTRY1*100,1,-1166.146,2232.443,154.4811,'Honor Hold Gryphon Brigadier, South Path 1 WP 1'),
(@ENTRY1*100,2,-1166.439,2233.399,154.4811,'Honor Hold Gryphon Brigadier, South Path 1 WP 2'),
(@ENTRY1*100,3,-1162.907,2207.568,140.9076,'Honor Hold Gryphon Brigadier, South Path 1 WP 3'),
(@ENTRY1*100,4,-1165.149,2160.382,126.1298,'Honor Hold Gryphon Brigadier, South Path 1 WP 4'),
(@ENTRY1*100,5,-1171.198,2119.914,110.0741,'Honor Hold Gryphon Brigadier, South Path 1 WP 5'),
(@ENTRY1*100,6,-1152.598,2108.961,101.9074,'Honor Hold Gryphon Brigadier, South Path 1 WP 6'),
(@ENTRY1*100,7,-1126.18,2129.599,118.6573,'Honor Hold Gryphon Brigadier, South Path 1 WP 7'),
(@ENTRY1*100,8,-1113.314,2146.836,135.1296,'Honor Hold Gryphon Brigadier, South Path 1 WP 8'),
(@ENTRY1*100,9,-1105.45,2173.646,171.0185,'Honor Hold Gryphon Brigadier, South Path 1 WP 9'),
(@ENTRY1*100,10,-1107.9,2202.193,195.935,'Honor Hold Gryphon Brigadier, South Path 1 WP 10'),
-- Honor Hold Gryphon Brigadier, South Path 2
((@ENTRY1*100)+1,1,-1166.146,2232.443,154.4811,'Honor Hold Gryphon Brigadier, South Path 2 WP 1'),
((@ENTRY1*100)+1,2,-1166.439,2233.399,154.4811,'Honor Hold Gryphon Brigadier, South Path 2 WP 2'),
((@ENTRY1*100)+1,3,-1182.963,2208.794,125.3797,'Honor Hold Gryphon Brigadier, South Path 2 WP 3'),
((@ENTRY1*100)+1,4,-1182.292,2161.906,114.2409,'Honor Hold Gryphon Brigadier, South Path 2 WP 4'),
((@ENTRY1*100)+1,5,-1175.9,2113.828,105.1853,'Honor Hold Gryphon Brigadier, South Path 2 WP 5'),
((@ENTRY1*100)+1,6,-1152.598,2108.961,104.5463,'Honor Hold Gryphon Brigadier, South Path 2 WP 6'),
((@ENTRY1*100)+1,7,-1126.18,2129.599,117.0184,'Honor Hold Gryphon Brigadier, South Path 2 WP 7'),
((@ENTRY1*100)+1,8,-1097.298,2159.928,136.074,'Honor Hold Gryphon Brigadier, South Path 2 WP 8'),
((@ENTRY1*100)+1,9,-1084.76,2185.17,157.8796,'Honor Hold Gryphon Brigadier, South Path 2 WP 9'),
((@ENTRY1*100)+1,10,-1074.359,2208.386,178.1295,'Honor Hold Gryphon Brigadier, South Path 2 WP 10'),
-- Honor Hold Gryphon Brigadier, South Path 3
((@ENTRY1*100)+2,1,-1166.146,2232.443,154.4811,'Honor Hold Gryphon Brigadier, South Path 3 WP 1'),
((@ENTRY1*100)+2,2,-1166.439,2233.399,154.4811,'Honor Hold Gryphon Brigadier, South Path 3 WP 2'),
((@ENTRY1*100)+2,3,-1150.548,2194.858,120.9303,'Honor Hold Gryphon Brigadier, South Path 3 WP 3'),
((@ENTRY1*100)+2,4,-1151.814,2161.048,110.9858,'Honor Hold Gryphon Brigadier, South Path 3 WP 4'),
((@ENTRY1*100)+2,5,-1152.937,2131.728,105.9581,'Honor Hold Gryphon Brigadier, South Path 3 WP 5'),
((@ENTRY1*100)+2,6,-1151.148,2107.598,99.458,'Honor Hold Gryphon Brigadier, South Path 3 WP 6'),
((@ENTRY1*100)+2,7,-1165.406,2089.037,115.6802,'Honor Hold Gryphon Brigadier, South Path 3 WP 7'),
((@ENTRY1*100)+2,8,-1174.068,2083.782,125.0691,'Honor Hold Gryphon Brigadier, South Path 3 WP 8'),
((@ENTRY1*100)+2,9,-1205.327,2083.083,164.097,'Honor Hold Gryphon Brigadier, South Path 3 WP 9'),
((@ENTRY1*100)+2,10,-1232.793,2084.872,183.4025,'Honor Hold Gryphon Brigadier, South Path 3 WP 10'),
((@ENTRY1*100)+2,11,-1264.571,2093.127,197.5136,'Honor Hold Gryphon Brigadier, South Path 3 WP 11'),
-- Honor Hold Gryphon Brigadier, South Path 4
((@ENTRY1*100)+3,1,-1166.146,2232.443,154.4811,'Honor Hold Gryphon Brigadier, South Path 4 WP 1'),
((@ENTRY1*100)+3,2,-1166.439,2233.399,154.4811,'Honor Hold Gryphon Brigadier, South Path 4 WP 2'),
((@ENTRY1*100)+3,3,-1152.79,2211.288,120.9303,'Honor Hold Gryphon Brigadier, South Path 4 WP 3'),
((@ENTRY1*100)+3,4,-1146.584,2178.448,110.9858,'Honor Hold Gryphon Brigadier, South Path 4 WP 4'),
((@ENTRY1*100)+3,5,-1155.939,2146.783,105.9581,'Honor Hold Gryphon Brigadier, South Path 4 WP 5'),
((@ENTRY1*100)+3,6,-1151.148,2107.598,99.68026,'Honor Hold Gryphon Brigadier, South Path 4 WP 6'),
((@ENTRY1*100)+3,7,-1142.785,2094.159,103.5414,'Honor Hold Gryphon Brigadier, South Path 4 WP 7'),
((@ENTRY1*100)+3,8,-1136.896,2085.377,109.1246,'Honor Hold Gryphon Brigadier, South Path 4 WP 8'),
((@ENTRY1*100)+3,9,-1119.036,2071.976,118.8748,'Honor Hold Gryphon Brigadier, South Path 4 WP 9'),
((@ENTRY1*100)+3,10,-1103.594,2050.397,128.2081,'Honor Hold Gryphon Brigadier, South Path 4 WP 10'),
((@ENTRY1*100)+3,11,-1080.568,2022.377,137.5138,'Honor Hold Gryphon Brigadier, South Path 4 WP 11');

-- Honor Hold Gryphon Brigadier, North Pathing
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY2*100, (@ENTRY2*100)+1, (@ENTRY2*100)+2, (@ENTRY2*100)+3);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
-- Honor Hold Gryphon Brigadier, North Path 1
(@ENTRY2*100,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,4,-774.873,1952.79,99.47905,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,5,-786.8572,1972.59,99.47905,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,6,-799.9429,2000.454,78.95126,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,7,-806.1043,2017.675,73.36794,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,8,-819.2725,2032.523,73.17354,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,9,-831.7571,2046.865,80.61793,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,10,-844.0977,2058.49,83.64579,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,11,-859.0389,2080.072,95.78463,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
(@ENTRY2*100,12,-883.3383,2095.611,107.5624,'Honor Hold Gryphon Brigadier, North Path 1 WP'),
-- Honor Hold Gryphon Brigadier, North Path 2
((@ENTRY2*100)+1,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,4,-773.3017,1941.179,99.47905,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,5,-792.3573,1953.981,99.47905,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,6,-812.7388,1993.078,78.95126,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,7,-823.2512,2008.549,73.36794,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,8,-823.4645,2030.833,73.17354,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,9,-812.5039,2051.152,80.61793,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,10,-775.5078,2066.004,83.64579,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
((@ENTRY2*100)+1,11,-728.4387,2072.975,87.72904,'Honor Hold Gryphon Brigadier, North Path 2 WP'),
-- Honor Hold Gryphon Brigadier, North Path 3
((@ENTRY2*100)+2,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,4,-773.3017,1941.179,99.47905,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,5,-798.551,1950.061,99.47905,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,6,-822.979,1966.302,78.95126,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,7,-829.1212,1999.823,73.36794,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,8,-823.4645,2030.833,73.17354,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,9,-822.0243,2049.509,80.61793,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,10,-838.6264,2088.113,83.64579,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,11,-857.7249,2123.352,87.72904,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
((@ENTRY2*100)+2,12,-856.7349,2157.759,99.95123,'Honor Hold Gryphon Brigadier, North Path 3 WP'),
-- Honor Hold Gryphon Brigadier, North Path 4
((@ENTRY2*100)+3,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,4,-773.3017,1941.179,99.47905,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,5,-792.3573,1953.981,99.47905,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,6,-812.7388,1993.078,78.95126,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,7,-823.2512,2008.549,73.36794,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,8,-823.4645,2030.833,73.17354,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,9,-812.5039,2051.152,80.61793,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,10,-838.6264,2088.113,83.64579,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,11,-857.7249,2123.352,87.72904,'Honor Hold Gryphon Brigadier, North Path 4 WP'),
((@ENTRY2*100)+3,12,-891.1043,2149.23,87.72904,'Honor Hold Gryphon Brigadier, North Path 4 WP');

-- Honor Hold Gryphon Brigadier, Forge Pathing
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY3*100, (@ENTRY3*100)+1, (@ENTRY3*100)+2, (@ENTRY3*100)+3);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
-- Honor Hold Gryphon Brigadier, Forge Path 1
(@ENTRY3*100,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,4,-779.0291,1934.054,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,5,-805.9227,1932.241,104.2291,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,6,-837.3495,1926.666,101.0902,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,7,-862.7343,1923.357,97.618,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,8,-897.9168,1921.757,99.59021,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,9,-914.8586,1930.438,97.67357,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,10,-932.5103,1940.806,109.0624,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,11,-945.1282,1950.602,122.7846,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,12,-966.2561,1954.868,135.8124,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
(@ENTRY3*100,13,-993.241,1956.073,157.4512,'Honor Hold Gryphon Brigadier, Forge Path 1 WP'),
-- Honor Hold Gryphon Brigadier, Forge Path 2
((@ENTRY3*100)+1,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,4,-780.6625,1927.177,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,5,-811.2864,1921.429,104.2291,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,6,-834.9781,1920.712,101.0902,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,7,-866.0516,1916.696,97.618,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,8,-895.7596,1922.273,99.59021,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,9,-923.1928,1916.771,97.67357,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,10,-948.4045,1901.38,98.9791,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,11,-966.732,1893.369,110.0068,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,12,-989.9695,1893.078,135.8124,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
((@ENTRY3*100)+1,13,-1025.913,1875.034,164.979,'Honor Hold Gryphon Brigadier, Forge Path 2 WP'),
-- Honor Hold Gryphon Brigadier, Forge Path 3
((@ENTRY3*100)+2,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,4,-773.3017,1941.179,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,5,-799.0213,1938.265,104.2291,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,6,-821.9453,1929.91,101.0902,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,7,-847.0975,1925.127,97.618,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,8,-884.1627,1919.391,99.59021,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,9,-910.0975,1918.052,97.67357,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,10,-931.7395,1901.312,98.9791,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,11,-938.8629,1883.565,110.0068,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
((@ENTRY3*100)+2,12,-948.2704,1857.24,135.8124,'Honor Hold Gryphon Brigadier, Forge Path 3 WP'),
-- Honor Hold Gryphon Brigadier, Forge Path 4
((@ENTRY3*100)+3,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,3,-750.1168,1929.094,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,4,-773.3017,1941.179,99.47905,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,5,-799.0213,1938.265,104.2291,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,6,-821.9453,1929.91,101.0902,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,7,-847.0975,1925.127,97.618,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,8,-884.1627,1919.391,99.59021,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,9,-898.5378,1920.82,97.67357,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,10,-909.0667,1943.895,98.9791,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,11,-882.7237,1983.156,110.0068,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,12,-857.6995,1997.67,135.8124,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,13,-834.7382,1999.236,151.1734,'Honor Hold Gryphon Brigadier, Forge Path 4 WP'),
((@ENTRY3*100)+3,14,-797.808,1990.238,154.7012,'Honor Hold Gryphon Brigadier, Forge Path 4 WP');

-- Honor Hold Gryphon Brigadier, Foothill Pathing
DELETE FROM `waypoints` WHERE `entry` IN (@ENTRY4*100, (@ENTRY4*100)+1, (@ENTRY4*100)+2);
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
-- Honor Hold Gryphon Brigadier, Foothill Path 1
(@ENTRY4*100,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 1'),
(@ENTRY4*100,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 2'),
(@ENTRY4*100,3,-750.1168,1929.094,115.7846,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 3'),
(@ENTRY4*100,4,-780.6038,1912.869,111.4513,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 4'),
(@ENTRY4*100,5,-812.3557,1903.761,119.8957,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 5'),
(@ENTRY4*100,6,-844.3373,1894.094,121.1179,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 6'),
(@ENTRY4*100,7,-875.8698,1888.307,134.0069,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 7'),
(@ENTRY4*100,8,-908.7481,1889.962,139.368,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 8'),
(@ENTRY4*100,9,-936.4296,1891.453,135.5625,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 9'),
(@ENTRY4*100,10,-956.9449,1888.206,129.8402,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 10'),
(@ENTRY4*100,11,-976.4232,1879.735,128.3126,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 11'),
(@ENTRY4*100,12,-999.7429,1861.678,156.9511,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 12'),
(@ENTRY4*100,13,-1019.369,1838.22,181.4233,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 13'),
(@ENTRY4*100,14,-1015.93,1818.592,198.4232,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 14'),
(@ENTRY4*100,15,-1003.392,1791.963,211.84,'Honor Hold Gryphon Brigadier, Foothill Path 1 WP 15'),
-- Honor Hold Gryphon Brigadier, Foothill Path 2
((@ENTRY4*100)+1,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 1'),
((@ENTRY4*100)+1,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 2'),
((@ENTRY4*100)+1,3,-750.1168,1929.094,115.7846,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 3'),
((@ENTRY4*100)+1,4,-780.6038,1912.869,111.4513,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 4'),
((@ENTRY4*100)+1,5,-812.3557,1903.761,119.8957,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 5'),
((@ENTRY4*100)+1,6,-844.3373,1894.094,121.1179,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 6'),
((@ENTRY4*100)+1,7,-875.8698,1888.307,134.0069,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 7'),
((@ENTRY4*100)+1,8,-905.6191,1885.849,139.368,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 8'),
((@ENTRY4*100)+1,9,-933.7491,1881.107,135.5625,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 9'),
((@ENTRY4*100)+1,10,-957.0587,1876.275,129.8402,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 10'),
((@ENTRY4*100)+1,11,-976.4232,1879.735,128.3126,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 11'),
((@ENTRY4*100)+1,12,-1001.597,1896.851,136.0901,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 12'),
((@ENTRY4*100)+1,13,-1026.942,1912.217,153.8956,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 13'),
((@ENTRY4*100)+1,14,-1046.058,1925.075,168.2844,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 14'),
((@ENTRY4*100)+1,15,-1065.902,1940.892,183.0622,'Honor Hold Gryphon Brigadier, Foothill Path 2 WP 15'),
-- Honor Hold Gryphon Brigadier, Foothill Path 3
((@ENTRY4*100)+2,1,-739.3298,1922.589,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 1'),
((@ENTRY4*100)+2,2,-738.3353,1922.693,100.9578,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 2'),
((@ENTRY4*100)+2,3,-750.1168,1929.094,115.7846,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 3'),
((@ENTRY4*100)+2,4,-780.6038,1912.869,111.4513,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 4'),
((@ENTRY4*100)+2,5,-812.3557,1903.761,119.8957,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 5'),
((@ENTRY4*100)+2,6,-852.6487,1887.492,134.7291,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 6'),
((@ENTRY4*100)+2,7,-885.8631,1878.916,144.8403,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 7'),
((@ENTRY4*100)+2,8,-910.2131,1876.215,149.118,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 8'),
((@ENTRY4*100)+2,9,-933.7659,1874.894,145.9792,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 9'),
((@ENTRY4*100)+2,10,-957.0587,1876.275,129.8402,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 10'),
((@ENTRY4*100)+2,11,-976.4232,1879.735,128.3126,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 11'),
((@ENTRY4*100)+2,12,-1003.331,1901.21,136.0901,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 12'),
((@ENTRY4*100)+2,13,-1019.146,1920.588,153.8956,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 13'),
((@ENTRY4*100)+2,14,-1035.73,1937.606,168.2844,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 14'),
((@ENTRY4*100)+2,15,-1055.794,1959.019,183.0622,'Honor Hold Gryphon Brigadier, Foothill Path 3 WP 15');
-- Pathing for Ol' Sooty Entry: 1225
SET @NPC := 8392;
SET @PATH := @NPC;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5679.014160,`position_y`=-3185.046875,`position_z`=319.508057 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`bytes2`,`mount`,`auras`) VALUES (@NPC,@PATH,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5716.181152,-3110.810791,316.686523,0,0,0,100,0),
(@PATH,2,-5716.187012,-3093.080078,325.600677,0,0,0,100,0),
(@PATH,3,-5712.214355,-3090.297607,327.738647,0,0,0,100,0),
(@PATH,4,-5705.484375,-3092.523438,329.362366,0,0,0,100,0),
(@PATH,5,-5681.826660,-3110.568848,338.121887,0,0,0,100,0),
(@PATH,6,-5659.498535,-3122.215576,344.336151,0,0,0,100,0),
(@PATH,7,-5639.585938,-3124.536133,348.404938,0,0,0,100,0),
(@PATH,8,-5618.112793,-3110.905762,360.618225,0,0,0,100,0),
(@PATH,9,-5621.486816,-3096.315918,368.247772,0,0,0,100,0),
(@PATH,10,-5632.212891,-3078.608398,374.990936,0,0,0,100,0),
(@PATH,11,-5629.793457,-3056.124023,384.465576,0,0,0,100,0),
(@PATH,12,-5642.278809,-3036.872314,385.471649,0,0,0,100,0),
(@PATH,13,-5609.369141,-3006.883301,386.288177,0,0,0,100,0),
(@PATH,14,-5643.634277,-3036.388672,385.531891,0,0,0,100,0),
(@PATH,15,-5630.174805,-3057.015869,384.385712,0,0,0,100,0),
(@PATH,16,-5629.840332,-3065.496338,381.129578,0,0,0,100,0),
(@PATH,17,-5634.866211,-3078.448975,374.489044,0,0,0,100,0),
(@PATH,18,-5620.416504,-3101.081543,364.819855,0,0,0,100,0),
(@PATH,19,-5624.629395,-3117.040527,354.493805,0,0,0,100,0),
(@PATH,20,-5644.949707,-3125.081787,347.271362,0,0,0,100,0),
(@PATH,21,-5660.741699,-3121.580566,343.975922,0,0,0,100,0),
(@PATH,22,-5676.210938,-3111.586914,340.021484,0,0,0,100,0),
(@PATH,23,-5691.895508,-3102.994385,333.646698,0,0,0,100,0),
(@PATH,24,-5711.662109,-3088.433594,328.761566,0,0,0,100,0),
(@PATH,25,-5717.663574,-3099.033691,321.686920,0,0,0,100,0),
(@PATH,26,-5705.214844,-3132.324219,315.837585,0,0,0,100,0),
(@PATH,27,-5679.014160,-3185.046875,319.508057,0,0,0,100,0);
-- Thargold Ironwing SAI
SET @ENTRY  := 29154;
SET @GOSSIP := 9776;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,11,53335,1,0,0,0,0,7,0,0,0,0,0,0,0, 'Thargold Ironwing - On gossip option select - cast spell'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0, 'Thargold Ironwing - On gossip option select - close gossip');
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (10062,10063,10054,10055,10046,10047,10048,10049,10050,10051,10044,10045);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(10062,12,0,0, 'achievement_quick_shave'),
(10063,12,1,0, 'achievement_quick_shave'),
(10044,12,0,0, 'achievement_unbroken'),
(10045,12,1,0, 'achievement_unbroken'),
(10054,12,0,0, 'achievement_shutout'),
(10055,12,1,0, 'achievement_shutout'),
(10046,12,0,0, 'achievement_three_car_garage_chopper'),
(10047,12,0,0, 'achievement_three_car_garage_siege'),
(10048,12,0,0, 'achievement_three_car_garage_demolisher'),
(10049,12,1,0, 'achievement_three_car_garage_chopper'),
(10050,12,1,0, 'achievement_three_car_garage_siege'),
(10051,12,1,0, 'achievement_three_car_garage_demolisher'),
(10062,11,0,0, 'achievement_quick_shave'),
(10063,11,0,0, 'achievement_quick_shave'),
(10044,11,0,0, 'achievement_unbroken'),
(10045,11,0,0, 'achievement_unbroken'),
(10054,11,0,0, 'achievement_shutout'),
(10055,11,0,0, 'achievement_shutout'),
(10046,11,0,0, 'achievement_three_car_garage_chopper'),
(10047,11,0,0, 'achievement_three_car_garage_siege'),
(10048,11,0,0, 'achievement_three_car_garage_demolisher'),
(10049,11,0,0, 'achievement_three_car_garage_chopper'),
(10050,11,0,0, 'achievement_three_car_garage_siege'),
(10051,11,0,0, 'achievement_three_car_garage_demolisher');
DELETE FROM `creature_text` WHERE `entry` IN (32295,28859);
INSERT INTO `creature_text` (entry,groupid,id,text,type,language,sound,comment) VALUE
(28859,0,0,'My patience has reached its limit, I will be rid of you!',1,0,14517,'Malygos - Aggro (Phase 1)'),
(28859,1,0,'Your stupidity has finally caught up to you',1,0,14519,'Malygos - Killed Player (1) (Phase 1)'),
(28859,1,1,'More artifacts to confiscate...',1,0,14520,'Malygos - Killed Player (2) (Phase 1)'),
(28859,1,2,'<Laughs> How very... naive...',1,0,14521,'Malygos - Killed Player (3) (Phase 1)'),
(28859,2,0,'I had hoped to end your lives quickly, but you have proven more... resilient then I had anticipated. Nonetheless, your efforts are in vain, it is you reckless, careless mortals who are to blame for this war! I do what I must... And if it means your... extinction... THEN SO BE IT',1,0,14522,'Malygos - End Phase One'),
(28859,3,0,'Few have experienced the pain I will now inflict upon you!',1,0,14523,'Malygos - Aggro (Phase 2)'),
(28859,4,0,'I will teach you IGNORANT children just how little you know of magic...',1,0,14524,'Malygos - Anti-Magic Shell'),
(28859,5,0,'Watch helplessly as your hopes are swept away...',1,0,14525,'Malygos - Magic Blast'),
(28859,6,0,'Your energy will be put to good use!',1,0,14526,'Malygos - Killed Player 1 (Phase 2)'),
(28859,6,1,'I am the spell-weaver! My power is infinite!',1,0,14527,'Malygos - Killed Player 2 (Phase 2)'),
(28859,6,2,'Your spirit will linger here forever!',1,0,14528,'Malygos - Killed Player 3 (Phase 2)'),
(28859,7,0,'ENOUGH! If you intend to reclaim Azeroth''s magic, then you shall have it...',1,0,14529,'Malygos - End Phase 2'),
(28859,8,0,'Now your benefactors make their appearance... But they are too late. The powers contained here are sufficient to destroy the world ten times over! What do you think they will do to you?',1,0,14530,'Intro Phase 3'),
(28859,9,0,'SUBMIT!',1,0,14531,'Malygos - Aggro (Phase 3)'),
(28859,10,0,'The powers at work here exceed anything you could possibly imagine!',1,0,14532,'Malygos - Surge of Power'),
(28859,11,0,'I AM UNSTOPPABLE!',1,0,14533,'Malygos - Buffed by a spark'),
(28859,12,0,'Alexstrasza! Another of your brood falls!',1,0,14534,'Malygos - Killed Player 1 (Phase 3)'),
(28859,12,1,'Little more then gnats!',1,0,14535,'Malygos - Killed Player 2 (Phase 3)'),
(28859,12,2,'Your red allies will share your fate...',1,0,14536,'Malygos - Killed Player 3 (Phase 3)'),
(28859,13,0,'Still standing? Not for long...',1,0,14537,'Malygos - Spell Casting 1(Phase 3)'),
(28859,13,1,'Your cause is lost',1,0,14538,'Malygos - Spell Casting 2 (Phase 3)'),
(28859,13,2,'Your fragile mind will be shattered!',1,0,14539,'Malygos - Spell Casting 3 (Phase 3)'),
(28859,14,0,'Unthinkable! The mortals will destroy... everything... my sister... what have you...',1,0,0,'Malygos - Death'),
(32295,0,0,'I did what I had to, brother. You gave me no alternative.',1,0,0,'Alexstrasza - Yell One'),
(32295,1,0,'And so ends the Nexus War.',1,0,0,'Alexstrasza - Yell Two'),
(32295,2,0,'This resolution pains me deeply, but the destruction, the monumental loss of life had to end. Regardless of Malygos'' recent transgressions, I will mourn his loss. He was once a guardian, a protector. This day, one of the world''s mightiest has fallen.',1,0,0,'Alexstrasza - Yell Three'),
(32295,3,0,'The red dragonflight will take on the burden of mending the devastation wrought on Azeroth. Return home to your people and rest. Tomorrow will bring you new challenges, and you must be ready to face them. Life... goes on.',1,0,0,'Alexstrasza - Yell Four');



SET @CGuid = 208901; -- (Set by TDB team - creature.guid - need X)
SET @GGuid = 151829; -- (Set by TDB team - gameobject.guid - need X)
SET @EquiEntry = 2433; -- (Set by TDB team - creature_equip_template.entry - need X)
SET @Gossip = 21257; -- (Set by TDB team - gossip_menu.entry - need 1)
SET @Event = 61; -- (Set by TDB team - game_event.entry - need 1)
-- Creature enums
SET @N_Vanira = 40184; -- Vanira
SET @N_VaniraTotem = 40187; -- Vanira's Sentry Totem
SET @N_Frog = 40176; -- Sen'jin Frog
SET @N_AtunnedFrog = 40188; -- Atunned Frog
SET @N_Voljin = 40391; -- Vol'jin
SET @N_Uruzin = 40253; -- Champion Uru'zin
SET @N_VoljinBoss = 39654; -- Vol'jin (on the island, starts fight)
SET @N_BatHandler = 40204; -- Handler Marnlek
SET @N_Bat = 40222; -- Scout Bat
SET @N_SpyFrogCredit = 40218; -- Spy Frog Credit
SET @N_TigerCredit = 40301; -- Tiger Matriarch Credit
SET @N_TigerSpirit = 40305; -- Spirit of the Tiger
SET @N_Matriarch = 40312; -- Tiger Matriarch (casts 75163 (Vicious Bite), 61184 (Pounce), 75159 (Claw))
SET @N_Zentabra = 40329; -- Zen'tabra
SET @N_DWarrior = 40392; -- Darkspear Warrior
SET @N_DScout = 40416; -- Darkspear Scout
SET @N_Citizien1 = 40256; -- Troll Citizien (1)
SET @N_Citizien2 = 40257; -- Troll Citizien (2)
SET @N_Volunteer1 = 40260; -- Troll Volunteer
SET @N_Volunteer2 = 40264; -- Troll Volunteer
SET @N_RDancer = 40356; -- Ritual Dancer
SET @N_TDanceleader = 40361; -- Troll Dance Leader
SET @N_DancePart = 40363; -- Dance Participant
SET @N_RDrummer = 40373; -- Ritual Drummer
SET @N_Omen = 40387; -- Omen Event Credit
SET @N_DAncestor = 40388; -- Darkspear Ancestor
SET @N_Voice = 40374; -- Voice of the Spirits
SET @N_Doctor = 40352; -- Witch Doctor Hez'tok
-- Gameobject enums
SET @G_BatTotem = 202833; -- Sen'jin Bat Totem
SET @G_BatStraw = 202834; -- Sen'jin Bat Roost Straw
SET @G_BatFence = 202835; -- Sen'jin Bat Roost Fence
SET @G_BatPost = 202839; -- Sen'jin Bat Roost Fence Post
SET @G_RDrum = 202879; -- Ritual Drum
SET @G_RGong = 202880; -- Ritual Gong
SET @G_RBrazier = 202881; -- Ritual Brazier
SET @G_SRDrum = 202882; -- Small Ritual Drum
SET @G_SRDrum2 = 202883; -- Small Ritual Drum 2
SET @G_Banner = 202885; -- Sen'jin Banner
SET @G_Tent = 202886; -- Sen'jin Tent
SET @G_Table = 202888; -- Sen'jin Table
SET @G_Book1 = 202889; -- Troll Book 1
SET @G_Book2 = 202890; -- Troll Book 2
SET @G_CCrate = 202891; -- Closed Weapon Crate
SET @G_OCrate = 202892; -- Open Weapon Crate
SET @G_SPennant = 202893; -- Sen'jin Pennant
-- Quest enums
SET @Q_DaPerfectSpies = 25444; -- Da Perfect Spies
SET @Q_FrogsAway = 25446; -- Frogs Away!
SET @Q_LadyOfDaTigers = 25470; -- Lady Of Da Tigers
SET @Q_DanceOfDeSpirits = 25480; -- Dance Of De Spirits
SET @Q_TrollinForVolunteers = 25461; -- Trollin' For Volunteers
SET @Q_PreparinForBattle = 25495; -- Preparin For Battle
SET @Q_ZalazanesFall = 25445; -- Zalazane's Fall
-- Spell enums
SET @S_Pickup = 74904; -- Pickup Sen'jin Frog [player -> creature]
SET @S_Pickup2 = 74905; -- Pickup Sen'jin Frog [creature -> player]
SET @S_InvsAura = 75433; -- Spawn Invisibility Aura (QZS 2)
SET @S_FrogsAway = 74977; -- Frogs Away!
SET @S_SeeSenjinFrogInvs = 75434; -- See Sen'jin Frog Invis
SET @S_SeeSpyFrogInvs =74982; -- See Spy Frog Invisibility
SET @S_Taxi_Frog = 74978; -- Echo Isles: Unlearned Spy Frog Taxi
SET @S_Taxi_Troll = 75421; -- Echo Isles: Unlearned Troll Recruit Taxi
SET @S_Taxi_Battle = 75422; -- Echo Isles: Unlearned Troll Battle Taxi
SET @S_SpyFrogInvs = 74980; -- Spy Frog Invisibility
SET @S_SmokeFlare = 74971; -- Red Flare State
SET @S_VisualSpawn = 31517; -- Bind Visual Spawn In DND
SET @S_SpyFrogState = 74917; -- Spy Frog State
SET @S_RideVehicle = 46598; -- Ride Vehicle Hardcoded
SET @S_Tiger = 75147; -- Spirit of the Tiger
SET @S_ForceTiger = 75186; -- Force Cast Spirit of the Tiger
SET @S_NatVisual = 60957; -- Cosmetic Nature Cast
SET @S_TigerAura = 75165; -- Spirit of the Tiger Aura
SET @S_TigerSeeInvs = 75180; -- Detect QZS 3
SET @S_TigerGhost = 22650; -- Ghost Visual
SET @S_BossEmotePAura =75213; -- Boss Emote & No Summon Aura
SET @S_TigerCredit = 40301; -- OCW TOTE On Quest Check (what?)
SET @S_MatriarchShroud = 75179; -- Matriarch's Shroud
SET @S_TigerQuestCredit = 75197; -- Zen'tabra Credit
SET @S_MatriarchSummonF = 75188; -- Force Cast Summon Tiger Matriarch
SET @S_MatriarchSummon = 75187; -- Summon Tiger Matriarch
SET @S_ZentabraSummon = 75181; -- Summon Zen'tabra
SET @S_ZentabraController = 75212; -- Controller Summon Zen'tabra Trigger
SET @S_ZentrabaSmoke = 36747; -- Spawn Smoke (Druid)
SET @S_ZentrabaTransform = 74931; -- [DND] Tiger Transform
SET @S_VolunterSummon1 = 75088; -- Motivate
SET @S_VolunterSummon2 = 75086; -- Motivate
-- Item enums
SET @I_VoljinDrums = 54215; -- Voljin Drums Questitem
UPDATE `creature_template` SET `spell1`=75159,`spell2`=75160,`spell3`=75161,`faction_A`=35,`faction_H`=35,`exp`=2,`minlevel`=80,`maxlevel`=80,`baseattacktime`=2500,`unit_flags`=`unit_flags`|16777224,`unit_class`=4,`speed_walk`=2.8,`speed_run`=1.5714285714286,`vehicleid`=736,`attackpower`=1167 WHERE `entry`=@N_TigerSpirit; -- Spirit of the Tiger CHECKME: speed_run and speed_walk
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN (@N_Frog,@N_TigerSpirit);
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(@N_Frog,@S_Pickup,@Q_DaPerfectSpies,1,@Q_DaPerfectSpies,1,0,0,0),
(@N_Frog,@S_Pickup2,@Q_DaPerfectSpies,1,@Q_DaPerfectSpies,3,0,0,0),
(@N_TigerSpirit,@S_RideVehicle,0,0,0,1,0,0,0); -- Spirit of the Tiger - Ride Vehicle Hardcoded
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@N_Frog,@N_AtunnedFrog,@N_Vanira,@N_Zentabra,@N_DScout,@N_Citizien1,@N_Citizien2,@N_Doctor,@N_DancePart,@N_RDrummer) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (@N_Vanira*100,@N_Zentabra*100,@N_DScout*100,@N_Doctor*100) AND `source_type`=9;
INSERT INTO `smart_scripts`(`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`)VALUES
(@N_Frog,0,0,0,8,0,100,0,@S_Pickup,0,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Echo Isles: Senjin Frog - add aura'),
(@N_AtunnedFrog,0,0,0,54,0,100,0,0,0,0,0,33,@N_SpyFrogCredit,0,0,0,0,0,0,0,0,0,0,0,0,0, 'Echo Isles: Spy Frog Killcredit'), -- FIXME: should be replaced by proper flare targeting
(@N_AtunnedFrog,0,1,0,25,0,100,0,0,0,0,0,89,5,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Attuned Frog: On reset set random movement'),
(@N_Vanira,0,0,0,19,0,100,0,@Q_LadyOfDaTigers,0,0,0,80,@N_Vanira*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Echo Isles: On quest accept run script'),
(@N_Vanira*100,9,0,0,0,0,100,0,0,0,0,0,11,@S_ForceTiger,0,0,0,0,0,7,0,0,0,0,0,0,0,'Echo Isles: Cast Force Tiger on player'),
(@N_Vanira*100,9,1,0,0,0,100,0,0,0,0,0,11,@S_NatVisual,0,0,0,0,0,1,0,0,0,0,0,0,0,'Echo Isles: Cast Nature Visual on self'),
(@N_Vanira*100,9,2,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Echo Isles: Say Text 0'),
(@N_Vanira*100,9,3,0,0,0,100,0,500,500,0,0,86,75165,0,22,0,0,0,1,0,0,0,0,0,0,0,'Echo Isles: Force Tiger cast 75165 on self'),
(@N_Zentabra,0,0,0,25,0,100,0,0,0,0,0,80,@N_Zentabra*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Call actionlist on spawn'),
(@N_Zentabra*100,9,0,0,0,0,100,0,0,0,0,0,66,0,0,0,0,0,0,23,0,0,0,0,0,0,0, 'Set orientation to player'),
(@N_Zentabra*100,9,1,0,0,0,100,0,0,0,0,0,11,@S_ZentrabaSmoke,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast spawn smoke effect on self'),
(@N_Zentabra*100,9,2,0,0,0,100,0,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 0'),
(@N_Zentabra*100,9,3,0,0,0,100,0,1500,1500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 1'),
(@N_Zentabra*100,9,4,0,0,0,100,0,5500,5500,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 2'),
(@N_Zentabra*100,9,5,0,0,0,100,0,5500,5500,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 3'),
(@N_Zentabra*100,9,6,0,0,0,100,0,5500,5500,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Say text 4'),
(@N_Zentabra*100,9,7,0,0,0,100,0,0,0,0,0,33,@N_TigerCredit,0,0,0,0,0,23,0,0,0,0,0,0,0, 'Award kill credit to player'),
(@N_Zentabra*100,9,8,0,0,0,100,0,5500,5500,0,0,11,@S_ZentrabaTransform,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Cast tiger transform on self'),
(@N_Zentabra*100,9,9,0,0,0,100,0,100,100,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Set run on self'),
(@N_Zentabra*100,9,10,0,0,0,100,0,0,0,0,0,46,10,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Move self forward 10 yards'),
(@N_Zentabra*100,9,11,0,0,0,100,0,600,600,0,0,41,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Despawn self'),
(@N_DScout,0,0,0,25,0,100,0,0,0,0,0,53,1,@N_DScout,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Start waypath on spawn'),
(@N_DScout,0,1,0,40,0,100,0,1,@N_DScout,0,0,60,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Set fly = 0 on waypoint 1'),
(@N_DScout,0,2,0,40,0,100,0,1,@N_DScout,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Set run = 0 on waypoint 1'),
(@N_DScout,0,3,0,40,0,100,0,1,@N_DScout,0,0,43,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Unmount on waypoint 1'),
(@N_DScout,0,4,0,40,0,100,0,6,@N_DScout,0,0,54,15000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Pause waypoint on waypoint 6'),
(@N_DScout,0,5,0,40,0,100,0,6,@N_DScout,0,0,66,0,0,0,0,0,0,1,0,0,0,0,0,0,0.820305, 'Darkspear Scout: Change orientation on waypoint 6'),
(@N_DScout,0,6,0,40,0,100,0,6,@N_DScout,0,0,80,@N_DScout*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Run script on waypoint 6'),
(@N_DScout,0,7,0,40,0,100,0,9,@N_DScout,0,0,41,500,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Despawn on waypoint 9'),
(@N_DScout*100,9,0,0,0,0,100,0,0,0,0,0,10,1,2,5,66,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Random emote 1,2,5,66'),
(@N_DScout*100,9,1,0,0,0,50,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Random text'),
(@N_DScout*100,9,2,0,0,0,50,0,1000,1000,0,0,1,0,0,0,0,0,0,9,@N_Voljin,0,15,0,0,0,0, 'Vol''Jin: Reply to Darkspear Scout'),
(@N_DScout*100,9,3,0,0,0,100,0,2000,2000,0,0,10,1,2,5,66,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Random emote 1,2,5,66'),
(@N_DScout*100,9,4,0,0,0,100,0,6000,6000,0,0,10,1,2,5,66,0,0,1,0,0,0,0,0,0,0, 'Darkspear Scout: Random emote 1,2,5,66'),
(@N_Citizien1,0,0,0,8,0,100,0,@S_VolunterSummon1,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Echo Isles: On spellhit - force despawn'),
(@N_Citizien2,0,0,0,8,0,100,0,@S_VolunterSummon2,0,0,0,41,1000,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Echo Isles: On spellhit - force despawn'),
(@N_Doctor, 0,0,0,62,0,0,0,@Gossip+0,0,0,0,80,@N_Doctor*100,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - On gossip select start script'),
(@N_Doctor*100,9,0,0,0,0,100,0,0,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Remove gossip flag'),
(@N_Doctor*100,9,1,0,0,0,100,0,1500,1500,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 0'),
(@N_Doctor*100,9,2,0,0,0,100,0,1000,1000,0,0,12,@N_RDrummer,1,50000,0,0,0,8,0,0,0,-812.137,-4986.7,17.3759,5.89921, 'Witch Doctor Hez''tok - Summon Ritual Drummer (1)'),
(@N_Doctor*100,9,3,0,0,0,100,0,0,0,0,0,12,@N_RDrummer,1,50000,0,0,0,8,0,0,0,-798.187,-4985.52,17.7904,4.41568, 'Witch Doctor Hez''tok - Summon Ritual Drummer (2)'),
(@N_Doctor*100,9,4,0,0,0,100,0,0,0,0,0,12,@N_RDrummer,1,50000,0,0,0,8,0,0,0,-799.888,-4975.01,17.9325,0.942478, 'Witch Doctor Hez''tok - Summon Ritual Drummer (3)'),
(@N_Doctor*100,9,5,0,0,0,100,0,3500,3500,0,0,69,0,0,0,0,0,0,8,0,0,0,-806.2,-4989.5,17.5177,0, 'Witch Doctor Hez''tok - Move to pos'),
(@N_Doctor*100,9,6,0,0,0,100,0,6500,6500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 1'),
(@N_Doctor*100,9,7,0,0,0,100,0,5500,5500,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 2'),
(@N_Doctor*100,9,8,0,0,0,100,0,3500,3500,0,0,5,25,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,9,0,0,0,100,0,3500,3500,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 3'),
(@N_Doctor*100,9,10,0,0,0,100,0,2500,2500,0,0,5,6,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,11,0,0,0,100,0,5000,5000,0,0,11,56745,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Drink Alcohol self'),
(@N_Doctor*100,9,12,0,0,0,100,0,600,600,0,0,11,29389,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Firebreathing self'),
(@N_Doctor*100,9,13,0,0,0,100,0,4000,4000,0,0,90,8,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Set bytes1 kneel state'),
(@N_Doctor*100,9,14,0,0,0,100,0,1000,1000,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-805.8477,-5003.044,20.18328,5.89921, 'Witch Doctor Hez''tok - Summon Dance Participant (1)'),
(@N_Doctor*100,9,15,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-801.0605,-4998.501,18.59358,4.41568, 'Witch Doctor Hez''tok - Summon Dance Participant (2)'),
(@N_Doctor*100,9,16,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-808.2397,-4985.208,19.54311,0.942478, 'Witch Doctor Hez''tok - Summon Dance Participant (3)'),
(@N_Doctor*100,9,17,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-799.2618,-4994.353,19.61933,5.89921, 'Witch Doctor Hez''tok - Summon Dance Participant (4)'),
(@N_Doctor*100,9,18,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-797.8184,-4986.597,21.60157,4.41568, 'Witch Doctor Hez''tok - Summon Dance Participant (5)'),
(@N_Doctor*100,9,19,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-805.1284,-4987.553,18.79003,0.942478, 'Witch Doctor Hez''tok - Summon Dance Participant (6)'),
(@N_Doctor*100,9,20,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-814.1109,-5001.676,19.44409,5.89921, 'Witch Doctor Hez''tok - Summon Dance Participant (7)'),
(@N_Doctor*100,9,21,0,0,0,100,0,0,0,0,0,12,@N_DancePart,1,40000,0,0,0,8,0,0,0,-795.7561,-4993.671,21.80729,5.89921, 'Witch Doctor Hez''tok - Summon Dance Participant (8)'),
(@N_Doctor*100,9,22,0,0,0,100,0,1000,1000,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-790.217041,-4999.733,17.171814,2.84488654, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (1)'),
(@N_Doctor*100,9,23,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-792.0052,-4994.14258,17.4839725,2.70526028, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (2)'),
(@N_Doctor*100,9,24,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-795.2049,-5003.078,17.716095,2.46091413, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (3)'),
(@N_Doctor*100,9,25,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-799.2274,-5005.68066,16.6322536,2.11184835, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (4)'),
(@N_Doctor*100,9,26,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-799.2557,-4990.76172,17.6279469,2.70527148, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (5)'),
(@N_Doctor*100,9,27,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-801.422058,-4998.04346,17.0008545,2.46088934, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (6)'),
(@N_Doctor*100,9,28,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-805.4358,-5002.88525,16.544487,1.727876, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (7)'),
(@N_Doctor*100,9,29,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-807.135,-4997.469,17.0008545,1.15000379, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (8)'),
(@N_Doctor*100,9,30,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-810.3698,-4993.825,17.1258545,0.808653831, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (9)'),
(@N_Doctor*100,9,31,0,0,0,100,0,0,0,0,0,12,@N_DAncestor,1,40000,0,0,0,8,0,0,0,-810.3889,-5004.778,16.12407,1.15191734, 'Witch Doctor Hez''tok - Summon Darkspear Ancestor (10)'),
(@N_Doctor*100,9,32,0,0,0,100,0,7000,7000,0,0,11,70663,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Shadow Nova self'),
(@N_Doctor*100,9,33,0,0,0,100,0,0,0,0,0,11,31309,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Spirit Particles self'),
(@N_Doctor*100,9,34,0,0,0,100,0,0,0,0,0,91,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Set bytes1 none'),
(@N_Doctor*100,9,35,0,0,0,100,0,100,100,0,0,3,@N_Voice,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Change entry to Voice of the Spirits'),
(@N_Doctor*100,9,36,0,0,0,100,0,100,100,0,0,3,0,31819,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Change model to Voice of the Spirits'),
(@N_Doctor*100,9,37,0,0,0,100,0,1000,1000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 4'),
(@N_Doctor*100,9,38,0,0,0,100,0,4000,4000,0,0,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 5'),
(@N_Doctor*100,9,39,0,0,0,100,0,3000,3000,0,0,5,25,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,40,0,0,0,100,0,3500,3500,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 6'),
(@N_Doctor*100,9,41,0,0,0,100,0,6000,6000,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 7'),
(@N_Doctor*100,9,42,0,0,0,100,0,4500,4500,0,0,5,274,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,43,0,0,0,100,0,5000,5000,0,0,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 8'),
(@N_Doctor*100,9,44,0,0,0,100,0,4500,4500,0,0,5,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,45,0,0,0,100,0,5500,5500,0,0,11,70663,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Shadow Nova self'),
(@N_Doctor*100,9,46,0,0,0,100,0,100,100,0,0,28,31309,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Remove aura Spirit Particles'),
(@N_Doctor*100,9,47,0,0,0,100,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Change entry and model to Witch Doctor Hez''tok'),
(@N_Doctor*100,9,48,0,0,0,100,0,4000,4000,0,0,1,9,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Say text 9'),
(@N_Doctor*100,9,49,0,0,0,100,0,2500,2500,0,0,5,2,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Do emote'),
(@N_Doctor*100,9,50,0,0,0,100,0,0,0,0,0,85,75319,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Omen Event Credit invoker'), -- working
-- (@N_Doctor*100,9,50,0,0,0,100,0,0,0,0,0,11,75319,2,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Cast Omen Event Credit self'), -- how it shold be but not working
(@N_Doctor*100,9,51,0,0,0,100,0,5000,5000,0,0,69,0,0,0,0,0,0,8,0,0,0,-805.0104,-4975.75,17.75085,0, 'Witch Doctor Hez''tok - Move to pos'),
(@N_Doctor*100,9,52,0,0,0,100,0,5000,5000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,4.625123, 'Witch Doctor Hez''tok - Change orientation'),
(@N_Doctor*100,9,53,0,0,0,100,0,2000,2000,0,0,82,1,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Witch Doctor Hez''tok - Enable gossip flag'),
(@N_DancePart,0,0,0,25,0,100,0,0,0,0,0,89,10,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Dance Participant - On reset set random movement'),
(@N_DancePart,0,1,0,25,0,100,0,0,0,0,0,3,0,22769,0,0,0,0,1,0,0,0,0,0,0,0, 'Dance Participant - On reset set model'),
(@N_RDrummer,0,0,0,1,0,100,0,0,0,1000,2000,5,38,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Ritual Drummer - Play emote attack 2h every 1 or 2 secs'),
(@N_RDrummer,0,1,0,1,0,100,0,0,0,5000,5000,11,75313,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Ritual Drummer - Cast Bang Ritual Gong every 5 seconds'),
(@N_RDrummer,0,2,0,1,0,100,1,4000,4000,0,0,4,7294,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Ritual Drummer - Play TrollDrumLoop after 4 seconds of spawn - not repeteable'),
(@N_RDrummer,0,3,0,1,0,100,0,0,0,30000,30000,4,7294,0,0,0,0,0,1,0,0,0,0,0,0,0, 'Ritual Drummer - Play Drumms sound every 30 secs');

DELETE FROM `creature_text` WHERE `entry` IN (@N_Vanira,@N_Zentabra,@N_Volunteer1,@N_Volunteer2,@N_Matriarch,@N_TigerCredit,@N_Doctor,@N_DScout,@N_Voljin);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@N_Vanira,0,0, 'O spirit of de tigers, lend $N your power and help us find de answers we seek!',0,0,100,5,0,0, 'Vanira'),
(@N_Zentabra,0,0, 'Dat be enough for now!',0,0,100,25,0,0, 'Zen''tabra'),
(@N_Zentabra,1,0, 'Don''t be lookin'' so surprised. Your shaman friend has sharp eyes, or should I say, sharp frogs.',0,0,100,1,0,0, 'Zen''tabra'),
(@N_Zentabra,2,0, 'My kind, da druids, we been layin'' low for some time now. We been waitin'' to see when an'' if Vol''jin might return.',0,0,100,11,0,0, 'Zen''tabra'),
(@N_Zentabra,3,0, 'Now dat it looks like de Darkspear be returnin'' to these isles, maybe de time has come for us to reveal ourselves.',0,0,100,1,0,0, 'Zen''tabra'),
(@N_Zentabra,4,0, 'Go back to Vol''jin an'' tell him dis: Zen''tabra stands ready to help him in de coming battle.',0,0,100,1,0,0, 'Zen''tabra'),
(@N_Volunteer1,0,0, 'Sign me up!',0,0,100,66,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer1,0,1, 'Anythin'' for Vol''jin!',0,0,100,0,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer1,0,2, 'I''d be glad to help.',0,0,100,273,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer1,0,3, 'Just point me at de enemy!',0,0,100,66,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer2,0,0, 'Sign me up!',0,0,100,66,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer2,0,1, 'Anythin'' for Vol''jin!',0,0,100,0,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer2,0,2, 'I''d be glad to help.',0,0,100,273,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer2,0,3, 'Just point me at de enemy!',0,0,100,66,0,0, 'Troll Volunteer JustSpawned'),
(@N_Volunteer1,1,0, 'Reportin'' for duty.',0,0,100,66,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer1,1,1, 'Ready to take de fight to Zalazane.',0,0,100,1,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer1,1,2, 'Ready to fight beside Vol''jin!',0,0,100,66,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer1,1,3, 'New troll here!',0,0,100,0,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer1,1,4, 'When does de trainin'' start?',0,0,100,6,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer2,1,0, 'Reportin'' for duty.',0,0,100,66,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer2,1,1, 'Ready to take de fight to Zalazane.',0,0,100,1,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer2,1,2, 'Ready to fight beside Vol''jin!',0,0,100,66,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer2,1,3, 'New troll here!',0,0,100,0,0,0, 'Troll Volunteer Quest Turn in'),
(@N_Volunteer2,1,4, 'When does de trainin'' start?',0,0,100,6,0,0, 'Troll Volunteer Quest Turn in'),
(@N_TigerCredit,0,0, 'The tiger matriarch appears! Prove yourself in combat!',3,0,100,0,0,0, 'Tiger Matriarch Credit'),
(@N_Doctor,0,0, 'Darkspears, we consult de spirits! Drummers, take your places!' ,0,0,100,25,0,0, 'Witch Doctor Hez''tok' ),
(@N_Doctor,1,0, 'Spirits, we be gathered here to ask for your guidance.' ,0,0,100,5,0,0, 'Witch Doctor Hez''tok' ),
(@N_Doctor,2,0, 'Our leader, Vol''jin, son of Sen''jin, issued de call to all Darkspears: reclaim de Echo Isles for our tribe.' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,3,0, 'Spirits! I offer me own body to you! Speak through me! Is de time right for mighty Vol''jin''s undertaking?' ,0,0,100,5,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,4,0, 'De ancestors hear ya, witch doctor!' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,5,0, 'Know dat your plans please us, Darkspears. De son of Sen''jin walks de right path.' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,6,0, 'De task in front of ya will not be easy, but ya have our blessin''.' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,7,0, 'Ya gave up your home an'' ya gave up de loas of your ancestors when ya left de Echo Isles. Dey will not be pleased dat you been ignorin'' dem.' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,8,0, 'Ya must make amends wit'' Bwonsamdi, de guardian of de dead, if ya hope to defeat Zalazane. It be de only way. Tell de son of Sen''jin dese things.' ,0,0,100,1,0,0, 'Witch Doctor Hez''tok'),
(@N_Doctor,9,0, 'De spirits have blessed us wit'' an answer! De Echo Isles will be ours again!' ,0,0,100,5,0,0, 'Witch Doctor Hez''tok'),
(@N_DScout,0,0, 'He got a big army, an'' he be plannin'' somethin'' down dere.' ,0,0,100,1,0,0, 'Darkspear Scout'),
(@N_DScout,0,1, 'Zalazane got most of his hexes trolls hidden under de canopy on de big island.' ,0,0,100,1,0,0, 'Darkspear Scout'),
(@N_Voljin,0,0, 'Thank ya, scout. Keep up da patrols. But for now, a rest is in order. Dismissed.' ,0,0,100,1,0,0, 'Vol''jin');
DELETE FROM `waypoints` WHERE `entry`=@N_DScout;
INSERT INTO `waypoints` (`entry`,`pointid`,`position_x`,`position_y`,`position_z`,`point_comment`) VALUES
(@N_DScout,1,-838.1788,-4989.835,14.93872, ''),
(@N_DScout,2,-829.3889,-4999.125,15.50085, ''),
(@N_DScout,3,-808.0018,-5010.587,15.36734, ''),
(@N_DScout,4,-796.1736,-5009.604,16.01879, ''),
(@N_DScout,5,-782.4566,-5002.518,17.26879, ''),
(@N_DScout,6,-758.7136,-5001.088,19.65562, 'Run script'),
(@N_DScout,7,-763.0104,-4995.054,20.06314, ''),
(@N_DScout,8,-753.5364,-4974.764,21.81314, ''),
(@N_DScout,9,-742.8715,-4961.878,22.66427, 'Despawn');
DELETE FROM `achievement_reward` WHERE `entry` IN (4784,4785);
INSERT INTO `achievement_reward` (`entry`,`title_A`,`title_H`,`item`,`sender`,`subject`,`text`) VALUES
(4784,0,0,0,37942, 'Emblem Quartermasters in Dalaran''s Silver Enclave', 'Your achievements in Northrend have not gone unnoticed, friend.$B$BThe Emblems you have earned may be used to purchase equipment from the various Emblem Quartermasters in Dalaran.$B$BYou may find us there, in the Silver Enclave, where each variety of Emblem has its own quartermaster.$B$BWe look forward to your arrival!'),
(4785,0,0,0,37941, 'Emblem Quartermasters in Dalaran''s Sunreaver Sanctuary', 'Your achievements in Northrend have not gone unnoticed, friend.$B$BThe Emblems you have earned may be used to purchase equipment from the various Emblem Quartermasters in Dalaran.$B$BYou may find us there, in the Sunreaver Sanctuary, where each variety of Emblem has its own quartermaster.$B$BWe look forward to your arrival!');
SET @ENTRY := 32487;
SET @SPELL1 := 61080; -- Putrid Punt
SET @SPELL2 := 41534; -- War Stomp
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,0,0,0,100,0,7000,8000,8000,9000,11,@SPELL1,1,0,0,0,0,2,0,0,0,0,0,0,0,'Putridus the Ancient - Combat - Cast Putrid Punt'),
(@ENTRY,0,1,0,0,0,100,0,6000,7000,12000,12000,11,@SPELL2,1,0,0,0,0,2,0,0,0,0,0,0,0,'Putridus the Ancient - Combat - Cast War Stomp');

