DELETE FROM `spell_proc_event` WHERE `entry` IN (34753, 34859);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(34753, 0, 6, 6144, 4, 4096, 0, 2, 0, 0, 0), -- rank1
(34859, 0, 6, 6144, 4, 4096, 0, 2, 0, 0, 0); -- rank2