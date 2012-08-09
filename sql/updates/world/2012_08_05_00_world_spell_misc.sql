-- Paralysis missing proc data
UPDATE `spell_proc_event` SET `SpellFamilyName` = 6 WHERE `entry` IN (87192,87195);

-- Mind melt cast reduction buff proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (81292,87160);
INSERT INTO `spell_proc_event` (`entry`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`) VALUES 
(81292, 6, 8192, 0, 0),
(87160, 6, 8192, 0, 0);

-- Mind spike dots hack removal.
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 73510 AND `spell_effect` IN (-34914,-2944,-589);

DELETE FROM `spell_script_names` WHERE `spell_id` IN (73510,8092);
INSERT INTO `spell_script_names` VALUES
(8092,'spell_pri_mind_blast'),
(73510,'spell_pri_mind_spike');