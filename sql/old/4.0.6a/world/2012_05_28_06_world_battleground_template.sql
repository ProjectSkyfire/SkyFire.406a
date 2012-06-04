-- Fix min lvl and Min, Max players on the TP and BG
DELETE FROM `battleground_template` WHERE `id` IN (120,108);
INSERT INTO `battleground_template` VALUES
(108,10,10,81,85,1726,0,1727,0,1,'','Twin Peaks'),
(120,10,10,85,85,1740,0,1739,0,1,'','The Battle for Gilneas');
