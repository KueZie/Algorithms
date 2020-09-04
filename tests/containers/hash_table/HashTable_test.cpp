#include <iostream>
#include "gtest/gtest.h"
#include "containers/hash_table/HashTable.h"

class HashTableTest : public ::testing::Test
{
protected:
    HashTableTest() {}
    ~HashTableTest() {}
};

TEST(HashTableTest, NumericDataRetrievableFromKey)
{
    containers::hash_table::HashTable<std::string, uint32_t> table;
    table.Add("Employee1", 678943);
    table.Add("Employee2", 678944);

    ASSERT_EQ(table.GetEntry("Employee1")->data, 678943);
    ASSERT_EQ(table.GetEntry("Employee2")->data, 678944);
    ASSERT_FALSE(table.GetEntry("Employee1")->data == table.GetEntry("Employee2")->data);
}

TEST(HashTableTest, StringDataRetrievableFromKey)
{
    containers::hash_table::HashTable<std::string, std::string> table;
    table.Add("Employee1", "678943");
    table.Add("Employee2", "678944");

    ASSERT_EQ(table.GetEntry("Employee1")->data, "678943");
    ASSERT_EQ(table.GetEntry("Employee2")->data, "678944");
    ASSERT_FALSE(table.GetEntry("Employee1")->data == table.GetEntry("Employee2")->data);
}

TEST(HashTableTest, ChainRelinkAfterEntryRemoval)
{
    containers::hash_table::HashTable<std::uint8_t, const char*, 2> table;
    table.Add(0, "TestData1");
    table.Add(2, "TestData2");
    table.Add(4, "TestData3");
    table.Remove(2);

    ASSERT_STREQ(table.GetEntry(0)->data, "TestData1");
    ASSERT_STREQ(table.GetEntry(4)->data, "TestData3");
}