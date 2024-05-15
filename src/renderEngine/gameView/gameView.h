
#ifndef D20_GAMEVIEW_H
#define D20_GAMEVIEW_H

#include "maps/map/map.h"
#include "characters/player/player.h"
#include <vector>
#include <algorithm>
#include <string>
#include "logs/logWriter.h"
using namespace std;

// just so that It can see them:
class Map;
class Player;

class GameView {

public:

    GameView();

    // This method renders the map on the console.
    static void renderMap(Map* map, Player* player);

    //This method renders UI to choose the map to load given a vector of all present maps in the system.
    //It returns the selected map.
    static string chooseMap(const vector<std::string>& maps);

    //This method renders UI to choose the campaign to load given a vector of all present campaigns in the system.
    //It returns the selected campaign.
    static string chooseCampaign(const vector<std::string>& campaigns);

    static void confirmCampaignMapsView(const vector<std::string> maps);

    // returns:
    // 0 if user choose the default package with 3 maps and random number and position of positionables
    // 1 if the user wants to specifically choose 1 map
    // 2 if the user wants to specifically choose 2 map
    // 3 if the user wants to specifically choose 3 map
    static int newCampaignCreatorView();

    // returns 0 if player chooses to use the default package of creating a map with random values,
    // returns 1 if player chooses to create the map themselves.
    static bool chooseBuildWay();

    static int selectMapsNumber();
};


#endif //D20_GAMEVIEW_H
