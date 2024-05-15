#pragma once
#include "stats/hp/hp.h"
#include "maps/positionable.h"

class Character;

class Friend : public Positionable
{
public:
    Friend();
    Friend(hptype heal_amount);

    hptype getHealAmount() const;

    bool getHasHealed() const;
    void setHasHealed(bool hasHealed);

    void setHealAmount(hptype amount);

    void serialize(std::ofstream& outFile) const override;
    void deserialize(std::ifstream& inFile) override;
private:
    hptype heal_amount;
    bool hasHealed;
};