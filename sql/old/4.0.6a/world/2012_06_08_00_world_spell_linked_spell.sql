DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN(21562, 27683, 1120, -82691, 19740);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(21562, 79105, 0, 'Power Word: Fortitude'), -- Power Word: Fortitude
(27683, 79107, 0, 'Shadow Protection'), -- Shadow Protection
(1120, 79264, 0, 'Drain Soul'), -- Drain Soul
(19740, 79063, 0, 'Blessing of Might'), -- Blessing of Might
(-82691, 91264, 0, 'Ring of frost immune'); -- immunity to ring of frost
