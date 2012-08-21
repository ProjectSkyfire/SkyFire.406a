DELETE FROM `spell_script_names` WHERE `spell_id` = 26573;
INSERT INTO `spell_script_names` VALUES
(26573,'spell_pal_consecration');

UPDATE `creature_template` SET `minlevel` = 85, `maxlevel` = 85, `flags_extra` = 128 WHERE `entry` = 43499;

-- Consecration Visual
DELETE FROM `creature_template_addon` WHERE `entry` = 43499;
INSERT INTO `creature_template_addon` VALUES
(43499,0,0,0,0,0,81298);