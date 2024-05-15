
#ifndef D20_PLAYER_H
#define D20_PLAYER_H

#include "characters/character/character.h"
#include <utility>

class Player: public Character {

public:
    Player();

    Player(std::string name, int initialHP);


    void serialize(std::ofstream& outFile) const override;
    void deserialize(std::ifstream& inFile) override;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);



private:
    Location::Position location;
    //Equipments equipments;

};


#endif //D20_PLAYER_H
