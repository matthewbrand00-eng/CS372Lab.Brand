#include <iostream>
#include "Array.h"

int main()
{
    Array<int> numbers(5);

    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        numbers[i] = static_cast<int>(i * 10);
    }

    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i] << ' ';
    }

    std::cout << '\n';

    Array<int> copy(numbers);

    std::cout << "Copied array: ";

    for (std::size_t i = 0; i < copy.size(); ++i)
    {
        std::cout << copy[i] << ' ';
    }

    std::cout << '\n';

    return 0;
}

