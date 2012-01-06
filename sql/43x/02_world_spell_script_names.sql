-- Delete ScriptName For Quest Morbent Fel
DELETE FROM spell_script_names WHERE ScriptName='spell_q55_sacred_cleansing';

-- Update ScriptName For Quest Marauders of Darrowshire
DELETE FROM spell_script_names WHERE ScriptName='spell_q5206_test_fetid_skull';
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES 
(17271, 'spell_q27389_test_fetid_skull');
