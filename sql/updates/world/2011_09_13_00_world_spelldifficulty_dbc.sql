-- treat all custom entries in spelldifficulty_dbc as backup
-- since not sure they are useful or not
-- quick note: max id of SpellDifficulty.dbc is 3942
UPDATE `spelldifficulty_dbc` SET `id` = `id` + 10000 WHERE `id` < 10000;
