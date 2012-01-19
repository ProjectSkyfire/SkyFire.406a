-- Halls of Origination fixes
-- thanks to arkania
-- Bridge and go's need checked for accuracy

-- Hero dif mob
UPDATE creature_template SET difficulty_entry_1= 48815 WHERE entry=39378;
UPDATE creature_template SET difficulty_entry_1= 48710 WHERE entry=39587;
UPDATE creature_template SET difficulty_entry_1= 48715 WHERE entry=39731;
UPDATE creature_template SET difficulty_entry_1= 48776 WHERE entry=39732;
-- Graveyard
INSERT INTO game_graveyard_zone VALUES (1823, 4945,0);
-- Respawn
UPDATE creature SET spawntimesecs=3600 WHERE map=644;
-- Spawn de GOBs
DELETE FROM gameobject WHERE map=644 AND id IN (206506, 202309, 202314, 202307);
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('206506','644','3','1','-641.39','304.37','52.9975','3.15858','0','0','0.999964','-0.00849289','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202309','644','3','1','-439.397','366.874','89.7929','3.13816','0','0','0.999999','0.00171597','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202314','644','3','1','-121.47','365.601','89.7908','6.27268','0','0','0.00525344','-0.999986','300','0','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('202307','644','3','1','-640.567','235.521','83.7956','1.49378','0','0','0.679362','0.733804','300','0','1');
-- Brann Barbabronce
SET @ENTRY  := 39908;
SET @GOSSIP := 39908;
SET @TEXTO := 'We\'re ready. Go Brann';
DELETE FROM `gossip_menu_option` WHERE `menu_id` = @GOSSIP;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`) VALUES
(@GOSSIP,'0','0',@TEXTO,'1','1','0','0','0','0','0',NULL);
UPDATE `creature_template` SET `gossip_menu_id` = @GOSSIP, `AIName`= 'SmartAI', minlevel=85, maxlevel=85 WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,0,@GOSSIP,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Brann Barbabronce - On gossip option select - Close gossip'),
(@ENTRY,0,1,0,61,0,100,0,0,0,0,0,9,0,0,0,0,0,0,15,202309,120,0,0.0,0.0,0.0,0.0,"Brann Barbabronce - Abre la puerta cuando habla");
DELETE FROM `creature` WHERE `id` = 39908 AND map =644; --
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('39908','644','3','1','0','0','-446.498','367.005','90.1698','0.0874934','3600','0','0','42','0','0','0','0','0');
-- Temple Guardian Anhuur
SET @ENTRY := 39425;
SET @SOURCETYPE := 0;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI",  ScriptName ='' WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,0,0,0,100,2,1000,2000,5000,10000,11,75592,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Temple Guardian Anhuur cast Divine Reckoning - Normal"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,2,0,0,5000,6500,11,75117,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Temple Guardian Anhuur cast Burning Light random - Normal"),
(@ENTRY,@SOURCETYPE,2,0,6,0,100,6,0,0,0,0,9,0,0,0,0,0,0,15,206506,100,0,0.0,0.0,0.0,0.0,"Activa el puente al morir"),
(@ENTRY,@SOURCETYPE,3,0,6,0,100,6,0,0,0,0,9,0,0,0,0,0,0,15,202307,120,0,0.0,0.0,0.0,0.0,"Abre la puerta cuando muere"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,4,0,0,5000,6500,11,94951,0,0,0,0,0,5,0,0,0,0.0,0.0,0.0,0.0,"Temple Guardian Anhuur cast Burning Light random - Hero"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,2,1000,2000,5000,10000,11,94951,1,0,0,0,0,2,0,0,0,0.0,0.0,0.0,0.0,"Temple Guardian Anhuur cast Divine Reckoning - Hero");
UPDATE `creature_template` SET `equipment_id` = 39425 WHERE `entry` = 39425;
DELETE FROM `creature_equip_template` WHERE (`entry`=39425);
INSERT INTO `creature_equip_template` (`entry`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES (39425, 55064, '0', '0');
-- Temple Guardian Anhuur
DELETE FROM `creature_loot_template` WHERE `entry`= 39425;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39425','55889','0','1','1','1','1'),
('39425','55888','0','1','1','1','1'),
('39425','55886','0','1','1','1','1'),
('39425','55887','0','1','1','1','1'),
('39425','55890','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 49262;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('49262','56407','0','1','1','1','1'),
('49262','56410','0','1','1','1','1'),
('49262','56411','0','1','1','1','1'),
('49262','56409','0','1','1','1','1'),
('49262','56408','0','1','1','1','1');

-- Earthrager Ptah
DELETE FROM `creature_loot_template` WHERE `entry`= 39428;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39428','56097','0','1','1','1','1'),
('39428','56095','0','1','1','1','1'),
('39428','56093','0','1','1','1','1'),
('39428','56096','0','1','1','1','1'),
('39428','56094','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48714;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48714','56423','0','1','1','1','1'),
('48714','56424','0','1','1','1','1'),
('48714','56425','0','1','1','1','1'),
('48714','56426','0','1','1','1','1'),
('48714','56422','0','1','1','1','1');

-- Anraphet
DELETE FROM `creature_loot_template` WHERE `entry`= 39788;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39788','57855','0','1','1','1','1'),
('39788','57857','0','1','1','1','1'),
('39788','57860','0','1','1','1','1'),
('39788','57856','0','1','1','1','1'),
('39788','57858','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48902;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48902','57870','0','1','1','1','1'),
('48902','57868','0','1','1','1','1'),
('48902','57867','0','1','1','1','1'),
('48902','57866','0','1','1','1','1'),
('48902','57869','0','1','1','1','1');

-- Isiset
DELETE FROM `creature_loot_template` WHERE `entry`= 39587;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39587','55994','0','1','1','1','1'),
('39587','55995','0','1','1','1','1'),
('39587','55996','0','1','1','1','1'),
('39587','55993','0','1','1','1','1'),
('39587','55992','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48710;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48710','56414','0','1','1','1','1'),
('48710','56416','0','1','1','1','1'),
('48710','56415','0','1','1','1','1'),
('48710','56412','0','1','1','1','1'),
('48710','56413','0','1','1','1','1');

-- Ammunae
DELETE FROM `creature_loot_template` WHERE `entry`= 39731;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39731','55997','0','1','1','1','1'),
('39731','56000','0','1','1','1','1'),
('39731','55998','0','1','1','1','1'),
('39731','55999','0','1','1','1','1'),
('39731','56001','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48715;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48715','56418','0','1','1','1','1'),
('48715','56419','0','1','1','1','1'),
('48715','56417','0','1','1','1','1'),
('48715','56421','0','1','1','1','1'),
('48715','56420','0','1','1','1','1');

-- Setesh
DELETE FROM `creature_loot_template` WHERE `entry`= 39732;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39732','57865','0','1','1','1','1'),
('39732','57864','0','1','1','1','1'),
('39732','57863','0','1','1','1','1'),
('39732','57862','0','1','1','1','1'),
('39732','57861','0','1','1','1','1');
DELETE FROM `creature_loot_template` WHERE `entry`= 48776;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48776','57875','0','1','1','1','1'),
('48776','57873','0','1','1','1','1'),
('48776','57871','0','1','1','1','1'),
('48776','57874','0','1','1','1','1'),
('48776','57872','0','1','1','1','1');

--
DELETE FROM `creature_loot_template` WHERE `entry`= 39378;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('39378','56098','0','1','1','1','1'),
('39378','56099','0','1','1','1','1'),
('39378','56100','0','1','1','1','1'),
('39378','56101','0','1','1','1','1'),
('39378','56102','0','1','1','1','1'),
('39378','56104','0','1','2','1','1'),
('39378','56105','0','1','2','1','1'),
('39378','56106','0','1','2','1','1'),
('39378','56107','0','1','2','1','1'),
('39378','56108','0','1','2','1','1');

DELETE FROM `creature_loot_template` WHERE `entry`= 48815;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('48815','56427','0','1','1','1','1'),
('48815','56428','0','1','1','1','1'),
('48815','56429','0','1','1','1','1'),
('48815','56430','0','1','1','1','1'),
('48815','56431','0','1','1','1','1'),
('48815','52078','0','1','0','1','1'),
('48815','56432','0','2','2','1','1'),
('48815','56433','0','2','2','1','1'),
('48815','56434','0','2','2','1','1'),
('48815','56435','0','2','2','1','1'),
('48815','56436','0','2','2','1','1');

-- lifts and towers thanks to kraven5
DELETE FROM gameobject_template WHERE entry =207547;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
('207547','11','9052','Lift of the Makers','','','','0','40','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','1');

DELETE FROM gameobject WHERE id=207547;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('207547','644','3','1','-505.319','193.743','79.01','1.54664','0','0','0.698513','0.715597','300','0','1');

DELETE FROM gameobject WHERE id IN (192570, 192571)  AND map=1;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('4002861','192571','1','1','1','-10211','-1837.83','20.1281','6.25565','0','0','0.0137672','-0.999905','3600','100','1');
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('4002889','192570','1','1','1','-10211','-1837.83','20.1281','6.25565','0','0','0.0137672','-0.999905','3600','100','1');

DELETE FROM `gameobject` WHERE `id`=207410;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(4012742, 207410, 644, 3, 1, -613.236, 487.993, 83.7949, 3.09979, 0, 0, 0.999782, 0.0208977, 300, 0, 1);

-- normal mode
DELETE FROM `creature_template` WHERE `entry`=39378 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 39378, 0, 0, 0, 0, 0, 33177, 0, 0, 0, "Rajh", "Construct of the Sun", "", 0, 83, 87, 3, 14, 14, 0, 1.0, 1.14286, 1.0, 1, 585, 753, 0, 849, 7.5, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 585, 753, 849, 7, 104, 39378, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 140, "SmartAI", 0, 3, 20.0, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 151, 1, 0, 613097436, 0, "", "1");
     
DELETE FROM `creature_template` WHERE `entry`=39731 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 39731, 0, 0, 0, 0, 0, 32943, 0, 0, 0, "Ammunae", "Construct of Life", "", 0, 83, 87, 3, 14, 14, 0, 1.0, 1.14286, 1.0, 1, 585, 753, 0, 849, 7.5, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 585, 753, 849, 7, 104, 39731, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, "SmartAI", 0, 1, 20.0, 1.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 151, 1, 0, 613097436, 0, "", "1");
     
DELETE FROM `creature_template` WHERE `entry`=40715 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 40715, 0, 0, 0, 0, 0, 37304, 0, 0, 0, "Lifewarden Nymph", "", "", 0, 82, 85, 3, 16, 16, 0, 1.0, 1.14286, 1.0, 1, 516, 696, 0, 813, 7.5, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 516, 696, 813, 7, 8, 40715, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, "", 0, 1, 4.0, 7.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 613097436, 0, "", "1");
     
DELETE FROM `creature_template` WHERE `entry`=40668 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 40668, 0, 0, 0, 0, 0, 30165, 0, 0, 0, "Living Vine", "", "", 0, 83, 85, 3, 14, 14, 0, 1.0, 1.14286, 1.0, 1, 530, 713, 0, 827, 7.5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 530, 713, 827, 10, 72, 40668, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 3, 4.0, 7.0, 1.0, 0, 0, 0, 0, 0, 0, 0, 401, 1, 0, 613097436, 0, "", "1");
     
DELETE FROM `creature_template` WHERE `entry`=39373 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 39373, 0, 0, 0, 0, 0, 5965, 0, 0, 0, "Sun-Touched Speaker", "", "", 0, 82, 85, 3, 16, 16, 0, 1.0, 1.14286, 1.0, 1, 530, 713, 0, 827, 7.5, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 530, 713, 827, 4, 72, 39373, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 33, "", 0, 1, 1.0E-4, 7.0, 1.0, 0, 52506, 0, 0, 0, 0, 0, 0, 1, 0, 613097436, 0, "", "1");
     
DELETE FROM `creature_template` WHERE `entry`=39366 LIMIT 1;
INSERT INTO `creature_template` ( `entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ( 39366, 0, 0, 0, 0, 0, 35165, 0, 0, 0, "Sun-Touched Servant", "", "", 0, 82, 85, 3, 16, 16, 0, 1.0, 1.14286, 1.0, 1, 530, 713, 0, 827, 7.5, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 530, 713, 827, 4, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, "", 0, 3, 4.0, 7.0, 1.0, 0, 52506, 0, 0, 0, 0, 0, 0, 1, 0, 613097436, 0, "", "1");

