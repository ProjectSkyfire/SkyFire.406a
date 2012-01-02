-- (18119) Improved Soul Fire (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (18119);
INSERT INTO `spell_proc_event` VALUES (18119, 0x00, 0x05, 0x00000000, 0x00000080, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);

-- (18120) Improved Soul Fire (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (18120);
INSERT INTO `spell_proc_event` VALUES (18120, 0x00, 0x05, 0x00000000, 0x00000080, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);
