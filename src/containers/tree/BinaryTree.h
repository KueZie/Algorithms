#pragma once

#include <memory>
#include "containers/tree/BinaryTreeNode.h"

namespace containers::tree
{

template<class DataType>
class BinaryTree
{
using BinaryTreeNodePtr = std::unique_ptr<BinaryTreeNode<DataType>>;
public:
    BinaryTree() = default;
    void Insert(DataType data)
    {
        BinaryTreeNodePtr* current = &root;

        while (*current != nullptr)
            if (data < (*current)->data)
                current = &(*current)->left;
            else
                current = &(*current)->right;

        auto new_node = std::make_unique<BinaryTreeNode<DataType>>(data);
        *current = std::move(new_node);
    }
private:
    BinaryTreeNodePtr root = nullptr;
};

}