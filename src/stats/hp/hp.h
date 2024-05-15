#ifndef HP_H
#define HP_H
#include <fstream>
using namespace std;

// DO NOT TOUCH THIS CLASS ANYMORE
typedef unsigned int hptype;
class HP {
public:
    explicit HP(hptype initialHP);

    void takeDamage(hptype damage);
    void heal(hptype amount);

    hptype getCurrentHP() const;
    hptype getMaxHP() const;

    // Serialize and deserialize functions
    void serialize(std::ofstream& outFile) const;
    void deserialize(std::ifstream& inFile);
    void setInitialHp(hptype h);
private:
    hptype currentHP;
    hptype maxHP;
};

#endif //HP_H