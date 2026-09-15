#include <chrono>
#include <iostream>
#include "Vector.h"

template <typename VectorType>
long long timeInsertions(std::size_t count)
{
    const int runs = 10;
    long long totalTime = 0;

    for (int run = 0; run < runs; ++run)
    {
        VectorType values;

        auto start = std::chrono::steady_clock::now();

        for (std::size_t i = 0; i < count; ++i)
        {
            values.push_back(static_cast<int>(i));
        }

        auto end = std::chrono::steady_clock::now();

        totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(
            end - start
        ).count();
    }

    return totalTime / runs;
}

int main()
{
    std::cout << "Size,ForLoopVector,CopyVector,LargeGrowthVector\n";

    for (std::size_t n = 2; n <= 1048576; n *= 2)
    {
        long long baseTime = timeInsertions<Vector<int>>(n);
        long long copyTime = timeInsertions<CopyVector<int>>(n);
        long long largeTime = timeInsertions<LargeGrowthVector<int>>(n);

        std::cout << n << ","
                  << baseTime << ","
                  << copyTime << ","
                  << largeTime << '\n';
    }

    return 0;
}
