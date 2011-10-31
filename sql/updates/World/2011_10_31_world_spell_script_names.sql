DELETE FROM spell_script_names WHERE spell_id = 5782 OR spell_id = -5782;
INSERT INTO spell_script_names (spell_id,scriptname) VALUES (5782,'spell_warl_fear');

DELETE FROM spell_script_names WHERE spell_id = 689 OR spell_id = -689;
INSERT INTO spell_script_names (spell_id,scriptname) VALUES (689,'spell_warl_drain_life');

DELETE FROM spell_script_names WHERE spell_id = 89420 OR spell_id = -89420;
INSERT INTO spell_script_names (spell_id,scriptname) VALUES (89420,'spell_warl_drain_life');

DELETE FROM spell_script_names WHERE spell_id = 47201; -- Remove this, deprecated