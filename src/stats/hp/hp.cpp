#include "hp.h"

HP::HP(const hptype initialHP) :  currentHP(initialHP), maxHP(initialHP) {
}

void HP::takeDamage(const hptype damage)
{
    if (damage >= currentHP)
    {
        currentHP = 0;
    }
    else
    {
        currentHP -= damage;
    }
}

void HP::setInitialHp(hptype h){
    currentHP = h;
    maxHP = h;
}

void HP::heal(const hptype amount) {
    currentHP += amount;

    if (currentHP > maxHP) {
        currentHP = maxHP;
    }
}

hptype HP::getCurrentHP() const {
    return currentHP;
}

hptype HP::getMaxHP() const {
    return maxHP;
}

void HP::serialize(std::ofstream& outFile) const {
    // Serialize current and max HP to the file
    outFile.write(reinterpret_cast<const char*>(&currentHP), sizeof(currentHP));
    outFile.write(reinterpret_cast<const char*>(&maxHP), sizeof(maxHP));
}

void HP::deserialize(std::ifstream& inFile) {
    // Deserialize current and max HP from the file
    inFile.read(reinterpret_cast<char*>(&currentHP), sizeof(currentHP));
    inFile.read(reinterpret_cast<char*>(&maxHP), sizeof(maxHP));
}
