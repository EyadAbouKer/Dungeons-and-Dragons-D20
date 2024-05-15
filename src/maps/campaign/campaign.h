#ifndef D20_CAMPAIGN_H
#define D20_CAMPAIGN_H


#include "maps/map/map.h"
#include "logs/logWriter.h"

class Campaign {

public:

    Campaign();

    Campaign(vector<Map*> maps);

    Map *getCurrentMap() const;

    void setCurrentMap(Map *currentMap);

    int getCurrentIndex() const;

    void setCurrentIndex(int currentIndex);

    void addMap(Map* map);

    bool loadCampaignMaps(const string& filePath);

    bool saveCampaignMaps(const string& filePath);

    bool loadCampaignSelector(const string& filePath);

    bool saveCampaignSelector(const string& filePath);

    void enterDoor();
private:
    vector<Map*> maps;
    vector<string> mapsNames; // a list of names of loaded maps files
    Map* currentMap;
    int currentIndex;
};


#endif //D20_CAMPAIGN_H
