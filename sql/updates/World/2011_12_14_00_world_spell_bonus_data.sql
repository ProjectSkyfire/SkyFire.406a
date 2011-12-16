DELETE FROM `spell_bonus_data` WHERE `entry` IN (17253,16827,49966);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
    (17253, 0, 0, 0.08, 0, 'Bite (Rank 1) - Hunter pet'),
    (16827, 0, 0, 0.08, 0, 'Claw (Rank 1) - Hunter pet'),
    (49966, 0, 0, 0.08, 0, 'Smack (Rank 1) - Hunter pet');