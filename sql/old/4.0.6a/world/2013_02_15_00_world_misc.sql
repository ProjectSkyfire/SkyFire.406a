-- Fix Mage's Tol barad Portals and Teleports

UPDATE gameobject_template SET data0=88341 WHERE entry=206615; -- ally portal
UPDATE gameobject_template SET data0=88339 WHERE entry=206616; -- horde portal

DELETE FROM spell_target_position WHERE id IN (88342, 88344);
INSERT INTO spell_target_position VALUES
(88342, 732, -334.60, 1043.80, 21.900, 1.5), -- ally teleport
(88344, 732, -601.40, 1382.03, 21.900, 1.5), -- horde teleport
(89597, 732, -334.60, 1043.80, 21.900, 1.5); -- Baradin's Wardens Tabard (63379)
