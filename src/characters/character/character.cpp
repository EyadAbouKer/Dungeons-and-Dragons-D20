#include "character.h"
#include "dice/dice.h"
#include "logs/logWriter.h"

Character::Character() : name("temp"), level(20), hp(100), inventory(20), attack_power(20) {}

Character::Character(std::string name, const int initialHP) :
	name(std::move(name)), level(20), hp(initialHP), inventory(20), attack_power(20)
{
    LogWriter::writeLogsToFile("A PLAYER IS BEING CREATED");
	for (int i = 0; i < static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT); ++i)
	{
		equipped_items[static_cast<EquipSlot>(i)] = nullptr;
	}
//    PlaySound(TEXT("SystemDefault"), NULL, SND_ALIAS);
}

Character::~Character()
{   LogWriter::writeLogsToFile("PLAYER IS BEING DELETED");
	for (auto& item : equipped_items)
	{
		delete item.second;
	}
}

void Character::setHp(int h)
{
    LogWriter::writeLogsToFile("SETTING HP TO "+std::to_string(h));
	hp.setInitialHp(h);
}

void Character::setAttackPower(int a)
{
	if (attack_power <= 100)
	{
		attack_power = a;
	}
	if (attack_power > 100)
	{
		attack_power = 100;
	}
}

void Character::gainXP(const unsigned amount)
{
	level.gainXP(amount);

}

leveltype Character::getCurrentLevel() const
{
	return level.getCurrentLevel();
}

leveltype Character::getMaxLevel() const
{
	return level.getMaxLevel();
}

hptype Character::getCurrentHP() const
{
	return hp.getCurrentHP();
}

hptype Character::getMaxHP() const
{
	return hp.getMaxHP();
}

// Modified version of eyad's progressBar for HP
std::string hpProgressBar(int currentHP, int maxHP, int numBars)
{
    LogWriter::writeLogsToFile("PROGRESS BAR IS BEING PRINTED");
	int x = 177, y = 219;
	int percentage = (double)currentHP / maxHP * 100;
	std::string bar;

	for (int i = 0; i < numBars; i++)
	{
		if (i < percentage * numBars / 100)
		{
			bar += (char)y;
		}
		else
		{
			bar += (char)x;
		}
	}
	return bar;
}

void Character::display_hp() const
{
	int totalWidth = 60;
	std::cout << "+" << std::string(totalWidth, '-') << "+\n";
	int title = this->name.length();
	int padding = (totalWidth - title) / 2;
	std::cout << "|" << std::setw(padding + title) << this->name << std::setw(totalWidth - padding - title + 2) << "|\n";
	std::cout << "+" << std::string(totalWidth, '-') << "+\n";

	std::string h = "HP |" + hpProgressBar(getCurrentHP(), getMaxHP(), 55);
	padding = totalWidth - h.length() - 2; // 4 spaces for "| " and " >" or "  "
	std::cout << "| " << h << std::string(padding + 1, ' ') << "|\n";
	std::cout << "+" << std::string(totalWidth, '-') << "+\n";
}

void Character::takeDamage(const hptype damage)
{
    LogWriter::writeLogsToFile("DAMAGE TAKEN BY PLAYER");
	hp.takeDamage(damage);
}

void Character::heal(hptype amount)
{
    LogWriter::writeLogsToFile("HEALING ");
	hp.heal(amount);
	std::cout << name << " healed for " << amount << "." << '\n';
}

const string& Character::getName() const
{
	return name;
}

void Character::serialize(std::ofstream& outFile) const
{
    LogWriter::writeLogsToFile("SAVING PALYER INFO");
	// Serialize other data specific to Character
	size_t nameSize = name.size();
	outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	outFile.write(name.c_str(), nameSize);

	level.serialize(outFile);
	hp.serialize(outFile);
}

void Character::deserialize(std::ifstream& inFile) {
    LogWriter::writeLogsToFile("FETCHING PLAYER INFO FROM FILE");
	// Deserialize other data specific to Character
	size_t nameSize;
	inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
	char* nameBuffer = new char[nameSize + 1]; // +1 for null terminator
	inFile.read(nameBuffer, nameSize);
	nameBuffer[nameSize] = '\0';
	name = std::string(nameBuffer);
	delete[] nameBuffer;

	level.deserialize(inFile);
	hp.deserialize(inFile);
}

//void Character::addObserver(CharacterObserver *o) {
//
//}
//
//void Character::removeObserver(CharacterObserver *o) {
//
//}
//
//void Character::notify() {
//
//}
//
//void Character::update(string name, int level, HP hp) {
//
void Character::setName(const string& n)
{
	Character::name = n;
}

scoretype Character::get_effective_strength() const
{
	int strength = ability_scores.get_strength();
	for (const auto& item : equipped_items)
	{
		if (item.second == nullptr)
		{
			continue;
		}

		strength += item.second->get_strength();
	}
	return strength;
}

scoretype Character::get_effective_dexterity() const
{
	int dexterity = ability_scores.get_dexterity();
	for (const auto& item : equipped_items)
	{
		dexterity += item.second->get_dexterity();
	}
	return dexterity;
}

scoretype Character::get_effective_constitution() const
{
	int constitution = ability_scores.get_constitution();
	for (const auto& item : equipped_items)
	{
		constitution += item.second->get_constitution();
	}
	return constitution;
}

scoretype Character::get_effective_intelligence() const
{
	int intelligence = ability_scores.get_intelligence();
	for (const auto& item : equipped_items)
	{
		intelligence += item.second->get_intelligence();
	}
	return intelligence;
}

scoretype Character::get_effective_wisdom() const
{
	int wisdom = ability_scores.get_wisdom();
	for (const auto& item : equipped_items)
	{
		wisdom += item.second->get_wisdom();
	}
	return wisdom;
}

scoretype Character::get_effective_charisma() const
{
	int charisma = ability_scores.get_charisma();
	for (const auto& item : equipped_items)
	{
		charisma += item.second->get_charisma();
	}
	return charisma;
}

void Character::add_to_inventory(Item& item)
{
    LogWriter::writeLogsToFile("ADDING ITEM TO INVENTORY");
	inventory.add(item);
}

void Character::remove_from_inventory(int index)
{
	inventory.remove(index);
}

void Character::equip_from_inventory()
{
    LogWriter::writeLogsToFile("EQUIPPING FROM INVENTORY");
	char input;
	int option = 0;

	do
	{
		std::system("cls");
		int totalWidth = 60;
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";
		std::string title = "Select items to equip";
		int padding = (totalWidth - title.length()) / 2;
		std::cout << "|" << std::setw(padding + title.length()) << title << std::setw(totalWidth - padding - title.length() + 2) << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		int maxEquipSlotLength = 0;
		for (int i = 0; i < inventory.size(); ++i)
		{
			// get equipment at index
			Item& item = inventory.get_item(i);
			Equipment& equipment = dynamic_cast<Equipment&>(item);

			std::string equipSlot = EquipSlotToString(equipment.get_slot());
			if (equipSlot.length() > maxEquipSlotLength)
			{
				maxEquipSlotLength = equipSlot.length();
			}
		}

		for (int i = 0; i < inventory.size(); ++i)
		{
			// get equipment at index
			Item& item = inventory.get_item(i);
			Equipment& equipment = dynamic_cast<Equipment&>(item);

			std::string equipSlot = EquipSlotToString(equipment.get_slot());
			std::string itemName = equipment.get_name();
			std::string item_name = equipSlot + std::string(maxEquipSlotLength - equipSlot.length() + 5, ' ') + "|   " + itemName;
			padding = totalWidth - item_name.length() - 4; // 4 spaces for "| " and " >" or "  "
			std::cout << "| " << (option == i ? "> " : "  ") << item_name << std::string(padding + 1, ' ') << "|\n";
			std::cout << "|" << std::string(totalWidth, '-') << "|\n";
		}

		std::string go_back_option = "Go back";
		padding = totalWidth - go_back_option.length() - 4; // 4 spaces for "| " and " >" or "  "
		std::cout << "| " << (option == inventory.size() ? "> " : "  ") << go_back_option << std::string(padding + 1, ' ') << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		input = _getch();

		if (input == UP_ARROW_KEY)
		{
			option = (option - 1 < 0) ? inventory.size() : option - 1;
		}

		if (input == DOWN_ARROW_KEY)
		{
			option = (option + 1 > inventory.size()) ? 0 : option + 1;
		}

		if (input == ENTER_KEY)
		{
			if (option == inventory.size()) return;

			try
			{
				// get equipment at index
				Item& item = inventory.get_item(option);
				Equipment& equipment = dynamic_cast<Equipment&>(item);

				// check if slot is already occupied
				if (equipped_items[equipment.get_slot()] != nullptr)
				{
					std::cerr << "There's already an item equipped in this slot.\n";
					std::this_thread::sleep_for(std::chrono::seconds(2));
					continue;
				}

				// equip item
				equipped_items[equipment.get_slot()] = &equipment;

				// remove from inventory
				inventory.remove(option);
			}
			catch (const std::bad_cast& bc)
			{
				std::cerr << "The item at the given index is not equipment.\n";
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
	} while (true);
}

void Character::unequip_to_inventory()
{
	char input;
	int option = 0;

	do
	{
		std::system("cls");
		int totalWidth = 60;
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";
		std::string title = "Select items to unequip";
		int padding = (totalWidth - title.length()) / 2;
		std::cout << "|" << std::setw(padding + title.length()) << title << std::setw(totalWidth - padding - title.length() + 2) << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		int maxEquipSlotLength = 0;
		for (int i = 0; i < static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT); ++i)
		{
			std::string equipSlot = EquipSlotToString(static_cast<EquipSlot>(i));
			if (equipSlot.length() > maxEquipSlotLength)
			{
				maxEquipSlotLength = equipSlot.length();
			}
		}

		for (int i = 0; i < static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT); ++i)
		{
			std::string equipSlot = EquipSlotToString(static_cast<EquipSlot>(i));
			std::string itemName = equipped_items[static_cast<EquipSlot>(i)] == nullptr ? "empty" : equipped_items[static_cast<EquipSlot>(i)]->get_name();
			std::string item_name = equipSlot + std::string(maxEquipSlotLength - equipSlot.length() + 5, ' ') + "|   " + itemName;
			padding = totalWidth - item_name.length() - 4; // 4 spaces for "| " and " >" or "  "
			std::cout << "| " << (option == i ? "> " : "  ") << item_name << std::string(padding + 1, ' ') << "|\n";
			std::cout << "|" << std::string(totalWidth, '-') << "|\n";
		}

		std::string go_back_option = "Go back";
		padding = totalWidth - go_back_option.length() - 4; // 4 spaces for "| " and " >" or "  "
		std::cout << "| " << (option == static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT) ? "> " : "  ") << go_back_option << std::string(padding + 1, ' ') << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		input = _getch();

		if (input == UP_ARROW_KEY)
		{
			option = (option - 1 < 0) ? static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT) : option - 1;
		}

		if (input == DOWN_ARROW_KEY)
		{
			option = (option + 1 > static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT)) ? 0 : option + 1;
		}

		if (input == ENTER_KEY)
		{
			if (option == static_cast<int>(EquipSlot::EQUIP_SLOT_COUNT)) return;

			if (equipped_items[static_cast<EquipSlot>(option)] == nullptr) // Check if the item in the selected slot is not nullptr
			{
				std::cout << "The selected slot is empty.\n";
				std::this_thread::sleep_for(std::chrono::seconds(2));
				continue;
			}

			// Get a pointer to the item to unequip
			Item* to_unequip = equipped_items[static_cast<EquipSlot>(option)];

			// Add the item to the inventory
			inventory.add(*to_unequip);

			// Remove the item from the equipped items
			equipped_items[static_cast<EquipSlot>(option)] = nullptr;
		}
	} while (true);
}

void Character::attack(Character& other)
{


	int roll = Dice::roll(20);
	std::cout << name << " rolled " << roll << ".\n";
	hptype damage = this->attack_power + roll;
    other.takeDamage(damage);
	std::cout << name << " hit " << other.name << " for " << damage << ".\n";
//    PlaySound(TEXT("..\\src\\sounds\\PlayerAttacking.wav"), NULL, SND_FILENAME);
}

void Character::show_equipped_items()
{
	for (auto it = equipped_items.begin(); it != equipped_items.end(); ++it)
	{
		std::cout
			<< static_cast<int>(it->first) << "\t"
			<< EquipSlotToString(it->first) << "\t";

		if (it->second == nullptr)
		{
			std::cout << "empty\n";
			continue;
		}

		std::cout << it->second->get_name() << '\n';
	}
}

void Character::open_inventory()
{
	char input;
	int option = 0;
	int max_option = 2;

	do
	{
		std::system("cls");

		std::string title = "Inventory";
		int totalWidth = 40;
		int padding = (totalWidth - title.length()) / 2;
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";
		std::cout << "|" << std::setw(padding + title.length()) << title << std::setw(totalWidth - padding - title.length() + 2) << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		std::string option1 = "Equip item";
		std::string option2 = "Unequip item";
		std::string option3 = "Close inventory";
		std::cout << "| " << (option == 0 ? "> " : "  ") << option1 << std::setw(totalWidth - option1.length() - 1) << "|\n";
		std::cout << "| " << (option == 1 ? "> " : "  ") << option2 << std::setw(totalWidth - option2.length() - 1) << "|\n";
		std::cout << "| " << (option == 2 ? "> " : "  ") << option3 << std::setw(totalWidth - option3.length() - 1) << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";
		input = _getch();

		if (input == UP_ARROW_KEY)
		{
			option = (option - 1 < 0) ? max_option : option - 1;
		}

		if (input == DOWN_ARROW_KEY)
		{
			option = (option + 1 > max_option) ? 0 : option + 1;
		}

		if (input == ENTER_KEY)
		{
			switch (option)
			{
			case 0:
				equip_from_inventory();
				break;
			case 1:
				unequip_to_inventory();
				break;
			case 2:
				return;
			}
		}
	} while (true);
}

void Character::take_loot(ItemContainer& chest)
{
	char input;
	int option = 0;
	int totalWidth = 60;
    LogWriter::writeLogsToFile("TAKING LOOT");
	do
	{

		std::system("cls");
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";
		std::string header = "Select items to take";
		int header_padding = (totalWidth - header.length()) / 2;
		std::cout << "|" << std::setw(header_padding + header.length()) << header << std::setw(totalWidth - header_padding - header.length() + 2) << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		int maxEquipSlotLength = 0;
		for (int i = 0; i < chest.size(); ++i)
		{
			// get item at index
			Item& item = chest.get_item(i);
			Equipment& equipment = dynamic_cast<Equipment&>(item);

			std::string equipSlot = EquipSlotToString(equipment.get_slot());
			if (equipSlot.length() > maxEquipSlotLength)
			{
				maxEquipSlotLength = equipSlot.length();
			}
		}

		for (int i = 0; i < chest.size(); ++i)
		{
			// get item at index
			Item& item = chest.get_item(i);
			Equipment& equipment = dynamic_cast<Equipment&>(item);

			std::string equipSlot = EquipSlotToString(equipment.get_slot());
			std::string itemName = equipment.get_name();
			std::string item_name = equipSlot + std::string(maxEquipSlotLength - equipSlot.length() + 5, ' ') + "|   " + itemName;
			int padding = totalWidth - item_name.length() - 4; // 4 spaces for "| " and " >" or "  "
			std::cout << "| " << (option == i ? "> " : "  ") << item_name << std::string(padding + 1, ' ') << "|\n";
			std::cout << "|" << std::string(totalWidth, '-') << "|\n";
		}

		std::string go_back_option = "Go back";
		int padding = totalWidth - go_back_option.length() - 4; // 4 spaces for "| " and " >" or "  "
		std::cout << "| " << (option == chest.size() ? "> " : "  ") << go_back_option << std::string(padding + 1, ' ') << "|\n";
		std::cout << "+" << std::string(totalWidth, '-') << "+\n";

		input = _getch();

		if (input == UP_ARROW_KEY)
		{
			option = (option - 1 < 0) ? chest.size() : option - 1;
		}

		if (input == DOWN_ARROW_KEY)
		{
			option = (option + 1 > chest.size()) ? 0 : option + 1;
		}

		if (input == ENTER_KEY)
		{
			if (option == chest.size()) return;

			try
			{
				// get item at index
				auto& to_transfer = chest.get_item(option);

				// add to inventory
				add_to_inventory(to_transfer);

				// remove from chest
				chest.remove(option);
			}
			catch (const std::out_of_range& oor)
			{
				std::cerr << "Index out of range. Please choose a valid index.";
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
	} while (true);
}

void Character::take_loot(Character& character)
{
	take_loot(character.inventory);
}

// this method is used to print the progress bar
std::string progressBar(int a)
{
	int x = 177, y = 219;
	if (a <= 10)
	{
		a = a * 10;
	}
	std::string bar;
	for (int i = 0; i < 100; i++)
	{
		if (i >= a)
		{
			break;
		}
		else
		{
			//            std::cout<<(char)y;
			bar += (char)y;
		}
	}
	for (int j = 0; j < 100; j++)
	{
		if (j >= a)
		{
			//            std::cout<<(char)x;
			bar += (char)x;
		}
	}
	return bar;
}
/**
 * Operator overloading for Abilities
*/
ostream& operator<<(ostream& os, const AbilityScores& ability_scores)
{
    LogWriter::writeLogsToFile("WRITING CHARACTER ABILITIES ");
	using std::setw;

	int width = 150; // Adjust as needed
	os << "+---------------------------------------------------------------------------------------------------------------------+\n"
		<< "|                                                             Abilities                                               |\n"
		<< "+---------------------------------------------------------------------------------------------------------------------+\n"
		<< "| Strength    |" << progressBar(ability_scores.get_strength()) << " " << ability_scores.get_strength() << "\n"
		<< "| Dexterity   |" << progressBar(ability_scores.get_dexterity()) << " " << ability_scores.get_dexterity() << " \n"
		<< "| Constitution|" << progressBar(ability_scores.get_constitution()) << " " << ability_scores.get_constitution() << "\n"
		<< "| Intelligence|" << progressBar(ability_scores.get_intelligence()) << " " << ability_scores.get_intelligence() << "\n"
		<< "| Wisdom      |" << progressBar(ability_scores.get_wisdom()) << " " << ability_scores.get_wisdom() << "\n"
		<< "| Charisma    |" << progressBar(ability_scores.get_charisma()) << " " << ability_scores.get_charisma() << "\n"
		<< "+---------------------------------------------------------------------------------------------------------------------+\n";
	return os;
}
// Operator overloading for Character
ostream& operator<<(ostream& os, const Character& character)
{
	os
		<< "+---------------------------------------------------------------------------------------------------------------------+\n"
		<< "|                                                            Player View                                              |\n"
		<< "+---------------------------------------------------------------------------------------------------------------------+\n"
		<< "|                                                            Name: " << character.name << "\n"
		<< "|                                                            position(X,Y): (" << ",  " << ")\n"
		<< "| HP          |" << progressBar(character.hp.getCurrentHP()) << " " << character.hp.getCurrentHP() << "\n"
		<< "| Attack      |" << progressBar(character.attack_power) << " " << character.attack_power << "\n"
		<< character.ability_scores;
	//       << "" << character.fightingAbilities;
	return os;
}






// ************oberver pattern

//}
/**observer list let a character knows who is observing it*/
std::list <CharacterObserver*> observersList;
/**description: addObserver observers
 * @param: you must pass the observer by reference CharacterObserver* o
 * */
void Character::addObserver(CharacterObserver* o)
{
	observersList.push_back(o);
}
/**description: removeObserver observers
 * @param: you must pass the observer by reference CharacterObserver* o
 * */
void Character::removeObserver(CharacterObserver* o)
{
	// traverse over the list and compare memory addresses of available observers, when found remove the pointer
	auto it = std::find(observersList.begin(), observersList.end(), o);
	observersList.remove(*it);
}

/**description: notify observers
 * loop over all observers and notify them of changes
 * */
void Character::notify()
{
	for (CharacterObserver* observer : observersList)
	{
		if (observer != this) //check if the observer is calling itself, if yes no need to notify itself as it is already notified
		{
			observer->update(this->name, this->level, this->hp, this->attack_power);
		}

	}
}

void Character::update(string n, LevelSystem l, HP h, int a)
{
	//***this update method is meant to let a CHARACTER OBSERVE ANOTHER CHARACTER***
	// ToDo: print the Character view here or implement any interactions between characters (will be needed if we decide to have multiple characters)
}

const ItemContainer &Character::getInventory() const {
    return inventory;
}

void Character::setInventory(const ItemContainer &inventory) {
    Character::inventory = inventory;
}
