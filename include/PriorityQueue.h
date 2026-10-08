#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "List.h"
#include <utility>

template <typename T>
class PriorityQueue
{
private:
    List<std::pair<unsigned int, T>> items;

public:
    void push(T newItem, unsigned int itemPriority)
    {
        std::pair<unsigned int, T> newEntry(itemPriority, newItem);

        auto current = items.begin();

        while (current != items.end() &&
               (*current).first >= itemPriority)
        {
            ++current;
        }

        items.insert(current, newEntry);
    }

    T& top()
    {
        return items.front().second;
    }

    void pop()
    {
        items.pop_front();
    }

    /*
        This linked-list implementation is not the most efficient way
        to implement a priority queue.

        push() is O(n) because the list must be traversed to find the
        correct location for the new item so that the list remains in
        priority order. Once that location is found, insertion into the
        linked list is O(1).

        top() is O(1) because the highest-priority item is always at
        the front of the list.

        pop() is O(1) because removing the item at the front of the
        linked list is a constant-time operation.

        Therefore, maintaining the priority-order invariant makes
        push() the expensive operation in this implementation.
    */
};

#endif
