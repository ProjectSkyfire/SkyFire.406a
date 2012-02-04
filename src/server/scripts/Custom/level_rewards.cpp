#include "ScriptPCH.h"

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
                money = 150000; // 15 gold
                break;
            case 19:
                money = 150000;
                break;
            case 29:
                money = 300000;
                break;
            case 39:
                money = 300000;
                break;
            case 49:
                money = 300000;
                break;
            case 59:
                money = 1000000;
                break;
            case 69:
                money = 2000000;
                break;
            case 79:
                money = 5000000;
                break;
            case 84:
                money = 10000000;
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
