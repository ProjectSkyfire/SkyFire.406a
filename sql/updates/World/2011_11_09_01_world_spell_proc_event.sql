-- (48965) Shadow Infusion (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (48965);
INSERT INTO `spell_proc_event` VALUES (48965, 0x00, 0x0F, 0x00002000, 0x00000000, 0x00000000, 0x00015000, 0x00000000, 0, 33, 0);

-- (49571) Shadow Infusion (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (49571);
INSERT INTO `spell_proc_event` VALUES (49571, 0x00, 0x0F, 0x00002000, 0x00000000, 0x00000000, 0x00015000, 0x00000000, 0, 66, 0);

-- (49572) Shadow Infusion (Rank 3)
DELETE FROM `spell_proc_event` WHERE `entry` IN (49572);
INSERT INTO `spell_proc_event` VALUES (49572, 0x00, 0x0F, 0x00002000, 0x00000000, 0x00000000, 0x00015050, 0x00000000, 0, 100, 0);
