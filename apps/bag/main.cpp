#include <iostream>
#include "Bag.h"

int main()
{
    Bag<int> bag;

    bag.add(10);
    bag.add(20);
    bag.add(10);

    std::cout << "Size: " << bag.getCurrentSize() << '\n';
    std::cout << "Contains 20: " << bag.contains(20) << '\n';
    std::cout << "Frequency of 10: " << bag.getFrequencyOf(10) << '\n';

    bag.remove(10);

    std::cout << "After removing one 10: "
              << bag.getFrequencyOf(10) << '\n';

    return 0;
}
