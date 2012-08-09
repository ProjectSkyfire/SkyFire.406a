-- Modify scale for bats in Trisfal Glades --
UPDATE `creature_template` SET `scale` = '0.4' WHERE `entry` IN (1553,1513,1512);
UPDATE `creature_template` SET `scale` = '0.7' WHERE `entry` IN (1554,10357);
