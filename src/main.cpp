#include <iostream>
#include <string>

#include "containers/hash_table/HashTable.h"

#ifdef ENABLE_TESTING
#include "gtest/gtest.h"
#endif

struct TestData {
  std::string data;
};

int main(int argc, char **argv) {
  auto table = containers::hash_table::HashTable<std::uint8_t , TestData, 10>();

  table.Add(0, {.data = "key is 0"});
  table.Add(10, {.data = "key is 10"});
  table.Add(20, {.data = "key is 20"});
  table.Add(22, {.data = "key is 22"});
  //table.Remove(20);
  table.Display();

  std::cout << std::endl << (table.GetEntry(20) == nullptr ? "nullptr" : table.GetEntry(20)->data.data) << std::endl;

  return 0;
}