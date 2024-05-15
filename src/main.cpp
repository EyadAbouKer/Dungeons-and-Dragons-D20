
#ifndef MAIN_CPP_INCLUDED
#define MAIN_CPP_INCLUDED

#include <iostream>
#include <cmath>
#include <conio.h>
#include "maps/map/map.h"
#include "characters/player/player.h"
#include "renderEngine/gameView/gameView.h"
#include "controllers/gameController/gameController.h"
#include "characters/player/players/abstract_character_builder.h"
#include "characters/player/players/bloodSeeker/bloodSeeker.h"
#include "characters/player/playerBuilder/builtPlayer.h"
#include "arena/combatarena/combatarena.h"
#include "arena/friendarena/friendarena.h"
#include "donut.cpp"
#include "characters/player/players/axe/axe.h"
#include "characters/player/players/assasin/assasin.h"
#include "characters/player/players/spiritBreaker/spiritBreaker.h"
#include "maps/campaign/campaign.h"
//#include <SFML/Audio.hpp>
#include "logs/logWriter.h"

using namespace std;
void equipment_test();
bool runGameWithMap(Map* map, Player* player, bool* qKeyHit = new bool(false));
void runGameWithCampaign(Campaign* campaign, Player* player);
void printGrid(const vector<vector<char>>& grid);
void attack_test();
Player choosePlayer();

int main() {

    Donut::donut();
    // speed up cout
//    std::ios_base::sync_with_stdio(false);
    auto p = choosePlayer();//keep it just for the GUI for now
    LogWriter::writeLogsToFile(p);

//    auto p1 = choosePlayer();
    auto* p1 = new Player{"PLAYER", 1000};
    p1->setAttackPower(40);


    auto* campaign = new Campaign();
    bool successfullyLoaded = campaign->loadCampaignSelector("../src/maps/files/loadedCampaigns/campaignFilesNames.txt");
    if (successfullyLoaded){
        runGameWithCampaign(campaign, p1);
        LogWriter::writeLogsToFile("Campaign successfully loaded");
    }
    else cout << "Sorry, something went wrong"<< endl;


//    Map* map = new Map(20, 20);
//    bool successfullyLoaded = map->loadMapSelector("../src/maps/files/loadedMaps/mapFilesNames.txt");
//    if (successfullyLoaded) runGameWithMap(map, p1);
//    else cout << "Sorry, something went wrong"<< endl;
//
//    map->saveMapSelector("../src/maps/files/loadedMaps/mapFilesNames.txt");


    delete p1;

    return 0;
}

void equipment_test()
{
    auto* p1 = new Player{"james", 500};
    auto* chest = new ItemContainer(5);
    auto* item1 = new Equipment("Item1", EquipSlot::Helmet);
    auto* item2 = new Equipment("Item2", EquipSlot::Helmet);
    auto* item3 = new Equipment("Item3", EquipSlot::Belt);
    auto* item4 = new Equipment("Item4", EquipSlot::Ring);

    p1->add_to_inventory(*item1);
    p1->add_to_inventory(*item2);

    chest->add(*item3);
    chest->add(*item4);

    p1->take_loot(*chest);
    p1->open_inventory();

    delete chest;
    delete p1;
}

void attack_test()
{
    auto* p1 = new Player{"mark", 500};
    auto* e1 = new Enemy{"zombie", 300};

    p1->setAttackPower(20);

    CombatArena arena{*p1, *e1};
    arena.begin();

    delete p1;
    delete e1;
}



//void testBuilderPattern(){
//
//    //This is how you must create special players from now on
//    Player *bloodSeeker = BuiltPlayer::constructPlayer(new BloodSeeker,"bllody");
//    delete bloodSeeker;
//}


// Function to run the game
bool runGameWithMap(Map* map, Player* player, bool* qKeyHit) {

    char input;
    do {
        system("CLS"); // Use "cls" on Windows
        GameView::renderMap(map, player);


        cout << "Use 'w' (up), 's' (down), 'a' (left), 'd' (right) to move the character.\n";
        cout << "Use 'i' to open inventory.\n";
        cout << "Press 'q' to quit.\n";
        input = _getch();

        // Determine the next position
        int nextX = player->getX(), nextY = player->getY();
        switch (input) {
            case 'a': // Move up, wrap to bottom if at top
                nextY = (player->getY() == 0) ? map->getBreadth() - 1 : player->getY() - 1;
                break;
            case 'd': // Move down, wrap to top if at bottom
                nextY = (player->getY() == map->getBreadth() - 1) ? 0 : player->getY() + 1;
                break;
            case 'w': // Move left, wrap to right if at left edge
                nextX = (player->getX() == 0) ? map->getWidth() - 1 : player->getX() - 1;
                break;
            case 's': // Move right, wrap to left if at right edge
                nextX = (player->getX() == map->getWidth() - 1) ? 0 : player->getX() + 1;
                break;
            case 'i':
                player->open_inventory();
                break;
            default:
                continue; // Skip the rest of the loop if the input is not a direction
        }

        // update player position to the new location
        int oldX=player->getX();
        int oldY = player->getY();
        player->setX(nextX);
        player->setY(nextY);
        // if there is an enemy, then remove it.(remove not fight for now)
        if (map->elements.count({player->getX(), player->getY()})) { // key exists
            if (map->elements[{player->getX(), player->getY()}].type == Location::Type::Enemy) {
                // the following is a logic that allows us to really fight the enemies
                CombatArena arena(*player, *dynamic_cast<Enemy*>(map->elements[{player->getX(), player->getY()}].positionable));
                int result = arena.begin();
                if (result == 1) { // player won
                    map->elements[{player->getX(), player->getY()}].type = Location::Type::Empty;
                    map->elements[{player->getX(), player->getY()}].positionable = nullptr;
                    map->elements.erase({player->getX(), player->getY()});
                } else if (result == -1) { // if player dies

                }

            } else if (map->elements[{player->getX(), player->getY()}].type == Location::Type::Chest) {
                auto* chest = dynamic_cast<ItemContainer*>(map->elements[{player->getX(), player->getY()}].positionable);
                chest->display();

                player->take_loot(*chest);

            } else if (map->elements[{player->getX(), player->getY()}].type == Location::Type::Friend) {
                auto* f1 = dynamic_cast<Friend*>(map->elements[{player->getX(), player->getY()}].positionable);
                FriendArena friendArena(*player, *f1);
                friendArena.begin();

            } else if (map->elements[{player->getX(), player->getY()}].type == Location::Type::Door) {

                return true; // meaning we leave this map

            } else if (map->elements[{player->getX(), player->getY()}].type == Location::Type::Wall) {
                // if there is a wall, undo the command to move
                player->setX(oldX);
                player->setY(oldY);
            }
        }
    } while (input != 'q'); // Quit the game if the user enters 'q'
    *qKeyHit = true;
    return false;
}


void runGameWithCampaign(Campaign* campaign, Player* player) {
    bool* qKeyHit = new bool(false); // a bool pointer variable to check if q key was clicked inside runGameWithMap() method
    do {
        bool doorAccessed = runGameWithMap(campaign->getCurrentMap(), player, qKeyHit);
        if (doorAccessed) campaign->enterDoor();
    } while (!*qKeyHit);
}









atomic<bool> inputReceived(false);

// Function to listen for user input
void waitForInput() {
    cout << "Press any key to exit..." << endl;
    _getch(); // Wait for a key press
    inputReceived.store(true); // Signal that input has been received
}



#endif // MAIN_CPP_INCLUDED


//Donut::donut();
//equipment_test();
/*
Player hh;
hh.ability_scores.set_strength(7);
hh.ability_scores.set_constitution(4);
hh.ability_scores.set_charisma(9);
hh.ability_scores.set_wisdom(2);
hh.setAttackPower(33);

//    PlaySound(TEXT("..\\src\\sounds\\deathSound.wav"), NULL, SND_FILENAME);
//    PlaySound(TEXT("..\\src\\sounds\\deathSound.wav"), NULL, SND_FILENAME);


//    Enemy e;
//    cout<<e;
//    Sleep(10000);
/**reference to how you should create a player:*/
//    Player* p = BuiltPlayer::constructPlayer(new BloodSeeker,"player name");
//    cout<<*p;



 Player choosePlayer(){
std::cout
        <<"+---------------------------------------------------------------------------------------------------------------------+\n"
        <<"|                                              WELCOME TO THE ARENA                                                 |\n"
        <<"+---------------------------------------------------------------------------------------------------------------------+\n"
        <<"|                                              CHOOSE YOUR CHARACTER___                                                 |\n"
        <<"|                                              1. AXE                                                 \n"
        <<"|                                              2. ASSASIN                                                 \n"
        <<"|                                              3. BLOOD SEEKER                                                 \n"
        <<"|                                              4. SPIRIT BREAKER                                                 \n"
        <<"+---------------------------------------------------------------------------------------------------------------------+\n";
     int choice;
     Player* p;

     cin>>choice;
     switch (choice) {
         case 1:
             p = BuiltPlayer::constructPlayer(new Axe,"AXE");
             break;
         case 2:
             p = BuiltPlayer::constructPlayer(new Assasin,"ASSASIN");
             break;
         case 3:
             p = BuiltPlayer::constructPlayer(new BloodSeeker,"BLOOD SEEKER");
             break;
         case 4:
             p = BuiltPlayer::constructPlayer(new SpiritBreaker,"SPIRIT BREAKER");
             break;

     }
     cout<<*p;
     cout<<"\n\nhit any key to proceed: ";
     cin>>choice;
     return *p;
 }



