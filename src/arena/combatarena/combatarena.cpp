#include "combatarena.h"
#include "logs/logWriter.h"
#include <random>


CombatArena::CombatArena(Player& player, Enemy& enemy)
{
	this->player = &player;
	this->enemy = &enemy;
}

// return 1 if player wins, 0 if player flees, and -1 if player dies
int CombatArena::begin()
{
	char input;
	int option = 0;
	int max_option = 2;
	do
	{
		std::system("cls");
		player->display_hp();
		enemy->display_hp();

		std::cout << "Actions\n";
        LogWriter::writeLogsToFile("PLAYER CHOSE ATTACK OR Flee");
		std::cout << (option == 0 ? "> " : "  ") << "attack\n";
		std::cout << (option == 1 ? "> " : "  ") << "flee\n";
		input = (char)_getch();

		if (input == UP_ARROW_KEY)
		{
			option = (option <= 0) ? max_option : --option;
            LogWriter::writeLogsToFile("UP ARROW PRESSED");
		}

		if (input == DOWN_ARROW_KEY)
		{
			option = (option >= max_option) ? 0 : ++option;
            LogWriter::writeLogsToFile("Down ARROW PRESSED");
		}

		if (input == ENTER_KEY)
		{
			switch (option)
			{
			case 0:
			{
                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                // Generate a random number between 0 and 1
                int roll = (int) std::rand() % 2;
                if (roll==1){
                    player->attack(*enemy);
                    LogWriter::writeLogsToFile("Player ATTACKING");
                    player->attack(*enemy);
                }else{
                    enemy->attack(*player);
                    LogWriter::writeLogsToFile("ENEMEY ATTACKING");
                }


				if (enemy->getCurrentHP() <= 0)
				{
					std::cout << enemy->getName() << " died.\n";
                    LogWriter::writeLogsToFile("ENEMIE DEAD");
					std::this_thread::sleep_for(std::chrono::seconds(1));
					return 1; // return 1 if the player wins
				}

				std::default_random_engine rng(std::random_device{}());
				std::uniform_real_distribution<float> dist(0.0f, 1.0f);

				float random_value = dist(rng);

				// 10% chance for enemy to heal 1/10 health
				if (random_value < 0.1f)
				{
					enemy->heal(enemy->getMaxHP() / 10);
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
				else
				{
					enemy->attack(*player);
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				if (player->getCurrentHP() <= 0)
				{
					std::cout << player->getName() << " died.\n";
					std::this_thread::sleep_for(std::chrono::seconds(1));
                           std::cout		<<"+---------------------------------------------------------------------------------------------------------------------+\n"
                                           <<"|**********************************************************GAME OVER**************************************************|\n"
                                           <<"+---------------------------------------------------------------------------------------------------------------------+\n";
                           std::cout       << "     ****************************************************"<<player->getName() <<" is dead****************************************\n";
                    LogWriter::writeLogsToFile("GAME IS ENDED");
                    cout<<"\n"
                          "$$$$$$$$\\  $$$$$$\\  $$\\       $$$$$$$$\\ $$$$$$$\\        $$$$$$\\  $$$$$$\\        $$\\   $$\\ $$$$$$\\ $$\\   $$\\  $$$$$$\\  \n"
                          "\\__$$  __|$$  __$$\\ $$ |      $$  _____|$$  __$$\\       \\_$$  _|$$  __$$\\       $$ | $$  |\\_$$  _|$$$\\  $$ |$$  __$$\\ \n"
                          "   $$ |   $$ /  $$ |$$ |      $$ |      $$ |  $$ |        $$ |  $$ /  \\__|      $$ |$$  /   $$ |  $$$$\\ $$ |$$ /  \\__|\n"
                          "   $$ |   $$$$$$$$ |$$ |      $$$$$\\    $$$$$$$\\ |        $$ |  \\$$$$$$\\        $$$$$  /    $$ |  $$ $$\\$$ |$$ |$$$$\\ \n"
                          "   $$ |   $$  __$$ |$$ |      $$  __|   $$  __$$\\         $$ |   \\____$$\\       $$  $$<     $$ |  $$ \\$$$$ |$$ |\\_$$ |\n"
                          "   $$ |   $$ |  $$ |$$ |      $$ |      $$ |  $$ |        $$ |  $$\\   $$ |      $$ |\\$$\\    $$ |  $$ |\\$$$ |$$ |  $$ |\n"
                          "   $$ |   $$ |  $$ |$$$$$$$$\\ $$$$$$$$\\ $$$$$$$  |      $$$$$$\\ \\$$$$$$  |      $$ | \\$$\\ $$$$$$\\ $$ | \\$$ |\\$$$$$$  |\n"
                          "   \\__|   \\__|  \\__|\\________|\\________|\\_______/       \\______| \\______/       \\__|  \\__|\\______|\\__|  \\__| \\______/ \n"
                          "                                                                                                                      \n"
                          "                                                                                                                      \n"
                          "                                                                                                                      ";


                    Sleep(5000);
                           exit(0);
					return -1; // return -1 if the enemy wins
				}
				break;
			}
			case 1:
				return 0; // return 0 if the player flees
			}
		}
	} while (true);
}
