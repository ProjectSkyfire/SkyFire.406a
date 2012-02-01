-- 2011051304
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_item_gift_of_the_harvester';
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_dk_death_gate';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(52481, 'spell_item_gift_of_the_harvester'),
(52751, 'spell_dk_death_gate');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (61407,62136,54069,56251,50785,59372);
INSERT INTO `spell_script_names` (spell_id,ScriptName) VALUES 
(61407,'spell_varos_energize_core_area_entry'),
(62136,'spell_varos_energize_core_area_entry'),
(54069,'spell_varos_energize_core_area_entry'),
(56251,'spell_varos_energize_core_area_entry'),
(50785,'spell_varos_energize_core_area_enemy'),
(59372,'spell_varos_energize_core_area_enemy');

DELETE FROM `spell_script_names` WHERE `spell_id`=51162 AND `ScriptName`='spell_eregos_planar_shift';
INSERT INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES
(51162,'spell_eregos_planar_shift');

DELETE FROM `spell_script_names` WHERE `spell_id` = 54798 AND `ScriptName`='spell_q12851_going_bearback';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(54798,'spell_q12851_going_bearback');

DELETE FROM `spell_script_names` WHERE `spell_id`=70292 AND `ScriptName`='spell_trash_mob_glacial_strike';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(70292,'spell_trash_mob_glacial_strike');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_dungeon_credit';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(58630,'spell_gen_dungeon_credit'),
(59046,'spell_gen_dungeon_credit'),
(59450,'spell_gen_dungeon_credit'),
(61863,'spell_gen_dungeon_credit'),
(64899,'spell_gen_dungeon_credit'),
(64985,'spell_gen_dungeon_credit'),
(65074,'spell_gen_dungeon_credit'),
(65195,'spell_gen_dungeon_credit'),
(68184,'spell_gen_dungeon_credit'),
(68572,'spell_gen_dungeon_credit'),
(68574,'spell_gen_dungeon_credit'),
(68663,'spell_gen_dungeon_credit'),
(72706,'spell_gen_dungeon_credit'),
(72830,'spell_gen_dungeon_credit'),
(72959,'spell_gen_dungeon_credit');

DELETE FROM `spell_script_names` WHERE `spell_id`=26678;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(26678,'spell_item_create_heart_candy');

DELETE FROM `spell_script_names` WHERE `spell_id` IN(63633,65594,62056,63985,64224,64225);
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES 
(63633,'spell_ulduar_rubble_summon'),
(65594,'spell_ulduar_cancel_stone_grip'),
(62056,'spell_ulduar_stone_grip'),
(63985,'spell_ulduar_stone_grip'),
(64224,'spell_ulduar_stone_grip_absorb'),
(64225,'spell_ulduar_stone_grip_absorb');

DELETE FROM `spell_script_names` WHERE `spell_id`=64702;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(64702, 'spell_ulduar_squeezed_lifeless');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_item_map_of_the_geyser_fields';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45853, 'spell_item_map_of_the_geyser_fields');

DELETE FROM `spell_script_names` WHERE `spell_id`=48917;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(48917, 'spell_q10041_q10040_who_are_they');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_symbol_of_life_dummy';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(8593, 'spell_symbol_of_life_dummy');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_ulduar_proximity_mines';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(63027, 'spell_ulduar_proximity_mines');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_valanar_kinetic_bomb_absorb';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(72054, 'spell_valanar_kinetic_bomb_absorb');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_putricide_ooze_channel';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(70447, 'spell_putricide_ooze_channel'),
(72836, 'spell_putricide_ooze_channel'),
(72837, 'spell_putricide_ooze_channel'),
(72838, 'spell_putricide_ooze_channel'),
(70672, 'spell_putricide_ooze_channel'),
(72455, 'spell_putricide_ooze_channel'),
(72832, 'spell_putricide_ooze_channel'),
(72833, 'spell_putricide_ooze_channel');

DELETE FROM `spell_script_names`  WHERE `ScriptName` IN ('spell_generic_clone', 'spell_generic_clone_weapon');
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45785, 'spell_generic_clone'),
(49889, 'spell_generic_clone'),
(50218, 'spell_generic_clone'),
(51719, 'spell_generic_clone'),
(57528, 'spell_generic_clone'),
(69828, 'spell_generic_clone'),
(41055, 'spell_generic_clone_weapon'),
(63416, 'spell_generic_clone_weapon'),
(69891, 'spell_generic_clone_weapon'),
(45206, 'spell_generic_clone_weapon'),
(69892, 'spell_generic_clone_weapon'),
(57593, 'spell_generic_clone_weapon');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_seaforium_blast';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(52408, 'spell_gen_seaforium_blast');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_item_vanquished_clutches';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(64981, 'spell_item_vanquished_clutches');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_turkey_marker';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(25281, 'spell_gen_turkey_marker');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (42489,42485,42492);
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(42489, 'spell_ooze_zap'),
(42485, 'spell_ooze_zap_channel_end'),
(42492, 'spell_energize_aoe');

DELETE FROM `spell_script_names` WHERE `spell_id`=63276;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`)
VALUES
(63276,'spell_mark_of_the_faceless');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (63489,62274);
INSERT INTO `spell_script_names` 
VALUES
(63489, 'spell_shield_of_runes'),
(62274, 'spell_shield_of_runes');

DELETE FROM `spell_script_names` WHERE `spell_id`=28441;
INSERT INTO `spell_script_names`(`spell_id`, `ScriptName`) VALUES
(28441, 'spell_item_ashbringer');

UPDATE `creature_template` SET `ScriptName`='boss_sister_svalna' WHERE `entry`=37126;
UPDATE `creature_template` SET `ScriptName`='npc_impaling_spear' WHERE `entry`=38248;
UPDATE `creature_template` SET `ScriptName`='npc_create_helper_cot' WHERE `entry`=27827;
UPDATE `creature_template` SET `ScriptName`='npc_princess_stillpine' WHERE `entry`=17682;
UPDATE `creature_template` SET `ScriptName` = 'boss_razorscale_controller' WHERE `entry` = 33233;
UPDATE `creature_template` SET `ScriptName`='mob_SonOfFlame' WHERE `entry`=12143;
UPDATE `creature_template` SET `ScriptName`='npc_highlord_tirion_fordring_lh' WHERE `entry`=37119;
UPDATE `creature_template` SET `ScriptName` = 'npc_corki' WHERE `entry` IN (18445,20812,18369);

UPDATE `gameobject_template` SET `ScriptName` = 'go_corkis_prison' WHERE `entry` IN (182349,182350,182521);
UPDATE `gameobject_template` SET `ScriptName`='go_princess_stillpines_cage' WHERE `entry`=181928;