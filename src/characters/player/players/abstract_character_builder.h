//
// Created by Admin on 4/3/2024.
//

#ifndef D20_ABSTRACT_CHARACTER_BUILDER_H
#define D20_ABSTRACT_CHARACTER_BUILDER_H
#include "characters/player/player.h"
#include <array>
#include "dice/dice.h"
class abstract_character_builder {
protected:
    Player* p;
    /**
 * getFighter()  return the fighter to be used in the build logic
 * */
public:
    Player* getPlayer();


/**
 * createCharacter() creates a character
 * */
    void createNewPlayer();

    virtual void buildCharacterName(std::string name)=0;
    virtual void buildAllAttributes()=0;
//HP hp;
//AbilityScores ability_scores;
//int attack_power;


//    static int rollAbilityScore(const std::string& rollNotation, int biass);
    static int rollFighterAbilityScore(const std::string &rollNotation,int level=1, int biass=0);
//    static int* abilityRandomGenerator();

};
//





#endif //D20_ABSTRACT_CHARACTER_BUILDER_H
