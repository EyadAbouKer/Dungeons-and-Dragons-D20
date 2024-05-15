#include "gameController.h"


GameController::GameController() :
player(nullptr),
map(nullptr)
{}


GameController::GameController(Player* player, Map* map) :
player(player),
map(map)
{}


Player* GameController::getPlayer() const {
    return this->player;
}

void GameController::setPlayer(Player* player) {
    this->player = player;
}

Map* GameController::getMap() const {
    return this->map;
}

void GameController::setMap(Map* map) {
    this->map = map;
}
