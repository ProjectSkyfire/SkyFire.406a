-- Cobra Shot focus effect
DELETE FROM spell_scripts WHERE id = 77767;
INSERT INTO spell_scripts (id,effindex,delay,command,datalong,datalong2,dataint) VALUES (77767,1,0,15,91954,1,1);

-- Steady Shot focus effect
DELETE FROM spell_scripts WHERE id = 56641;
INSERT INTO spell_scripts (id,effindex,delay,command,datalong,datalong2,dataint) VALUES (56641,2,0,15,77443,1,1);