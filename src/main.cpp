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
  auto table = containers::hash_table::HashTable<std::string, TestData>();

  table.Add("Huntego", {.data = "Hunter1"});
  table.Add("Hunter", {.data = "Hunter1"});
  table.Remove("Hunter");
  const auto &entry = table.GetEntry("Hunter");
  std::cout << (entry == nullptr ? "null" : entry->data.data) << std::endl;

  return 0;
}