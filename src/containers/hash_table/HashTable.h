#pragma once

#include <memory>
#include <numeric>
#include <cassert>
#include <sstream>
#include <type_traits>

#include "HashTableEntry.h"
#include "util/interfaces/interfaces.h"
#include "util/logging.h"

/* INFO: The actual hash table and it's associated buckets are allocated on the stack.
 *        However, all of the list items in the bucket are just instances of shared_ptr<...> to heap allocated
 *        HashTableEntry instances.
 *
 *        This implementation currently supports numeric and string data types as keys, as well as all data types that are
 *        copyable.
 *
 *    __________________
 *   |    Hash Table    |
 *   |__________________|
 *   | Key: "TestData1" |
 *   | Next: nullptr    |
 *   |__________________|         __________________          __________________
 *   | Key: "ListItem1" |        | Key: "ListItem2" |        | Key: "ListItem3" |
 *   | Next: *------>   |        | Next: *------>   |        | Next: nullptr    |
 *   |__________________|        |__________________|        |__________________|
 *   | Key: "TestData3" |
 *   | Next: nullptr    |
 *  |__________________|
 */
namespace containers
{
namespace hash_table
{

template<typename KeyType, typename DataType, size_t size = 100>
class HashTable : public util::interfaces::IDisplayable
{
using Entry = HashTableEntry<KeyType, DataType>;
using EntryPtr = std::shared_ptr<Entry>;
public:
  HashTable() = default;

  ~HashTable() = default;

  /**
   * @brief Creates a new `HashTableEntry` with the given key and data and adds the entry to the containing array.
   * @param key
   * @param data
   */
  void Add(KeyType key, DataType data)
  {
      uint32_t index = DefaultHashCodeGenerator(key); // Find bucket for the given key
      assert(index < size); // Make sure index is not out of range
      EntryPtr& entry = entries[index]; // Get first element in the bucket

      // This seems like it can be optimized to not have an if-else
      if (entry != nullptr) {
          EntryPtr tmp = entry;

          while (tmp->next != nullptr)
              tmp = tmp->next;

          tmp->next = std::make_shared<Entry>(key, data, nullptr);
      } else {
          entry = std::make_shared<Entry>(key, data, nullptr);
      }

  }

  /**
   * @brief Get entry in hash table that matches the given key.
   * @param key
   * @return First entry matching the given key; nullptr if not found.
   */
  EntryPtr GetEntry(KeyType key)
  {
      auto index = DefaultHashCodeGenerator(key);// Find bucket for the given key
      assert(index < size); // Make sure index is not out of range
      EntryPtr entry = entries[index]; // Get first element in the bucket

      while (entry != nullptr)
      {
          if (entry->key == key) return entry;

          entry = entry->next; // Move forward in the linkage
      }

      return nullptr; // Return NULL if entry not found.
  }

  /**
   * @brief Gets the number of buckets or elements in the containing array.
   * @return size
   */
  size_t Size() const { return size; }

  /**
   * @brief Remove entry from HashTable instance.
   * @param key
   * @warning Operation invalidates the `next` pointer of the removed entry, but allows continues operations
   *          on the removed entry as long as there are valid references alive.
   */
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

  /**
   * @result Displays the contents of the HashTable instance in a readable form to stdout.
   */
  void Display() const override
  {
      std::stringstream output_buffer;

      for (auto it = entries.begin(); it < entries.end(); ++it)
      {
          if (*it != nullptr) {
              EntryPtr entry = *it;
              output_buffer << it - entries.begin() << ". Key: " << std::to_string(entry->key) << "\n";

              int depth = 1; // Represents how many entries deep we are in ->next
              while (entry->next != nullptr)
              {
                  for (int i = 0; i < depth; ++i)
                      output_buffer << "\t"; // Add an additional tab for every level we go deep.
                  output_buffer << "`-----> Key: " << std::to_string(entry->next->key) << "\n"; // Add the data on the line.

                  // Increment
                  entry = entry->next;
                  ++depth;
              }

              std::cout << output_buffer.str();
              output_buffer.str("");
              output_buffer.clear();
          }
      }
  }

    // Allow [] operator usage instead of explicit GetEntry calls.
  EntryPtr operator[](const KeyType& key) { return GetEntry(key); }
  HashTable& operator=(const HashTable& other) = delete; // Remove copy assignment.
  //HashTable& operator=(HashTable&& other) = delete;

private:
  uint32_t DefaultHashCodeGenerator(uint32_t key) const { return key % size; }
  uint32_t DefaultHashCodeGenerator(std::string key) const { return std::accumulate(key.begin(), key.end(), 0) % size; }

  std::array<EntryPtr, size> entries = { nullptr }; // Contains the entries in buckets or chains.
}; // End HashTable

} // End hash_table

} // End data_types