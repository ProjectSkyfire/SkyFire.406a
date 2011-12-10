ALTER TABLE `guild` DROP COLUMN `totalXP`;
ALTER TABLE `guild` DROP COLUMN `todayXP`;
ALTER TABLE `guild` DROP COLUMN `XPCap`;
ALTER TABLE `guild` DROP COLUMN `level`;

ALTER TABLE `guild` ADD COLUMN `xp` BIGINT(20) AFTER `BankMoney`;
ALTER TABLE `guild` ADD COLUMN `level` INT(10) AFTER `xp`;
ALTER TABLE `guild` ADD COLUMN `m_today_xp` BIGINT(20) AFTER `level`;
ALTER TABLE `guild` ADD COLUMN `m_xp_cap` BIGINT(20) AFTER `m_today_xp`;