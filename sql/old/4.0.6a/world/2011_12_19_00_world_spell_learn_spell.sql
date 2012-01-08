DELETE FROM `spell_learn_spell` WHERE `entry` IN (87500,87498,87497,87496,87495,87494,87493,87492,87491,86467);
INSERT INTO `spell_learn_spell` (`entry`,`SpellID`,`Active`) VALUES
(87500,86479,1), -- Warrior
(87498,86478,1), -- Warlock
(87497,86477,1), -- Shaman
(87496,86476,1), -- Rogue
(87495,86475,1), -- Priest
(87494,86474,1), -- Paladin
(87493,86472,1), -- Hunter
(87492,86471,1), -- DK
(87491,86470,1), -- Druid
(86467,86473,1); -- Mage
