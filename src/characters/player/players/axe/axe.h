//
// Created by Admin on 4/4/2024.
//

#ifndef D20_AXE_H
#define D20_AXE_H


//#include "characters/player/playerBuilder/abstract_character_builder.h"
#include "dice/dice.h"
#include "characters/player/players/abstract_character_builder.h"
#include <string>
class Axe : public abstract_character_builder{
public:
    void buildCharacterName(std::string name) override;

protected:
    void buildAllAttributes() override;


private:
};


#endif //D20_AXE_H
