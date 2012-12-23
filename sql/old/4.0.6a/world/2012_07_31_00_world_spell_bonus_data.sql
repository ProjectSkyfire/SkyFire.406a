DELETE FROM `spell_script_names` WHERE `ScriptName` LIKE 'spell_pri_chakra_sanctuary_heal_target_selector';
INSERT INTO `spell_script_names` VALUES
(88686,'spell_pri_chakra_sanctuary_heal_target_selector');

DELETE FROM `spell_bonus_data` WHERE `entry` IN (88668,88686);
INSERT INTO `spell_bonus_data` VALUES
(88668,0.279,0,0,0,'Priest - Sanctuary 4yd AoE Heal'),
(88686,0.199,0,0,0,'Priest - Sanctuary 8yd AoE Heal'); -- Guessing 
