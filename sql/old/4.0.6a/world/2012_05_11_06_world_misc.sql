-- Battle for gilneas & twinpeaks

-- Fix min lvl and Min, Max players on the TP and BG
DELETE FROM `battleground_template` WHERE `id` IN (120,108);
INSERT INTO `battleground_template` VALUES
(108,10,10,81,85,1726,0,1727,0,1,'','Twin Peaks'),
(120,10,10,85,85,1740,0,1739,3.23,1,'','The Battle for Gilneas');

-- bg_holiday's (not sure what new bitmasks are, so havent used "game_event_battleground_holiday")
DELETE FROM `game_event` WHERE `EventEntry` IN (18,19,20,21,30,42,75,78);
INSERT  INTO `game_event` VALUES (18,'2010-10-21 12:01:00','2020-12-30 11:59:00',60480,5758,283,'Call to Arms: Alterac Valley!',0);
INSERT  INTO `game_event` VALUES (19,'2010-09-16 12:01:00','2020-12-30 11:59:00',60480,5758,284,'Call to Arms: Warsong Gulch!',0);
INSERT  INTO `game_event` VALUES (20,'2010-10-07 12:01:00','2020-12-30 11:59:00',60480,5758,285,'Call to Arms: Arathi Basin!',0);
INSERT  INTO `game_event` VALUES (21,'2010-10-14 12:01:00','2020-12-30 11:59:00',60480,5758,353,'Call to Arms: Eye of the Storm!',0);
INSERT  INTO `game_event` VALUES (30,'2010-09-23 12:01:00','2020-12-30 11:59:00',60480,5758,400,'Call to Arms: Strand of the Ancients!',0);
INSERT  INTO `game_event` VALUES (42,'2010-09-30 12:01:00','2020-12-30 11:59:00',60480,5758,420,'Call to Arms: Isle of Conquest!',0);
INSERT  INTO `game_event` VALUES (75,'2012-05-11 12:01:00','2020-12-30 11:59:00',60480,5758,436,'Call to Arms: Twin Peaks!',0);
INSERT  INTO `game_event` VALUES (78,'2012-05-04 12:01:00','2020-12-30 11:59:00',60480,5758,288,'Call to Arms: The Battle for Gilneas',0);


-- Strings
DELETE FROM skyfire_string WHERE entry IN (1250, 1251, 1252, 1253, 1254, 1255, 1256, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264);
INSERT INTO skyfire_string (entry, content_default, content_loc1, content_loc2, content_loc3, content_loc4, content_loc5, content_loc6, content_loc7, content_loc8) VALUES 
(1250, 'The Battle for Gilneas begins in 2 minutes.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1251, 'The Battle for Gilneas begins in 1 minute.', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1252, 'The Battle for Gilneas begins in 30 seconds. Prepare yourselves!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1253, 'The Battle for Gilneas has begun!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1254, 'Alliance', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1255, 'Horde', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1256, 'lighthouse', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1257, 'waterworks', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1258, 'mine', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1259, 'The %s has taken the %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1260, '$n has defended the %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1261, '$n has assaulted the %s', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1262, '$n claims the %s! If left unchallenged, the %s will control it in 1 minute!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1263, 'The Alliance has gathered $1776W resources, and is near victory!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(1264, 'The Horde has gathered $1777W resources, and is near victory!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

-- HORDE GATE
DELETE FROM gameobject_template WHERE entry=207178;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(207178, 0, 10215, 'Horde Gate', 0, 0, 13623);

-- ALLIANCE GATE
DELETE FROM gameobject_template WHERE entry=205496;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(205496, 0, 6354, 'Alliance Gate', 0, 0, 13623);

-- ALLIANCE DOOR
DELETE FROM gameobject_template WHERE entry=207177;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES 
(207177, 0, 9062, 'Alliance Door', 0, 0, 13623);

-- MINE BANNER
DELETE FROM gameobject_template WHERE entry=208782;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208782, 10, 6271, 'Mine Banner', 0, 0, 13623);

-- WATERWORKS BANNER
DELETE FROM gameobject_template WHERE entry=208785;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208785, 10, 6271, 'Waterworks Banner', 0, 0, 13623);

-- LIGHTHOUSE BANNER
DELETE FROM gameobject_template WHERE entry=205557;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(205557, 10, 6271, 'Lighthouse Banner', 0, 0, 13623);

-- CONTESTED BANNER
DELETE FROM gameobject_template WHERE entry=208733;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208733, 1, 6254, 'Contested Banner', 0, 0, 13623);

-- CONTESTED BANNER
DELETE FROM gameobject_template WHERE entry=208754;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208754, 1, 6254, 'Contested Banner', 0, 0, 13623);

-- CONTESTED BANNER
DELETE FROM gameobject_template WHERE entry=208724;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208724, 1, 6252, 'Contested Banner', 0, 0, 13623);

-- ALLIANCE BANNER
DELETE FROM gameobject_template WHERE entry=208718;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208718, 1, 6251, 'Alliance Banner', 0, 0, 13623);

-- ALLIANCE BANNER
DELETE FROM gameobject_template WHERE entry=208673;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208673, 1, 6251, 'Alliance Banner', 0, 0, 13623);

-- ALLIANCE BANNER
DELETE FROM gameobject_template WHERE entry=208739;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208739, 1, 6251, 'Alliance Banner', 0, 0, 13623);

-- HORDE BANNER
DELETE FROM gameobject_template WHERE entry=208766;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208766, 1, 6253, 'Horde Banner', 0, 0, 13623);

-- HORDE BANNER
DELETE FROM gameobject_template WHERE entry=208748;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208748, 1, 6253, 'Horde Banner', 0, 0, 13623);

-- HORDE BANNER
DELETE FROM gameobject_template WHERE entry=208727;
INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
(208727, 1, 6253, 'Horde Banner', 0, 0, 13623);

-- TwinPeaks Gates
DELETE FROM `gameobject_template` WHERE `entry` BETWEEN '402189' AND '402191';
DELETE FROM `gameobject_template` WHERE `entry` BETWEEN '402364' AND '402366';
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `AIName`, `ScriptName`, `WDBVerified`) VALUES
('402189','3','10122','TWINPEAKS_DWARVEN_GATE_03','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623'),
('402190','3','10123','TWINPEAKS_DWARVEN_GATE_01','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623'),
('402191','3','10124','TWINPEAKS_DWARVEN_GATE_02','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623'),
('402364','3','10442','TWINPEAKS_ORC_GATE_01','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623'),
('402365','3','10443','TWINPEAKS_ORC_GATE_02','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623'),
('402366','3','10444','TWINPEAKS_ORC_GATE_03','','','','0','0','1','0','0','0','0','0','0','0','-1','0','0','0','0','-1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','13623');

-- not sure wth this is...
-- PVP HOLIDAY (H) TB
-- DELETE FROM gameobject_template WHERE entry=207465;
-- INSERT INTO gameobject_template (entry, TYPE, displayId, NAME, data1, data6, WDBVerified) VALUES
-- (207465, 5, 8618, 'PVP HOLIDAY (H) TBfG', 0, 0, 13623);
