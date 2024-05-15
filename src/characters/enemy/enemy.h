

#ifndef D20_ENEMY_H
#define D20_ENEMY_H

#include "characters/character/character.h"

class Enemy : public Character {

public:

    Enemy();

    Enemy(std::string name, int initialHP);
//    void attack();

    void serialize(std::ofstream& outFile) const override;
    void deserialize(std::ifstream& inFile) override;

private:


};


#endif //D20_ENEMY_H
