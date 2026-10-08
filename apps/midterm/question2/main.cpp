#include <iostream>
#include "Vector.h"

int main()
{
    Vector<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);

    std::cout << "Vector elements: ";

    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    auto first = numbers.begin();
    auto second = numbers.begin();

    std::cout << "Begin iterators equal: "
              << (first == second) << '\n';

    ++second;

    std::cout << "After increment equal: "
              << (first == second) << '\n';

    std::cout << "Second element: "
              << *second << '\n';

    return 0;
}
