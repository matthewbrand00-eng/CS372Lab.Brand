#include <iostream>
#include "Queue.h"

int josephus(int numberOfPlayers, int passes)
{
    Queue<int> players;

    // Add players so person 1 is first in the queue.
    for (int i = 1; i <= numberOfPlayers; ++i)
    {
        players.push(i);
    }

    while (true)
    {
        // Pass the potato M times.
        for (int i = 0; i < passes; ++i)
        {
            int current = players.back();
            players.pop();
            players.push(current);
        }

        // The person holding the potato is eliminated.
        int eliminated = players.back();
        players.pop();

        // If nobody remains, the eliminated person was the winner.
        if (players.empty())
        {
            return eliminated;
        }

        std::cout << "Eliminated: " << eliminated << '\n';
    }
}

int main()
{
    int n;
    int m;

    std::cout << "Enter number of players: ";
    std::cin >> n;

    std::cout << "Enter number of passes: ";
    std::cin >> m;

    int winner = josephus(n, m);

    std::cout << "Winner: " << winner << '\n';

    return 0;
}

