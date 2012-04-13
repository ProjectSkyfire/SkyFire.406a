-- update worldstates
DELETE FROM `worldstates` WHERE `entry` IN (31001,31002,31003,31004,33280,55629);
INSERT INTO `worldstates` VALUES ('33280', '0', NULL);
INSERT INTO `worldstates` VALUES ('55629', '0', NULL);
INSERT INTO `worldstates` VALUES ('31001', '0', 'WG war status');
INSERT INTO `worldstates` VALUES ('31002', '0', 'WG clock');
INSERT INTO `worldstates` VALUES ('31003', '0', 'WG Fortress Defender');
INSERT INTO `worldstates` VALUES ('31004', '0', 'WG TEMP Battle Control Faction');