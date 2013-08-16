UPDATE creature_template SET ScriptName = '' WHERE entry = 66392;   -- hotrod (Spell Can't have NPC scriptname)
DELETE FROM npc_spellclick_spells WHERE npc_entry = 66392; -- hotrod (removes unneeded spell_clicks)
UPDATE creature_template SET unit_flags = 512 WHERE entry = 34865; -- Tunneling Worm (fixes npc unit flag, these are to be yellow)
