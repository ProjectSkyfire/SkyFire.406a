-- Early Frost talent
DELETE FROM spell_linked_spell WHERE spell_effect=94315;
INSERT INTO spell_linked_spell
(spell_trigger, spell_effect, TYPE, COMMENT) VALUES
(116,94315,0, "Frostball -> Early  Frost");