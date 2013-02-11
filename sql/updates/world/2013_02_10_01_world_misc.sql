-- Health, faction, damage and level fixes for mobs in Blackrock Caverns

UPDATE creature_template SET health_mod=15, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=530, maxdmg=713, attackpower=827, baseattacktime=2000 WHERE entry IN (39708,39980,39982,39985,39978,39985,40004,40019,40017,40021,50284);
UPDATE creature_template SET `Health_mod`=22.8152 WHERE entry IN (39665, 39698);
UPDATE creature_template SET health_mod=45.05232558139535, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=545, maxdmg=723, attackpower=839, dmg_multiplier=7.5, baseattacktime=2000 WHERE entry IN (39987,39994,40023);
UPDATE creature_template SET health_mod=3, minlevel=85, maxlevel=85, faction_A=16, faction_H=16, mindmg=470, maxdmg=650, attackpower=750, baseattacktime=2000 WHERE entry IN (40084);
