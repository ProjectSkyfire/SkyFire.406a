-- (63374) Frozen Power (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (63374);
INSERT INTO `spell_proc_event` VALUES (63374, 0x00, 0x0B, 0x80000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 100, 0);

-- (63373) Frozen Power (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (63373);
INSERT INTO `spell_proc_event` VALUES (63373, 0x00, 0x0B, 0x80000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 50, 0);