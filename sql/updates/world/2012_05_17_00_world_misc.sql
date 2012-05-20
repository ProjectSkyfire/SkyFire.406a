
-- Misc Gilneas Fixes to include db support for core scripted Save Krennan Aranas quest
UPDATE quest_template SET EndText="Speak to Lord Godfrey at the Military District in Gilneas City.", CompletedText='' WHERE entry=14293;

UPDATE creature SET phasemask=2 WHERE guid=4051;

DELETE FROM creature WHERE id=35907;

UPDATE `creature_template` SET `speed_run`=1.28571426868439, `npcflag`=0, `VehicleId`=494, `minlevel`=4, `maxlevel`=4, `Faction_A`=2203, `Faction_H`=2203,`Unit_Flags`=8, `Modelid1`=236, `Resistance2`=90, `Resistance4`=1, `unit_class`=2, `scriptname`='npc_greymane_horse', `mechanic_immune_mask`=2147483647 WHERE `entry`=35905;

DELETE FROM creature_template_addon WHERE entry=35753;
UPDATE creature_template SET inhabittype=5 WHERE entry=3871227;
DELETE FROM creature_template_addon WHERE entry=3871227;
INSERT INTO creature_template_addon VALUES
(3871227,0,0,0,0,473,'');

DELETE FROM creature WHERE guid=69;
INSERT INTO creature VALUES
(69,3871227,638,1,4,0,0,-1674.45,1349.29,20.38,6.15351,15,0,0,102,0,0,0,0,0);

-- Save Krennan Aranas Waypoints
DELETE FROM script_waypoint WHERE entry=35905;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`) VALUES
(35905,1,-1791.55,1381.92,19.8183,0),
(35905,2,-1772.75,1361.92,19.6939,0),
(35905,3,-1759.41,1357.74,19.9291,0),
(35905,4,-1713.19,1347.35,19.6855,0),
(35905,5,-1706.18,1347.33,19.90,0),
(35905,6,-1668.35,1348.68,15.1382,0),
(35905,7,-1664.11,1356.47,15.1351,0),
(35905,8,-1678.52,1360.17,15.1359,0),
(35905,9,-1702.23,1353.7,19.2279,0),
(35905,10,-1742.5,1366.78,19.9632,0),
(35905,11,-1762.66,1390.97,19.9748,0),
(35905,12,-1774.7,1431.09,19.7806,0);

REPLACE INTO creature_addon VALUES
(6430673,0,0,8,0,0,''),
(6430776,0,0,3,0,0,'');

DELETE FROM creature WHERE guid IN (705922,705923,705924,705925);
DELETE FROM creature_addon WHERE guid IN (705922,705923,705924,705925);

DELETE FROM gameobject_template WHERE entry=300246;
INSERT INTO gameobject_template VALUES
(300246,8,0,'TEMP Krennan Aranas Location','','','',0,0,1,0,0,0,0,0,0,1630,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'','',1);

DELETE FROM gameobject WHERE id=300246;
INSERT INTO gameobject VALUES
(85,300246,638,1,4,-1674.09,1348.42,15.2845,0.0996814,0,0,0.0498201,0.998758,300,0,1);

DELETE FROM script_texts WHERE entry IN('-1999971','-1999972','-1999973');
INSERT INTO script_texts VALUES
(0,-1999971,'Rescue Krennan Aranas by using your vehicle''s ability.$B|TInterface\Icons\inv_misc_groupneedmore.blp:64|t',"","","","","","","","",0,5,0,0,"King Greymane's Horse"),
(0,-1999972,'Thank you! I owe you my life.','','','','','','','','',20922,0,0,1,"Krennan Arnasas 2"),
(0,-1999973,'Help! Up here!','','','','','','','','',20921,1,0,0,"Krennan Yell for Help");

DELETE FROM creature_template WHERE entry=35907;
INSERT INTO creature_template VALUES
(35907,0,0,0,0,0,29906,0,0,0,'Krennan Aranas','Journeyman Chemist','',0,4,4,0,2203,2203,0,1,1.14286,1,0,2,2,0,24,1,0,0,1,32776,0,0,0,0,0,0,1,1,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,'npc_krennan_aranas_c2',1);

DELETE FROM conditions WHERE sourcetypeorreferenceid=13 AND sourceentry=68228 LIMIT 1;
INSERT INTO conditions VALUES 
(13,1,68228,0,0,31,0,3,3871227,0,0,0,'','Effect _0 Needs to target Krennan Aranas');

DELETE FROM conditions WHERE sourcetypeorreferenceid=17 AND sourceentry=68219 LIMIT 1;
INSERT INTO conditions VALUES 
(17,0,68219,0,0,30,0,300246,10,0,0,11002,'','Needs to be near Krennan Aranas');

DELETE FROM creature_template WHERE entry IN (3871227);
INSERT INTO creature_template VALUES
(3871227,0,0,0,0,0,29906,0,0,0,'Krennan Aranas','Journeyman Chemist','',0,1,10,0,35,35,3,1,1.14286,1,0,13,17,0,42,1,0,0,1,0,0,0,0,0,0,0,9,13,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'',0,5,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,'',1);

DELETE FROM skyfire_string WHERE entry=11002;
INSERT INTO skyfire_string VALUES
(11002,'You must be near Krennan Aranas!','','','','','','','','');

DELETE FROM creature_text WHERE entry =35905;
INSERT INTO creature_text VALUES
(35905,0,0,'Rescue Krennan Aranas by using your vehicle''s ability.$B|TInterface\Icons\inv_misc_groupneedmore.blp:64|t',42,0,100,0,0,0,'King Greymane''s Horse');


