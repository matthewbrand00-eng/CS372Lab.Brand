#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "List.h"
#include <cstddef>
#include <functional>

template <typename T>
class CircularList : public List<T>
{
public:
    void traverse(
        std::size_t start,
        std::function<void(T&)> doIt)
    {
        if (this->empty() || start >= this->size())
        {
            return;
        }

        std::size_t current = start;

        do
        {
            doIt((*this)[current]);

            current = (current + 1) % this->size();

        } while (current != start);
    }
};

#endif
