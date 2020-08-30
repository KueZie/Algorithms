// Header ONLY
#pragma once

#include <memory>

template <typename KeyType, typename DataType>
struct HashTableEntry
{
    using HashTableEntryPtr = std::shared_ptr<HashTableEntry>;
    KeyType           key;
    DataType          data;
    HashTableEntryPtr next; // Used to resolve key conflicts.
    HashTableEntry(const KeyType& _key, const DataType& _data, const HashTableEntryPtr& _next)
    {
        key = _key;
        data = _data;
        next = _next;
    }
};