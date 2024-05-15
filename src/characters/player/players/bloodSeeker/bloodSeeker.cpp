//
// Created by Admin on 4/4/2024.
//

#include "bloodSeeker.h"


void BloodSeeker::buildCharacterName(std::string name) {
    p->setName(name);
}

void BloodSeeker::buildAllAttributes() {
    p->ability_scores.set_wisdom(0);
    p->ability_scores.set_constitution(0);
    p->ability_scores.set_charisma(8);
    p->ability_scores.set_strength(3 + Dice::roll());
    p->ability_scores.set_dexterity(7 + Dice::roll());
    p->ability_scores.set_intelligence(8 + Dice::roll());
    p->setHp(80);
    p->setAttackPower(60);
    Equipment item2("Item1", EquipSlot::Armor);
    Equipment item1("Item2", EquipSlot::Boots);
    p->add_to_inventory(item1);
    p->add_to_inventory(item2);
}
