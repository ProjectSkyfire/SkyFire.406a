#include "ScriptPCH.h"
#include "World.h"

class Reset_OnDuelEnd : public PlayerScript
{
    public:
        Reset_OnDuelEnd() : PlayerScript("Reset_OnDuelEnd") {}

    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type)
    {
        // reset cooldowns in elewynn forest and durotar
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN) && (winner->GetZoneId() == sWorld->getIntConfig(CONFIG_DUEL_RESET_ONE) || winner->GetZoneId() == sWorld->getIntConfig(CONFIG_DUEL_RESET_TWO)))
        {
            winner->RemoveArenaSpellCooldowns();
            looser->RemoveArenaSpellCooldowns();
            winner->SetHealth(winner->GetMaxHealth());
            looser->SetHealth(looser->GetMaxHealth());
            if (winner->getPowerType() == POWER_MANA) 
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            if (looser->getPowerType() == POWER_MANA) 
                looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
        }
    }
};

void AddSC_DuelReset()
{
    new Reset_OnDuelEnd;
}