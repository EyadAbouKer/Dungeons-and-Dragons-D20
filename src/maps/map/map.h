
#ifndef D20_MAP_H
#define D20_MAP_H

#include <iostream>
#include <fstream>
#include <map>
#include "maps/positionable.h"
#include "characters/enemy/enemy.h"
#include "characters/character/friend.h"
#include "characters/player/player.h"
#include "renderEngine/gameView/gameView.h"

using namespace std;


struct Element {
    Location::Type type;
    Positionable* positionable;
};

class Map {

public:

    std::map<Location::Position, Element> elements;

    Map();

    Map(int width, int breadth);

    bool saveMap(const string& filePath);

    bool loadMap(const string& filePath);

    bool loadWalls(const string& filePath);

    void createSimpleMap();

    void createSimpleMap2();

    void createSimpleMap3();

    void displayMap();

    bool saveToFile(const string& filePath);

    int getWidth() const;

    void setWidth(int width);

    int getBreadth() const;

    void setBreadth(int breadth);

    bool loadMapSelector(const string& filePath);

    bool saveMapSelector(const string& filePath);

    int getNumberOfEnemies() const;

private:
    int width{};
    int breadth{};
};


#endif //D20_MAP_H
