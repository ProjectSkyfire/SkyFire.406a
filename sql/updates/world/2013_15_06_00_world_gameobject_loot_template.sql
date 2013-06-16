-- Updated gameobjects quest loot entrys with missing data
DELETE FROM `gameobject_loot_template` WHERE `entry` IN (1691,2772,28414);

INSERT INTO `gameobject_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
(1691, 31955, 100, 1, 0, 1, 1), -- Arelion's Knapsack
(2772, 5339, 100, 1, 0, 1, 1), -- Serpentbloom
(28414, 52491, 100, 1, 0, 1, 1); -- Mug of Ol' Barkerstout
