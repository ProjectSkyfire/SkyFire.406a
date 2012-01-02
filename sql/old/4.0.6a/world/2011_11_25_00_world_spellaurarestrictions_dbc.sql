DROP TABLE IF EXISTS spellaurarestrictions_dbc;
CREATE TABLE spellaurarestrictions_dbc(
	`Id` INT NOT NULL DEFAULT '0',
	`CasterAuraState` INT NOT NULL DEFAULT '0',
	`TargetAuraState` INT NOT NULL DEFAULT '0',
	`CasterAuraStateNot` INT NOT NULL DEFAULT '0',
	`TargetAuraStateNot` INT NOT NULL DEFAULT '0',
	`casterAuraSpell` INT NOT NULL DEFAULT '0',
	`targetAuraSpell` INT NOT NULL DEFAULT '0',
	`excludeCasterAuraSpell` INT NOT NULL DEFAULT '0',
	`excludeTargetAuraSpell` INT NOT NULL DEFAULT '0',
	PRIMARY KEY (`Id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='';