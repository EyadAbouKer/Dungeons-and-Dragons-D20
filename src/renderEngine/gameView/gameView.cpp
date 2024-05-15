#include "gameView.h"

// Constructor
GameView::GameView() = default;

void GameView::renderMap(Map* map, Player* player)
{
    std::vector<std::vector<char>> grid(map->getWidth(), std::vector<char>(map->getBreadth(), '.'));
    for (auto& element : map->elements)
    {
        char c = '.';
        if (element.second.type == Location::Type::Enemy) c = 'E';
        else if (element.second.type == Location::Type::Wall) c = (char)186;
        else if (element.second.type == Location::Type::Chest) c = 'C';
        else if (element.second.type == Location::Type::Friend) c = 'F';
        else if (element.second.type == Location::Type::Door) c = 'D';
        grid[element.first.x][element.first.y] = c;
    }
    grid[player->getX()][player->getY()] = 'P';

    // Use a string stream to build the map string
    std::ostringstream mapStream;
    for (const auto& row : grid)
    {
        for (char c : row)
        {
            mapStream << c << " ";
        }
        mapStream << '\n';
    }

    // Print the entire map at once
    std::cout << mapStream.str();
    LogWriter::writeLogsToFilee(mapStream.str());
}

string GameView::chooseMap(const vector<std::string>& maps) {
    char input;
    int option = 0;
    int max_option = maps.size();
    do {
        std::system("cls");
        std::cout << "Choices\n";
        for (int i = 0; i < maps.size(); i++) {
            std::cout << (option == i ? "> " : "  ") << maps[i] << "\n";
        }
        std::cout << (option == maps.size() ? "> " : "  ") << "Create new map" << "\n";
        input = (char)_getch();

        if (input == UP_ARROW_KEY) {
            option = (option <= 0) ? max_option : --option;
        }

        if (input == DOWN_ARROW_KEY) {
            option = (option >= max_option) ? 0 : ++option;
        }

        if (input == ENTER_KEY) {
            if (option == maps.size()) { //meaning that "create new map" option is selected
                return "create new map";
            }
            return maps[option]; // if a loaded map is selected, we return its name.
        }

    } while (true);
}

string GameView::chooseCampaign(const vector<std::string>& campaigns) {
    char input;
    int option = 0;
    int max_option = campaigns.size();
    do {
        std::system("cls");
        std::cout << "Choices\n";
        for (int i = 0; i < campaigns.size(); i++) {
            std::cout << (option == i ? "> " : "  ") << campaigns[i] << "\n";
        }
        std::cout << (option == campaigns.size() ? "> " : "  ") << "Create new campaign" << "\n";
        input = (char)_getch();

        if (input == UP_ARROW_KEY) {
            option = (option <= 0) ? max_option : --option;
        }

        if (input == DOWN_ARROW_KEY) {
            option = (option >= max_option) ? 0 : ++option;
        }

        if (input == ENTER_KEY) {
            if (option == campaigns.size()) { //meaning that "create new map" option is selected
                return "create new campaign";
            }
            return campaigns[option]; // if a loaded map is selected, we return its name.
        }

    } while (true);
}

void GameView::confirmCampaignMapsView(const vector<std::string> maps) {
    std::system("cls");
    std::cout << "Campaign maps loaded successfully\n";
    std::cout << "you have the following " << maps.size() << " maps to win this campaign\n";
    for (const auto & map : maps) {
        std::cout << "  " << map << "\n";
    }
    cout << "The game starts now\n";
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Pause for 2 seconds

}

int GameView::newCampaignCreatorView() {
    bool isRandomMapCreation = GameView::chooseBuildWay();
    if (isRandomMapCreation) return 0;
    else {
        return GameView::selectMapsNumber();
    }

}

bool GameView::chooseBuildWay() {
    char input;
    int option = 0;
    int max_option = 1;
    do {
        std::system("cls");
        std::cout << "Choose number of maps you want to have in your campaign:\n";

        std::cout << (option == 0 ? "> " : "  ") << "use random maps creation\n";
        std::cout << (option == 1 ? "> " : "  ") << "create maps yourself\n";
        input = (char)_getch();

        if (input == UP_ARROW_KEY)
        {
            option = (option <= 0) ? max_option : --option;
        }

        if (input == DOWN_ARROW_KEY)
        {
            option = (option >= max_option) ? 0 : ++option;
        }

        if (input == ENTER_KEY)
        {
            return option;
        }
    } while (true);
}


int GameView::selectMapsNumber() {
    char input;
    int option = 0;
    int max_option = 2;
    do {
        std::system("cls");
        std::cout << "Choose number of maps you want to have in your campaign:\n";

        std::cout << (option == 0 ? "> " : "  ") << "1 map\n";
        std::cout << (option == 1 ? "> " : "  ") << "2 maps\n";
        std::cout << (option == 2 ? "> " : "  ") << "3 maps\n";
        input = (char)_getch();

        if (input == UP_ARROW_KEY)
        {
            option = (option <= 0) ? max_option : --option;
        }

        if (input == DOWN_ARROW_KEY)
        {
            option = (option >= max_option) ? 0 : ++option;
        }

        if (input == ENTER_KEY)
        {
            return option+1;
        }
    } while (true);
}



