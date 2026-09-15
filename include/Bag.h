#ifndef BAG_H
#define BAG_H

#include "List.h"
#include <cstddef>

template <typename T>
class Bag
{
private:
    List<T> items;

public:
    Bag() = default;

    bool isEmpty() const
    {
        return items.empty();
    }

    std::size_t getCurrentSize() const
    {
        return items.size();
    }

    bool add(const T& item)
    {
        items.push_back(item);
        return true;
    }

    bool remove(const T& item)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (*it == item)
            {
                items.erase(it);
                return true;
            }
        }

        return false;
    }

    void clear()
    {
        while (!items.empty())
        {
            items.pop_front();
        }
    }

    bool contains(const T& item) const
    {
        for (auto it = items.cbegin(); it != items.cend(); ++it)
        {
            if (*it == item)
            {
                return true;
            }
        }

        return false;
    }

    int getFrequencyOf(const T& item) const
    {
        int count = 0;

        for (auto it = items.cbegin(); it != items.cend(); ++it)
        {
            if (*it == item)
            {
                ++count;
            }
        }

        return count;
    }
};

#endif

