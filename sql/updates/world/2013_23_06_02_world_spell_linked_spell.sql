-- Last Stand spell fix
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN(12975,53478);
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `comment`) VALUES 
(12975,12976,'Warrior Last Stand'),
(53478,53479,'Hunter Last Stand'); 