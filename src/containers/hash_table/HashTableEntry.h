// Header ONLY
#pragma once

#include <memory>

namespace containers
{
namespace hash_table
{
template <typename KeyType, typename DataType>
struct HashTableEntry
{
    using HashTableEntryPtr = std::shared_ptr<HashTableEntry>;
    KeyType           key;
    DataType          data;
    HashTableEntryPtr next; // Used to resolve key conflicts.
    HashTableEntry(KeyType _key, DataType _data, HashTableEntryPtr _next)
    {
        key = _key;
        data = _data;
        next = _next;
    }
}; // End HashTableEntry

} // End hash_table

} // End data_types