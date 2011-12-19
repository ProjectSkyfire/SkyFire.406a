-- (47230) Fel Synergy (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47230);
INSERT INTO `spell_proc_event` VALUES (47230, 0x00, 0x05, 0x00000000, 0x00000000, 0x00000000, 0x00851154, 0x00000000, 0, 50, 0);

-- (47231) Fel Synergy (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (47231);
INSERT INTO `spell_proc_event` VALUES (47231, 0x00, 0x05, 0x00000000, 0x00000000, 0x00000000, 0x00051154, 0x00000000, 0, 100, 0);
