DELETE FROM `spell_proc_event` WHERE entry IN (50685, 50686, 50687);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(50685, 0, 4, 64, 0, 0, 16, 2, 0, 0, 0),
(50686, 0, 4, 64, 0, 0, 16, 2, 0, 0, 0),
(50687, 0, 4, 64, 0, 0, 16, 2, 0, 0, 0);