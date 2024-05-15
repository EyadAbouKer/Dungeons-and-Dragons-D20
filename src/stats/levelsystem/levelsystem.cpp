
#include "levelsystem.h"

LevelSystem::LevelSystem(const int maxLvl) : currentLevel(1), maxLevel(maxLvl), currentXP(0), xpThreshold(300) {
}

void LevelSystem::gainXP(const unsigned amount) {
    // Add the gained XP to the current total
    currentXP += amount;

    // Check if the XP threshold for leveling up is reached
    while (currentXP >= xpThreshold && currentLevel < maxLevel) {
        // Level up
        currentLevel++;
        currentXP -= xpThreshold; // Deduct the threshold XP

        // Increase the threshold for the next level
        xpThreshold = static_cast<unsigned>(static_cast<float>(xpThreshold) * xpMultiplier);
    }
}

int LevelSystem::getCurrentLevel() const {
    return currentLevel;
}

int LevelSystem::getMaxLevel() const {
    return maxLevel;
}

void LevelSystem::serialize(std::ofstream& outFile) const {
    // Serialize current level, max level, current XP, and XP threshold to the file
    outFile.write(reinterpret_cast<const char*>(&currentLevel), sizeof(currentLevel));
    outFile.write(reinterpret_cast<const char*>(&maxLevel), sizeof(maxLevel));
    outFile.write(reinterpret_cast<const char*>(&currentXP), sizeof(currentXP));
    outFile.write(reinterpret_cast<const char*>(&xpThreshold), sizeof(xpThreshold));
}

void LevelSystem::deserialize(std::ifstream& inFile) {
    // Deserialize current level, max level, current XP, and XP threshold from the file
    inFile.read(reinterpret_cast<char*>(&currentLevel), sizeof(currentLevel));
    inFile.read(reinterpret_cast<char*>(&maxLevel), sizeof(maxLevel));
    inFile.read(reinterpret_cast<char*>(&currentXP), sizeof(currentXP));
    inFile.read(reinterpret_cast<char*>(&xpThreshold), sizeof(xpThreshold));
}
