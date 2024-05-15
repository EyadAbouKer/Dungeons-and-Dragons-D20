//
// Created by Admin on 4/4/2024.
//


#include "axe.h"
void Axe::buildCharacterName(std::string name) {
    p->setName(name);
}

void Axe::buildAllAttributes() {
    p->ability_scores.set_wisdom(0);
    p->ability_scores.set_constitution(0);
    p->ability_scores.set_charisma(4);
    p->ability_scores.set_strength(7 + Dice::roll());
    p->ability_scores.set_dexterity(4 + Dice::roll());
    p->ability_scores.set_intelligence(2 + Dice::roll());
    p->setHp(70);
    p->setAttackPower(70);
    Equipment item1("Item1", EquipSlot::Weapon);
    p->add_to_inventory(item1);
}
