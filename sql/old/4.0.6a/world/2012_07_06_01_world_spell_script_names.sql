-- Resistance is futile periodic aura on enemy
DELETE FROM `spell_script_names` WHERE `spell_id` = 83676;
INSERT INTO `spell_script_names` VALUES
(83676,'spell_hun_resistance_is_futile');

-- Kill command refund proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (82897);
INSERT INTO `spell_proc_event` VALUES
(82897,0,9,0,2048,0,1024,0,0,0,0);