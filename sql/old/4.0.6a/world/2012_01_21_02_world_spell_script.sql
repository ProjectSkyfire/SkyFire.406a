DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_gen_damage_reduction_aura';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(20911,'spell_gen_damage_reduction_aura'), -- Blessing of Sanctuary
(25899,'spell_gen_damage_reduction_aura'), -- Greater Blessing of Sanctuary
(63944,'spell_gen_damage_reduction_aura'); -- Renewed Hope

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_warr_vigilance';
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(50720,'spell_warr_vigilance'); -- Vigilance