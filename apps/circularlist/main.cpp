#include <iostream>
#include "CircularList.h"

void printValue(int& value)
{
    std::cout << value << ' ';
}

int main()
{
    CircularList<int> numbers;

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);
    numbers.push_back(50);

    std::cout << "Start at index 0: ";
    numbers.traverse(0, printValue);
    std::cout << '\n';

    std::cout << "Start at index 2: ";
    numbers.traverse(2, printValue);
    std::cout << '\n';

    std::cout << "Start at index 4: ";
    numbers.traverse(4, printValue);
    std::cout << '\n';

    return 0;
}
