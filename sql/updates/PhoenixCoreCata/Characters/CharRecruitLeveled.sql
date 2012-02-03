-- -------------------------------------------------------------------------
-- ---------------------------- Recruit Leveled ----------------------------
-- -------------------------------------------------------------------------
CREATE TABLE `recruit_leveled` (
	`guid` INT(10) NOT NULL DEFAULT '0',
	`accId` INT(10) NULL DEFAULT NULL,
	`recruiterId` INT(10) NULL DEFAULT NULL,
	`level` INT(10) NULL DEFAULT NULL,
	PRIMARY KEY (`guid`)
)
COMMENT='In this table are stored recruited friends that have reached 60 or 85 level'
COLLATE='latin1_swedish_ci'
ENGINE=InnoDB;