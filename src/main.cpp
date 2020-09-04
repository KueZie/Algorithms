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
  auto table = containers::hash_table::HashTable<std::string, TestData, 10>();

  table.Add("Huntego", {.data = "Hunter1"});
  table.Add("Hunter", {.data = "Hunter1"});
  table.Add("Huntergogo", {.data = "Hunter1"});
  table.Add("Hunteeeee", {.data = "Hunter2"});
  table.Remove("Huntego");
  table.Display();

  std::cout << std::endl << (table.GetEntry("Huntego") == nullptr ? "nullptr" : table.GetEntry("Huntego")->key) << std::endl;

  return 0;
}