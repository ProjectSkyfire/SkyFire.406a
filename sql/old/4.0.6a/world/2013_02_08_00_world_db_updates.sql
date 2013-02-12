-- Drop unused tables from skyfire DB
DROP TABLE IF EXISTS `creature_onkill_reputation`;
DROP TABLE IF EXISTS `game_event_npc_gossip`;

-- DB Realignment

ALTER TABLE `instance_template`
	CHANGE COLUMN `parent` `parent` SMALLINT(5) UNSIGNED NOT NULL AFTER `map`;
	
ALTER TABLE `creature_classlevelstats`
	CHANGE COLUMN `basehp0` `basehp0` INT(10) NOT NULL AFTER `class`,
	CHANGE COLUMN `basehp1` `basehp1` INT(10) NOT NULL AFTER `basehp0`,
	CHANGE COLUMN `basehp2` `basehp2` INT(10) NOT NULL AFTER `basehp1`;	

ALTER TABLE `gameobject_template`
	CHANGE COLUMN `data24` `data24` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data23`,
	CHANGE COLUMN `data25` `data25` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data24`,
	CHANGE COLUMN `data26` `data26` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data25`,
	CHANGE COLUMN `data27` `data27` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data26`,
	CHANGE COLUMN `data28` `data28` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data27`,
	CHANGE COLUMN `data29` `data29` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data28`,
	CHANGE COLUMN `data30` `data30` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data29`,
	CHANGE COLUMN `data31` `data31` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `data30`,
	CHANGE COLUMN `WDBVerified` `WDBVerified` SMALLINT(6) NULL DEFAULT '1' AFTER `ScriptName`;	
ALTER TABLE `game_event`
	CHANGE COLUMN `EventEntry` `EventEntry` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `game_event_battleground_holiday`
	CHANGE COLUMN `eventEntry` `eventEntry` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `game_event_condition`
	CHANGE COLUMN `eventEntry` `eventEntry` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' FIRST;

ALTER TABLE `instance_template`
	CHANGE COLUMN `allowMount` `allowMount` TINYINT(3) NOT NULL DEFAULT '0' AFTER `script`;
	
ALTER TABLE `spell_proc_event`
	CHANGE COLUMN `SpellFamilyMask0` `SpellFamilyMask0` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyName`,
	CHANGE COLUMN `SpellFamilyMask1` `SpellFamilyMask1` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyMask0`,
	CHANGE COLUMN `SpellFamilyMask2` `SpellFamilyMask2` INT(10) UNSIGNED NULL DEFAULT NULL AFTER `SpellFamilyMask1`;
ALTER TABLE `spell_proc`
	CHANGE COLUMN `charges` `charges` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `cooldown`;
	
ALTER TABLE `spell_enchant_proc_data`
	CHANGE COLUMN `procEx` `procEx` INT(10) UNSIGNED NOT NULL DEFAULT '0' AFTER `PPMChance`;
	
ALTER TABLE `item_template`
	CHANGE COLUMN `spellcharges_1` `spellcharges_1` SMALLINT(6) NULL DEFAULT NULL AFTER `spelltrigger_1`;
	
ALTER TABLE `quest_template`
   CHANGE COLUMN `Method` `Method` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '2' AFTER `entry`,
	CHANGE COLUMN `ZoneOrSort` `ZoneOrSort` MEDIUMINT(8) NOT NULL DEFAULT '0' AFTER `Method`,
	CHANGE COLUMN `MinLevel` `MinLevel` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SkillOrClassMask`,
	CHANGE COLUMN `MaxLevel` `MaxLevel` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `MinLevel`,
	CHANGE COLUMN `QuestLevel` `QuestLevel` MEDIUMINT(8) NOT NULL DEFAULT '1' AFTER `MaxLevel`,
	CHANGE COLUMN `Type` `Type` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `QuestLevel`,
	CHANGE COLUMN `RequiredSkillValue` `RequiredSkillValue` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredRaces`,
	CHANGE COLUMN `RepObjectiveFaction` `RepObjectiveFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredSkillValue`,
	CHANGE COLUMN `RepObjectiveFaction2` `RepObjectiveFaction2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RepObjectiveValue`,
	CHANGE COLUMN `RequiredMinRepFaction` `RequiredMinRepFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RepObjectiveValue2`,
	CHANGE COLUMN `RequiredMaxRepFaction` `RequiredMaxRepFaction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredMinRepValue`,
	CHANGE COLUMN `PointMapId` `PointMapId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewMailDelaySecs`,
	CHANGE COLUMN `SuggestedPlayers` `SuggestedPlayers` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RequiredMaxRepValue`,
	CHANGE COLUMN `SpecialFlags` `SpecialFlags` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `QuestFlags`,
	CHANGE COLUMN `CharTitleId` `CharTitleId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SpecialFlags`,
	CHANGE COLUMN `PlayersSlain` `PlayersSlain` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `CharTitleId`,
	CHANGE COLUMN `BonusTalents` `BonusTalents` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `PlayersSlain`,
	CHANGE COLUMN `RewardArenaPoints` `RewardArenaPoints` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `BonusTalents`,
	CHANGE COLUMN `RewXPId` `RewXPId` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `NextQuestInChain`,
	CHANGE COLUMN `SrcItemCount` `SrcItemCount` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `SrcItemId`,
	CHANGE COLUMN `ReqItemCount1` `ReqItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemId6`,
	CHANGE COLUMN `ReqItemCount2` `ReqItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount1`,
	CHANGE COLUMN `ReqItemCount3` `ReqItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount2`,
	CHANGE COLUMN `ReqItemCount4` `ReqItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount3`,
	CHANGE COLUMN `ReqItemCount5` `ReqItemCount5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount4`,
	CHANGE COLUMN `ReqItemCount6` `ReqItemCount6` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqItemCount5`,
	CHANGE COLUMN `ReqSourceCount1` `ReqSourceCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceId4`,
	CHANGE COLUMN `ReqSourceCount2` `ReqSourceCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount1`,
	CHANGE COLUMN `ReqSourceCount3` `ReqSourceCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount2`,
	CHANGE COLUMN `ReqSourceCount4` `ReqSourceCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqSourceCount3`,
	CHANGE COLUMN `ReqCreatureOrGOCount1` `ReqCreatureOrGOCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOId4`,
	CHANGE COLUMN `ReqCreatureOrGOCount2` `ReqCreatureOrGOCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount1`,
	CHANGE COLUMN `ReqCreatureOrGOCount3` `ReqCreatureOrGOCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount2`,
	CHANGE COLUMN `ReqCreatureOrGOCount4` `ReqCreatureOrGOCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ReqCreatureOrGOCount3`,
	CHANGE COLUMN `RewChoiceItemCount1` `RewChoiceItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemId6`,
	CHANGE COLUMN `RewChoiceItemCount2` `RewChoiceItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount1`,
	CHANGE COLUMN `RewChoiceItemCount3` `RewChoiceItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount2`,
	CHANGE COLUMN `RewChoiceItemCount4` `RewChoiceItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount3`,
	CHANGE COLUMN `RewChoiceItemCount5` `RewChoiceItemCount5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount4`,
	CHANGE COLUMN `RewChoiceItemCount6` `RewChoiceItemCount6` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewChoiceItemCount5`,
    CHANGE COLUMN `RewItemCount1` `RewItemCount1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemId4`,
	CHANGE COLUMN `RewItemCount2` `RewItemCount2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount1`,
	CHANGE COLUMN `RewItemCount3` `RewItemCount3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount2`,
	CHANGE COLUMN `RewItemCount4` `RewItemCount4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `RewItemCount3`,
	CHANGE COLUMN `RewRepFaction1` `RewRepFaction1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewItemCount4`,
	CHANGE COLUMN `RewRepFaction2` `RewRepFaction2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction1`,
	CHANGE COLUMN `RewRepFaction3` `RewRepFaction3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction2`,
	CHANGE COLUMN `RewRepFaction4` `RewRepFaction4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction3`,
	CHANGE COLUMN `RewRepFaction5` `RewRepFaction5` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'faction id from Faction.dbc in this case' AFTER `RewRepFaction4`,
	CHANGE COLUMN `DetailsEmote1` `DetailsEmote1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `PointOpt`,
	CHANGE COLUMN `DetailsEmote2` `DetailsEmote2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote1`,
	CHANGE COLUMN `DetailsEmote3` `DetailsEmote3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote2`,
	CHANGE COLUMN `DetailsEmote4` `DetailsEmote4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmote3`,	
	CHANGE COLUMN `IncompleteEmote` `IncompleteEmote` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `DetailsEmoteDelay4`,
	CHANGE COLUMN `CompleteEmote` `CompleteEmote` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `IncompleteEmote`,
	CHANGE COLUMN `OfferRewardEmote1` `OfferRewardEmote1` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `CompleteEmote`,
	CHANGE COLUMN `OfferRewardEmote2` `OfferRewardEmote2` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote1`,
	CHANGE COLUMN `OfferRewardEmote3` `OfferRewardEmote3` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote2`,
	CHANGE COLUMN `OfferRewardEmote4` `OfferRewardEmote4` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `OfferRewardEmote3`;	
	
ALTER TABLE `game_event`
	CHANGE COLUMN `EventEntry` `EventEntry` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' FIRST;
	
ALTER TABLE `vehicle_accessory`
	CHANGE COLUMN `seat_id` `seat_id` TINYINT(4) NOT NULL DEFAULT '0' AFTER `accessory_entry`,
	CHANGE COLUMN `minion` `minion` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `seat_id`,
	CHANGE COLUMN `summontype` `summontype` TINYINT(3) NOT NULL DEFAULT '0' AFTER `description`;

ALTER TABLE `vehicle_template_accessory`
	CHANGE COLUMN `seat_id` `seat_id` TINYINT(4) NOT NULL DEFAULT '0' AFTER `accessory_entry`,
	CHANGE COLUMN `minion` `minion` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' AFTER `seat_id`,
	CHANGE COLUMN `summontype` `summontype` TINYINT(3) UNSIGNED NOT NULL DEFAULT '6' COMMENT 'see enum TempSummonType' AFTER `description`;
	
ALTER TABLE `instance_encounters`
	CHANGE COLUMN `lastEncounterDungeon` `lastEncounterDungeon` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'If not 0, LfgDungeon.dbc entry for the instance it is last encounter in' AFTER `creditEntry`;	
	
ALTER TABLE `game_graveyard_zone`
	CHANGE COLUMN `faction` `faction` MEDIUMINT(8) UNSIGNED NOT NULL DEFAULT '0' AFTER `ghost_zone`;	
	
ALTER TABLE `game_event_seasonal_questrelation`
	CHANGE COLUMN `eventEntry` `eventEntry` SMALLINT(5) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Entry of the game event' AFTER `questId`;

ALTER TABLE `npc_spellclick_spells`
	CHANGE COLUMN `user_type` `user_type` TINYINT(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'relation with summoner: 0-no 1-friendly 2-raid 3-party player can click' AFTER `cast_flags`;
	
ALTER TABLE `guild_xp_for_level`
	CHANGE COLUMN `xp_for_next_level` `xp_for_next_level` INT(20) NOT NULL AFTER `lvl`;	
	
ALTER TABLE `item_loot_template`
	CHANGE COLUMN `maxcount` `maxcount` TINYINT(3) UNSIGNED NOT NULL DEFAULT '1' AFTER `mincountOrRef`;	
	
ALTER TABLE `skill_fishing_base_level`
	CHANGE COLUMN `skill` `skill` MEDIUMINT(8) NOT NULL DEFAULT '0' COMMENT 'Base skill level requirement' AFTER `entry`;
	
ALTER TABLE `script_texts`
	CHANGE COLUMN `type` `type` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `sound`,
	CHANGE COLUMN `language` `language` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `type`,
	CHANGE COLUMN `emote` `emote` MEDIUMINT(5) UNSIGNED NOT NULL DEFAULT '0' AFTER `language`;
	