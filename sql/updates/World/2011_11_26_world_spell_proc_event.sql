-- Atonement rank 1
DELETE FROM `spell_proc_event` WHERE `entry` IN (14523);
INSERT INTO `spell_proc_event` VALUES (14523, 0x00, 0x06, 0x00000080, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);

-- Atonement rank 2
DELETE FROM `spell_proc_event` WHERE `entry` IN (81749);
INSERT INTO `spell_proc_event` VALUES (81749, 0x00, 0x06, 0x00000080, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);
