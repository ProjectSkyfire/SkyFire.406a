DELETE FROM playercreateinfo_spell WHERE spell = 79684;
DELETE FROM spell_learn_spell WHERE spellid = 79684;
INSERT INTO spell_learn_spell (entry, spellid, active) VALUES (5143, 79684, 0);