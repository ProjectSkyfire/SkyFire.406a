#include "ScriptPCH.h"
#include "Config.h"

enum LevelRewards
{
    GIFT_LEVEL_REWARD  = 62540 // Lil' Deathwing http://www.wowhead.com/item=62540
};

class level_rewards : public PlayerScript
{
public:
    level_rewards() : PlayerScript("level_rewards") {}

    void OnLevelChanged(Player* player, uint8 oldLevel)
    {
        if (player->isGameMaster())
            return;

        uint32 money = 0;

        switch (oldLevel)
        {
            case 9:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.10",0);
                break;
            case 19:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.20",0);
                break;
            case 29:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.30",0);
                break;
            case 39:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.40",0);
                break;
            case 49:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.50",0);
                break;
            case 59:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.60",0);
                break;
            case 69:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.70",0);
                break;
            case 79:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.80",0);
                break;
            case 84:
                money = ConfigMgr::GetIntDefault("Gold.Lvl.Reward.85",0);
                break;
            default:
                return;
        }

        MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

        MailDraft draft("Congratulations", "You are progressing in the game and deserves a reward. Take this and spend on something useful.");

        SQLTransaction trans = CharacterDatabase.BeginTransaction();

        if (money > 0)
            draft.AddMoney(money);

        if (oldLevel == 84)
        {
            Item* item = Item::CreateItem(GIFT_LEVEL_REWARD, 1, 0);
            item->SaveToDB(trans);
            draft.AddItem(item);
        }

        draft.SendMailTo(trans, MailReceiver(player), sender);
        CharacterDatabase.CommitTransaction(trans);
    }
};

void AddSC_level_rewards()
{
    new level_rewards();
}
