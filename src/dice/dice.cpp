
#include "dice/dice.h"


/**
 * @brief Roll dice using the given notation and return the result.
 *
 * @details Only dice of type d4, d6, d8, d10, d12, d20, d100 are valid.
 * @param notation The dice notation to use (e.g., "3d6+2").
 * @return int The total of the dice roll.
 * @throw std::invalid_argument If the dice notation is invalid.
 */

//int Dice::roll(const std::string& notation)
//{
//    // Define the dice notation pattern
//    std::regex pattern("(\\d+)(?:D|d)(4|6|8|10|12|20|100)(?:\\+(\\d+))?");
//    std::smatch matches;
//
//    // Validate the dice notation
//    if (!std::regex_match(notation, matches, pattern))
//    {
//        throw std::invalid_argument("Invalid dice notation. Please use xdy[+z]. Example: 5d10+2");
//    }
//
//    // Extract the number of rolls and the type of die from the  notation
//    int timesToRoll = std::stoi(matches[1]);
//    int die = std::stoi(matches[2]);
//
//    // Initialize the random number generator
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> distr(1, die);
//
//    // Roll the dice the specified number of times
//    int total = 0;
//    for (int i = 0; i < timesToRoll; ++i)
//    {
//        total += distr(gen);  // Add the result of each roll to the total
//    }
//
//    // Add the optional modifier, if present
//    if (matches[3].matched)
//    {
//        total += std::stoi(matches[3]);
//    }
////    std::cout << "Result of the dice throw: " << total << std::endl;
//
////
//    return total;
//}

// Function to generate a random number between 1 and 4
int Dice::roll(int i)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, i);
    return distr(gen);
}















































//*
//
//#include "dice/dice.h"
//
//
///**
// * @brief Roll dice using the given notation and return the result.
// *
// * @details Only dice of type d4, d6, d8, d10, d12, d20, d100 are valid.
// * @param notation The dice notation to use (e.g., "3d6+2").
// * @return int The total of the dice roll.
// * @throw std::invalid_argument If the dice notation is invalid.
// */
//
//int Dice::roll(const std::string& notation)
//{
//    // Define the dice notation pattern
////    std::regex pattern("(\\d+)(?:D|d)(4|6|8|10|12|20|100)(?:\\+(\\d+))?");
////    std::smatch matches;
////
////    // Validate the dice notation
////    if (!std::regex_match(notation, matches, pattern))
////    {
////        throw std::invalid_argument("Invalid dice notation. Please use xdy[+z]. Example: 5d10+2");
////    }
//
//    // Extract the number of rolls and the type of die from the  notation
////    int timesToRoll = std::stoi(matches[1]);
////    int die = std::stoi(matches[2]);
//    int timesToRoll = 0;
//    int die = 0;
//
//    // Initialize the random number generator
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> distr(1, die);
//
//    // Roll the dice the specified number of times
//    int total = 0;
//    for (int i = 0; i < timesToRoll; ++i)
//    {
//        total += distr(gen);  // Add the result of each roll to the total
//    }
//
//    // Add the optional modifier, if present
////    if (matches[3].matched)
//    {
////        total += std::stoi(matches[3]);
//    }
////    std::cout << "Result of the dice throw: " << total << std::endl;
//
//
//    return total;
//}
//
//
// /