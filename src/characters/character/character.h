#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <Windows.h>
#include "itemcontainer.h"
#include <string>
#include <fstream>
#include "stats/hp/hp.h"
#include "stats/levelsystem/levelsystem.h"
#include "maps/positionable.h"
#include <algorithm>
#include "characters/character/characterObserverPattern/CharacterObserver.h"
#include <stats/abilityscores/abilityscores.h>
#include "items/equipment/equipment.h"
#include <map>
#include <vector>
#include <utility>
#include <list>
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include "asciitable.h"
#include "friend.h"
using namespace std;


class Character : public Positionable, public CharacterObserver {
public:
    Character();
    Character(std::string name, int initialHP);
    ~Character();
    friend ostream &operator<<(ostream &os, const Character &character);
    void gainXP(unsigned amount);

    leveltype getCurrentLevel() const;
    leveltype getMaxLevel() const;

    void setName(const string &n);
    void setHp(int h);
    void setAttackPower(int a);

    hptype getCurrentHP() const;
    hptype getMaxHP() const;
    void display_hp() const;

    void takeDamage(hptype damage);
    void heal(hptype amount);

    const string& getName() const;
    void serialize(std::ofstream& outFile) const override;
    void deserialize(std::ifstream& inFile) override;

    // Ability scores
    scoretype get_effective_strength() const;
    scoretype get_effective_dexterity() const;
    scoretype get_effective_constitution() const;
    scoretype get_effective_intelligence() const;
    scoretype get_effective_wisdom() const;
    scoretype get_effective_charisma() const;

    // Inventory
    void open_inventory();
    void take_loot(ItemContainer& chest);
    void take_loot(Character& character);
    void add_to_inventory(Item& item);
    void remove_from_inventory(int index);
    void equip_from_inventory();
    void unequip_to_inventory();

    void attack(Character& other);

    void show_equipped_items();
//    ************************************************* OBSERVER PATTERN **************************************************************************
    void addObserver(CharacterObserver *o);
    void removeObserver(CharacterObserver *o);

    void notify();


    void update(string name, LevelSystem level, HP hp, int attack_power) override;
    AbilityScores ability_scores;

    const ItemContainer &getInventory() const;

    void setInventory(const ItemContainer &inventory);

protected:
    std::string name;
    LevelSystem level;
    HP hp;
    std::map<EquipSlot, Equipment*> equipped_items;
    ItemContainer inventory;

    int attack_power;
};



#endif //CHARACTER_H
