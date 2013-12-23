-- Misc Midsummer fire festival object relocation in bloodelf starting area
DELETE FROM game_event_gameobject WHERE guid IN (209773, 150857);
INSERT game_event_gameobject (`guid`,`eventEntry`) VALUES 
(209773, 1),
(150857, 1);

DELETE FROM game_event_creature WHERE guid = 202740;
INSERT game_event_creature (`guid`,`eventEntry`) VALUES 
(202740, 1);

DELETE FROM gameobject WHERE guid IN (209773, 150857);
INSERT INTO `gameobject` VALUES ('209773', '187960', '530', '1', '1', '9392.83', '-6770.73', '14.6574', '1.46368', '0', '0', '0.668238', '0.743947', '300', '0', '1');
INSERT INTO `gameobject` VALUES ('150857', '187960', '530', '1', '1', '9371.65', '-6766.64', '15.4183', '5.82106', '0', '0', '0.22901', '-0.973424', '300', '0', '1');