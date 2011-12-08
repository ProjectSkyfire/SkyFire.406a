-- Argent Tournament Mount Spells (for quests)
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('62544', '62575', '62863', '62960');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('62544', 'spell_tournament_trust'), -- Thrust
('62575', 'spell_tournament_shield_breaker'), -- Shield-Breaker
('62863', 'spell_tournament_duel'), -- Duel
('62960', 'spell_tournament_charge'); -- Charge