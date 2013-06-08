-- Blessing of Might
DELETE FROM `spell_script_names` WHERE `spell_id` = 19740;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(19740, 'spell_pal_bless_of_might');

-- Blessing of King
DELETE FROM `spell_script_names` WHERE `spell_id` = 20217;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(20217, 'spell_pal_bless_of_king');
