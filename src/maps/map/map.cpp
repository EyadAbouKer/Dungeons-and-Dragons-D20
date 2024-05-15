#include "map.h"
#include "logs/logWriter.h"
#include "characters/enemy/enemieBuilder/creeps/creeps.h"
#include "dice/dice.h"
#include <random>

Map::Map() : width(20), breadth(20) {}

Map::Map(int width, int breadth) : width(width), breadth(breadth) {}


int Map::getWidth() const {
    return width;
}

void Map::setWidth(int width) {
    Map::width = width;
}

int Map::getBreadth() const {
    return breadth;
}

void Map::setBreadth(int breadth) {
    Map::breadth = breadth;
}


bool Map::saveMap(const string& filePath) {
    ofstream outFile(filePath, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Couldn't open file for writing\n";
        return false;
    }

    // Write width and breadth to file
    outFile.write(reinterpret_cast<const char*>(&width), sizeof(width));
    outFile.write(reinterpret_cast<const char*>(&breadth), sizeof(breadth));

    // Write number of elements
    int numElements = elements.size();
    outFile.write(reinterpret_cast<const char*>(&numElements), sizeof(numElements));

    // Write elements
    for (const auto& [position, element] : elements) {
        // Write position
        outFile.write(reinterpret_cast<const char*>(&position), sizeof(position));

        // Write element type
        outFile.write(reinterpret_cast<const char*>(&element.type), sizeof(element.type));

        // Serialize positionable object
        if (element.type != Location::Type::Wall && element.type != Location::Type::Empty && element.type != Location::Type::Door)
            LogWriter::writeLogsToFile("SAVING MAP INFO");
            element.positionable->serialize(outFile);
    }

    outFile.close();

    // saving map information as text in a file
    saveToFile("../src/maps/files/loadedMapsInfo/mapInfo1.txt");

    return true;
}

bool Map::loadMap(const string& filePath) {
    ifstream inFile(filePath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Couldn't open file for reading\n";
        return false;
    }

    // Read width and breadth from file
    inFile.read(reinterpret_cast<char*>(&width), sizeof(width));
    inFile.read(reinterpret_cast<char*>(&breadth), sizeof(breadth));

    // Read number of elements
    int numElements;
    inFile.read(reinterpret_cast<char*>(&numElements), sizeof(numElements));

    // Read elements
    for (int i = 0; i < numElements; ++i) {
        Location::Position position;
        inFile.read(reinterpret_cast<char*>(&position), sizeof(position));

        Element element;
        inFile.read(reinterpret_cast<char*>(&element.type), sizeof(element.type));

        // Depending on the type, create an instance of the corresponding Positionable class
        // and deserialize it
        switch (element.type) {
            case Location::Type::Enemy: {
                auto* enemy = new Creeps();
                enemy->deserialize(inFile);
                element.positionable = dynamic_cast<Enemy*>(enemy);
                break;
            }
            case Location::Type::Null:
            case Location::Type::Empty:
            case Location::Type::Wall:
            case Location::Type::Door: {
                element.positionable = nullptr;
                break;
            }
            case Location::Type::Chest: {
                auto* chest = new ItemContainer();
                chest->deserialize(inFile);
                element.positionable = dynamic_cast<ItemContainer*>(chest);
                break;
            }
            case Location::Type::Friend: {
                auto* friend1 = new Friend();
                friend1->deserialize(inFile);
                element.positionable = dynamic_cast<Friend*>(friend1);
            };

                // Add cases for other Positionable types as needed
            default:
                cerr << "Unknown element type\n";
                break;
        }

        elements[position] = element;
    }

    inFile.close();
    return true;
}

ItemContainer* generateChest()
{
    // creating a chest in the map
    auto* chest = new ItemContainer(4);

    // Randomly generated item names
    std::vector<std::string> helmetNames = {
        "Helm of Celestial Wisdom",
        "Crown of Eternal Frost",
        "Veil of Shadowed Whispers",
        "Helmet of the Astral Guardian",
        "Helm of Radiant Insight"
    };

    std::vector<std::string> armorNames = {
        "Plate of Resilient Valor",
        "Robes of the Arcane Sage",
        "Scalemail of the Dragonheart",
        "Armor of the Celestial Sentinel",
        "Plate of Valor's Endurance"
    };

    std::vector<std::string> beltNames = {
        "Girdle of Endless Stamina",
        "Sash of Elusive Shadows",
        "Waistband of the Earthshaker",
        "Belt of the Eternal Voyager",
        "Girdle of Endless Vigor"
    };

    std::vector<std::string> bootsNames = {
        "Boots of Fleetfooted Grace",
        "Greaves of Thundering Stride",
        "Slippers of the Moonlit Path",
        "Boots of the Celestial Traveler",
        "Boots of Nimble Evasion"
    };

    std::vector<std::string> ringNames = {
        "Ring of Timeless Enigma",
        "Band of Elemental Harmony",
        "Signet of the Astral Voyager",
        "Ring of Eternal Guardianship",
        "Ring of Enigmatic Timelessness"
    };

    std::vector<std::string> weaponNames = {
        "Blade of the Crimson Dawn",
        "Staff of Arcane Echoes",
        "Bow of the Starfall",
        "Sword of the Celestial Champion",
        "Blade of Dawn's Embrace"
    };

    std::vector<std::string> shieldNames = {
        "Aegis of the Guardian",
        "Towering Bulwark",
        "Buckler of the Swift Defender",
        "Shield of the Astral Sentinel",
        "Aegis of Guardian's Resolve"
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    // Randomly select items for the chest
    auto getRandomItem = [&gen](const std::vector<std::string>& names)
        {
            std::uniform_int_distribution<> dist(0, names.size() - 1);
            return names[dist(gen)];
        };

    auto* item1 = new Equipment(getRandomItem(helmetNames), EquipSlot::Helmet);
    auto* item2 = new Equipment(getRandomItem(armorNames), EquipSlot::Armor);
    auto* item3 = new Equipment(getRandomItem(beltNames), EquipSlot::Belt);
    auto* item4 = new Equipment(getRandomItem(bootsNames), EquipSlot::Boots);
    auto* item5 = new Equipment(getRandomItem(ringNames), EquipSlot::Ring);
    auto* item6 = new Equipment(getRandomItem(weaponNames), EquipSlot::Weapon);
    auto* item7 = new Equipment(getRandomItem(shieldNames), EquipSlot::Shield);

    std::vector<Item*> allItems = { item1, item2, item3, item4, item5, item6, item7 };

    // Shuffle the indices
    std::shuffle(allItems.begin(), allItems.end(), gen);

    // Add the first 4 shuffled items to the chest
    for (int i = 0; i < 4; ++i)
    {
        chest->add(*allItems[i]);
    }

    // Delete the items that were not added to the chest
    for (int i = 4; i < 7; ++i)
    {
        delete allItems[i];
    }

    return chest;
}

void Map::createSimpleMap() {

//    this->elements[{0, 1}] = {Location::Type::Enemy, new Enemy("ENEMY", 400)};
//    this->elements[{3, 3}] = {Location::Type::Enemy, new Enemy("ENEMY", 1000)};
//    this->elements[{5, 5}] = {Location::Type::Enemy, new Enemy("ENEMY", 500)};
    this->elements[{Dice::roll(5), Dice::roll(5)}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{Dice::roll(10), 10}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{Dice::roll(7), Dice::roll(7)}] = {Location::Type::Enemy, new Creeps()};

    Map::loadWalls("walls1");

    auto* chest1 = generateChest();

    this->elements[{5, 0}] = {Location::Type::Chest, chest1};

    // creating some friends in the map
    auto* f1 = new Friend(10);
    this->elements[{6, 1}] = {Location::Type::Friend, f1};

    auto* f2 = new Friend(15);
    this->elements[{8, 3}] = {Location::Type::Friend, f2};

    this->elements[{8, 0}] = {Location::Type::Door, nullptr};

}

// TODO: modify this to make a new map.
void Map::createSimpleMap3() {
//    this->elements[{3, 3}] = {Location::Type::Enemy, new Enemy("louay", 400)};
//    this->elements[{7, 7}] = {Location::Type::Enemy, new Enemy("samer", 1000)};
//    this->elements[{9, 9}] = {Location::Type::Enemy, new Enemy("Abood", 500)};
//    this->elements[{12, 12}] = {Location::Type::Enemy, new Enemy("Abood", 500)};
    this->elements[{Dice::roll(5), Dice::roll(5)}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{Dice::roll(10), Dice::roll(10)}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{Dice::roll(10), Dice::roll(10)}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{Dice::roll(12), Dice::roll(12)}] = {Location::Type::Enemy, new Creeps()};

    Map::loadWalls("walls2");

    // creating a chest in the map
    auto* chest1 = new ItemContainer(4);

    auto* item1 = new Equipment("helmet", EquipSlot::Helmet);
    auto* item2 = new Equipment("belt", EquipSlot::Belt);
    auto* item3 = new Equipment("ring", EquipSlot::Ring);

    chest1->add(*item1);
    chest1->add(*item2);
    chest1->add(*item3);

    this->elements[{5, 2}] = {Location::Type::Chest, chest1};

    // creating some friends in the map
    auto* f1 = new Friend(10);
    this->elements[{8, 3}] = {Location::Type::Friend, f1};

    auto* f2 = new Friend(15);
    this->elements[{16, 3}] = {Location::Type::Friend, f2};

    this->elements[{8, 12}] = {Location::Type::Door, nullptr};
}

void Map::createSimpleMap2() {
//    this->elements[{3, 3}] = {Location::Type::Enemy, new Enemy("CREEP", 400)};
//    this->elements[{7, 7}] = {Location::Type::Enemy, new Enemy("CREEP", 1000)};
//    this->elements[{9, 9}] = {Location::Type::Enemy, new Enemy("CREEP", 500)};
//    this->elements[{12, 12}] = {Location::Type::Enemy, new Enemy("TITAN", 500)};
    this->elements[{3, 3}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{7, 7}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{9, 9}] = {Location::Type::Enemy, new Creeps()};
    this->elements[{12, 12}] = {Location::Type::Enemy, new Creeps()};

    Map::loadWalls("walls2");

    // creating a chest in the map
    auto* chest1 = generateChest();

    this->elements[{5, 2}] = {Location::Type::Chest, chest1};

    // creating some friends in the map
    auto* f1 = new Friend(10);
    this->elements[{8, 3}] = {Location::Type::Friend, f1};

    auto* f2 = new Friend(15);
    this->elements[{16, 3}] = {Location::Type::Friend, f2};

    this->elements[{8, 12}] = {Location::Type::Door, nullptr};
}

void Map::displayMap() {
    for (auto& element : this->elements)
    {
        if (element.second.type == Location::Type::Enemy) {
            cout << "Enemy: (" << element.first.x << ", " << element.first.y << "): " << dynamic_cast<Enemy*>(element.second.positionable)->getName() << endl;
        } else if (element.second.type == Location::Type::Wall) {
            cout << "Wall: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Wall) {
            cout << "Chest: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Friend) {
            cout << "Friend: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Door) {
            cout << "Door: (" << element.first.x << ", " << element.first.y << ")" << endl;
        }
    }
}




bool Map::saveToFile(const string& filePath) {
    ofstream outFile(filePath, ios::binary);
    if (!outFile.is_open()) {
        cerr << "Error: Couldn't open file for writing\n";
        return false;
    }

    for (auto& element : this->elements)
    {
        if (element.second.type == Location::Type::Enemy) {
            outFile << "Enemy: (" << element.first.x << ", " << element.first.y << "): " << dynamic_cast<Enemy*>(element.second.positionable)->getName() << endl;
        } else if (element.second.type == Location::Type::Wall) {
            outFile << "Wall: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Wall) {
            outFile << "Chest: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Friend) {
            outFile << "Friend: (" << element.first.x << ", " << element.first.y << ")" << endl;
        } else if (element.second.type == Location::Type::Door) {
            outFile << "Door: (" << element.first.x << ", " << element.first.y << ")" << endl;
        }
    }
    outFile.close();

    return true;
}


// This method reads walls from files located inside "loadedWalls" folder and uses the passed file name
// to fill the backend map with walls.
bool Map::loadWalls(const string &filePath) {

    std::ifstream file("../src/maps/files/loadedWalls/" + filePath);
    if (file.is_open()) {
        std::string line;
        int lineCounter = 0;

        while (std::getline(file, line)) {
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == '|' ) {
                    elements[{lineCounter, i}].type = Location::Type::Wall;
                    elements[{lineCounter, i}].positionable = nullptr;
                }
            }
            lineCounter++;
        }
    } else {
        cout << "Could not open file" << endl;
    }
    return false;
}

// returns true if it succeeds in loading the maps;
bool Map::loadMapSelector(const string &filePath) {
    ifstream inFile(filePath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Couldn't open file for writing\n";
        return false;
    }
    std::vector<std::string> maps;

    std::string mapName;
    while (std::getline(inFile, mapName)) {
        // triming leading and trailing whitespaces from a string
        mapName.erase(0, mapName.find_first_not_of(" \t\n\r\f\v"));
        mapName.erase(mapName.find_last_not_of(" \t\n\r\f\v") + 1);
        maps.push_back(mapName);
    }
    inFile.close();
    string selectedMap = GameView::chooseMap(maps);
    if (selectedMap == "create new map") createSimpleMap2(); // create simple map option is selected
    else loadMap("../src/maps/files/loadedMaps/" + selectedMap); // loading a map option is selected
    return true;
}

bool Map::saveMapSelector(const string &filePath) {
    ifstream inFile(filePath, ios::binary);
    if (!inFile.is_open()) {
        cerr << "Error: Couldn't open file for reading\n";
        return false;
    }

    bool nameExists = false; // to check if the "mapFilesNames.txt" file contains the inputed name or not
    string fileName;
    cout << "where do you want to save the current map? enter only file name. Ex. \"map1.txt\" without quotes" << endl;
    cin >> fileName;

    std::string mapName;
    while (std::getline(inFile, mapName)) {
        // triming leading and trailing whitespaces from a string
        mapName.erase(0, mapName.find_first_not_of(" \t\n\r\f\v"));
        mapName.erase(mapName.find_last_not_of(" \t\n\r\f\v") + 1);

        if (mapName == fileName) {
            nameExists = true;
            break;
        }
    }
    // override the value of the file
    saveMap("../src/maps/files/loadedMaps/" + fileName);
    if (!nameExists) {
        ofstream outFile(filePath, ios::app);
        if (!outFile.is_open()) {
            cerr << "Error: Couldn't open file for writing\n";
            return false;
        }
        // append to the file of loadable maps
        outFile << fileName << endl;
    }

    cout << "Successfully saved. See you in a bit" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 2 seconds
    return true;
}

int Map::getNumberOfEnemies() const
{
    int enemy_counter = 0;

    for (auto i = elements.begin(); i != elements.end(); ++i)
    {
        if (i->second.type == Location::Enemy)
        {
            enemy_counter++;
        }
    }

    return enemy_counter;
}


