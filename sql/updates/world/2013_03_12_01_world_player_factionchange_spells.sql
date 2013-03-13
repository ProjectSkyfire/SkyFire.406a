-- Faction change spell conversion for Reins of the Traveler's Tundra Mammoth
DELETE FROM `player_factionchange_spells` WHERE `alliance_id`=61425;
INSERT INTO `player_factionchange_spells` (`alliance_id`,`horde_id`) VALUES
(61425,61447);
