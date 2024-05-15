#pragma once
#include <vector>
#include <algorithm>
#include "items/item/item.h"
#include <iostream>
#include "items/equipment/equipment.h"
#include "maps/positionable.h"
#include <chrono>
#include <thread>

class Character;

class ItemContainer : public Positionable {
public:
    ItemContainer();
	explicit ItemContainer(int max_size);
	~ItemContainer() override;

	void add(Item& item);
	void remove(int index);

	void display();

	Item& get_item(int index);

	int size() const;

	ItemContainer* generateChest();

    void serialize(std::ofstream& outFile) const override;

    void deserialize(std::ifstream& inFile) override;

private:
	std::vector<Item*> items;
	int max_size;
};