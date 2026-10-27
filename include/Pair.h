
#ifndef PAIR_H
#define PAIR_H

#include <compare>

template <typename Key, typename Value>
struct Pair
{
    Key first;
    Value second;

    auto operator<=>(const Pair&) const = default;
};

#endif
