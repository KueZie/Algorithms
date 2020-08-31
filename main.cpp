#include <iostream>
#include <string>

#include "HashTable/HashTable.h"

int main(int argv, char** argc)
{
    auto table = HashTable<std::string, uint32_t>();

    table.Add("Huntego", 69);
    table.Add("Hunter", 10);

    const auto& entry = table.GetEntry("Hunter");

    std::cout << (entry == nullptr ? 0 : entry->data) << std::endl;

    return 0;
}