-- Change the spell ID's for spell_gen_av_drekthar_presence.
DELETE FROM `spell_script_names` WHERE `ScriptName`="spell_gen_av_drekthar_presence";

INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45822, 'spell_gen_av_drekthar_presence'),
(45823, 'spell_gen_av_drekthar_presence'),
(45824, 'spell_gen_av_drekthar_presence'),
(45826, 'spell_gen_av_drekthar_presence'),
(45828, 'spell_gen_av_drekthar_presence'),
(45829, 'spell_gen_av_drekthar_presence'),
(45830, 'spell_gen_av_drekthar_presence');

-- Removed spell not found in DBC for "spell_dk_death_coil"
DELETE FROM `spell_script_names` WHERE `spell_id`= -62900;