-- ARCHAEOLOGY (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=78670;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(78670, 78670, 1),
(78670, 88961, 2),
(78670, 89718, 3),
(78670, 89719, 4),
(78670, 89720, 5),
(78670, 89721, 6),
(78670, 89722, 7);

-- COOKING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2550;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(2550, 2550, 1),
(2550, 3102, 2),
(2550, 3413, 3),
(2550, 18260, 4),
(2550, 33359, 5),
(2550, 51296, 6),
(2550, 88053, 7);

-- FIRST AID (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=3273;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(3273, 3273, 1),
(3273, 3274, 2),
(3273, 7924, 3),
(3273, 10846, 4),
(3273, 27028, 5),
(3273, 45542, 6),
(3273, 74559, 7);

-- FISHING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=7620;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(7620, 7620, 1),
(7620, 7731, 2),
(7620, 7732, 3),
(7620, 18248, 4),
(7620, 33095, 5),
(7620, 51294, 6),
(7620, 88868, 7);

-- RIDING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=33388;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(33388, 33388, 1),
(33388, 33391, 2),
(33388, 34090, 3),
(33388, 34091, 4),
(33388, 90265, 5);
