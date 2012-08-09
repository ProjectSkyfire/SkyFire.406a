-- fix FOR impending doom 
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85106, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 5, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85107, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 10, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (85108, 0, 5, 2097153, 64, 0, 65536, 1027, 0, 15, 0);

-- fix FOR soul leech
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (30293, 0, 5, 128, 131200, 0, 0, 1027, 0, 0, 0);
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (30295, 0, 5, 128, 131200, 0, 0, 0, 0, 0, 0);

-- fix FOR glyph OF spirit tap
REPLACE INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`)
VALUES (63237, 0, 6, 0, 2, 0, 65536, 0, 0, 100, 0);
