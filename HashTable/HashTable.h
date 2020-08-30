#pragma once

#include <memory>
#include <numeric>
#include <cassert>

#include "HashTableEntry.h"

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
      std::cout << index << std::endl;
      assert(index < size);
      EntryPtr entry = entries[index];

      while (entries[index] != nullptr)
      {
          if (entry->key == key) return entry;

          entry = entry->next;
      }

      return nullptr; // Return NULL if entry not found.
  }

  size_t Size() const { return size; }

  void Remove() {}

  EntryPtr operator[](const KeyType& key) { return GetEntry(key); }
  HashTable& operator=(const HashTable& other) = delete;
  HashTable& operator=(HashTable&& other) = delete;

private:
  uint32_t DefaultHashCodeGenerator(uint32_t key) const { return key % size; }
  uint32_t DefaultHashCodeGenerator(std::string key) const { return std::accumulate(key.begin(), key.end(), 0) % size; }
  std::array<EntryPtr, size> entries = { nullptr };
};