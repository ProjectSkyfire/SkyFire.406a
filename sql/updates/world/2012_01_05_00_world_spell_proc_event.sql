-- (35104) Bombardment (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (35104);
INSERT INTO `spell_proc_event` VALUES (35104, 0x00, 0x09, 0x00001000, 0x00000000, 0x00000000, 0x00001140, 0x00000002, 0, 100, 0);

-- (35110) Bombardment (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (35110);
INSERT INTO `spell_proc_event` VALUES (35110, 0x00, 0x09, 0x00001000, 0x00000000, 0x00000000, 0x00001140, 0x00000002, 0, 100, 0);
