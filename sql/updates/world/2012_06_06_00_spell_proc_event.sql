-- Glyph of hemorrhage (Thanks CrYser)
DELETE FROM `spell_proc_event` WHERE `entry` = 56807;
INSERT INTO `spell_proc_event`
(`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES
(56807, 0, 8, 33554432, 0, 0, 16, 0, 0, 0, 0);
