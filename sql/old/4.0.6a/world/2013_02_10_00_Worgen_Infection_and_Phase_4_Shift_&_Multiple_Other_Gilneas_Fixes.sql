
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
