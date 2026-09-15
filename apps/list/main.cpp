#include <iostream>
#include <utility>
#include "List.h"

int main()
{
    List<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_front(5);

    std::cout << "Original: ";

    for (int value : numbers)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    List<int> copied(numbers);

    std::cout << "Copy: ";

    for (int value : copied)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    List<int> assigned;
    assigned = numbers;

    std::cout << "Assigned: ";

    for (int value : assigned)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    List<int> moved(std::move(numbers));

    std::cout << "Moved: ";

    for (int value : moved)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    return 0;
}
