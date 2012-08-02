-- Will of the Necropolis
DELETE FROM spell_proc_event WHERE entry=96171;
INSERT INTO spell_proc_event (entry, ppmRate, cooldown) VALUES (96171, 1, 45);
