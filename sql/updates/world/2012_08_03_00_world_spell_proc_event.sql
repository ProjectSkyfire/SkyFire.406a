DELETE FROM spell_linked_spell WHERE spell_effect=-96171;

-- Rune tap 0 cost charge drop
DELETE FROM `spell_proc_event` WHERE `entry` = 96171;
INSERT INTO `spell_proc_event` VALUES
(96171,0,15,134217728,0,0,0,0,0,0,0);

-- Will of the forsaken talent aura proc cooldown.
DELETE FROM `spell_proc_event` WHERE `entry` IN (52284,81163,81164);
INSERT INTO `spell_proc_event` (`entry`,`Cooldown`) VALUES
(52284,45),
(81163,45),
(81164,45);