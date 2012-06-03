-- Blast Wave script update
DELETE FROM `spell_script_names` WHERE `spell_id`=-11113;
INSERT INTO `spell_script_names` VALUES
(11113,'spell_mage_blast_wave');

-- Deep Wounds
DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_warr_deep_wounds';
INSERT INTO `spell_script_names` VALUES
(12162,'spell_warr_deep_wounds'),
(12850,'spell_warr_deep_wounds'),
(12868,'spell_warr_deep_wounds');
