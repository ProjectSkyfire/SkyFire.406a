ALTER TABLE `creature_onkill_reputation` RENAME `creature_onkill_reward`;

ALTER TABLE `creature_onkill_reward`
 ADD COLUMN `CurrencyId1` SMALLINT (6) UNSIGNED NOT NULL DEFAULT 0 AFTER `TeamDependent`,
 ADD COLUMN `CurrencyId2` SMALLINT (6) UNSIGNED NOT NULL DEFAULT 0 AFTER `CurrencyId1`,
 ADD COLUMN `CurrencyId3` SMALLINT (6) UNSIGNED NOT NULL DEFAULT 0 AFTER `CurrencyId2`,
 ADD COLUMN `CurrencyCount1` MEDIUMINT (9) NOT NULL DEFAULT 0 AFTER `CurrencyId3`,
 ADD COLUMN `CurrencyCount2` MEDIUMINT (9) NOT NULL DEFAULT 0 AFTER `CurrencyCount1`,
 ADD COLUMN `CurrencyCount3` MEDIUMINT (9) NOT NULL DEFAULT 0 AFTER `CurrencyCount2`;

UPDATE `command` SET `name` = 'reload creature_onkill_reward' WHERE `name` = 'reload creature_onkill_reputation';
