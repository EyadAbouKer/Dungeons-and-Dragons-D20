//
// Created by Admin on 4/4/2024.
//

#ifndef D20_SPIRITBREAKER_H
#define D20_SPIRITBREAKER_H



#include "dice/dice.h"
#include "characters/player/players/abstract_character_builder.h"

class SpiritBreaker : public abstract_character_builder{
public:
    void buildCharacterName(std::string name) override;

protected:
    void buildAllAttributes() override;


private:
};


#endif //D20_SPIRITBREAKER_H
