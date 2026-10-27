
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "Dictionary.h"

int main()
{
    Dictionary<std::string, int> scores;

    assert(scores.isEmpty());

    // Insert entries
    scores.insert({"Charlie", 90});
    scores.insert({"Alice", 95});
    scores.insert({"Bob", 85});

    assert(scores.size() == 3);

    // Access and modify
    assert(scores.at("Alice") == 95);
    scores["Bob"] = 100;
    assert(scores.at("Bob") == 100);

    // operator[] inserts missing keys
    scores["David"] = 88;
    assert(scores.size() == 4);

    // Duplicate insertion should not change size
    scores.insert({"Alice", 70});
    assert(scores.size() == 4);
    assert(scores.at("Alice") == 95);

    // Keys should be sorted
    auto& keys = scores.keys();

    assert(keys.size() == 4);
    assert(keys[0] == "Alice");
    assert(keys[1] == "Bob");
    assert(keys[2] == "Charlie");
    assert(keys[3] == "David");

    std::cout << "Keys: ";
    for (const auto& key : keys)
        std::cout << key << " ";
    std::cout << '\n';

    std::cout << "Values: ";
    for (const auto& value : scores.values())
        std::cout << value << " ";
    std::cout << '\n';

    // Remove an entry
    scores.erase("Charlie");
    assert(scores.size() == 3);

    bool threw = false;

    try
    {
        scores.at("Charlie");
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }

    assert(threw);

    // Test copying
    Dictionary<std::string, int> copied(scores);
    copied["Alice"] = 50;

    assert(scores.at("Alice") == 95);
    assert(copied.at("Alice") == 50);

    // Test moving
    Dictionary<std::string, int> moved(std::move(copied));
    assert(moved.at("Alice") == 50);

    // Clear
    moved.clear();
    assert(moved.isEmpty());
    assert(moved.size() == 0);

    std::cout << "All Dictionary tests passed!\n";
    // Test AVL tree with many entries
Dictionary<int, int> largeDictionary;

for (int i = 0; i < 1000; ++i)
{
    largeDictionary[i] = i * 10;
}

assert(largeDictionary.size() == 1000);

for (int i = 0; i < 1000; ++i)
{
    assert(largeDictionary.at(i) == i * 10);
}

// Remove half the entries
for (int i = 0; i < 1000; i += 2)
{
    largeDictionary.erase(i);
}

assert(largeDictionary.size() == 500);

for (int i = 1; i < 1000; i += 2)
{
    assert(largeDictionary.at(i) == i * 10);
}

std::cout << "1,000-entry AVL test passed!\n";

// Test move constructor and move assignment
Dictionary<int, int> source;
source[10] = 100;
source[20] = 200;

Dictionary<int, int> destination(std::move(source));

assert(source.isEmpty());
assert(source.size() == 0);
assert(destination.size() == 2);
assert(destination.at(10) == 100);

Dictionary<int, int> assignedDestination;
assignedDestination = std::move(destination);

assert(destination.isEmpty());
assert(destination.size() == 0);
assert(assignedDestination.size() == 2);
assert(assignedDestination.at(20) == 200);

std::cout << "Rule of Five move tests passed!\n";
    return 0;
}
