
#include "enemy.h"

void Enemy::serialize(ofstream &outFile) const {
    Character::serialize(outFile);
}

void Enemy::deserialize(ifstream &inFile) {
    Character::deserialize(inFile);
}

Enemy::Enemy() : Character() {}

Enemy::Enemy(std::string name, int initialHP) : Character(name, initialHP){}

//void Enemy::attack() {
//
//    if(){
//
//    }else{
//
//    }
//
//
////
////    int roll = Dice::roll(20);
////    std::cout << name << " rolled " << roll << ".\n";
////    hptype damage = this->attack_power + roll;
////    other.takeDamage(damage);
////    std::cout << name << " hit " << other.name << " for " << damage << ".\n";
////    PlaySound(TEXT("..\\src\\sounds\\PlayerAttacking.wav"), NULL, SND_FILENAME);
//
//
//}

//std::string progressBar(int a)
//{
//    int x = 177, y = 219;
//    if (a <= 10)
//    {
//        a = a * 10;
//    }
//    std::string bar;
//    for (int i = 0; i < 100; i++)
//    {
//        if (i >= a)
//        {
//            break;
//        }
//        else
//        {
//            //            std::cout<<(char)y;
//            bar += (char)y;
//        }
//    }
//    for (int j = 0; j < 100; j++)
//    {
//        if (j >= a)
//        {
//            //            std::cout<<(char)x;
//            bar += (char)x;
//        }
//    }
//    return bar;
//}
//
//ostream& operator<<(ostream& os, const AbilityScores& ability_scores)
//{
//    using std::setw;
//
//    int width = 150; // Adjust as needed
//    os << "+---------------------------------------------------------------------------------------------------------------------+\n"
//       << "|                                                             Abilities                                               |\n"
//       << "+---------------------------------------------------------------------------------------------------------------------+\n"
//       << "| Strength    |" << progressBar(ability_scores.get_strength()) << " " << ability_scores.get_strength() << "\n"
//       << "| Dexterity   |" << progressBar(ability_scores.get_dexterity()) << " " << ability_scores.get_dexterity() << " \n"
//       << "| Constitution|" << progressBar(ability_scores.get_constitution()) << " " << ability_scores.get_constitution() << "\n"
//       << "| Intelligence|" << progressBar(ability_scores.get_intelligence()) << " " << ability_scores.get_intelligence() << "\n"
//       << "| Wisdom      |" << progressBar(ability_scores.get_wisdom()) << " " << ability_scores.get_wisdom() << "\n"
//       << "| Charisma    |" << progressBar(ability_scores.get_charisma()) << " " << ability_scores.get_charisma() << "\n"
//       << "+---------------------------------------------------------------------------------------------------------------------+\n";
//    return os;
//}
//// Operator overloading for Character
//ostream& operator<<(ostream& os, const Character& character)
//{
//    os
//            << "+---------------------------------------------------------------------------------------------------------------------+\n"
//            << "|                                                            Enemy View                                               |\n"
//            << "+---------------------------------------------------------------------------------------------------------------------+\n"
//            << "|                                                            Name: " << character.name << "\n"
//            << "|                                                            position(X,Y): (" << ",  " << ")\n"
//            << "| HP          |" << progressBar(character.hp.getCurrentHP()) << " " << character.hp.getCurrentHP() << "\n"
//            << "| Attack      |" << progressBar(character.attack_power) << " " << character.attack_power << "\n"
//            << character.ability_scores;
//    //       << "" << character.fightingAbilities;
//    return os;
//}
