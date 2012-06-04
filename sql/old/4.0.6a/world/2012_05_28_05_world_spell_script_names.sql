-- Execute
DELETE FROM `spell_script_names` WHERE `spell_id` = 5308;
INSERT INTO `spell_script_names` VALUES
(5308,'spell_warr_execute');
-- Spell Bonus Data
DELETE FROM `spell_bonus_data` WHERE `entry` = 5308;
INSERT INTO `spell_bonus_data` VALUES
(5308,0,0,0.437,0,'Warrior - Execute');