/**
 * @author Hunter Goram
 * @date 09/04/2020
 * @details Defines several different node types for linked lists.
 */

#pragma once

#include <memory>

template<typename DataType>
struct UnidirectionalLiskedListNode
{
    DataType data;
    UnidirectionalLiskedListNode<DataType>* next;
    UnidirectionalLiskedListNode() : data(0), next(nullptr) {}
    explicit UnidirectionalLiskedListNode(DataType _data) : data(_data), next(nullptr) {}
    explicit UnidirectionalLiskedListNode(DataType _data, UnidirectionalLiskedListNode<DataType>* _next)
        : data(_data), next(_next) {}
};


struct  BiDirectionalLinkedListNode
{

};