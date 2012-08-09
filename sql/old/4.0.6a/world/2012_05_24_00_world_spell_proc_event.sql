-- Arcane Missiles
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (79683,-79683,5143);
INSERT INTO `spell_linked_spell` VALUES 
(79683, 79808, 0, 'Arcane Missiles aurastate link'),
(-79683, -79808, 0, 'Arcane Missiles aurastate link'),
-- On retail, you lose the 79683 aura by just clicking on arcane missiles
(5143,-79683,0,'Arcane missiles! aura removal due to arcane missiles cast');

-- 79683 in fact doesnt proc at all by using 5143, thats wy i remove the 79683 manually up there
-- this is here just to make sure no other spell will proc it. 
DELETE FROM `spell_proc_event` WHERE `entry` = 79683;
INSERT INTO `spell_proc_event` VALUES
(79683,64,3,2048,0,0,0,0,0,0,0);

-- 79684 Offensive State (DND) for goblins and worgens
DELETE FROM `playercreateinfo_spell` WHERE `race` IN (9,22) AND `class` = 8 AND `Spell` = 79684; 
INSERT INTO `playercreateinfo_spell` VALUES
(9,8,79684,'Mages - Offensive State (DND) - Enables Arcane Missiles'), -- Goblin
(22,8,79684,'Mages - Offensive State (DND) - Enables Arcane Missiles'); -- Worgen

