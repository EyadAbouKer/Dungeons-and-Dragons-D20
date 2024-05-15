
#include "player.h"




Player::Player() : Character(), location({0, 0})  {}

Player::Player(std::string name, int initialHP) : Character(std::move(name), initialHP), location({0, 0}) {}

void Player::serialize(ofstream &outFile) const {
    Character::serialize(outFile);
}

void Player::deserialize(ifstream &inFile) {
    Character::deserialize(inFile);
}

int Player::getX() const {
    return location.x;
}

void Player::setX(int x) {
    location.x = x;
}

int Player::getY() const {
    return location.y;
}

void Player::setY(int y) {
    location.y = y;

}



