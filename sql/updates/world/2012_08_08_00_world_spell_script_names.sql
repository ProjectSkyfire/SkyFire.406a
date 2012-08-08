DELETE FROM `spell_script_names` WHERE `spell_id` IN (77767,56641);
INSERT INTO `spell_script_names` VALUES
(77767,'spell_hun_cobra_shot'),
(56641,'spell_hun_steady_shot');

-- Class scripts should be on their proper files
DELETE FROM `spell_scripts` WHERE `id` IN (56641,77767);

-- Just a bullshit warning removal
DELETE FROM `spell_script_names` WHERE `spell_id`= -8092;