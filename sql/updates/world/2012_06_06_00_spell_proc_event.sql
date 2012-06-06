DELETE FROM `spell_proc_event` WHERE `entry` IN ('56807', '79133', '79134');
INSERT INTO `spell_proc_event`
(`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES
('56807', '0', '8', '33554432', '0', '0', '16', '0', '0', '0', '0'),        -- Glyph of hemorrhage (Thanks CrYser)
('79133', '0', '8', '1048832', '0', '0', '262144', '0', '0', '30', '0'),    -- Venomous wounds rank 1
('79134', '0', '8', '1048832', '0', '0', '262144', '0', '0', '60', '0');    -- Venomous wounds rank 2