DELETE FROM `creature_text` WHERE `entry` IN (36612);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
('36612','0','0','This is the beginning AND the end, mortals. None may enter the master\'s sanctum!','14','0','100','0','0','0','SAY_ENTER_ZONE'),
('36612','1','0','The Scourge will wash over this world as a swarm of death and destruction!','14','0','100','0','0','0','SAY_AGGRO'),
('36612','2','0','BONE STORM!','14','0','100','0','0','0','SAY_BONE_STORM'),
('36612','3','0','Bound by bone!','14','0','100','0','0','0','SAY_BONESPIKE'),
('36612','4','0','More bones for the offering!','14','0','100','0','0','0','SAY_KILL'),
('36612','5','0','I see... only darkness...','14','0','100','0','0','0','SAY_DEATH'),
('36612','6','0','THE MASTER\'S RAGE COURSES THROUGH ME!','14','0','100','0','0','0','SAY_BERSERK'),
('36612','7','0','You Sunreaver Lackeys are all the same.','14','0','100','0','0','0','EMOTE_BONE_STORM');
