/*
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2011 TrilliumEMU <http://www.arkania.net/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "ScriptMgr.h"

class spell_tournament_charge : public SpellScriptLoader
{
    public:
        spell_tournament_charge() : SpellScriptLoader("spell_tournament_charge") { }

        class spell_tournament_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tournament_charge_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Unit *caster = GetCaster())
                    {
                        caster->CastSpell(target, 74399, true);
                        caster->CastSpell(target, 68321, true);

                        if (target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->GetEntry() == 33272)
                        {
                            //Kill Credit
                            if (Unit *player = caster->GetCharmerOrOwner())
                                player->CastSpell(player, 62658, true);
                        }
                    }

                    if (target->GetAura(64100))
                        target->RemoveAuraFromStack(64100);
                    else if (target->GetAura(62552))
                        target->RemoveAuraFromStack(62552);
                    else if (target->GetAura(62719))
                        target->RemoveAuraFromStack(62719);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_tournament_charge_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_tournament_charge_SpellScript();
        }
};

class spell_tournament_shield_breaker : public SpellScriptLoader
{
    public:
        spell_tournament_shield_breaker() : SpellScriptLoader("spell_tournament_shield_breaker") { }

        class spell_tournament_shield_breaker_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tournament_shield_breaker_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Unit *caster = GetCaster())
                    {
                        caster->CastSpell(target, 62626, true );

                        if (target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->GetEntry() == 33243)
                        {
                            //Kill Credit
                            if (Unit *player = caster->GetCharmerOrOwner())
                                player->CastSpell(player, 62673, true);
                        }
                    }

                    if (target->GetAura(64100))
                        target->RemoveAuraFromStack(64100);
                    else if (target->GetAura(62552))
                        target->RemoveAuraFromStack(62552);
                    else if (target->GetAura(62719))
                        target->RemoveAuraFromStack(62719);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_tournament_shield_breaker_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_tournament_shield_breaker_SpellScript();
        }
};

class spell_tournament_trust : public SpellScriptLoader
{
    public:
        spell_tournament_trust() : SpellScriptLoader("spell_tournament_trust") { }

        class spell_tournament_trust_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tournament_trust_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (Unit *caster = GetCaster())
                    {
                        if (target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->GetEntry() == 33229)
                        {
                            //Kill Credit
                            if (Unit *player = caster->GetCharmerOrOwner())
                                player->CastSpell(player, 62672, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_tournament_trust_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_tournament_trust_SpellScript();
        }
};

class spell_tournament_duel : public SpellScriptLoader
{
    public:
        spell_tournament_duel() : SpellScriptLoader("spell_tournament_duel") { }

        class spell_tournament_duel_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_tournament_duel_SpellScript);

            void HandleEffectScriptEffect(SpellEffIndex /*effIndex*/)
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Unit *caster = GetCaster()->GetCharmerOrOwner())
                        caster->CastSpell(target, 62875, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_tournament_duel_SpellScript::HandleEffectScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_tournament_duel_SpellScript();
        }
};

void AddSC_argen_tournament()
{
    new spell_tournament_charge;
    new spell_tournament_shield_breaker;
    new spell_tournament_trust;
    new spell_tournament_duel;
}
