-- Spell.Warrior.Blood.Craze 
DELETE FROM `spell_proc_event` WHERE `entry` IN ( 16487, 16489, 16492);
INSERT INTO `spell_proc_event` VALUES
(16487,0,0,0,0,0,0,0,0,10,0),
(16489,0,0,0,0,0,0,0,0,10,0),
(16492,0,0,0,0,0,0,0,0,10,0);

-- Talent.Paladin.Infusion_of_Light
DELETE FROM `spell_proc_event` WHERE `entry` IN ( 53569, 53576);
INSERT INTO `spell_proc_event` VALUES
(53569,0,10,0x40200000,0x10000,0,0,2,0,0,0),
(53576,0,10,0x40200000,0x10000,0,0,2,0,0,0);

-- Talent.Paladin.Blessed_Life
DELETE FROM `spell_proc_event` WHERE `entry` IN ( 31828, 31829);
INSERT INTO `spell_proc_event` VALUES
(31828,0,0,0,0,0,0,0,0,50,8),
(31829,0,0,0,0,0,0,0,0,100,8);

-- Spell.Warrior.Rude.Interruption
DELETE FROM `spell_proc_event` WHERE `entry` IN (61221, 61216);
INSERT INTO `spell_proc_event` VALUES 
(61221,0,4,0,0,0,4112,0,0,100,120), 
(61216,0,4,0,0,0,4112,0,0,100,120);
