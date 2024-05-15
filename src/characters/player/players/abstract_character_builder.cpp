//
// Created by Admin on 4/3/2024.
//

#include "abstract_character_builder.h"

Player *abstract_character_builder::getPlayer() {
    return p;
}

void abstract_character_builder::createNewPlayer() {
    p = new Player();
}
//int abstract_character_builder::rollAbilityScore(const std::string& rollNotation, int bias){
//    // Initialize an array to hold the dice rolls
//    std::array<int, 4> rolls{};
//
//    // Roll a six-sided die four times
//    for (int& roll : rolls) roll = Dice::roll(rollNotation);
//
//    // Sort the rolls in descending order
//    std::sort(rolls.begin(), rolls.end(), [](int a, int b) {
//        return a > b;
//    });
//
//    rolls[3] = 0;// Discard the lowest roll
//
//    // Sum the remaining rolls
//    int sum = 0;
//    for (int roll : rolls)
//        sum += roll;
//
//    // Return the sum of the rolls
//    return sum + bias;
//}

//int abstract_character_builder::rollFighterAbilityScore(const std::string& rollNotation,int level, int bias){
//
//    if(level > 5){
//
//    }
//    // Initialize an array to hold the dice rolls
//    std::array<int, 4> rolls{};
//
//    // Roll a six-sided die four times
//    for (int& roll : rolls) roll = Dice::roll(rollNotation);
//
//    // Sort the rolls in descending order
//    std::sort(rolls.begin(), rolls.end(), [](int a, int b) {
//        return a > b;
//    });
//
//    rolls[3] = 0;// Discard the lowest roll
//
//    // Sum the remaining rolls
//    int sum = 0;
//    for (int roll : rolls)
//        sum += roll;
//
//    // Return the sum of the rolls
//    return sum + bias;
//}



//int* abstract_character_builder::abilityRandomGenerator() {
//    int* values = new int[6];
//    for (int i = 0; i < 6; i++) {
//        values[i] = rollAbilityScore("4d6", 0);
//    }
//
//    // Sort the array
//    std::sort(values, values + 6);
//
//    return values;
//}
//void move();