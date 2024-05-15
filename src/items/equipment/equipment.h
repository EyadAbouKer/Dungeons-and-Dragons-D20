#pragma once
#include "items/item/item.h"
#include "stats/abilityscores/abilityscores.h"

enum class EquipSlot
{
	Helmet,
	Armor,
	Belt,
	Boots,
	Ring,
	Weapon,
	Shield,
	EQUIP_SLOT_COUNT,
	None
};

std::string EquipSlotToString(EquipSlot slot);

class Equipment : public Item
{
public:
    Equipment();
	Equipment(const std::string& name, EquipSlot slot_type);

	scoretype get_strength() const;
	scoretype get_dexterity() const;
	scoretype get_constitution() const;
	scoretype get_intelligence() const;
	scoretype get_wisdom() const;
	scoretype get_charisma() const;

	EquipSlot get_slot() const;

	virtual void set_strength(scoretype value);
	virtual void set_dexterity(scoretype value);
	virtual void set_constitution(scoretype value);
	virtual void set_intelligence(scoretype value);
	virtual void set_wisdom(scoretype value);
	virtual void set_charisma(scoretype value);

    void serialize(std::ofstream& outFile) const override;
    void deserialize(std::ifstream& inFile) override;
private:
	AbilityScores ability_scores;
	EquipSlot slot_type;

	int adjust_score(int score);

protected:
};