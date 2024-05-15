#include "friend.h"

Friend::Friend() : heal_amount(30), hasHealed(false)
{
}


Friend::Friend(hptype heal_amount) : heal_amount(heal_amount), hasHealed(false)
{
}

hptype Friend::getHealAmount() const
{
    return heal_amount;
}

bool Friend::getHasHealed() const
{
    return hasHealed;
}

void Friend::setHasHealed(bool hasHealed)
{
    this->hasHealed = hasHealed;
}

void Friend::setHealAmount(hptype amount)
{
    heal_amount = amount;
}

// Serialize method
void Friend::serialize(std::ofstream& outFile) const {
    // Serialize heal_amount
    outFile.write(reinterpret_cast<const char*>(&heal_amount), sizeof(heal_amount));

    // Serialize hasHealed
    outFile.write(reinterpret_cast<const char*>(&hasHealed), sizeof(hasHealed));
}

// Deserialize method
void Friend::deserialize(std::ifstream& inFile) {
    // Deserialize heal_amount
    inFile.read(reinterpret_cast<char*>(&heal_amount), sizeof(heal_amount));

    // Deserialize hasHealed
    inFile.read(reinterpret_cast<char*>(&hasHealed), sizeof(hasHealed));
}
