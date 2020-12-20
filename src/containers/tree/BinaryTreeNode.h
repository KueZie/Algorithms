#pragma once

#include <memory>

namespace containers::tree
{

template<class DataType>
struct BinaryTreeNode {
    using BinaryTreeNodePtr = std::unique_ptr<BinaryTreeNode>;
    BinaryTreeNodePtr left{};
    BinaryTreeNodePtr right{};
    DataType data;
    explicit BinaryTreeNode(DataType _data) noexcept : data(_data) {}
};

}