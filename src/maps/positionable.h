
#ifndef D20_POSITIONABLE_H
#define D20_POSITIONABLE_H

#include <fstream>

namespace Location {
    enum Type {
        Null, // for the cells outside the map
        Enemy,
        Friend,
        Chest,
        Wall,
        Door, // the door will be pointing to the next map object, or to nullptr if it is the last map in the campaign (player won)
        Empty,
        Titan
    };

    struct Position {
        int x;
        int y;

        // Less-than operator
        bool operator<(const Position& other) const {
            if (x != other.x)
                return x < other.x;
            return y < other.y;
        }

        // Assignment operator
        Position& operator=(const Position& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
            }
            return *this;
        }
    };
}



class Positionable {

public:
    // Virtual destructor
    virtual ~Positionable() = default;

    // Pure virtual functions for serialization and deserialization
    virtual void serialize(std::ofstream& outFile) const = 0;
    virtual void deserialize(std::ifstream& inFile) = 0;
private:


};

#endif //D20_POSITIONABLE_H
