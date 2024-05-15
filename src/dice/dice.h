#pragma once
#include <string>
#include <random>
//#include <regex>//generating error
#include <stdexcept>
#include <iostream>

/**
 * @brief A class that represents a dice roller.
 *
 * This class can roll dice using a standard notation of the form xdy[+z],
 * where x is the number of dice, y is the type of dice (4, 6, 8, 10, 12, 20, or 100),
 * and z is an optional modifier to add to the total.
 *
 * For example, 3d6+2 means roll three six-sided dice and add two to the sum.
 */
class Dice
{
public:
    /**
     * @brief Roll dice using the given notation and return the result.
     *
     * @param notation The dice notation to use.
     * @return int The total of the dice roll.
     * @throw std::invalid_argument If the dice notation is invalid.
     */
//    static int roll(const std::string& notation);

    static int roll(int i = 4);
};

