DELETE FROM spell_bonus_data WHERE entry = 53351;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (53351, 0.3, "Hunter - Kill Shot");

DELETE FROM spell_bonus_data WHERE entry = 56641;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (56641, 0.021, "Hunter - Steady Shot");

DELETE FROM spell_bonus_data WHERE entry = 19434;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (19434, 0.724, "Hunter - Aimed Shot");

DELETE FROM spell_bonus_data WHERE entry = 82928;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (82928, 0.724, "Hunter - Aimed Shot!");

DELETE FROM spell_bonus_data WHERE entry = 77767;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (77767, 0.017, "Hunter - Cobra Shot");

DELETE FROM spell_bonus_data WHERE entry = 3044;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (3044, 0.0483, "Hunter - Arcane Shot");

DELETE FROM spell_bonus_data WHERE entry = 53209;
INSERT INTO spell_bonus_data (entry, ap_bonus, comments) VALUES (53209, 0.732, "Hunter - Chimera Shot");

-- (53241) Marked for Death (Rank 1)
DELETE FROM `spell_proc_event` WHERE `entry` IN (53241);
INSERT INTO `spell_proc_event` VALUES (53241, 0x00, 0x09, 0x00000800, 0x00000000, 0x00000001, 0x00000100, 0x00000000, 0, 100, 0);

-- (53243) Marked for Death (Rank 2)
DELETE FROM `spell_proc_event` WHERE `entry` IN (53243);
INSERT INTO `spell_proc_event` VALUES (53243, 0x00, 0x09, 0x00000800, 0x00000000, 0x00000001, 0x00000100, 0x00000000, 0, 100, 0);