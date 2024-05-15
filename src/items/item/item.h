#pragma once
#include <string>
#include <fstream>

class Item
{
public:
    Item();
	Item(std::string  name);
	virtual ~Item();

	const std::string& get_name();

    virtual void serialize(std::ofstream& outFile) const;

    virtual void deserialize(std::ifstream& inFile);
private:
	std::string name;
};