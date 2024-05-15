#pragma once
#include "characters/player/player.h"
#include "characters/enemy/enemy.h"
#include <conio.h>
#include "asciitable.h"
class CombatArena
{
public:
	CombatArena(Player& player, Enemy& enemy);

	int begin();
private:
	Player* player;
	Enemy* enemy;
};