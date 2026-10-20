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

    

        // Test removing nodes
    List<int> removalTest;
    removalTest.push_back(10);
    removalTest.push_back(20);
    removalTest.push_back(30);

    removalTest.pop_front();
    removalTest.pop_back();

    std::cout << "After removals: "
            << removalTest.front() << std::endl;

    // Test that copies are independent
    List<int> originalTest;
    originalTest.push_back(100);

    List<int> copiedTest = originalTest;
    copiedTest.push_back(200);

    std::cout << "Original size: "
            << originalTest.size() << std::endl;

    std::cout << "Copy size: "
            << copiedTest.size() << std::endl;

    // Test removing every node
    removalTest.pop_front();

    std::cout << "Empty after removal: "
            << removalTest.empty() << std::endl;

            
    return 0;
}
