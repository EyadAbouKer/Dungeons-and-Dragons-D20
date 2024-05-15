#include "equipment.h"

Equipment::Equipment(const std::string& name, EquipSlot slot_type) :
	Item(name), slot_type(slot_type)
{
}


Equipment::Equipment() :
        Item("equipment"), slot_type(EquipSlot::Armor)
{
}

scoretype Equipment::get_strength() const
{
	return ability_scores.get_strength();
}

scoretype Equipment::get_dexterity() const
{
	return ability_scores.get_dexterity();
}

scoretype Equipment::get_constitution() const
{
	return ability_scores.get_constitution();
}

scoretype Equipment::get_intelligence() const
{
	return ability_scores.get_intelligence();
}

scoretype Equipment::get_wisdom() const
{
	return ability_scores.get_wisdom();
}

scoretype Equipment::get_charisma() const
{
	return ability_scores.get_charisma();
}

EquipSlot Equipment::get_slot() const
{
	return slot_type;
}

void Equipment::set_strength(scoretype value)
{
	ability_scores.set_strength(adjust_score(value));
}

void Equipment::set_dexterity(scoretype value)
{
	ability_scores.set_dexterity(adjust_score(value));
}

void Equipment::set_constitution(scoretype value)
{
	ability_scores.set_constitution(adjust_score(value));
}

void Equipment::set_intelligence(scoretype value)
{
	ability_scores.set_intelligence(adjust_score(value));
}

void Equipment::set_wisdom(scoretype value)
{
	ability_scores.set_wisdom(adjust_score(value));
}

void Equipment::set_charisma(scoretype value)
{
	ability_scores.set_charisma(adjust_score(value));
}

int Equipment::adjust_score(int score)
{
	if (score > 5)
	{
		return 5;
	}

	return score;
}

std::string EquipSlotToString(EquipSlot slot)
{
	switch (slot)
	{
	case EquipSlot::Helmet: return "Helmet";
	case EquipSlot::Armor: return "Armor";
	case EquipSlot::Belt: return "Belt";
	case EquipSlot::Boots: return "Boots";
	case EquipSlot::Ring: return "Ring";
	case EquipSlot::Weapon: return "Weapon";
	case EquipSlot::Shield: return "Shield";
	case EquipSlot::None: return "None";
	default: return "Unknown";
	}
}

// Serialize method
void Equipment::serialize(std::ofstream& outFile) const {
    // Serialize Item data
    Item::serialize(outFile);

    // Serialize slot_type
    outFile.write(reinterpret_cast<const char*>(&slot_type), sizeof(slot_type));

    // Serialize ability_scores
    outFile.write(reinterpret_cast<const char*>(&ability_scores), sizeof(ability_scores));
}

// Deserialize method
void Equipment::deserialize(std::ifstream& inFile) {
    // Deserialize Item data
    Item::deserialize(inFile);

    // Deserialize slot_type
    inFile.read(reinterpret_cast<char*>(&slot_type), sizeof(slot_type));

    // Deserialize ability_scores
    inFile.read(reinterpret_cast<char*>(&ability_scores), sizeof(ability_scores));
}

