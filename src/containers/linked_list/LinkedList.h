/**
 * @author Hunter Goram
 * @date 09/04/2020
 * @details Implementation of a unidirectional linked list.
 */

#pragma once

//#include <>

#include "util/logging.h"
#include "containers/linked_list/LinkedListNode.h"

namespace containers
{
namespace list
{

template<typename T>
class LinkedList
{
using Node = UnidirectionalLiskedListNode<T>;

public:
    LinkedList() = default;
    ~LinkedList() = default;

    /**
     *
     * @param data
     */
    void PushBack(T data)
    {
        Node* current = std::copy(head);

        if (current == nullptr)
        {
            head = new Node(data);
        }

        // Iterate through the list until the last element is reached.
        while (current->next != nullptr)
            current = current->next;

        current->next = new Node(data);
    }
    /**
     *
     * @param data
     */
    void PushBack(T&& data)
    {
        Node* current = head;

        // Make sure operation on a nullptr don't take place.
        if (current == nullptr)
        {
            head = new Node(std::move(data));
        }

        // Iterate through the list until the last element is reached.
        while (current->next != nullptr)
            current = current->next;

        current->next = new Node(std::move(data));
    }
    /**
     *
     * @param data
     */
    void Remove(const T& data)
    {

    }
    /**
     *
     * @param index
     * @return Reference to node at given index; if index is out of range, nullptr.
     */
    Node& GetIndex(uint64_t index)
    {
        Node* current = head;
        for (uint64_t i = 0; i < index; ++i)
            if (current != nullptr)
                current = current->next;
            else
                return nullptr;

        return *current;
    }
private:
    Node* head = nullptr;
};

} // End list
} // End containers