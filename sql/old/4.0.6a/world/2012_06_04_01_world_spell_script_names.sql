DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_sha_mana_tide_totem';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_gen_damage_reduction_aura';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_pal_blessing_of_sanctuary';

-- Paladin Sanctuary
DELETE FROM `spell_proc_event` WHERE `entry` IN (20911,84628,84629);
INSERT INTO `spell_proc_event` VALUES 
(20911, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84628, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0),
(84629, 0, 0, 0, 0, 0, 0, 112, 0, 0, 0);
