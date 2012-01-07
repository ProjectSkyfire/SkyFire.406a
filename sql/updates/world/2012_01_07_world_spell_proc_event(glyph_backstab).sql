-- Glyph of Backstab
DELETE FROM `spell_proc_event` WHERE `entry` = 56800;
INSERT INTO `spell_proc_event` VALUES (56800, 1, 8, 4, 0, 0, 16, 2, 0, 100, 0);