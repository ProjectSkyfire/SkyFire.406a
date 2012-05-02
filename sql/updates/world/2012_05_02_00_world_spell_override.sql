CREATE TABLE IF NOT EXISTS `spell_override` (
	`overrideSpell` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`affSpell` INT(10) NOT NULL DEFAULT '0', 
	`aura` INT(10) NOT NULL DEFAULT '0', 
	`comment` LONGTEXT NOT NULL DEFAULT '',
	PRIMARY KEY	(`overrideSpell`)
) ENGINE=MYISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED;

INSERT INTO spell_override VALUES
(93402,8921,48517,"Eclipse (Solar)"),
(91183,82731,0,"Frostfire orb"),
(88625,2050,0,"Chakra: Holy Word: Chastise"),
(88684,88625,0,"Chakra: Holy Word: Serenity"),
(88685,88625,0,"Chakra: Holy Word: Sanctuary"),
-- idky these are on spell-override there not aura 332
(86213,86121,0,"Soul Swap: Exhale"),
(91711,6229,9173,"Nether Ward Talent"),
(92315,11366,0,"Pyroblast!"),
(82928,19434,0,"Aimed Shot!"), 
(89420,689,0,"Drain Life"),
(81170,6785,0,"Ravage");