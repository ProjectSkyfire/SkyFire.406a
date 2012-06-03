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



