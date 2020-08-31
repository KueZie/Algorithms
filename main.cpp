#include <iostream>
#include <string>

#include "HashTable/HashTable.h"

struct TestData
{
    std::string data;
};

int main(int argv, char** argc)
{
    auto table = HashTable<std::string, TestData>();

    table.Add("Huntego", { .data = "Hunter1" });
    table.Add("Hunter", { .data = "Hunter1" });
    table.Remove("Hunter");
    const auto& entry = table.GetEntry("Hunter");
    std::cout << (entry == nullptr ? "null" : entry->data.data) << std::endl;

    return 0;
}