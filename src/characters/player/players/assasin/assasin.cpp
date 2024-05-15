//
// Created by Admin on 4/4/2024.
//

#include "assasin.h"

void Assasin::buildCharacterName(std::string name) {
    p->setName(name);
}

void Assasin::buildAllAttributes() {
    p->ability_scores.set_wisdom(0);
    p->ability_scores.set_constitution(0);
    p->ability_scores.set_charisma(10);
    p->ability_scores.set_strength(5 + Dice::roll());
    p->ability_scores.set_dexterity(8 + Dice::roll());
    p->ability_scores.set_intelligence(9 + Dice::roll());
    p->setHp(90);
    p->setAttackPower(50);
    Equipment item2("Item1", EquipSlot::Ring);
    Equipment item1("Item2", EquipSlot::Helmet);
    p->add_to_inventory(item1);
    p->add_to_inventory(item2);
}


