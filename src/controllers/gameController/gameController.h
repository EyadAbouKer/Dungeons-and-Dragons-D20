
#ifndef D20_GAMECONTROLLER_H
#define D20_GAMECONTROLLER_H


#include "maps/positionable.h"
#include "characters/player/player.h"
#include "renderEngine/gameView/gameView.h"
#include "maps/map/map.h"

class GameController {

public:
    GameController();
    GameController(Player* player, Map* map);

    /**
     * This method checks what the player has around him (UP, DOWN, RIGHT, LEFT)
     * It updates the variables (upMove, downMove, etc.) accordingly
     */
    void updateSurrounding();

    Player* getPlayer() const;

    void setPlayer(Player* player);

    Map* getMap() const;

    void setMap(Map* map);

private:
    Player* player;
    Map* map;

};


#endif //D20_GAMECONTROLLER_H
