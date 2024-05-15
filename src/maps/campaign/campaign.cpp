#include "campaign.h"


Campaign::Campaign() : currentMap(nullptr), currentIndex(-1)
{
}

Campaign::Campaign(vector<Map*> maps) : currentMap(maps[0]), currentIndex(0), maps(maps)
{
}

Map *Campaign::getCurrentMap() const {
    LogWriter::writeLogsToFile("GETTING CURRENT MAP");
    return currentMap;
}

void Campaign::setCurrentMap(Map *currentMap) {
    Campaign::currentMap = currentMap;
}

int Campaign::getCurrentIndex() const {
    return currentIndex;
}

void Campaign::setCurrentIndex(int currentIndex) {
    Campaign::currentIndex = currentIndex;
}


void Campaign::addMap(Map* map) {
    this->maps.push_back(map);
    LogWriter::writeLogsToFile("ADDING MAP ");

    if (currentMap == nullptr) {
        currentMap = maps[0];
        currentIndex = 0;
    }
}

bool Campaign::loadCampaignMaps(const string &filePath) {
    ifstream inFile(filePath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Couldn't open file for writing\n";
        LogWriter::writeLogsToFile("Error: Couldn't open file for writing");
        return false;
    }
    vector<std::string> mapNames;
    std::string mapName;
    LogWriter::writeLogsToFile("MAP CHOSEN IS"+mapName);
    while (std::getline(inFile, mapName)) {
        // triming leading and trailing whitespaces from a string
        mapName.erase(0, mapName.find_first_not_of(" \t\n\r\f\v"));
        mapName.erase(mapName.find_last_not_of(" \t\n\r\f\v") + 1);
        Map* map = new Map();
        map->loadMap("../src/maps/files/loadedMaps/" + mapName);
        addMap(map);
        mapNames.push_back(mapName);
    }
    this->mapsNames = mapNames;
    GameView::confirmCampaignMapsView(mapNames);

    inFile.close();
    return true;
}

bool Campaign::saveCampaignMaps(const string &filePath) {
    return false;
}

bool Campaign::loadCampaignSelector(const string &filePath) {
    ifstream inFile(filePath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Couldn't open file for writing\n";
        return false;
    }
    LogWriter::writeLogsToFile("LOADING CAMPAIGN SELECTOR");
    std::vector<std::string> campaigns;

    std::string campaignName;
    while (std::getline(inFile, campaignName)) {
        // triming leading and trailing whitespaces from a string
        LogWriter::writeLogsToFile("triming leading and trailing whitespaces from a string");
        campaignName.erase(0, campaignName.find_first_not_of(" \t\n\r\f\v"));
        campaignName.erase(campaignName.find_last_not_of(" \t\n\r\f\v") + 1);
        campaigns.push_back(campaignName);
    }
    inFile.close();

    string selectedCampaign = GameView::chooseCampaign(campaigns);
    if (selectedCampaign == "create new campaign") {
        int selectedOption = GameView::newCampaignCreatorView(); // create simple map option is selected
        if (selectedOption == 0) {
            // write the code to load 3 maps from the default package
        } else { // the user wants to create the maps themselves
            // TODO: tell the user that there will be a map(s) creation process
            while (selectedOption--) {
                // write the code for the view of creating a map (selecting the number of enemies, friends, etc)
            }
        }
    }
    else loadCampaignMaps("../src/maps/files/loadedCampaigns/" + selectedCampaign); // loading a map option is selected

    return true;
}

bool Campaign::saveCampaignSelector(const string &filePath) {
    LogWriter::writeLogsToFile("SAVING CAMPAIGN");

    return true;
}

void Campaign::enterDoor() {
    LogWriter::writeLogsToFile("DOOR ENTERED");
    currentIndex++;
    if (currentIndex < maps.size()) {
        currentMap = maps[currentIndex];
    } else {
        cout << "Player won this game!!!" << endl;
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
        std::this_thread::sleep_for(std::chrono::seconds(9)); // Pause for 2 seconds
        exit(0);
    }
}





