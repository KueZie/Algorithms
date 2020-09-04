#pragma once

#include <memory>

template<typename DataType>
struct MonodirectionalLinkedListNode
{
    DataType data;
    MonodirectionalLinkedListNode<DataType>* next;
};


struct [[nodiscard]] BiDirectionalLinkedListNode
{

};