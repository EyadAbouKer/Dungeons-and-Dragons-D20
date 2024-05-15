#include "friendarena.h"
#include <random>


FriendArena::FriendArena(Player& player, Friend& f)
{
    this->player = &player;
    this->f = &f;

    // Friend can heal 20%, 40%, or 60% of player's maxHP
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 3);

    int random_value = dist(rng);

    switch (random_value)
    {
    case 1:
        f.setHealAmount(player.getMaxHP() * 0.2);
        break;
    case 2:
        f.setHealAmount(player.getMaxHP() * 0.4);
        break;
    case 3:
        f.setHealAmount(player.getMaxHP() * 0.6);
        break;
    }
}

// return 1 if player wins, 0 if player flees, and -1 if player dies
void FriendArena::begin()
{
    char input;
    int option = 0;
    int totalWidth = 60;

    do
    {
        std::system("cls");
        player->display_hp();
        std::cout << "+" << std::string(totalWidth, '-') << "+\n";

        std::string header = "Friend ( can heal ";
        if (f->getHealAmount() == player->getMaxHP() * 0.2)
        {
            header += "20% )";
        }
        else if (f->getHealAmount() == player->getMaxHP() * 0.4)
        {
            header += "40% )";
        }
        else if (f->getHealAmount() == player->getMaxHP() * 0.6)
        {
            header += "60% )";
        }

        int header_padding = (totalWidth - header.length()) / 2;
        std::cout << "|" << std::setw(header_padding + header.length()) << header << std::setw(totalWidth - header_padding - header.length() + 2) << "|\n";
        std::cout << "+" << std::string(totalWidth, '-') << "+\n";

        std::string heal_option = "Heal";
        int padding = totalWidth - heal_option.length() - 4; // 4 spaces for "| " and " >" or "  "
        std::cout << "| " << (option == 0 ? "> " : "  ") << heal_option << std::string(padding + 1, ' ') << "|\n";
        std::cout << "|" << std::string(totalWidth, '-') << "|\n";

        std::string go_back_option = "Go Back";
        padding = totalWidth - go_back_option.length() - 4; // 4 spaces for "| " and " >" or "  "
        std::cout << "| " << (option == 1 ? "> " : "  ") << go_back_option << std::string(padding + 1, ' ') << "|\n";
        std::cout << "+" << std::string(totalWidth, '-') << "+\n";

        input = _getch();

        if (input == UP_ARROW_KEY)
        {
            option = (option - 1 < 0) ? 1 : option - 1;
        }

        if (input == DOWN_ARROW_KEY)
        {
            option = (option + 1 > 1) ? 0 : option + 1;
        }

        if (input == ENTER_KEY)
        {
            switch (option)
            {
                case 0:
                    if (!f->getHasHealed())
                    {
                        player->heal(f->getHealAmount());
                        f->setHasHealed(true); // Set to true after healing
                    }
                    else
                    {
                        std::cout << "You can only heal once.\n";
                        std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 2 seconds
                    }
                    break;
                case 1:
                    return;
            }
        }

    } while (true);
}
