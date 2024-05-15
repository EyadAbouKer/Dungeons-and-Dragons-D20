#pragma once
#include "characters/player/player.h"
#include "characters/enemy/enemy.h"
#include <conio.h>
#include "asciitable.h"

class FriendArena
{
public:
    FriendArena(Player& player, Friend& f);
    void begin();
private:
    Player* player;
    Friend* f;
};
