-- Deep Wounds
DELETE FROM spell_script_names WHERE spell_id IN (12162, -12162, 12850, -12850, 12868, -12868);
INSERT INTO spell_script_names (spell_id, scriptname) VALUES (-12162, "spell_warr_deep_wounds");


-- Spirit Healer Res
DELETE FROM spell_script_names WHERE spell_id IN (17251, -17251);
INSERT INTO spell_script_names (spell_id, scriptname) VALUES (17251, "spell_gen_spirit_healer_res");

-- Reindeer Transformation
DELETE FROM spell_script_names WHERE spell_id IN (25860, -25860);
INSERT INTO spell_script_names (spell_id, scriptname) VALUES (25860, "spell_gen_reindeer_transformation");