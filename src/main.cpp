#include <iostream>
#include <string>

#include "containers/hash_table/HashTable.h"
#include "containers/tree/BinaryTree.h"

#ifdef ENABLE_TESTING
#include "gtest/gtest.h"
#endif

struct TestData {
  std::string data;
};

int main(int argc, char **argv) {
  auto btree = containers::tree::BinaryTree<int>();

  btree.Insert(10);
  btree.Insert(20);

  return 0;
}