#pragma once

#include <memory>
#include <numeric>
#include <cassert>

#include "HashTableEntry.h"

#if DEBUG
#   define DEBUG_LOG(x) std::cout << x << std::endl
#else
#   define DEBUG_LOG(x)
#endif

// INFO: The actual hash table and it's associated buckets are allocated on the stack.
//       However, all of the list items in the bucket are just instances of shared_ptr<...> to heap allocated
//       HashTableEntry instances.
//
//       This implementation currently supports numeric and string data types as keys, as well as all data types that are
//       copyable.
//
//   __________________
//  |    Hash Table    |
//  |__________________|
//  | Key: "TestData1" |
//  | Next: nullptr    |
//  |__________________|         __________________          __________________
//  | Key: "ListItem1" |        | Key: "ListItem2" |        | Key: "ListItem3" |
//  | Next: *------>   |        | Next: *------>   |        | Next: nullptr    |
//  |__________________|        |__________________|        |__________________|
//  | Key: "TestData3" |
//  | Next: nullptr    |
//  |__________________|

namespace containers
{
namespace hash_table
{

template<typename KeyType, typename DataType, size_t size = 100>
class HashTable
{
using Entry = HashTableEntry<KeyType, DataType>;
using EntryPtr = std::shared_ptr<Entry>;
public:
  HashTable() {}

  ~HashTable() {}

  void Add(KeyType key, DataType data)
  {
      uint32_t index = DefaultHashCodeGenerator(key);
      EntryPtr& entry = entries[index];

      // This seems like it can be optimized to not have an if-else
      if (entry != nullptr) {
          while (entry->next != nullptr)
              entry = entry->next;

          entry->next = std::make_shared<Entry>(key, data, nullptr);
      } else {
          entry = std::make_shared<Entry>(key, data, nullptr);
      }
  }
  // Get entry in hash table that matches the given key.
  // CAUTION: Returns a nullptr when an entry with the given key is not found.
  EntryPtr GetEntry(KeyType key)
  {
      auto index = DefaultHashCodeGenerator(key);
      assert(index < size);
      EntryPtr entry = entries[index];

      while (entry != nullptr)
      {
          if (entry->key == key) return entry;

          entry = entry->next; // Move forward in the linkage
      }

      return nullptr; // Return NULL if entry not found.
  }

  size_t Size() const { return size; }

  // Remove entry from HashTable.
  // CAUTION: Operation invalidates the `next` pointer of the removed entry, but allows continues operations
  // on the removed entry as long as there are valid references alive.
  void Remove(KeyType key)
  {
      auto index = DefaultHashCodeGenerator(key); // Find bucket index
      assert(index < size);
      EntryPtr entry = entries[index];

      if (entry == nullptr)
      {
          DEBUG_LOG("Unable to resolve index of HashTable item: `" << key << "`; no items removed.\n");
          return;
      }

      // If the entry to remove is the first in the bucket
      if (entry->key == key)
      {
          entries[index] = std::move(entry->next);
          return;
      }
      // Runs when entry to delete isn't first in the bucket.
      // Runs until the variable entry is equal to the node before the entry to delete.
      while (entry->next != nullptr)
      {
          if (entry->next->key == key) break;

          entry = entry->next;
      }
      // Ensure that the correct node is set, and not just the last node in the chain.
      if (entry->next->key == key)
      {
          entry->next = std::move(entry->next->next); // No memory cleanups necessary
      }
      else
      {
          DEBUG_LOG("Unable to resolve index of HashTable item: `" << key << "`; no items removed.\n");
      }
  }

  EntryPtr operator[](const KeyType& key) { return GetEntry(key); }
  HashTable& operator=(const HashTable& other) = delete;
  //HashTable& operator=(HashTable&& other) = delete;

private:
  uint32_t DefaultHashCodeGenerator(uint32_t key) const { return key % size; }
  uint32_t DefaultHashCodeGenerator(std::string key) const { return std::accumulate(key.begin(), key.end(), 0) % size; }
  std::array<EntryPtr, size> entries = { nullptr };
}; // End HashTable

} // End hash_table

} // End data_types