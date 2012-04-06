-- ALCHEMIE (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2259;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(2259, 2259, 1),
(2259, 3101, 2),
(2259, 3464, 3),
(2259, 11611, 4),
(2259, 28596, 5),
(2259, 51304, 6),
(2259, 80731, 7);

-- BLACKSMITHING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2018;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES
(2018, 2018, 1),
(2018, 3100, 2),
(2018, 3538, 3),
(2018, 9785, 4),
(2018, 29844, 5),
(2018, 51300, 6),
(2018, 76666, 7);

-- ENCHANTING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=7411;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES
(7411, 7411, 1),
(7411, 7412, 2),
(7411, 7413, 3),
(7411, 13920, 4),
(7411, 28029, 5),
(7411, 51313, 6),
(7411, 74258, 7);

-- ENGINEERING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=4036;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(4036, 4036, 1),
(4036, 4037, 2),
(4036, 4038, 3),
(4036, 12656, 4),
(4036, 30350, 5),
(4036, 51306, 6),
(4036, 82774, 7);

-- HERBALISM (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2366;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(2366, 2366, 1),
(2366, 2368, 2),
(2366, 3570, 3),
(2366, 11993, 4),
(2366, 28695, 5),
(2366, 50300, 6),
(2366, 74519, 7);

-- HERBALISM (LIFEBLOOD)
DELETE FROM spell_ranks WHERE first_spell_id=81708;
DELETE FROM spell_ranks WHERE first_spell_id=55428;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(81708, 81708, 1),
(81708, 55428, 2),
(81708, 55480, 3),
(81708, 55500, 4),
(81708, 55501, 5),
(81708, 55502, 6),
(81708, 55503, 7);

-- INSCRIPTION (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=45357;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(45357, 45357, 1),
(45357, 45358, 2),
(45357, 45359, 3),
(45357, 45360, 4),
(45357, 45361, 5),
(45357, 45363, 6),
(45357, 86008, 7);

-- JEWELCRAFTING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=25229;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(25229, 25229, 1),
(25229, 25230, 2),
(25229, 28894, 3),
(25229, 28895, 4),
(25229, 28897, 5),
(25229, 51311, 6),
(25229, 73318, 7);

-- LETHERWORKING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2108;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(2108, 2108, 1),
(2108, 3104, 2),
(2108, 3811, 3),
(2108, 10662, 4),
(2108, 32549, 5),
(2108, 51302, 6),
(2108, 81199, 7);

-- MINING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=2575;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(2575, 2575, 1),
(2575, 2576, 2),
(2575, 3564, 3),
(2575, 10248, 4),
(2575, 29354, 5),
(2575, 50310, 6),
(2575, 74517, 7);

-- MINING (TOUGHNESS)
DELETE FROM spell_ranks WHERE first_spell_id=53120;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(53120, 53120, 1),
(53120, 53121, 2),
(53120, 53122, 3),
(53120, 53123, 4),
(53120, 53124, 5),
(53120, 53040, 6),
(53120, 74496, 7);

-- SKINNING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=8613;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(8613, 8613, 1),
(8613, 8617, 2),
(8613, 8618, 3),
(8613, 10768, 4),
(8613, 32678, 5),
(8613, 50305, 6),
(8613, 74522, 7);

-- SKINNING (MASTER OF ANATOMY)
DELETE FROM spell_ranks WHERE first_spell_id=53125;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(53125, 53125, 1),
(53125, 53662, 2),
(53125, 53663, 3),
(53125, 53664, 4),
(53125, 53665, 5),
(53125, 53666, 6),
(53125, 74495, 7);

-- TAILORING (PROFESSION)
DELETE FROM spell_ranks WHERE first_spell_id=3908;
INSERT INTO spell_ranks (first_spell_id, spell_id, rank) VALUES 
(3908, 3908, 1),
(3908, 3909, 2),
(3908, 3910, 3),
(3908, 12180, 4),
(3908, 26790, 5),
(3908, 51309, 6),
(3908, 75156, 7);