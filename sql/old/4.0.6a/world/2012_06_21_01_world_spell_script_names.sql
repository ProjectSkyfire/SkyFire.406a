DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_dru_glyph_of_starfire';
INSERT INTO `spell_script_names` VALUES
(54846,'spell_dru_glyph_of_starfire');

UPDATE `spell_proc_event` SET `CustomChance` = 100 WHERE `entry` = 54845;