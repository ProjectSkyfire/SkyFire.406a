ALTER TABLE `realmlist` CHANGE `gamebuild` `gamebuild` INT( 11 ) UNSIGNED NOT NULL DEFAULT '14333';
UPDATE `realmlist` SET `gamebuild`=13623;