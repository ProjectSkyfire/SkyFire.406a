--  54640 Teleport (Teleports defenders behind the walls on the Isle of Ulduran, Strand of the Ancients) - FIX THIS?
DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=54640;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(54640,54643,0, 'WG teleporter');

-- Spell area
DELETE FROM `spell_area` WHERE `spell` IN (58730,57940);
INSERT INTO `spell_area` (`spell`,`area`,`quest_start`,`quest_start_active`,`quest_end`,`aura_spell`,`racemask`,`gender`,`autocast`) VALUES
(58730,4581,0,0,0,0,0,2,1), -- Restricted Flight Area (Wintergrasp Eject)
(58730,4539,0,0,0,0,0,2,1),
(58730,4197,0,0,0,0,0,2,1),
(58730,4585,0,0,0,0,0,2,1),
(58730,4612,0,0,0,0,0,2,1),
(58730,4582,0,0,0,0,0,2,1),
(58730,4583,0,0,0,0,0,2,1),
(58730,4589,0,0,0,0,0,2,1),
(58730,4575,0,0,0,0,0,2,1),
(58730,4538,0,0,0,0,0,2,1),
(58730,4577,0,0,0,0,0,2,1),
(57940,65,0,0,0,0,0,2,1), -- Essence of Wintergrasp
(57940,66,0,0,0,0,0,2,1),
(57940,67,0,0,0,0,0,2,1),
(57940,206,0,0,0,0,0,2,1),
(57940,210,0,0,0,0,0,2,1),
(57940,394,0,0,0,0,0,2,1),
(57940,395,0,0,0,0,0,2,1),
(57940,1196,0,0,0,0,0,2,1),
(57940,2817,0,0,0,0,0,2,1),
(57940,3456,0,0,0,0,0,2,1),
(57940,3477,0,0,0,0,0,2,1),
(57940,3537,0,0,0,0,0,2,1),
(57940,3711,0,0,0,0,0,2,1),
(57940,4100,0,0,0,0,0,2,1),
(57940,4196,0,0,0,0,0,2,1),
(57940,4228,0,0,0,0,0,2,1),
(57940,4264,0,0,0,0,0,2,1),
(57940,4265,0,0,0,0,0,2,1),
(57940,4272,0,0,0,0,0,2,1),
(57940,4273,0,0,0,0,0,2,1),
(57940,4395,0,0,0,0,0,2,1),
(57940,4415,0,0,0,0,0,2,1),
(57940,4416,0,0,0,0,0,2,1),
(57940,4493,0,0,0,0,0,2,1),
(57940,4494,0,0,0,0,0,2,1),
(57940,4603,0,0,0,0,0,2,1);

-- Spell scripts
DELETE FROM `spell_scripts` WHERE `id`=49899;
INSERT INTO `spell_scripts` (`id`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES
(49899,0,1,406,0,0,0,0,0,0); -- Activate Robotic Arms

-- Spell Target position for Wintergrasp Graveyard spells
DELETE FROM `spell_target_position` WHERE `id` IN (59760,59762,59763,59765,59766,59767,59769);
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(59760,571,5537.986,2897.493,517.057,4.819249), -- Teleport: Fortress Graveyard 
(59762,571,5104.750,2300.940,368.579,0.733038), -- Teleport: Sunken Ring "area 4538"
(59763,571,5099.120,3466.036,368.484,5.317802), -- Teleport: Broken Temple "area 4539 & 4589"
(59765,571,5032.454,3711.382,372.468,3.971623), -- Teleport: Horde Landing Zone
(59766,571,4331.716,3235.695,390.251,0.008500), -- Teleport: Westspark Factory Graveyard "area 4611"
(59767,571,4314.648,2408.522,392.642,6.268125), -- Teleport: Eastspark Factory Graveyard "area 4612"
(59769,571,5140.790,2179.120,390.950,1.972220); -- Teleport: Alliance Landing Zone

-- thanks to Malcorm
-- Invisible Stalker text for Wintergrasp from sniff
DELETE FROM `creature_text` WHERE `entry`=15214;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(15214,0,0, 'Let the battle begin!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,1,0, 'The Broken Temple siege workshop has been attacked by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,2,0, 'The Broken Temple siege workshop has been captured by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,3,0, 'The Broken Temple siege workshop has been attacked by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,4,0, 'The Broken Temple siege workshop has been captured by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,5,0, 'The Sunken Ring siege workshop has been attacked by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,6,0, 'The Sunken Ring siege workshop has been captured by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,7,0, 'The Sunken Ring siege workshop has been attacked by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,8,0, 'The Sunken Ring siege workshop has been captured by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,9,0, 'The Eastspark siege workshop has been attacked by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,10,0, 'The Eastspark siege workshop has been captured by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,11,0, 'The Eastspark siege workshop has been attacked by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,12,0, 'The Eastspark siege workshop has been captured by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,13,0, 'The Westspark siege workshop has been attacked by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,14,0, 'The Westspark siege workshop has been captured by the Horde!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,15,0, 'The Westspark siege workshop has been attacked by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,16,0, 'The Westspark siege workshop has been captured by the Alliance!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,17,0, 'The north-western keep tower has been damaged!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,18,0, 'The north-western keep tower has been destroyed!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,19,0, 'The south-eastern keep tower has been damaged!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,20,0, 'The south-eastern keep tower has been destroyed!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,21,0, 'The western tower has been damaged!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,22,0, 'The western tower has been destroyed!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,23,0, 'The southern tower has been damaged!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,24,0, 'The southern tower has been destroyed!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,25,0, 'The eastern tower has been damaged!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,26,0, 'The eastern tower has been destroyed!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,27,0, 'The Horde has defended Wintergrasp Fortress!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,28,0, 'The Horde has captured Wintergrasp Fortress!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,29,0, 'The Alliance has defended Wintergrasp Fortress!',41,0,100,0,0,0, 'Invisible Stalker'),
(15214,30,0, 'The Alliance has captured Wintergrasp Fortress!',41,0,100,0,0,0, 'Invisible Stalker');