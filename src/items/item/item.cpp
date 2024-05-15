#include "item.h"

#include <utility>

Item::Item() :
        name("item")
{
}

Item::Item(std::string  name) :
	name(std::move(name))
{
}

Item::~Item() = default;

const std::string& Item::get_name()
{
	return name;
}

void Item::serialize(std::ofstream &outFile) const {
    // Serialize name size
    size_t nameSize = name.size();
    outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));

    // Serialize name
    outFile.write(name.c_str(), nameSize);
}

void Item::deserialize(std::ifstream &inFile) {
    // Deserialize name size
    size_t nameSize;
    inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));

    // Deserialize name
    char* nameBuffer = new char[nameSize + 1]; // +1 for null terminator
    inFile.read(nameBuffer, nameSize);
    nameBuffer[nameSize] = '\0';
    name = std::string(nameBuffer);
    delete[] nameBuffer;
}
