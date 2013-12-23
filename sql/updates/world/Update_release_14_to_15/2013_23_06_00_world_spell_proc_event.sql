-- spell_proc_event improved steady shot, master marksman, rude interruption, Bloodsurge, invocation
DELETE FROM `spell_proc_event` WHERE `entry` IN ('34485','34486','34487','46913','46914','46915','53221','53222','53224','61216','61221','84722','84723');
INSERT INTO `spell_proc_event` VALUES (34485, 0, 9, 0, 1, 0, 0, 0, 0, 20, 0);
INSERT INTO `spell_proc_event` VALUES (34486, 0, 9, 0, 1, 0, 0, 0, 0, 40, 0);
INSERT INTO `spell_proc_event` VALUES (34487, 0, 9, 0, 1, 0, 0, 0, 0, 60, 0);
INSERT INTO `spell_proc_event` VALUES (46913, 0, 4, 0, 1024, 0, 0, 0, 0, 10, 0);
INSERT INTO `spell_proc_event` VALUES (46914, 0, 4, 0, 1024, 0, 0, 0, 0, 20, 0);
INSERT INTO `spell_proc_event` VALUES (46915, 0, 4, 0, 1024, 0, 0, 0, 0, 30, 0);
INSERT INTO `spell_proc_event` VALUES (53221, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (53222, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (53224, 0, 9, 0, 1, 0, 0, 0, 0, 50, 0);
INSERT INTO `spell_proc_event` VALUES (61216, 0, 4, 2056, 0, 0, 4112, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (61221, 0, 4, 2056, 0, 0, 4112, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (84722, 0, 3, 16384, 0, 0, 0, 0, 0, 100, 0);
INSERT INTO `spell_proc_event` VALUES (84723, 0, 3, 16384, 0, 0, 0, 0, 0, 100, 0);
