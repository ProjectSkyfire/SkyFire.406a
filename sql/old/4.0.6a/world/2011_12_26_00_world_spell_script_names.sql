-- Ice Barrier
DELETE FROM spell_script_names WHERE spell_id = 11426;
INSERT INTO spell_script_names (spell_id, scriptname) VALUES (11426, 'spell_mage_ice_barrier');

-- Improved Power Word: Shield
DELETE FROM spell_script_names WHERE spell_id = 17;
INSERT INTO spell_script_names (spell_id, scriptname) VALUES (17, 'spell_pri_power_word_shield');