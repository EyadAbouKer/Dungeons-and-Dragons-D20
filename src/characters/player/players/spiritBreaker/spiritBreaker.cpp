//
// Created by Admin on 4/4/2024.
//

#include "spiritBreaker.h"

void SpiritBreaker::buildCharacterName(std::string name) {
    p->setName(name);
}

void SpiritBreaker::buildAllAttributes() {
    p->ability_scores.set_wisdom(0);
    p->ability_scores.set_constitution(0);
    p->ability_scores.set_charisma(5);
    p->ability_scores.set_strength(10 + Dice::roll());
    p->ability_scores.set_dexterity(3 + Dice::roll());
    p->ability_scores.set_intelligence(4 + Dice::roll());
    p->setHp(50);
    p->setAttackPower(85);
    Equipment item1("Item1", EquipSlot::None);
    p->add_to_inventory(item1);
}
