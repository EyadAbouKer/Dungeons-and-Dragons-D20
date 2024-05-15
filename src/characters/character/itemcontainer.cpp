#include "itemcontainer.h"


ItemContainer::ItemContainer() : max_size(5) {
    items.reserve(max_size);
    for (auto& item : items) {
        item = nullptr;
    }
}
ItemContainer::ItemContainer(int max_size) : max_size(max_size)
{
	items.reserve(max_size);
	for (auto& item : items)
	{
		item = nullptr;
	}
}

ItemContainer::~ItemContainer()
{
	for (auto& item : items)
	{
		delete item;
	}
}

void ItemContainer::add(Item& item)
{
	items.push_back(&item);
}

void ItemContainer::remove(int index)
{
	if (index < 0 || index > items.size())
	{
		std::cout << "That is not a valid index.";
		return;
	}

	items.erase(items.begin() + index);
}

void ItemContainer::display()
{
	for (int i = 0; i < items.size(); i++)
	{

		std::cout << i << "\t" << items[i]->get_name();

		auto* equipment = dynamic_cast<Equipment*>(items[i]);
		if (equipment != nullptr) // the item is an Equipment
		{
			std::cout << '\t' << EquipSlotToString(equipment->get_slot());
		}

		std::cout << std::endl;
	}
}

Item& ItemContainer::get_item(int index)
{
	return *items.at(index);
}

int ItemContainer::size() const
{
	return items.size();
}

ItemContainer* ItemContainer::generateChest()
{
	return nullptr;
}

void ItemContainer::serialize(std::ofstream &outFile) const {
    // Serialize max_size
    outFile.write(reinterpret_cast<const char*>(&max_size), sizeof(max_size));

    // Serialize number of items
    size_t numItems = items.size();
    outFile.write(reinterpret_cast<const char*>(&numItems), sizeof(numItems));

    // Serialize each item
    for (const auto& item : items) {
        item->serialize(outFile);
    }
}

void ItemContainer::deserialize(std::ifstream &inFile) {
    // Deserialize max_size
    inFile.read(reinterpret_cast<char*>(&max_size), sizeof(max_size));

    // Deserialize number of items
    size_t numItems;
    inFile.read(reinterpret_cast<char*>(&numItems), sizeof(numItems));

    // Deserialize each item
    for (size_t i = 0; i < numItems; ++i) {
        auto* newItem = new Equipment(); // Assuming default constructor exists
        newItem->deserialize(inFile);
        items.push_back(dynamic_cast<Equipment*>(newItem));
    }
}

