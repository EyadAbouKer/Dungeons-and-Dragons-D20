//
// Created by Admin on 4/4/2024.
//

#ifndef D20_ASSASIN_H
#define D20_ASSASIN_H


#include <string>
//#include "characters/player/playerBuilder/abstract_character_builder.h"
#include "dice/dice.h"
#include "characters/player/players/abstract_character_builder.h"

class Assasin : public abstract_character_builder{

public:
    void buildCharacterName(std::string name) override;

protected:
    void buildAllAttributes() override;


private:

};


#endif //D20_ASSASIN_H
//private:
//int* bias;
//public:
//void buildAbilities() override;
//
//void buildFightingAbilities(int level) override;
//
//
//void buildFightingAbilities();
//};