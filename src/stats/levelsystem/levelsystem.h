
#ifndef LEVELSYSTEM_H
#define LEVELSYSTEM_H

#include <fstream>
using namespace std;

typedef int leveltype;
class LevelSystem {
public:
    explicit LevelSystem(leveltype maxLvl);

    void gainXP(unsigned amount);

    leveltype getCurrentLevel() const;
    leveltype getMaxLevel() const;

    // Serialize and deserialize functions
    void serialize(std::ofstream& outFile) const;
    void deserialize(std::ifstream& inFile);

private:
    leveltype currentLevel;
    leveltype maxLevel;
    unsigned currentXP;
    unsigned xpThreshold;
    static constexpr float xpMultiplier = 1.5f;
};

#endif //LEVELSYSTEM_H
