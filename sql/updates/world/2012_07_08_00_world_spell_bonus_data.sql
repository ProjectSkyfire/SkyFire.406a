-- fix FOR swipe (bear), lacerate, thrash
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (779, 0, 0, 0.114, -1, 'Druid - Swipe (Bear)');
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (33745, 0, 0, 0.0766, 0.00512, 'Druid - Lacerate');
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (77758, 0, 0, 0.154, 0.026, 'Druid - Thrash');

-- fix FOR insect swarm 
REPLACE INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`)
VALUES (5570, -1, 0.13, -1, -1, 'Druid - Insect Swarm');
