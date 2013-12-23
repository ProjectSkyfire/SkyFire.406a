-- Plate Specialization
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87509','87510','87511');
INSERT INTO `spell_learn_spell` VALUES (87509, 86526, 1);
INSERT INTO `spell_learn_spell` VALUES (87510, 86524, 1);
INSERT INTO `spell_learn_spell` VALUES (87511, 86525, 1);

-- Mail Specialization
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87506','87507');
INSERT INTO `spell_learn_spell` VALUES (87506, 86528, 1);
INSERT INTO `spell_learn_spell` VALUES (87507, 86529, 1);

-- Leather Specializations
DELETE FROM `spell_learn_spell` WHERE `entry` IN('87504','87505');
INSERT INTO `spell_learn_spell` VALUES (87504, 86531, 1);
INSERT INTO `spell_learn_spell` VALUES (87505, 86530, 1);