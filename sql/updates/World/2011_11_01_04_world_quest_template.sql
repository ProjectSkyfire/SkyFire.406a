-- Fixes Monkey Business creature kill count
UPDATE quest_template SET reqcreatureorgoid1 = 34699 WHERE entry = 14019;
UPDATE quest_template SET ReqSpellCast1 = 67917 WHERE entry = 14019;