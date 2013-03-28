/* ***************************************************************
 *            SkyFireDB-release12 hotfixes.                      *
 *                                                               *
 *  since i could NOT fully nail down every                      *
 *  fix that had gone missing i ran through last known           *
 *  place in archive history and added the noticible changesets  *
 *  missing and/or possibly missing from this DB revision.       *
 *  more can be afoul'd, still checking.                         *
 *                                                               *
 *  Please Note: this file should NOT be moved to sql.old        *
 *               it is merely a hotfix.                          *
 *************************************************************** */

/* 
* sql\updates\world\2012_05_26_00_world_sacrifices_quest.sql 
*/ 
DELETE FROM creature_text WHERE entry IN (35230);
INSERT INTO creature_text VALUES
(35230, 0, 0, 'Let''s round up as many of them as we can.  Every worgen chasing us is one less worgen chasing the survivors!', 12, 0, 100, 0, 0, 19506, 'Lord Darius Crowley'),
(35230, 1, 0, 'You''ll never catch us, you blasted mongrels!', 14, 0, 100, 0, 0, 19505, 'Lord Darius Crowley'),
(35230, 1, 1, 'Over here, you flea bags!', 14, 0, 100, 0, 0, 19504, 'Lord Darius Crowley'),
(35230, 1, 2, 'Come and get us, you motherless beasts!', 14, 0, 100, 0, 0, 19503, 'Lord Darius Crowley');

UPDATE `creature_template` SET `speed_run`=1.28571426868439, `VehicleId`=463, `minlevel`=4, `maxlevel`=4, `faction_h`=2203, `faction_a`=2203, `Unit_Flags`=8, `Modelid1`=238, `Resistance4`=1, `mechanic_immune_mask`=2147483647, `scriptname`='npc_crowley_horse' WHERE `entry`=35231;

DELETE FROM script_waypoint WHERE entry=35231;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`) VALUES
(35231,1,-1733.16,1657.12,20.487,0),
(35231,2,-1708.57,1668.38,20.603,0),
(35231,3,-1672.35,1654.15,20.4894,0),
(35231,4,-1667.97,1621.56,20.4894,0),
(35231,5,-1695.44,1613.45,20.4894,0),
(35231,6,-1706.51,1635.75,20.4894,0),
(35231,7,-1695.11,1672.98,20.6713,0),
(35231,8,-1672.25,1704.1,20.4989,0),
(35231,9,-1647.89,1709.19,20.4978,0),
(35231,10,-1610.74,1711.23,22.6819,0),
(35231,11,-1559.29,1707.9,20.4853,0),
(35231,12,-1541.24,1635.49,21.23,0),
(35231,13,-1516.68,1622.81,20.4866,0),
(35231,14,-1441.73,1629.45,20.4866,0),
(35231,15,-1423.11,1603.72,20.4866,0),
(35231,16,-1416.55,1583.68,20.485,0),
(35231,17,-1447.75,1538.23,20.4857,0),
(35231,18,-1465.08,1533.48,20.4857,0),
(35231,19,-1500.87,1564.68,20.4867,0),
(35231,20,-1536.46,1579.09,27.7734,0),
(35231,21,-1542.2,1573.9,29.2055,0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=44427;
INSERT INTO npc_spellclick_spells VALUES
(44427,67766,3,0);

DELETE FROM conditions WHERE sourcetypeorreferenceid=18 AND sourcegroup=44427 AND sourceentry=67766 LIMIT 2;
INSERT INTO conditions VALUES
(18,44427,67766,0,0,9,0,14212,0,0,0,0,"","Npc_spellclick_spells - 'Quest Sacrifices' Must Be Accepted"),
(18,44427,67766,0,0,8,0,14212,0,0,1,0,"","Npc_spellclick_spells - 'Quest Sacrifices' Must NOT Be Completed");

UPDATE creature_template SET npcflag=16777216 WHERE entry=44427;

DELETE FROM conditions WHERE sourcetypeorreferenceid=13 AND sourceentry=67063 LIMIT 1;
INSERT INTO conditions VALUES
(13,7,67063,0,0,31,0,3,35229,0,0,0,"","Must focus damage on Bloodfang Stalker");

UPDATE quest_template SET questflags=0, specialflags=0, reqcreatureorgoid1=35582, endtext="Speak to Tobias Mistmantle at the Light's Dawn Cathedral in Gilneas City.", completedtext='' WHERE entry=14212;

DELETE FROM `creature_template` WHERE `entry`=35231 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 35231, 0, 0, 0, 0, 0, 238, 0, 0, 0, "Crowley's Horse", "", "", 0, 4, 4, 0, 2203, 2203, 0, 1.0, 1.28571, 1.0, 0, 13, 17, 0, 42, 1.0, 0, 0, 1, 8, 0, 0, 0, 0, 0, 0, 13, 17, 42, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 67063, 0, 0, 0, 0, 0, 0, 0, 0, 463, 0, 0, "", 0, 3, 10.0, 1.0, 1.0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2147483647, 0, "npc_crowley_horse", "1");

UPDATE creature_template SET killcredit1=35582, scriptname="npc_bloodfang_stalker_c1" WHERE entry=35229;

/* 
* sql\updates\world\2012_05_26_01_world_gilneas_spirit_healers.sql 
*/ 
DELETE FROM creature WHERE guid IN(329187,296,297,298,299);
INSERT INTO creature VALUES
(296,39660,638,1,3,0,39660,-1383.46,1367.65,35.6246,3.00336,300,0,0,4120,0,0,0,0,0),
(297,39660,638,1,12,0,39660,-1759.07,1409.46,21.1424,2.78345,300,0,0,4120,0,0,0,0,0),
(298,39660,638,1,8,0,39660,-1768.89,1663.75,20.9098,5.43417,300,0,0,4120,0,0,0,0,0),
(299,39660,638,1,1032,0,39660,-1568.57,1588.28,28.0998,0.749277,300,0,0,4120,0,0,0,0,0);

 
 
/* 
* sql\updates\world\2012_05_28_01_world_spell_bonus_data.sql 
*/ 
DELETE FROM `spell_bonus_data` WHERE `entry` = 85673;
INSERT INTO `spell_bonus_data` VALUES
(85673,0.209,0,0.198,0,'Paladin - Word of Glory'); 
 
/* 
* sql\updates\world\2012_05_28_02_world_spell_proc_event.sql 
*/ 
-- (85117,86172,90174) Divine Purpose
DELETE FROM `spell_proc_event` WHERE `entry` IN (85117,86172,90174);
INSERT INTO `spell_proc_event` VALUES 
(85117, 3, 10, 8388608, 2228354, 40960, 67600, 0, 0, 100, 0),
(86172, 3, 10, 8388608, 2228354, 40960, 67600, 0, 0, 100, 0);
 
 
/* 
* sql\updates\world\2012_05_28_03_world_spell_proc_event.sql 
*/ 
-- Pursuit of Justice
UPDATE `spell_proc_event` SET `Cooldown` = 0, `procFlags` = 0, `procEx` = 65536 WHERE `entry` IN (26022,26023);

-- Pursuit of Justice and Blessed Life Cooldown marker
DELETE FROM `spell_dbc` WHERE `Id` = 32733;
INSERT INTO `spell_dbc` (`Id`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `AttributesEx6`, `AttributesEx7`, `AttributesEx8`, `CastingTimeIndex`, `DurationIndex`, `PowerType`, `RangeIndex`, `Speed`, `SpellVisualId_1`, `SpellVisualId_2`, `SpellIconId`, `ActiveIconId`, `SchoolMask`, `RuneCostId`, `SpellDifficultyId`, `SpellScalingId`, `SpellAuraOptionsId`, `SpellAuraRestrictionsId`, `SpellCastingRequirementsId`, `SpellCategoriesId`, `SpellClassOptionsId`, `SpellCooldownsId`, `SpellEquippedItemsId`, `SpellInterruptsId`, `SpellLevelsId`, `SpellPowerId`, `SpellReagentsId`, `SpellShapeshiftId`, `SpellTargetRestrictionsId`, `SpellTotemsId`, `unk`) 
VALUES (32733, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `spelleffect_dbc` WHERE `Id` = 200000;
INSERT INTO `spelleffect_dbc` (`Id`, `effect`, `effectAmplitude`, `effectAura`, `effectAuraPeriod`, `effectBasePoints`, `effectUnk_320`, `effectChainAmplitude`, `effectChainTargets`, `effectDieSides`, `effectItemType`, `effectMechanic`, `effectMiscValue`, `effectMiscValueB`, `effectPointsPerCombo`, `effectRadiusIndex`, `effectRadiusMaxIndex`, `effectRealPointsPerLevel`, `effectSpellClassMask_1`, `effectSpellClassMask_2`, `effectSpellClassMask_3`, `effectTriggerSpell`, `implicitTargetA`, `implicitTargetB`, `effectSpellId`, `effectIndex`) 
VALUES (200000, 6, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32733, 0);



 
 
/* 
* sql\updates\world\2012_05_28_04_world_spell_script_names.sql 
*/ 
-- Mage old polymorph script for Elrodan
DELETE FROM `spell_script_names` WHERE `spell_id` = 118;
 
 
/* 
* sql\updates\world\2012_05_28_05_world_spell_script_names.sql 
*/ 
-- Execute
DELETE FROM `spell_script_names` WHERE `spell_id` = 5308;
INSERT INTO `spell_script_names` VALUES
(5308,'spell_warr_execute');
-- Spell Bonus Data
DELETE FROM `spell_bonus_data` WHERE `entry` = 5308;
INSERT INTO `spell_bonus_data` VALUES
(5308,0,0,0.437,0,'Warrior - Execute'); 

/* 
* sql\updates\world\2012_05_29_00_world_gameobject_template.sql 
*/ 
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES (208779, 10, 6271, 'Lighthouse Banner', '', 'Capturing', '', 35, 0, 1, 0, 0, 0, 0, 0, 0, 1479, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 23936, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES (208780, 10, 6271, 'Waterworks Banner', '', 'Capturing', '', 35, 0, 1, 0, 0, 0, 0, 0, 0, 1479, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 23936, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES (208781, 10, 6271, 'Mines Banner', '', 'Capturing', '', 35, 0, 1, 0, 0, 0, 0, 0, 0, 1479, 0, 0, 3000, 0, 0, 0, 0, 0, 0, 23936, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
 
 
/* 
* sql\updates\world\2012_05_30_00_world_npc_spellclick_spell.sql 
*/ 
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (34776, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (35069, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (34793, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (34802, 68503, 1, 0);
 
 
/* 
* sql\updates\world\2012_05_30_01_world_npc_spellclick_spell.sql 
*/ 
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (34929, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (36838, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (36839, 68503, 1, 0);
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES (34935, 68503, 1, 0);
 
 
/* 
* sql\updates\world\2012_05_30_02_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` IN (11885,11886,11887,11888,11889);
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(11885,'spell_item_muisek_vessel'),
(11886,'spell_item_muisek_vessel'),
(11887,'spell_item_muisek_vessel'),
(11888,'spell_item_muisek_vessel'),
(11889,'spell_item_muisek_vessel');
 
 
/* 
* sql\updates\world\2012_05_30_03_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (7744,42292,59752);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (7744,42292,72752,72757);
INSERT INTO `spell_script_names` VALUES
(7744,'spell_pvp_trinket_wotf_shared_cd'),
(42292,'spell_pvp_trinket_wotf_shared_cd'); 
 
/* 
* sql\updates\world\2012_06_01_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = 79637;
INSERT INTO `spell_script_names` VALUES
(79637,'spell_item_flask_of_enhancement');
 
-- Deep Wounds
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_warr_deep_wounds';
INSERT INTO `spell_script_names` VALUES
(12162,'spell_warr_deep_wounds'),
(12850,'spell_warr_deep_wounds'),
(12868,'spell_warr_deep_wounds');
 
 
/* 
* sql\updates\world\2012_06_03_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id`=-5308; -- Execute "Ranks", clear one more stupid warning on startup

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_item_gnomish_death_ray';
INSERT INTO `spell_script_names` VALUES
(13280,'spell_item_gnomish_death_ray');


DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (13278,-13278);
INSERT INTO `spell_linked_spell` VALUES
(13278,13493,0,'Gnomish Death Ray caster overtime damage apply'),
(-13278,-13493,0,'Gnomish Death Ray caster overtime damage removal');
 
 
/* 
* sql\updates\world\2012_06_04_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_gen_lifeblood'; 
 
/* 
* sql\updates\world\2012_06_04_01_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_sha_mana_tide_totem';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_gen_damage_reduction_aura';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_pal_blessing_of_sanctuary';

-- Paladin Sanctuary
DELETE FROM `spell_proc_event` WHERE `entry` IN (20911,84628,84629);
INSERT INTO `spell_proc_event` VALUES 
(20911, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84628, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84629, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0);
 
 
/* 
* sql\updates\world\2012_06_06_00_world_spell_linked_spell.sql 
*/ 
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN(1126);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(1126, 79061, 0, 'Mark of the Wild'); 
 
/* 
* sql\updates\world\2012_06_08_00_world_spell_linked_spell.sql 
*/ 
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN(21562, 27683, 1120, -82691, 19740);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(21562, 79105, 0, 'Power Word: Fortitude'), -- Power Word: Fortitude
(27683, 79107, 0, 'Shadow Protection'), -- Shadow Protection
(1120, 79264, 0, 'Drain Soul'), -- Drain Soul
(19740, 79063, 0, 'Blessing of Might'), -- Blessing of Might
(-82691, 91264, 0, 'Ring of frost immune'); -- immunity to ring of frost
 
 
/* 
* sql\updates\world\2012_06_08_09_world_spell_linked_spell.sql 
*/ 
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = '1120';
 
 
/* 
* sql\updates\world\2012_06_08_10_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = '1120';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES ('1120','spell_warl_drain_soul'); 
 
/* 
* sql\updates\world\2012_06_08_11_world_creature_template.sql 
*/ 
--  Webbed Crusader - Stopped Movement --
UPDATE `creature_template` SET `unit_flags` = 131076 WHERE `entry` IN (30273,30268);

--  Primordial Drake Egg - Stopped Movement --
UPDATE `creature_template` SET `unit_flags` = 131076 WHERE `entry` = 28408;
 
 
/* 
* sql\updates\world\2012_06_09_00_world_spell_script_names.sql 
*/ 
-- divine storm
DELETE FROM `spell_script_names` WHERE `spell_id` = 53385;
INSERT INTO `spell_script_names` VALUES (53385, 'spell_pal_divine_storm');
 
 
/* 
* sql\updates\world\2012_06_09_01_world_spell_script_names.sql 
*/ 
-- warlock: Demonic circle
DELETE FROM `spell_script_names` WHERE `spell_id` IN (48018, 48020);
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (48018, 'spell_warl_demonic_circle_summon');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (48020, 'spell_warl_demonic_circle_teleport');
 
 
/* 
* sql\updates\world\2012_06_09_02_world_spell_script_names.sql 
*/ 
-- spell_items
DELETE FROM `spell_script_names` WHERE `spell_id` IN (29200,47170,51582,55004,50243,35745);
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (29200,'spell_item_purify_helboar_meat');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (47170,'spell_item_impale_leviroth');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (51582,'spell_item_rocket_boots');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (55004,'spell_item_nitro_boots');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (50243,'spell_item_teach_language');
INSERT  INTO `spell_script_names`(`spell_id`,`ScriptName`) VALUES (35745,'spell_item_socrethars_stone'); 
 
/* 
* sql\updates\world\2012_06_14_00_world_spell_script_names.sql 
*/ 
-- Shaman: Mana Tide
DELETE FROM `spell_script_names` WHERE `spell_id` = '16191';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('16191', 'spell_sha_mana_tide'); 
 
/* 
* sql\updates\world\2012_06_16_00_spell_proc_event.sql 
*/ 
DELETE FROM `spell_proc_event` WHERE `entry` IN ('56807', '56800', '79133', '79134', '11095', '12872', '12873');
INSERT INTO `spell_proc_event`
(`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) 
VALUES
('56807','0','8','33554432','0','0','16','0','0','0','0'),        -- Glyph of hemorrhage (Thanks CrYser)
('56800','0','8','4','0','0','16','2','0','0','0'),               -- Glyph of backstab (Thanks CrYser)
('79133','0','8','1048832','0','0','262144','0','0','30','0'),    -- Venomous wounds rank 1
('79134','0','8','1048832','0','0','262144','0', '0','60','0'),    -- Venomous wounds rank 2
('11095','0','3','4194320','0','0','0','0','0', '0','0'),         -- Critical mass rank 1
('12872','0','3','4194320','0','0','0','0','0', '0','0'),         -- Critical mass rank 2
('12873','0','3','4194320','0','0','0','0','0', '0','0');         -- Critical mass rank 3 
 
/* 
* sql\updates\world\2012_06_16_01_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = '86939';
INSERT INTO `spell_script_names`
(`spell_id`, `ScriptName`)
VALUES
('86939','spell_item_adventurers_journal'); 
 
/* 
* sql\updates\world\2012_06_17_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_moonkin_form_passive';
DELETE FROM `spell_proc_event` WHERE `entry` = 24905; 
 
/* 
* sql\updates\world\2012_06_17_01_world_spell_proc_event.sql 
*/ 
-- Pursuit of Justice
UPDATE `spell_proc_event` SET `procFlags` = 139808 WHERE `entry` IN (26022,26023); 
 
/* 
* sql\updates\world\2012_06_17_02_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_mage_summon_water_elemental'; 
 
/* 
* sql\updates\world\2012_06_19_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_warl_seed_of_corruption';
INSERT INTO `spell_script_names` VALUES
(27285,'spell_warl_seed_of_corruption'),
(32865,'spell_warl_seed_of_corruption'); 
 
/* 
* sql\updates\world\2012_06_21_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` IN ('spell_mage_incanters_absorbtion_absorb','spell_mage_incanters_absorbtion_manashield');
INSERT INTO `spell_script_names` VALUES
(543,'spell_mage_incanters_absorbtion_absorb'),
(1463,'spell_mage_incanters_absorbtion_manashield'); 
 
/* 
* sql\updates\world\2012_06_21_01_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_glyph_of_starfire';
INSERT INTO `spell_script_names` VALUES
(54846,'spell_dru_glyph_of_starfire');

UPDATE `spell_proc_event` SET `CustomChance` = 100 WHERE `entry` = 54845; 
 
/* 
* sql\updates\world\2012_06_23_00_world_spell_script_names.sql 
*/ 
-- Wrong spell for gnomish death ray script, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 13278;

-- Wrong spell for ashbringer script, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 18112;

-- Wrong spell for hunter's scatter shot, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 19503;

-- Wrong spell for warrior's charge, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 34846;

-- Wrong spell for warrior's slam
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_warr_slam';
INSERT INTO `spell_script_names` VALUES
(1464,'spell_warr_slam');

-- Wrong spell for priest's pain and suffering, the right one is already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 47580;

-- Starfall Script Correction
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_starfall_aoe'; 
INSERT INTO `spell_script_names` VALUES
(50286,'spell_dru_starfall_aoe');

-- Deprecated script
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_berserk'; 

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_warr_vigilance'; 
INSERT INTO `spell_script_names` VALUES
(50725,'spell_warr_vigilance');

-- Juggernaut proc data
DELETE FROM `spell_proc_event` WHERE `entry` IN (64976,65156);
INSERT INTO `spell_proc_event` VALUES
(64976,0,4,1,0,0,0,0,0,0,0),
(65156,0,4,35651584,0,0,0,0,0,0,0);


/* 
* sql\updates\world\2012_06_24_00_world_spell_script_names.sql 
*/ 
-- WHO THE FUCK set a sacred cleasing quest spell into the sacred cleasing paladin talent? for gods sake.
-- the right id is already on DB
DELETE FROM `spell_script_names` WHERE `spell_id` = 53551;

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_mark_of_nature';
INSERT INTO `spell_script_names` VALUES
(25042,'spell_mark_of_nature');

-- Missing mark of nature and xt002 heart overload
DELETE FROM `spelleffect_dbc` WHERE `Id` IN (200001,200002);
INSERT INTO `spelleffect_dbc` (`Id`, `effect`, `effectAmplitude`, `effectAura`, `effectAuraPeriod`, `effectBasePoints`, `effectUnk_320`, `effectChainAmplitude`, `effectChainTargets`, `effectDieSides`, `effectItemType`, `effectMechanic`, `effectMiscValue`, `effectMiscValueB`, `effectPointsPerCombo`, `effectRadiusIndex`, `effectRadiusMaxIndex`, `effectRealPointsPerLevel`, `effectSpellClassMask_1`, `effectSpellClassMask_2`, `effectSpellClassMask_3`, `effectTriggerSpell`, `implicitTargetA`, `implicitTargetB`, `effectSpellId`, `effectIndex`) VALUES 
(200001, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 62791, 0),
(200002, 6, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 22, 15, 25042, 0);

-- Telluric poultice completion spell wrong spellscript id the right one is already on DB
DELETE FROM `spell_script_names` WHERE `spell_id` = 55797;

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_freya_attuned_to_nature_dose_reduction';
INSERT INTO `spell_script_names` VALUES
(62524,'spell_freya_attuned_to_nature_dose_reduction'), -- 2 stack reduction
(62525,'spell_freya_attuned_to_nature_dose_reduction'), -- 10 stack reduction
(62521,'spell_freya_attuned_to_nature_dose_reduction'); -- 25 stack reduction 
 
/* 
* sql\updates\world\2012_06_24_01_world_spell_script_names.sql 
*/ 
-- Wrong spell id for spell_marrowgar_bone_spike_graveyard, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 73143;

-- Wrong spell id for spell_deathbringer_rune_of_blood, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72410;

-- Wrong spell id for spell_deathbringer_blood_link_aura, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72202;

-- Wrong spell id for spell_deathbringer_blood_link
DELETE FROM `spell_script_names` WHERE `spell_id` = 70897;
INSERT INTO `spell_script_names` VALUES 
(72202,'spell_deathbringer_blood_link');

-- Wrong spell id for spell_cultist_dark_martyrdom, the right ones are already set
DELETE FROM `spell_script_names` WHERE `spell_id` = 72176;

-- Wrong spell id for spell_marrowgar_coldflame.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_marrowgar_coldflame';
INSERT INTO `spell_script_names` VALUES
(69140,'spell_marrowgar_coldflame');

-- Wrong spell id for spell_xt002_gravity_bomb_damage.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_xt002_gravity_bomb_damage';
INSERT INTO `spell_script_names` VALUES
(63025,'spell_xt002_gravity_bomb_damage'),
(64233,'spell_xt002_gravity_bomb_damage');

-- Wrong spell id for spell_tournament_trust.
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_tournament_trust';
INSERT INTO `spell_script_names` VALUES
(62544,'spell_tournament_trust'); 
 
/* 
* sql\updates\world\2012_06_24_02_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_worgen_last_stand_movie';
INSERT INTO `spell_script_names` VALUES
(65731,'spell_worgen_last_stand_movie'); -- Guessing, need confirmation from the gilneas guys.

DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_pal_guarded_by_the_light'; 
 
/* 
* sql\updates\world\2012_06_29_00_world_spell_script_names.sql 
*/ 
-- Chakra
DELETE FROM `spell_proc_event` WHERE `entry` = 14751;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) 
VALUES (14751, 6, 6, 7808, 18, 2710, 0, 0, 0, 0, 0);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (81208,81585,81206,88685,88667,88687);
INSERT INTO `spell_script_names` VALUES
(81208,'spell_pri_chakra_swap_supressor'),
(81585,'spell_pri_chakra_serenity_proc'),
(81206,'spell_pri_chakra_swap_supressor'),
(88685,'spell_pri_chakra_sanctuary_heal'),
(88667,'spell_pri_chakra_sanctuary_heal');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (81206);
INSERT INTO `spell_linked_spell` VALUES
(81206,81207,0,'Chakra:Sanctuary - Renew spellmod link');

DELETE FROM `spell_group` WHERE `id` = 1501;
INSERT INTO `spell_group` VALUES
(1501,81206), -- Chakra: Sanctuary
(1501,81208), -- Chakra: Serenity
(1501,81209); -- Chakra: Chastise

DELETE FROM `spell_group_stack_rules` WHERE `group_id` = 1501;
INSERT INTO `spell_group_stack_rules` VALUES
(1501,2); -- Only 1 chakra effect can be active on the caster.
 
 
/* 
* sql\updates\world\2012_07_06_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` IN (687,28176);
INSERT INTO `spell_script_names` VALUES
(687,'spell_warl_nether_ward_swap_supressor'),
(28176,'spell_warl_nether_ward_swap_supressor'); 
 
/* 
* sql\updates\world\2012_07_06_01_world_spell_script_names.sql 
*/ 
-- Resistance is futile periodic aura on enemy
DELETE FROM `spell_script_names` WHERE `spell_id` = 83676;
INSERT INTO `spell_script_names` VALUES
(83676,'spell_hun_resistance_is_futile');

-- Kill command refund proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (82897);
INSERT INTO `spell_proc_event` VALUES
(82897,0,9,0,2048,0,1024,0,0,0,0); 
 
/* 
* sql\updates\world\2012_07_08_00_world_spell_bonus_data.sql 
*/ 
-- fix FOR swipe (bear), lacerate, thrash
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (779, 0, 0, 0.114, 0, 'Druid - Swipe (Bear)');
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (33745, 0, 0, 0.0766, 0.00512, 'Druid - Lacerate');
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (77758, 0, 0, 0.154, 0.026, 'Druid - Thrash');

-- fix FOR insect swarm 
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (5570, 0, 0.13, 0, 0, 'Druid - Insect Swarm');
 
 
/* 
* sql\updates\world\2012_07_08_01_world_spell_proc_event.sql 
*/ 
-- fix FOR impending doom 
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85106, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 5, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85107, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 10, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85108, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 15, 0);

-- fix FOR soul leech
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (30293, 0, 5, 128, 131200, 0, 0, 1027, 0, 0, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (30295, 0, 5, 128, 131200, 0, 0, 0, 0, 0, 0);

-- fix FOR glyph OF spirit tap
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (63237, 0, 6, 0, 2, 0, 65536, 0, 0, 100, 0);
 
 
/* 
* sql\updates\world\2012_07_09_00_world_playecreateinfo_spell.sql 
*/ 
-- Eclipse Mastery driver passive
DELETE FROM `playercreateinfo_spell` WHERE `Spell` = 79577;
INSERT INTO `playercreateinfo_spell` VALUES
(4,11,79577,'Druid - Eclipse Mastery Driver Passive'),
(6,11,79577,'Druid - Eclipse Mastery Driver Passive'),
(8,11,79577,'Druid - Eclipse Mastery Driver Passive'),
(22,11,79577,'Druid - Eclipse Mastery Driver Passive');
 
 
/* 
* sql\updates\world\2012_07_11_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` IN (2912,5176,78674);
INSERT INTO `spell_script_names` VALUES
(2912,'spell_dru_eclipse_energize'),
(5176,'spell_dru_eclipse_energize'),
(78674,'spell_dru_eclipse_energize'); 
 
/* 
* sql\updates\world\2012_07_12_00_world_spell_proc_event.sql 
*/ 
-- (87099) Sin and Punishment (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (87099);
INSERT INTO `spell_proc_event` VALUES (87099, 1, 6, 0, 0, 0, 262144, 2, 0, 100, 0);

-- (87100) Sin and Punishment (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (87100);
INSERT INTO `spell_proc_event` VALUES (87100, 1, 6, 0, 0, 0, 262144, 2, 0, 100, 0);
 
 
/* 
* sql\updates\world\2012_07_12_01_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = 77478;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(77478, 'spell_sha_earthquake');
 
 
/* 
* sql\updates\world\2012_07_13_00_world_creature_template.sql 
*/ 
UPDATE `creature_template` SET `ScriptName` = 'npc_shadowy_apparition' WHERE `entry` = 46954;
 
 
/* 
* sql\updates\world\2012_07_13_01_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = 87212;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (87212, 'spell_shadowy_apparition_proc');
 
 
/* 
* sql\updates\world\2012_07_13_02_world_spell_proc_event.sql 
*/ 
-- (78202) Shadowy Apparition (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (78202);
INSERT INTO `spell_proc_event` VALUES (78202, 32, 6, 32768, 0, 0, 262144, 0, 0, 100, 0);

-- (78203) Shadowy Apparition (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (78203);
INSERT INTO `spell_proc_event` VALUES (78203, 32, 6, 32768, 0, 0, 262144, 0, 0, 100, 0);
 
 
/* 
* sql\updates\world\2012_07_15_00_world_creature_template.sql 
*/ 
-- Modify scale for bats in Trisfal Glades --
UPDATE `creature_template` SET `scale` = '0.4' WHERE `entry` IN (1553,1513,1512);
UPDATE `creature_template` SET `scale` = '0.7' WHERE `entry` IN (1554,10357);
 
 
/* 
* sql\updates\world\2012_07_15_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_gen_enable_mastery';
INSERT INTO `spell_script_names` VALUES
(86467,'spell_gen_enable_mastery'),
(87491,'spell_gen_enable_mastery'),
(87492,'spell_gen_enable_mastery'),
(87493,'spell_gen_enable_mastery'),
(87494,'spell_gen_enable_mastery'),
(87495,'spell_gen_enable_mastery'),
(87496,'spell_gen_enable_mastery'),
(87497,'spell_gen_enable_mastery'),
(87498,'spell_gen_enable_mastery'),
(87500,'spell_gen_enable_mastery'); 
 
/* 
* sql\updates\world\2012_07_27_00_world_spell_script_names.sql 
*/ 
REPLACE INTO spell_script_names VALUES (-86948,'spell_mage_cauterize'); -- Cauterize rank 1
REPLACE INTO spell_script_names VALUES (-86949,'spell_mage_cauterize'); -- Cauterize rank 2
 
 
/* 
* sql\updates\world\2012_07_30_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_mage_cauterize';
INSERT INTO `spell_script_names` VALUES
(86948,'spell_mage_cauterize'),
(86949,'spell_mage_cauterize');
 
 
/* 
* sql\updates\world\2012_07_31_00_world_spell_bonus_data.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_pri_chakra_sanctuary_heal_target_selector';
INSERT INTO `spell_script_names` VALUES
(88686,'spell_pri_chakra_sanctuary_heal_target_selector');

DELETE FROM `spell_bonus_data` WHERE `entry` IN (88668,88686);
INSERT INTO `spell_bonus_data` VALUES
(88668,0.279,0,0,0,'Priest - Sanctuary 4yd AoE Heal'),
(88686,0.199,0,0,0,'Priest - Sanctuary 8yd AoE Heal'); -- Guessing 
 
 
/* 
* sql\updates\world\2012_08_02_00_world_spell_linked_spell.sql 
*/ 
-- Will of the Necropolis
DELETE FROM spell_linked_spell WHERE spell_effect=-96171;
INSERT INTO spell_linked_spell VALUES (48982, -96171, 0, "Rune Tap - Will of the Necropolis");
 
 
/* 
* sql\updates\world\2012_08_02_00_world_spell_proc_event.sql 
*/ 
-- Will of the Necropolis
DELETE FROM spell_proc_event WHERE entry=96171;
INSERT INTO spell_proc_event (entry, ppmRate, cooldown) VALUES (96171, 1, 45);
 
 
/* 
* sql\updates\world\2012_08_03_00_world_spell_proc_event.sql 
*/ 
DELETE FROM spell_linked_spell WHERE spell_effect=-96171;

-- Rune tap 0 cost charge drop
DELETE FROM `spell_proc_event` WHERE `entry` = 96171;
INSERT INTO `spell_proc_event` VALUES
(96171,0,15,134217728,0,0,0,0,0,0,0);

-- Will of the forsaken talent aura proc cooldown.
DELETE FROM `spell_proc_event` WHERE `entry` IN (52284,81163,81164);
INSERT INTO `spell_proc_event` (`entry`,`Cooldown`) VALUES
(52284,45),
(81163,45),
(81164,45); 
 
/* 
* sql\updates\world\2012_08_05_00_world_spell_misc.sql 
*/ 
-- Paralysis missing proc data
UPDATE `spell_proc_event` SET `SpellFamilyName` = 6 WHERE `entry` IN (87192,87195);

-- Mind melt cast reduction buff proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (81292,87160);
INSERT INTO `spell_proc_event` (`entry`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`) VALUES 
(81292, 6, 8192, 0, 0),
(87160, 6, 8192, 0, 0);

-- Mind spike dots hack removal.
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 73510 AND `spell_effect` IN (-34914,-2944,-589);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (73510,8092);
INSERT INTO `spell_script_names` VALUES
(8092,'spell_pri_mind_blast'),
(73510,'spell_pri_mind_spike'); 
 
/* 
* sql\updates\world\2012_08_08_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` IN (77767,56641);
INSERT INTO `spell_script_names` VALUES
(77767,'spell_hun_cobra_shot'),
(56641,'spell_hun_steady_shot');

-- Class scripts should be on their proper files
DELETE FROM `spell_scripts` WHERE `id` IN (56641,77767);

-- Just a bullshit warning removal
DELETE FROM `spell_script_names` WHERE `spell_id`= -8092; 
 
/* 
* sql\updates\world\2012_08_18_00_world_creature.sql 
*/ 
UPDATE `creature_template` SET `dynamicflags` = 8 WHERE `entry` IN (49355,49356);

DELETE FROM `creature` WHERE `id` IN (49355,49356);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(346863, 49355, 609, 1, 4, 0, 0, 1331.62, -5760.19, 137.652, 3.11027, 300, 0, 0, 3090, 0, 0, 0, 0, 0),
(346864, 49356, 609, 1, 4, 0, 0, 1321, -5757.45, 137.562, 6.26701, 300, 0, 0, 3090, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE `guid` IN (346863,346864);
INSERT INTO `creature_addon` VALUES
(346863, 0, 0, 65544, 1, 0, NULL),
(346864, 0, 0, 65544, 1, 0, NULL);
 
 
/* 
* sql\updates\world\2012_08_18_01_world_gameobject.sql 
*/ 
-- 52598 Ebon Hold: Chapter II, Skybox aura removal on quest 12779 completion (an end to all things...)
-- Chapter IV applies a new screen effect.
UPDATE `spell_area` SET `quest_end`=12779 WHERE  `spell`=52598 AND `area`=4298 AND `quest_start`=12706;

-- Player's death gate teleport correction, was using orbaz's deathgate one.
UPDATE `gameobject_template` SET `data0` = 53822 WHERE `entry` = 190942;

-- Deathgate teleport floor correction (should teleport to the second one).
UPDATE `spell_target_position` SET `target_position_z` = 426.02 WHERE `id` = 53822;

-- Acherus portals floor correction.
DELETE FROM `gameobject` WHERE `id` IN (193052,193053);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(NULL, 193053, 0, 1, 256, 2321.82, -5662.22, 426.03, 0.686441, 0, 0, 0.336521, 0.941676, 300, 0, 1),
(NULL, 193052, 0, 1, 256, 2345.86, -5695.94, 426.029, 0.501083, 0, 0, 0.247929, 0.968778, 300, 0, 1);
 
 
/* 
* sql\updates\world\2012_08_19_00_world_misc.sql 
*/ 
-- Quest fix 27671 (See to the Survivors)
UPDATE `creature` SET `spawntimesecs` = '30' WHERE id = 33024;
UPDATE `creature` SET `spawntimesecs` = '30' WHERE id = 33024;

DELETE FROM `spell_scripts` WHERE `id` = '86264' AND `command` = '18';
INSERT INTO `spell_scripts` (`id`, `command`, `datalong`) VALUES ('86264', '18', '1000');

DELETE FROM `conditions` WHERE `SourceEntry` = 86264 AND `ConditionValue1` = '46268';
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceEntry`, `ConditionTypeOrReference`, `ConditionValue1`) VALUES ('17', '86264', '19', '46268');

-- Target Acquisition Device flags fix
UPDATE `creature_template` SET `unit_flags` = unit_flags | 33554432, `InhabitType` = '4', `MovementType`='1' WHERE entry = 46012;
UPDATE `creature` SET `spawndist` = '10' WHERE id = 46012;
UPDATE `creature` SET `MovementType` = 1 WHERE `guid` IN (245058,244998,244980,244933,244812,244805,244799,244685,244622,244562,244139,244002,243995,243586,243563,243520,243395,243163,243108,242776); 
 
/* 
* sql\updates\world\2012_08_21_00_world_creature.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `spell_id` = 26573;
INSERT INTO `spell_script_names` VALUES
(26573,'spell_pal_consecration');

UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85, `flags_extra` = 128 WHERE `entry` = 43499;

-- Consecration Visual
DELETE FROM `creature_template_addon` WHERE `entry` = 43499;
INSERT INTO `creature_template_addon` VALUES
(43499,0,0,0,0,0,81298); 
 
/* 
* sql\updates\world\2012_08_21_01_world_spell_proc_event.sql 
*/ 
DELETE FROM `spell_proc_event` WHERE `entry` = 63320; 
 
/* 
* sql\updates\world\2012_08_22_00_world_spell_proc_event.sql 
*/ 
DELETE FROM `spell_script_names` WHERE  `spell_id` IN (2825,32182,80353,90355);
INSERT INTO `spell_script_names` VALUES
(2825,'spell_raid_haste'),
(32182,'spell_raid_haste'),
(80353,'spell_raid_haste'),
(90355,'spell_raid_haste');
 
/* 
* sql\updates\world\2013_01_01_00_world_stormwind_gryphon_rider.sql 
*/ 
UPDATE creature_template SET ScriptName = 'npc_stormwind_gryphon_rider' WHERE entry = '51348';
 
 
/* 
* sql\updates\world\2013_01_01_01_world_stormwind_guard.sql 
*/ 
UPDATE creature_template SET ScriptName = 'npc_stormwind_guard' WHERE entry = '68';
 
 
/* 
* sql\updates\world\2013_01_01_02_world_stormwind_harbor_guard.sql 
*/ 
UPDATE creature_template SET ScriptName = 'npc_stormwind_harbor_guard' WHERE entry = '29712';
 
 
/* 
* sql\updates\world\2013_01_01_03_world_stormwind_city_patroler.sql 
*/ 
UPDATE creature_template SET ScriptName = 'npc_stormwind_city_patroller' WHERE entry = '1976';
 
 
/* 
* sql\updates\world\2013_01_01_04_world_stormwind_royal_guard.sql 
*/ 
UPDATE creature_template SET ScriptName = 'npc_stormwind_royal_guard' WHERE entry = '1756';
 
 
/* 
* sql\updates\world\2013_01_05_00_world_skyfire_string.sql 
*/ 
DELETE FROM `skyfire_string` WHERE entry=714;
INSERT INTO `skyfire_string` VALUES ('714', 'Map: %s, Area: %s, Zone: %s, Phase: %u', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
DELETE FROM `skyfire_string` WHERE entry=716;
INSERT INTO `skyfire_string` VALUES ('716', 'Map: %s, Area: %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
 
 
/* 
* sql\updates\world\2013_01_17_00_Human_Start_Script_Fixes.sql 
*/ 
UPDATE creature_template SET ainame="", scriptname="npc_blackrock_battle_worg" WHERE entry=49871;
UPDATE creature_template SET ainame="", scriptname="npc_stormwind_infantry" WHERE entry=49869;

UPDATE creature SET curhealth = 71 WHERE id=49869;

DELETE FROM smart_scripts WHERE entryorguid IN (49869,3871226);

UPDATE creature_template SET unit_flags=559104 WHERE entry=49869;

DELETE FROM creature WHERE guid IN (1503,1502,1501,1500,1499,1498,1497,1504,1505,1506,1507,1508,1509,1510,1511);
DELETE FROM creature WHERE id = 3871226;

INSERT INTO creature VALUES
(1503,49871,0,1,1,22475,49871,-8907.5,-81.2662,87.0249,4.22497,180,0,0,42,0,0,0,0,0),
(1502,49871,0,1,1,22475,49871,-8867.82,-118.155,80.7175,3.49063,180,0,0,42,0,0,0,0,0),
(1501,49871,0,1,1,22475,49871,-8854.82,-131.378,81.3207,3.79694,180,0,0,42,0,0,0,0,0),
(1500,49871,0,1,1,22475,49871,-8834.28,-146.561,80.7984,3.85584,180,0,0,42,0,0,0,0,0),
(1499,49871,0,1,1,22475,49871,-8819.64,-140.266,81.1232,4.07182,180,0,0,42,0,0,0,0,0),
(1498,49871,0,1,1,22475,49871,-8809.08,-150.332,83.0395,3.58488,180,0,0,42,0,0,0,0,0),
(1497,49871,0,1,1,22475,49871,-8805.24,-163.706,81.7227,3.00525,180,0,0,42,0,0,0,0,0),
(1504,49871,0,1,1,22475,49871,-8950.54,-83.8305,88.1096,4.30744,180,0,0,42,0,0,0,0,0),
(1505,49871,0,1,1,22475,49871,-8968.71,-80.7567,87.6939,3.71054,180,0,0,42,0,0,0,0,0),
(1506,49871,0,1,1,22475,49871,-8983.21,-69.4477,89.1003,3.64771,180,0,0,42,0,0,0,0,0),
(1507,49871,0,1,1,22475,49871,-8980.7,-54.1663,91.5915,2.90551,180,0,0,42,0,0,0,0,0),
(1508,49871,0,1,1,22475,49871,-9019.22,-117.442,87.57,1.13836,180,0,0,42,0,0,0,0,0),
(1509,49871,0,1,1,22475,49871,-8999.96,-132.611,84.0323,0.0270168,180,0,0,42,0,0,0,0,0),
(1510,49871,0,1,1,22475,49871,-8985.42,-149.092,81.504,0.270479,180,0,0,42,0,0,0,0,0),
(1511,49871,0,1,1,22475,49871,-8960,-226.453,77.352,0.474666,180,0,0,42,0,0,0,0,0);

DELETE FROM creature_addon WHERE guid IN (1503,1502,1501,1500,1499,1498,1497,1504,1505,1506,1507,1508,1509,1510,1511);
INSERT INTO creature_addon VALUES
(1503,0,0,0,1,0,""),
(1502,0,0,0,1,0,""),
(1501,0,0,0,1,0,""),
(1500,0,0,0,1,0,""),
(1499,0,0,0,1,0,""),
(1498,0,0,0,1,0,""),
(1497,0,0,0,1,0,""),
(1504,0,0,0,1,0,""),
(1505,0,0,0,1,0,""),
(1506,0,0,0,1,0,""),
(1507,0,0,0,1,0,""),
(1508,0,0,0,1,0,""),
(1509,0,0,0,1,0,""),
(1510,0,0,0,1,0,""),
(1511,0,0,0,1,0,"");

DELETE FROM creature_template_addon WHERE entry = 49869;

INSERT INTO creature_template_addon VALUES
(49869,0,0,0,1,0,"");

DELETE FROM creature_text WHERE entry=49869 AND groupid=1 LIMIT 5;
INSERT INTO creature_text VALUES
(49869,1,0,"Come, monsters! We will crush you!",14,0,100,0,0,0,"Stormwind Infantry - Yell"),
(49869,1,1,"I'll kill a hundred more of your battle worgs!",14,0,100,0,0,0,"Stormwind Infantry - Yell"),
(49869,1,2,"Look alive, men! There are orcs and worgs about!",14,0,100,0,0,0,"Stormwind Infantry - Yell"),
(49869,1,3,"Your filthy dogs won't be enough!",14,0,100,0,0,0,"Stormwind Infantry - Yell"),
(49869,1,4,"Your worgs are no match for the might of Stormwind!",14,0,100,0,0,0,"Stormwind Infantry - Yell");

 
 
/* 
* sql\updates\world\2013_01_25_00_Misc_Worgen_Starting_Area_Fixes_and_Script_Names.sql 
*/ 


-- Small Chicken Fix Again
UPDATE creature_template SET speed_run = "0.857143", inhabittype = 1 WHERE entry = 44426;

-- Remove Double Spawn of Rogue Trainer
DELETE FROM creature WHERE guid = 338950;
-- Give her a Dagger
DELETE FROM creature_equip_template WHERE entry = 35871;
INSERT INTO creature_equip_template VALUES
(35871,50055,0,0);
-- Now we set her Bytes2 to Melee Ready (appear ready for combat) AND set her stealthy aura
DELETE FROM creature_template_addon WHERE entry = 35871;
INSERT INTO creature_template_addon VALUES
(35871, 0, 0, 0, 1, 0, '34189');
DELETE FROM creature_addon WHERE guid = 342530;
DELETE FROM creature WHERE guid IN (342530, 246);
INSERT INTO creature VALUES
(246,35871,638,1,2,0,0,-1696.627,1298.148,20.36746,2.234021,600,0,0,42,0,0,0,0,0);

DELETE FROM waypoints WHERE entry IN (3516700,3545600, 3518800, 3517000);

DELETE FROM smart_scripts WHERE entryorguid IN (35077, 35188, 3507700, 35170, 3507701, 3507702, 1415400, 1415401, 1415402, 3871204, 35167, 35456);

DELETE FROM creature_template WHERE entry IN (3871204, 35077);

INSERT INTO creature_template VALUES
(35077,0,0,0,0,0,29593,0,0,0,"Lord Darius Crowley",'','',0,88,88,0,2163,2163,3,1,1.14286,1,1,5,8,0,40,1.5,1111,0,1,0,0,0,0,0,0,0,8,11,0,7,262148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,33,'',0,1,11,1,1,0,0,0,0,0,0,0,0,1,0,613097436,0,"npc_lord_darius_crowley_c1",13623);

UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_alpha_c1" WHERE ENTRY = 35170;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_alpha_c2" WHERE ENTRY = 35167;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_runt_c1" WHERE ENTRY = 35188;
UPDATE creature_template SET AIName = "", flags_extra = 64, scriptname = "npc_worgen_runt_c2" WHERE ENTRY = 35456;
UPDATE creature_template SET AIName = "", scriptname = "npc_sean_dempsey" WHERE ENTRY = 35081;

UPDATE quest_template SET reqcreatureorgoid1 = "0", reqcreatureorgocount1 = "0" WHERE entry = 14154;

-- Not sure why he spawns below the map but this fixes it
UPDATE creature SET position_z = 52.29 WHERE guid = 35077;
 
 
/* 
* sql\updates\world\2013_02_08_00_world_db_updates.sql 
*/ 
-- Drop unused tables from skyfire DB
DROP TABLE IF EXISTS `creature_onkill_reputation`;
DROP TABLE IF EXISTS `game_event_npc_gossip`;

-- DB Realignment

ALTER TABLE `instance_template`
	CHANGE COLUMN `parent` `parent` SMALLINT(5) UNSIGNED NOT NULL AFTER `map`;
	
ALTER TABLE `creature_classlevelstats`
	CHANGE COLUMN `basehp0` `basehp0` INT(10) NOT NULL AFTER `class`,
	CHANGE COLUMN `basehp1` `basehp1` INT(10) NOT NULL AFTER `basehp0`,
	CHANGE COLUMN `basehp2` `basehp2` INT(10) NOT NULL AFTER `basehp1`;	

ALTER TABLE `gameobject_template`
	CHANGE COLUMN `data24` `data24` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data23`,
	CHANGE COLUMN `data25` `data25` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data24`,
	CHANGE COLUMN `data26` `data26` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data25`,
	CHANGE COLUMN `data27` `data27` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data26`,
	CHANGE COLUMN `data28` `data28` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data27`,
	CHANGE COLUMN `data29` `data29` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data28`,
	CHANGE COLUMN `data30` `data30` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data29`,
	CHANGE COLUMN `data31` `data31` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data30`,
	CHANGE COLUMN `WDBVerified` `WDBVerified` SMALLINT(6) NULL DEFAULT '1' AFTER `ScriptName`;	
ALTER TABLE `game_event`
	CHANGE COLUMN `EventEntry` `EventEntry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `game_event_battleground_holiday`
	CHANGE COLUMN `eventEntry` `eventEntry` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `game_event_condition`
	CHANGE COLUMN `eventEntry` `eventEntry` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' FIRST;

ALTER TABLE `instance_template`
	CHANGE COLUMN `allowMount` `allowMount` TINYINT(3) NOT NULL DEFAULT '0' AFTER `script`;
	
ALTER TABLE `spell_proc_event`
	CHANGE COLUMN `SpellFamilyMask0` `SpellFamilyMask0` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyName`,
	CHANGE COLUMN `SpellFamilyMask1` `SpellFamilyMask1` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyMask0`,
	CHANGE COLUMN `SpellFamilyMask2` `SpellFamilyMask2` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyMask1`;
ALTER TABLE `spell_proc`
	CHANGE COLUMN `charges` `charges` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `cooldown`;
	
ALTER TABLE `spell_enchant_proc_data`
	CHANGE COLUMN `procEx` `procEx` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `PPMChance`;
	
ALTER TABLE `item_template`
	CHANGE COLUMN `spellcharges_1` `spellcharges_1` SMALLINT(6) NULL DEFAULT NULL AFTER `spelltrigger_1`;
	
ALTER TABLE `quest_template`
   CHANGE COLUMN `Method` `Method` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '2' AFTER `entry`,
	CHANGE COLUMN `ZoneOrSort` `ZoneOrSort` MEDIUMINT(8) NOT NULL DEFAULT '0' AFTER `Method`,
	CHANGE COLUMN `MinLevel` `MinLevel` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SkillOrClassMask`,
	CHANGE COLUMN `MaxLevel` `MaxLevel` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `MinLevel`,
	CHANGE COLUMN `QuestLevel` `QuestLevel` MEDIUMINT(8) NOT NULL DEFAULT '1' AFTER `MaxLevel`,
	CHANGE COLUMN `Type` `Type` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `QuestLevel`,
	CHANGE COLUMN `RequiredSkillValue` `RequiredSkillValue` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredRaces`,
	CHANGE COLUMN `RepObjectiveFaction` `RepObjectiveFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredSkillValue`,
	CHANGE COLUMN `RepObjectiveFaction2` `RepObjectiveFaction2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RepObjectiveValue`,
	CHANGE COLUMN `RequiredMinRepFaction` `RequiredMinRepFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RepObjectiveValue2`,
	CHANGE COLUMN `RequiredMaxRepFaction` `RequiredMaxRepFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredMinRepValue`,
	CHANGE COLUMN `PointMapId` `PointMapId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewMailDelaySecs`,
	CHANGE COLUMN `SuggestedPlayers` `SuggestedPlayers` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredMaxRepValue`,
	CHANGE COLUMN `SpecialFlags` `SpecialFlags` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `QuestFlags`,
	CHANGE COLUMN `CharTitleId` `CharTitleId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SpecialFlags`,
	CHANGE COLUMN `PlayersSlain` `PlayersSlain` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `CharTitleId`,
	CHANGE COLUMN `BonusTalents` `BonusTalents` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `PlayersSlain`,
	CHANGE COLUMN `RewardArenaPoints` `RewardArenaPoints` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `BonusTalents`,
	CHANGE COLUMN `RewXPId` `RewXPId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `NextQuestInChain`,
	CHANGE COLUMN `SrcItemCount` `SrcItemCount` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SrcItemId`,
	CHANGE COLUMN `ReqItemCount1` `ReqItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemId6`,
	CHANGE COLUMN `ReqItemCount2` `ReqItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount1`,
	CHANGE COLUMN `ReqItemCount3` `ReqItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount2`,
	CHANGE COLUMN `ReqItemCount4` `ReqItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount3`,
	CHANGE COLUMN `ReqItemCount5` `ReqItemCount5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount4`,
	CHANGE COLUMN `ReqItemCount6` `ReqItemCount6` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount5`,
	CHANGE COLUMN `ReqSourceCount1` `ReqSourceCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceId4`,
	CHANGE COLUMN `ReqSourceCount2` `ReqSourceCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount1`,
	CHANGE COLUMN `ReqSourceCount3` `ReqSourceCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount2`,
	CHANGE COLUMN `ReqSourceCount4` `ReqSourceCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount3`,
	CHANGE COLUMN `ReqCreatureOrGOCount1` `ReqCreatureOrGOCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOId4`,
	CHANGE COLUMN `ReqCreatureOrGOCount2` `ReqCreatureOrGOCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount1`,
	CHANGE COLUMN `ReqCreatureOrGOCount3` `ReqCreatureOrGOCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount2`,
	CHANGE COLUMN `ReqCreatureOrGOCount4` `ReqCreatureOrGOCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount3`,
	CHANGE COLUMN `RewChoiceItemCount1` `RewChoiceItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemId6`,
	CHANGE COLUMN `RewChoiceItemCount2` `RewChoiceItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount1`,
	CHANGE COLUMN `RewChoiceItemCount3` `RewChoiceItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount2`,
	CHANGE COLUMN `RewChoiceItemCount4` `RewChoiceItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount3`,
	CHANGE COLUMN `RewChoiceItemCount5` `RewChoiceItemCount5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount4`,
	CHANGE COLUMN `RewChoiceItemCount6` `RewChoiceItemCount6` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount5`,
    CHANGE COLUMN `RewItemCount1` `RewItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemId4`,
	CHANGE COLUMN `RewItemCount2` `RewItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount1`,
	CHANGE COLUMN `RewItemCount3` `RewItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount2`,
	CHANGE COLUMN `RewItemCount4` `RewItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount3`,
	CHANGE COLUMN `RewRepFaction1` `RewRepFaction1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewItemCount4`,
	CHANGE COLUMN `RewRepFaction2` `RewRepFaction2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction1`,
	CHANGE COLUMN `RewRepFaction3` `RewRepFaction3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction2`,
	CHANGE COLUMN `RewRepFaction4` `RewRepFaction4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction3`,
	CHANGE COLUMN `RewRepFaction5` `RewRepFaction5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction4`,
	CHANGE COLUMN `DetailsEmote1` `DetailsEmote1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `PointOpt`,
	CHANGE COLUMN `DetailsEmote2` `DetailsEmote2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote1`,
	CHANGE COLUMN `DetailsEmote3` `DetailsEmote3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote2`,
	CHANGE COLUMN `DetailsEmote4` `DetailsEmote4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote3`,	
	CHANGE COLUMN `IncompleteEmote` `IncompleteEmote` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmoteDelay4`,
	CHANGE COLUMN `CompleteEmote` `CompleteEmote` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `IncompleteEmote`,
	CHANGE COLUMN `OfferRewardEmote1` `OfferRewardEmote1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `CompleteEmote`,
	CHANGE COLUMN `OfferRewardEmote2` `OfferRewardEmote2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote1`,
	CHANGE COLUMN `OfferRewardEmote3` `OfferRewardEmote3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote2`,
	CHANGE COLUMN `OfferRewardEmote4` `OfferRewardEmote4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote3`;	
	
ALTER TABLE `game_event`
	CHANGE COLUMN `EventEntry` `EventEntry` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `vehicle_accessory`
	CHANGE COLUMN `seat_id` `seat_id` TINYINT(4) NOT NULL DEFAULT '0' AFTER `accessory_entry`,
	CHANGE COLUMN `minion` `minion` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `seat_id`,
	CHANGE COLUMN `summontype` `summontype` TINYINT(3) NOT NULL DEFAULT '0' AFTER `description`;

ALTER TABLE `vehicle_template_accessory`
	CHANGE COLUMN `seat_id` `seat_id` TINYINT(4) NOT NULL DEFAULT '0' AFTER `accessory_entry`,
	CHANGE COLUMN `minion` `minion` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `seat_id`,
	CHANGE COLUMN `summontype` `summontype` TINYINT(3) UNSIGNED NOT NULL DEFAULT '6' COMMENT 'see enum TempSummonType' AFTER `description`;
	
ALTER TABLE `instance_encounters`
	CHANGE COLUMN `lastEncounterDungeon` `lastEncounterDungeon` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'If not 0, LfgDungeon.dbc entry for the instance it is last encounter in' AFTER `creditEntry`;	
	
ALTER TABLE `game_graveyard_zone`
	CHANGE COLUMN `faction` `faction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ghost_zone`;	
	
ALTER TABLE `game_event_seasonal_questrelation`
	CHANGE COLUMN `eventEntry` `eventEntry` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Entry of the game event' AFTER `questId`;

ALTER TABLE `npc_spellclick_spells`
	CHANGE COLUMN `user_type` `user_type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'relation with summoner: 0-no 1-friendly 2-raid 3-party player can click' AFTER `cast_flags`;
	
ALTER TABLE `guild_xp_for_level`
	CHANGE COLUMN `xp_for_next_level` `xp_for_next_level` INT(20) NOT NULL AFTER `lvl`;	
	
ALTER TABLE `item_loot_template`
	CHANGE COLUMN `maxcount` `maxcount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `mincountOrRef`;	
	
ALTER TABLE `skill_fishing_base_level`
	CHANGE COLUMN `skill` `skill` MEDIUMINT(8) NOT NULL DEFAULT '0' COMMENT 'Base skill level requirement' AFTER `entry`;
	
ALTER TABLE `script_texts`
	CHANGE COLUMN `type` `type` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `sound`,
	CHANGE COLUMN `language` `language` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `type`,
	CHANGE COLUMN `emote` `emote` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `language`;
	 
 
/* 
* sql\updates\world\2013_02_08_01_world_command.sql 
*/ 
UPDATE IGNORE `command` SET `name`='reload creature_onkill_reward', `help`='Syntax: .reload creature_onkill_reward\r\nReload creature_onkill_reward table.' WHERE  `name`='reload creature_onkill_reputation' LIMIT 1; 
 
/* 
* sql\updates\world\2013_02_10_00_Worgen_Infection_and_Phase_4_Shift_&_Multiple_Other_Gilneas_Fixes.sql 
*/ 

UPDATE creature_template SET AIName = "", scriptname = "npc_josiah_avery_p2" WHERE entry = 35369;

UPDATE creature_template SET AIName = "", scriptname = "npc_lorna_crowley_p4" WHERE entry = 35378;

UPDATE creature_template SET AIName = "", scriptname = "npc_king_genn_greymane_p4" WHERE entry = 35550; 

UPDATE creature_template SET flags_extra = 64 WHERE entry IN (35170, 35167, 35188, 35456);

UPDATE quest_template SET questflags = 0, specialflags = 0 WHERE entry IN (14285, 14286, 14287, 14288, 14289, 14290, 14291); 

UPDATE creature_template SET AIName = "", scriptname = "npc_gwen_armstead_p2" WHERE entry = 35840;

UPDATE creature_text SET groupid = 1 WHERE entry = 35550 LIMIT 3;

UPDATE quest_template SET questflags = 0, nextquestinchain = 14293 WHERE entry = 14214;

DELETE FROM `creature_template` WHERE `entry`=35631 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 35631, 0, 0, 0, 0, 0, 30213, 30210, 30211, 30212, "Gilnean Mastiff", "", "", 0, 4, 4, 0, 35, 35, 0, 1.0, 1.14286, 1.0, 0, 5, 7, 0, 24, 1.0, 0, 0, 1, 8, 0, 52, 0, 0, 0, 0, 5, 7, 24, 1, 1, 0, 0, 0, 0, 0, 47, 1, 30, 0, 67805, 0, 0, 0, 0, 0, 0, 0, 10510, 0, 0, 0, "", 0, 3, 0.0, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, "npc_gilnean_mastiff", "13623");

DELETE FROM `creature_template` WHERE `entry`=35463 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 35463, 0, 0, 0, 0, 0, 36781, 0, 0, 0, "Bloodfang Lurker", "", "", 0, 3, 4, 0, 16, 16, 0, 1.0, 1.14286, 1.0, 0, 7, 8, 0, 28, 1.2, 0, 0, 2, 512, 0, 0, 0, 0, 0, 0, 7, 8, 28, 7, 0, 35463, 0, 0, 0, 90, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 1, 2.0723, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, "npc_bloodfang_lurker", "13623");

DELETE FROM `creature_template` WHERE `entry`=50415 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 50415, 0, 0, 0, 0, 0, 20570, 11686, 0, 0, "Josiah Event Trigger", "", "", 0, 1, 1, 0, 35, 35, 0, 1.0, 1.14286, 1.0, 0, 2, 2, 0, 24, 1.0, 0, 0, 1, 134, 0, 0, 0, 0, 0, 0, 2, 2, 24, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 3, 1.35, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 128, "npc_josiah_avery_trigger", "13623");

DELETE FROM creature_text WHERE entry = 50415 AND groupid = 1 LIMIT 1;
INSERT INTO creature_text VALUES (50415,1,0,"You've been bitten by a worgen. It's probably nothing, but it sure stings a little.$B$B|TInterface\Icons\INV_Misc_monsterfang_02.blp:32|t",42,0,100,0,0,0,"Josiah Event Trigger");

DELETE FROM smart_scripts WHERE entryorguid IN (35369, 35370, 35631, 35463, 3537000, 35550, 35378, 3871205, 50474, 50471, 5026000, 5026000, 5026001, 5026001, 5026002, 5026002, 5026003, 5026003, 5026004, 5026004, 5026005, 5026005, 5026006, 5026006, 5026007, 5026007, -1418, -1419, -1420, -1421, -1422, -1423, -1424, -1425, -1426, -1427, -1428, -1429, -1430, -1431, -1432, -1433, -1434, -1435, -1436, -1437, -1438, -1439); -- Remove unused SAI scripts

DELETE FROM creature_template WHERE entry = 3871205; -- Remove old custom Lorna from DB - no longer needed 

UPDATE quest_template SET rewspellcast = 0 WHERE entry = 14204; -- This will be done through core scripting now

DELETE FROM creature WHERE guid = 338949; -- duplicate spawn

DELETE FROM creature WHERE id = 35463;
INSERT INTO creature VALUES
(911,35463,638,1,4,0,0,-1746.25,1516.59,26.8466,3.91994,300,3,0,172,104,1,0,0,0),
(912,35463,638,1,4,0,0,-1719.09,1482.57,22.9173,3.66783,300,5,0,172,104,1,0,0,0),
(913,35463,638,1,4,0,0,-1725.19,1478.43,23.8691,0.569429,300,6,0,172,104,1,0,0,0),
(914,35463,638,1,4,0,0,-1767.99,1514.33,26.4892,3.228,300,2,0,172,104,1,0,0,0),
(915,35463,638,1,4,0,0,-1764.61,1452.77,20.3364,4.1461,300,5,0,172,104,1,0,0,0),
(916,35463,638,1,4,0,0,-1763.41,1471.27,22.2031,5.09251,300,3,0,172,104,1,0,0,0),
(917,35463,638,1,4,0,0,-1763.41,1471.27,22.2031,5.09251,300,2,0,172,104,1,0,0,0),
(918,35463,638,1,4,0,0,-1764.83,1467.7,21.5091,1.23149,300,7,0,172,104,1,0,0,0),
(919,35463,638,1,4,0,0,-1764.82,1457.56,20.5486,1.61791,300,5,0,172,104,1,0,0,0),
(920,35463,638,1,4,0,0,-1761.8,1450.64,21.2129,4.75165,300,5,0,172,104,1,0,0,0),
(921,35463,638,1,4,0,0,-1787.96,1452.54,19.3604,3.09594,300,0,0,172,104,0,0,0,0),
(922,35463,638,1,4,0,0,-1806.9,1448.96,18.9908,4.98561,300,0,0,172,104,0,0,0,0),
(923,35463,638,1,4,0,0,-1805.65,1464.36,18.9394,1.8558,300,0,0,172,104,0,0,0,0),
(924,35463,638,1,4,0,0,-1805.46,1485.12,19.4559,1.44582,300,0,0,172,104,0,0,0,0),
(925,35463,638,1,4,0,0,-1789.94,1481.71,20.0719,5.74902,300,0,0,172,104,0,0,0,0),
(926,35463,638,1,4,0,0,-1803.7,1497.04,19.7457,1.5707,300,0,0,172,104,0,0,0,0),
(927,35463,638,1,4,0,0,-1802.49,1515.7,19.7831,1.0759,300,0,0,172,104,0,0,0,0),
(928,35463,638,1,4,0,0,-1792.27,1522.61,20.1585,0.430305,300,0,0,172,104,0,0,0,0),
(929,35463,638,1,4,0,0,-1785.37,1511.63,19.7823,5.66734,300,0,0,172,104,0,0,0,0),
(930,35463,638,1,4,0,0,-1767.05,1508.61,26.4891,0.0242534,300,0,0,172,104,0,0,0,0),
(931,35463,638,1,4,0,0,-1746.6,1511.85,26.2231,0.0902268,300,0,0,172,104,0,0,0,0),
(932,35463,638,1,4,0,0,-1731.64,1509.93,26.2231,5.65242,300,0,0,172,104,0,0,0,0),
(933,35463,638,1,4,0,0,-1730.5,1471.14,24.1399,5.11677,300,0,0,172,104,0,0,0,0),
(934,35463,638,1,4,0,0,-1760.86,1496.46,26.223,4.63454,300,0,0,172,104,0,0,0,0),
(935,35463,638,1,4,0,0,-1809.18,1436.2,19.4122,1.77647,300,0,0,172,104,0,0,0,0);

UPDATE creature_text SET groupid = 1 WHERE entry = 50474 LIMIT 3;

UPDATE creature_template SET AIName = "", scriptname = "npc_gilneas_city_guard_p8" WHERE entry = 50474;

UPDATE creature_template SET AIName = "", scriptname = "npc_afflicted_gilnean_p8" WHERE entry = 50471;

UPDATE creature_template SET AIName = "", scriptname = "npc_gilnean_crow" WHERE entry = 50260;

DELETE FROM creature_template WHERE entry = 3871206;

DELETE FROM creature WHERE id = 3871206;

DELETE FROM gameobject WHERE id = 207417 LIMIT 4;
INSERT INTO gameobject VALUES
(140, 207417, 638, 1, 2047, -1611.9, 1312.53, 18.3812, 3.29631, 0, 0, 0.997009, -0.0772822, 300, 0, 1),
(141, 207417, 638, 1, 2047, -1626.86, 1310.16, 20.3633, 0.221471, 0, 0, 0.110509, 0.993875, 300, 0, 1),
(142, 207417, 638, 1, 2047, -1403.83, 1432.14, 35.5562, 1.5535, 0, 0, 0.700967, 0.713194, 300, 0, 1),
(143, 207417, 638, 1, 2047, -1798.65, 1549.93, 22.7365, 1.51812, 0, 0, 0.688241, 0.725482, 300, 0, 1);

UPDATE creature SET id = 50260 WHERE guid IN (1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430, 1431, 1432, 1433, 1434, 1435, 1436, 1437, 1438, 1439);

DELETE FROM creature WHERE guid IN (1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430, 1431, 1432, 1433, 1434, 1435, 1436, 1437, 1438, 1439, 951, 952, 953, 954, 955, 956, 957, 958, 959, 960, 961, 962, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980);

DELETE FROM creature_addon WHERE guid IN (1418, 1419, 1420, 1421, 1422, 1423, 1424, 1425, 1426, 1427, 1428, 1429, 1430, 1431, 1432, 1433, 1434, 1435, 1436, 1437, 1438, 1439, 951, 952, 953, 954, 955, 956, 957, 958, 959, 960, 961, 962, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980);

INSERT INTO creature_addon VALUES
(951, 0, 0, 0, 0, 455, ""),
(952, 0, 0, 0, 0, 455, ""),
(953, 0, 0, 0, 0, 455, ""),
(954, 0, 0, 0, 0, 455, ""),
(955, 0, 0, 0, 0, 455, ""),
(956, 0, 0, 0, 0, 455, ""),
(957, 0, 0, 0, 0, 455, ""),
(958, 0, 0, 0, 0, 455, ""),
(959, 0, 0, 0, 0, 455, ""),
(960, 0, 0, 0, 0, 455, ""),
(961, 0, 0, 0, 0, 455, ""),
(962, 0, 0, 0, 0, 455, ""),
(963, 0, 0, 0, 0, 455, ""),
(964, 0, 0, 0, 0, 455, ""),
(965, 0, 0, 0, 0, 455, ""),
(966, 0, 0, 0, 0, 455, ""),
(967, 0, 0, 0, 0, 455, ""),
(968, 0, 0, 0, 0, 455, ""),
(969, 0, 0, 0, 0, 455, ""),
(970, 0, 0, 0, 0, 455, ""),
(971, 0, 0, 0, 0, 455, ""),
(972, 0, 0, 0, 0, 455, ""),
(973, 0, 0, 0, 0, 455, ""),
(974, 0, 0, 0, 0, 455, ""),
(975, 0, 0, 0, 0, 455, ""),
(976, 0, 0, 0, 0, 455, ""),
(977, 0, 0, 0, 0, 455, ""),
(978, 0, 0, 0, 0, 455, ""),
(979, 0, 0, 0, 0, 455, ""),
(980, 0, 0, 0, 0, 455, "");

INSERT INTO creature VALUES
(951, 50260, 638, 1, 2047, 0, 0, -1796.01, 1549.16, 22.726, 0.963629, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(952, 50260, 638, 1, 2047, 0, 0, -1801.02, 1551.07, 22.7451, 3.16274, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(953, 50260, 638, 1, 2047, 0, 0, -1800.82, 1547.72, 22.7376, 4.77517, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(954, 50260, 638, 1, 2047, 0, 0, -1797.94, 1545.4, 22.5087, 5.9352, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(955, 50260, 638, 1, 2047, 0, 0, -1798.71, 1548.19, 22.7355, 1.87391, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(956, 50260, 638, 1, 2047, 0, 0, -1797.43, 1552.06, 22.7326, 1.19768, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(957, 50260, 638, 1, 2047, 0, 0, -1799.29, 1550.65, 22.7378, 3.79264, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(958, 50260, 638, 1, 2047, 0, 0, -1799.7, 1553.23, 22.741, 1.72861, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(959, 50260, 638, 1, 2047, 0, 0, -1404.77, 1439.38, 35.556, 4.28982, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(960, 50260, 638, 1, 2047, 0, 0, -1402.46, 1437.24, 35.5559, 1.13566, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(961, 50260, 638, 1, 2047, 0, 0, -1400.51, 1441.15, 35.5559, 3.28529, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(962, 50260, 638, 1, 2047, 0, 0, -1403.77, 1441.6, 35.5559, 4.21835, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(963, 50260, 638, 1, 2047, 0, 0, -1406.25, 1441.85, 35.5559, 4.1241, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(964, 50260, 638, 1, 2047, 0, 0, -1409.18, 1438.57, 35.947, 6.2164, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(965, 50260, 638, 1, 2047, 0, 0, -1407.22, 1439.84, 35.5561, 6.11273, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(966, 50260, 638, 1, 2047, 0, 0, -1401.44, 1438.85, 35.5561, 1.90299, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(967, 50260, 638, 1, 2047, 0, 0, -1406.2, 1436.88, 35.5561, 1.22441, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(968, 50260, 638, 1, 2047, 0, 0, -1401.86, 1440.29, 35.5561, 3.51463, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(969, 50260, 638, 1, 2047, 0, 0, -1399.08, 1437.95, 35.5561, 3.1557, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(970, 50260, 638, 1, 2047, 0, 0, -1616.96, 1317.65, 19.1091, 4.37548, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(971, 50260, 638, 1, 2047, 0, 0, -1617.03, 1309.57, 19.3648, 1.83393, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(972, 50260, 638, 1, 2047, 0, 0, -1615.77, 1306.3, 19.2244, 2.5565, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(973, 50260, 638, 1, 2047, 0, 0, -1619.88, 1307.22, 19.9435, 1.9596, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(974, 50260, 638, 1, 2047, 0, 0, -1619.39, 1310.94, 19.7299, 0.420211, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(975, 50260, 638, 1, 2047, 0, 0, -1617.5, 1312.99, 19.35, 5.82061, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(976, 50260, 638, 1, 2047, 0, 0, -1619.84, 1314.45, 19.6611, 0.307109, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(977, 50260, 638, 1, 2047, 0, 0, -1622.55, 1312.44, 20.0398, 0.0440004, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(978, 50260, 638, 1, 2047, 0, 0, -1621.57, 1314.44, 19.9151, 1.53626, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(979, 50260, 638, 1, 2047, 0, 0, -1621.55, 1309.14, 20.0544, 5.98946, 30, 0, 0, 42, 0, 0, 0, 0, 0),
(980, 50260, 638, 1, 2047, 0, 0, -1615.11, 1310.87, 18.9664, 1.13177, 30, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE conditions SET conditionvalue2 = 50260 WHERE sourceentry = 93275 LIMIT 1;
 
 
/* 
* sql\updates\world\2013_02_10_01_world_misc.sql 
*/ 
-- Health, faction, damage and level fixes for mobs in Blackrock Caverns

UPDATE creature_template SET health_mod=15, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=530, maxdmg=713, attackpower=827, baseattacktime=2000 WHERE entry IN (39708,39980,39982,39985,39978,39985,40004,40019,40017,40021,50284);
UPDATE creature_template SET `Health_mod`=22.8152 WHERE entry IN (39665, 39698);
UPDATE creature_template SET health_mod=45.05232558139535, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=545, maxdmg=723, attackpower=839, dmg_multiplier=7.5, baseattacktime=2000 WHERE entry IN (39987,39994,40023);
UPDATE creature_template SET health_mod=3, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=470, maxdmg=650, attackpower=750, baseattacktime=2000 WHERE entry IN (40084);
 
 
/* 
* sql\updates\world\2013_02_15_00_world_misc.sql 
*/ 
-- Fix Mage's Tol barad Portals and Teleports

UPDATE gameobject_template SET data0=88341 WHERE entry=206615; -- ally portal
UPDATE gameobject_template SET data0=88339 WHERE entry=206616; -- horde portal

DELETE FROM spell_target_position WHERE id IN (88342, 88344);
INSERT INTO spell_target_position VALUES
(88342, 732, -334.60, 1043.80, 21.900, 1.5), -- ally teleport
(88344, 732, -601.40, 1382.03, 21.900, 1.5), -- horde teleport
(89597, 732, -334.60, 1043.80, 21.900, 1.5); -- Baradin's Wardens Tabard (63379)
 
 
/* 
* sql\updates\world\2013_02_15_01_world_spell_script_names.sql 
*/ 
-- Removing Blast Wave effect it no longer exists.
DELETE FROM spell_script_names WHERE spell_id=-11113;
 
 
/* 
* sql\updates\world\2013_02_16_00_world_gilneas_save_krennan_cinema_sai_to_core_script_conversion.sql 
*/ 
UPDATE creature_template SET AIName = "", scriptname = "npc_lord_godfrey_p4_8" WHERE entry = 35906;

UPDATE creature_template SET AIName = "", scriptname = "npc_commandeered_cannon" WHERE entry = 35914;

UPDATE creature_template SET AIName = "" WHERE entry =50420;

DELETE FROM smart_scripts WHERE entryorguid IN (5042000, 50420, 35096, 35914);

DELETE FROM creature WHERE guid = 69;
INSERT INTO creature VALUES (69, 35753, 638, 1, 4, 0, 0, -1674.45, 1349.29, 20.38, 6.15351, 15, 0, 0, 102, 0, 0, 0, 0, 0);

DELETE FROM creature_text WHERE entry = 35753;
INSERT INTO creature_text VALUES (35753, 0, 1, 'Help!  Up here!', 14, 0, 100, 0, 0, 20921, 'Krennan Aranas In Tree');

DELETE FROM creature_template_addon WHERE entry = 3871227;
DELETE FROM creature_addon WHERE guid = 69;
INSERT INTO creature_addon VALUES (69, 0, 0, 0, 0, 473, "");

DELETE FROM creature_template WHERE entry = 3871227;
UPDATE creature_template SET inhabittype = 7 WHERE entry = 35753;

UPDATE creature_template SET unit_flags = 512 WHERE entry = 35509;
UPDATE creature_template SET unit_flags = 134 WHERE entry = 35914;

DELETE FROM script_texts WHERE entry IN (-1999971, -1999972);

DELETE FROM creature_text WHERE entry = 35907;

INSERT INTO creature_text VALUES (35907, 0, 0, "Thank you! I owe you my life.", 12, 0, 0, 1, 0, 20922, "Saved Krennan Aranas");

DELETE FROM conditions WHERE conditionvalue2 = 3871227 LIMIT 1;
 
 
/* 
* sql\updates\world\2013_02_16_01_world_conditions.sql 
*/ 
-- Remove unused condition.
DELETE FROM `conditions` WHERE `SourceEntry`=86264; 
 
/* 
* sql\updates\world\2013_02_17_00_world_spell_script_names .sql 
*/ 
-- Change the spell ID's for spell_gen_av_drekthar_presence.
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_gen_av_drekthar_presence";

INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45822, 'spell_gen_av_drekthar_presence'),
(45823, 'spell_gen_av_drekthar_presence'),
(45824, 'spell_gen_av_drekthar_presence'),
(45826, 'spell_gen_av_drekthar_presence'),
(45828, 'spell_gen_av_drekthar_presence'),
(45829, 'spell_gen_av_drekthar_presence'),
(45830, 'spell_gen_av_drekthar_presence');

-- Removed spell not found in DBC for "spell_dk_death_coil"
DELETE FROM `spell_script_names` WHERE `spell_id`= -62900; 
 
/* 
* sql\updates\world\2013_02_17_01_world_creature_addon.sql 
*/ 
-- Remove unused creature addons.
DELETE FROM `creature_addon` WHERE `guid`=6430673;
DELETE FROM `creature_addon` WHERE `guid`=6430776; 
 
/* 
* sql\updates\world\2013_02_18_00_world_gameobject_template.sql 
*/ 
-- Update data fields for non lootable game objects.
UPDATE gameobject_template SET data0=0, data1=0 WHERE entry IN(173234, 19542, 202137, 181839, 106318, 177726, 160845, 175331, 176215, 142184, 141596, 203373, 175487, 337, 173232, 3240, 194821, 181837, 203288, 161495, 28414, 175329, 176213, 203102, 175322, 202179, 153453, 182526, 39726, 39709, 3238, 176645, 193967, 28238, 105570, 1759, 175166, 203286, 180905, 184933, 194463, 194424, 148842, 203100, 39345, 202177, 1571, 39779, 153451, 203061, 103664, 39717, 206786, 194314, 28565, 177805, 176643, 2857, 185900, 83763, 181757, 176248, 3661, 177681, 202896, 39791, 204297, 179006, 175488, 194312, 179548, 188192, 28561, 176641, 2855, 187021, 12654, 35876, 186325, 202554, 202212, 188066, 39791, 206890, 179004, 35934, 142477, 175245, 39770, 181287, 28556, 175950, 2846, 103713, 3767, 186672, 144064, 165554, 193603, 202552, 334, 202745, 176639, 190613, 175785, 202775, 176327, 178504, 203138, 3694, 2772, 206996, 190696, 92013, 39788, 186831, 184847, 113772, 39706, 176637, 193996, 39694, 180392, 176325, 177790, 2842, 184622, 3763, 180346, 13872, 126049, 180167, 201384, 3646, 187674, 39705, 192081, 27848, 4149, 186744, 184691, 184620, 186634, 142076, 202351, 35556, 3690, 196465, 74448, 50937, 180165, 203396, 153471, 203017, 201924, 178105, 2714, 124389, 2884, 176360, 103574, 39507, 193092, 177747, 2404120, 11714, 50935, 39786, 38652, 181628, 176089, 131979, 153469, 34773, 203015, 203387, 103820, 39756, 142088, 89635, 186740, 186467, 103774, 164662, 74731, 193944, 21148, 193905, 39336, 194957, 26961, 29658, 2710, 113757, 176356, 201874, 186667, 185574, 201803, 73939, 185567, 21146, 149483, 175892, 192190, 190718, 180228, 153472, 206839, 27848, 26959, 2708, 202081, 186736, 201872, 201801, 176308, 206410, 190484, 149481, 39335, 206952, 75299, 192188, 19020, 207494, 104574, 153463, 27080, 2054, 175966, 175385, 201799, 142344, 188367, 35469, 175888, 75297, 194200, 204279, 202876, 179025, 176189, 195323, 181620, 179914, 86492, 2743, 176150, 39702, 194324, 180690, 272, 190558, 20807, 175964, 205246, 176304, 184980, 195709, 202339, 24734, 3710, 19870, 19597, 123332, 175264, 201572, 179533, 193197, 183933, 190563, 33841, 195374, 161513, 203230, 3715, 202337, 39820, 184599, 178245, 19868, 19595, 206289, 203453, 150079, 180654, 179492, 190561, 105581, 187238, 34736, 39844, 202608, 19873, 39822, 142191, 178785, 39344, 35540, 191179, 179490, 105579, 18036, 181876, 202574, 3743, 165739, 186648, 181109, 3704, 207523, 35368, 19283, 104564, 176112, 201977, 203410, 179488, 181874, 3702, 175334, 39335, 180216, 194158, 150080, 157936, 204880, 121264, 177844, 181872, 184938, 39495, 35358, 202864, 179562, 164798, 17155, 19541, 4095, 195201, 58, 194822, 202607, 205884, 251, 184936, 175330, 35356, 203103, 202180, 153454, 39726, 3239, 178584, 203287, 147557, 186640, 128308, 142181, 203101, 184849, 9630, 194315, 39708, 35331, 3237, 177806, 2656, 140971, 2858, 105569, 175165, 186404, 205538, 103711, 184932, 125477, 176249, 194423, 203099, 179007, 173266, 194313, 39774, 28563, 177804, 176642, 36123, 201710, 179703, 184930, 175565, 203104, 3660, 202863, 190354, 39792, 203097, 192676, 192127, 179005, 28559, 176640, 3768, 40107, 177926, 28604, 202560, 169243, 160836, 202553, 35990, 190614, 28553, 175407, 2852, 175949, 179426, 179008, 333, 176638, 190612, 2850, 2843, 3764, 181098, 3693, 178464, 144054, 205144, 180168, 35989, 103662, 1594, 331, 39706, 192082, 176636, 188525, 187875, 2848, 153123, 184621, 177750, 3691, 184304, 196466, 184814, 180166, 39787, 20726, 178106, 39701, 187981, 176634, 182063, 203312, 184619, 203172, 39701, 186633, 39488, 35556, 50936, 180164, 181629, 191536, 153470, 203016, 178104, 181898, 103821, 39756, 124388, 2883, 177792, 186741, 186468, 203209, 85562, 193091, 11713, 1691, 181085, 181627, 177287, 131978, 153468, 203014, 190643, 194331, 39507, 89634, 177241, 186739, 201875, 186466, 178325, 21147, 181671, 3685, 39846, 175893, 192191, 204284, 181083, 190719, 194956, 180229, 153473, 201579, 26960, 2709, 202082, 201802, 176309, 203198, 2560, 21145, 35467, 175588, 149482, 175891, 39336, 192189, 40061, 19021, 204282, 190717, 104575, 27848, 153464, 20920, 194327, 2707, 203311, 202080, 2055, 179832, 35572, 128403, 201800, 176307, 192536, 175928, 190483, 1667, 39488, 194789, 175889, 128293, 192187, 194201, 204280, 39343, 191535, 195324, 206905, 176151, 153462, 35518, 152608, 161557, 194325, 180691, 179497, 2907, 175802, 176344, 175384, 185569, 185562, 195710, 192192, 202340, 39819, 194238, 75296, 19871, 179644, 19598, 123333, 35331, 202875, 179024, 176188, 58369, 203307, 175970, 195375, 92423, 175382, 36086, 34991, 202338, 39821, 178246, 39342, 19869, 19596, 123331, 104569, 152094, 184862, 182506, 179532, 39754, 35540, 193196, 190562, 123214, 179486, 33839, 179826, 2554, 201794, 39845, 3714, 202336, 3707, 178244, 123329, 39345, 186263, 39341, 176145, 180754, 186734, 190560, 202065, 39843, 19872, 177624, 19284, 35948, 178784, 191458, 39340, 179528, 203032, 2084, 23505, 187072, 105578, 181875, 39842, 35358, 165738, 175886, 181108, 3703, 38644, 194159, 150081, 141979, 203409, 179526, 201937, 4096, 181873, 184939, 176224, 175606, 181687, 203113, 19861, 180215, 126260, 201974);
 
 
/* 
* sql\updates\world\2013_03_03_00_world_misc.sql 
*/ 
-- Exarch Menelaous - Missing condition for gossip 7370
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=7370 AND `SourceEntry`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,7370,0,0,0,9,9456,0,0,0,0,'','Exarch Menelaous - Show gossip option if player has quest 9456');
 
 
/* 
* sql\updates\world\2013_03_03_01_world_conditions.sql 
*/ 
-- Exarch Menelaous - Missing condition for gossip 7370
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=7370 AND `SourceEntry`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,7370,0,0,0,9,9456,0,0,0,0,'','Exarch Menelaous - Show gossip option if player has quest 9456');
 
 
/* 
* sql\updates\world\2013_03_12_00_world_player_factionchange_items.sql 
*/ 
-- Faction change item conversion for Reins of the Traveler's Tundra Mammoth
DELETE FROM `player_factionchange_items` WHERE `alliance_id`=44235;
INSERT INTO `player_factionchange_items` (`race_A`, `alliance_id`, `commentA`, `race_H`, `horde_id`, `commentH`) VALUES
(0,44235,'Reins of the Traveler''s Tundra Mammoth',0,44234,'Reins of the Traveler''s Tundra Mammoth');
 
 
/* 
* sql\updates\world\2013_03_12_01_world_player_factionchange_spells.sql 
*/ 
-- Faction change spell conversion for Reins of the Traveler's Tundra Mammoth
DELETE FROM `player_factionchange_spells` WHERE `alliance_id`=61425;
INSERT INTO `player_factionchange_spells` (`alliance_id`,`horde_id`) VALUES
(61425,61447);
 
 
/* 
* sql\updates\world\2013_03_13_00_world_gameobject.sql 
*/ 
-- GO missing spawn
-- Zone: Tanaris, Area: Land's End Beach or Finisterrae Beach
SET @GO_ENTRY := 142189; -- GO Inconspicuous Landmark entry
SET @GO_GUID := 329; -- Need one guid
SET @POOL := 355; -- Need one entry

DELETE FROM `gameobject` WHERE `id`=@GO_ENTRY;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(17499,@GO_ENTRY,1,1,1,-10249.2,-3981.8,1.66783,-0.750491,0,0,0.366501,-0.930418,900,100,1), -- Already in TDB
(17498,@GO_ENTRY,1,1,1,-10119.7,-4052.46,5.33005,-0.366519,0,0,0.182236,-0.983255,900,100,1), -- Already in TDB
(@GO_GUID,@GO_ENTRY,1,1,1,-10154.2,-3948.635,7.744733,2.652894,0,0,0.970295,0.241925,900,100,1);

DELETE FROM `pool_template` WHERE `entry`=@POOL;
INSERT INTO `pool_template` (`entry`,`max_limit`,`description`) VALUES
(@POOL,1 , 'GO Inconspicuous Landmark (142189)');

DELETE FROM `pool_gameobject` WHERE `guid` IN (17498,17499,@GO_GUID);
INSERT INTO `pool_gameobject` (`guid`,`pool_entry`,`chance`,`description`) VALUES
(17498,@POOL,0, 'Inconspicuous Landmark'),
(17499,@POOL,0, 'Inconspicuous Landmark'),
(@GO_GUID,@POOL,0, 'Inconspicuous Landmark'); 
 
/* 
* sql\updates\world\2013_03_13_01_world_creature_template.sql 
*/ 
-- Fix Night Elf Corpse (16804) so it can't be attacked
UPDATE `creature_template` SET `unit_flags`=768, `dynamicflags`=40 WHERE `entry` = 16804;
 
 
/* 
* sql\updates\world\2013_03_14_00_world_spell_proc_event.sql 
*/ 
-- Honor Among Thieves proc
UPDATE `spell_proc_event` SET `CustomChance`=33 WHERE `entry`=51698; -- Rank 1
UPDATE `spell_proc_event` SET `CustomChance`=66 WHERE `entry`=51700; -- Rank 2
UPDATE `spell_proc_event` SET `CustomChance`=100 WHERE `entry`=51701; -- Rank 3
 
 
/* 
* sql\updates\world\2013_03_14_01_world_misc.sql 
*/ 
UPDATE `creature_template` SET `faction_A`=1914,`faction_H`=1914,`unit_flags`=33024 WHERE `entry`=26452;

DELETE FROM `creature_template_addon` WHERE `entry`=26452;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(26452,0,0,0,1,383,''); 
 
/* 
* sql\updates\world\2013_03_24_00_world_spellauraoptions_dbc.sql 
*/ 
DROP TABLE IF EXISTS `spellauraoptions_dbc`;
CREATE TABLE `spellauraoptions_dbc` (
	`Id` INT UNSIGNED NOT NULL DEFAULT '0',
	`StackAmount` INT UNSIGNED NOT NULL DEFAULT '0',
	`procChance` INT UNSIGNED NOT NULL DEFAULT '0',
	`procCharges` INT UNSIGNED NOT NULL DEFAULT '0',
	`procFlags` INT NOT NULL DEFAULT '0',
	PRIMARY KEY (`Id`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8 COMMENT='';
 
 
/* 
* sql\updates\world\2013_03_27_00_world_lfg_dungeon_event.sql 
*/ 
DROP TABLE IF EXISTS `lfg_dungeon_event`;
CREATE TABLE `lfg_dungeon_event` (
  `dungeonId` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Dungeon entry from dbc',
  `eventEntry` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Event Associated to Dungeon Finder',
  PRIMARY KEY  (`dungeonId`,`eventEntry`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8;


INSERT INTO `lfg_dungeon_event` VALUES ('285', '12');
INSERT INTO `lfg_dungeon_event` VALUES ('286', '1');
INSERT INTO `lfg_dungeon_event` VALUES ('287', '24');
INSERT INTO `lfg_dungeon_event` VALUES ('288', '8');
INSERT INTO `lfg_dungeon_event` VALUES ('296', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('297', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('298', '0');
INSERT INTO `lfg_dungeon_event` VALUES ('299', '0');
 
 
/* 
* sql\updates\world\2013_03_27_00_world_spell_script_names.sql 
*/ 
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_pal_righteous_defense';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES (31789,'spell_pal_righteous_defense');
 