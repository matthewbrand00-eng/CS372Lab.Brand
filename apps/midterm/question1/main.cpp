#include <iostream>
#include <string>
#include "PriorityQueue.h"

int main()
{
    PriorityQueue<std::string> queue;

    queue.push("Low", 1);
    queue.push("Very High", 10);
    queue.push("Medium", 5);
    queue.push("High", 8);

    std::cout << queue.top() << '\n';
    queue.pop();

    std::cout << queue.top() << '\n';
    queue.pop();

    std::cout << queue.top() << '\n';
    queue.pop();

    std::cout << queue.top() << '\n';

    return 0;
}

