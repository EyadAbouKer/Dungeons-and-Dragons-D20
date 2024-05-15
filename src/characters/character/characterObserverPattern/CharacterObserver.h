//
// Created by Admin on 3/30/2024.
//

#ifndef D20_CHARACTEROBSERVER_H
#define D20_CHARACTEROBSERVER_H


#include <string>
#include "stats/hp/hp.h"
#include "stats/levelsystem/levelsystem.h"

class CharacterObserver {
public:
    virtual void update(std::string name, LevelSystem level , HP hp, int attack_power)=0;
};


#endif //D20_CHARACTEROBSERVER_H
