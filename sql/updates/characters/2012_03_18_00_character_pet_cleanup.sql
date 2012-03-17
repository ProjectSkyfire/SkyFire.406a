delete from character_pet where CreatedBySpell != 0;
delete from `character_pet_declinedname` WHERE `id` not in (select character_pet.id from character_pet);
delete from `pet_aura` WHERE `guid` not in (select id from character_pet);
delete from `pet_spell` WHERE `guid` not in (select id from character_pet);
delete from `pet_spell_cooldown` WHERE `guid` not in (select id from character_pet);
delete from `pet_aura` WHERE `guid` not in (select id from character_pet);