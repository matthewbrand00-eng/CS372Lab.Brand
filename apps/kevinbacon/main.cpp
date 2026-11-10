
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "AdjListGraph.hpp"
#include "AdjMatrixGraph.hpp"
#include "GraphAlgorithms.h"

using namespace std;

// Tests the same cycle function against both graph types.
void testCycles(Graph<int>& graph)
{
    for (int i = 1; i <= 5; ++i)
        graph.addNode(i);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
    graph.addEdge(4, 5);

    assert(isSimpleCycle(graph, {1, 2, 3, 4, 1}));

    // Does not return to the beginning.
    assert(!isSimpleCycle(graph, {1, 2, 3, 4}));

    // Edge 3 -> 1 does not exist.
    assert(!isSimpleCycle(graph, {1, 2, 3, 1}));

    // Vertex 2 is visited twice.
    assert(!isSimpleCycle(graph, {1, 2, 3, 2, 3, 4, 1}));

    // Missing vertex.
    assert(!isSimpleCycle(graph, {1, 2, 99, 1}));

    // A self-loop is not a simple cycle here.
    graph.addEdge(5, 5);
    assert(!isSimpleCycle(graph, {5, 5}));

    assert(!isSimpleCycle(graph, {}));
}

// Friendships are represented in both directions.
void addFriendship(Graph<string>& graph,
                   const string& a,
                   const string& b)
{
    graph.addEdge(a, b);
    graph.addEdge(b, a);
}

void testSocialGraph(Graph<string>& graph)
{
    // Fictional example network for the assignment.
    // It does not claim these are real-world friendships.
    vector<string> people = {
        "Matthew",        // 0
        "Friend 1",       // 1
        "Friend 2",       // 2
        "Actor A",        // 3
        "Actor B",        // 4
        "Friend 3",       // 5
        "Friend 4",       // 6
        "Friend 5",       // 7
        "Friend 6",       // 8
        "Friend 7",       // 9
        "Friend 8",       // 10
        "Friend 9",       // 11
        "Friend 10",      // 12
        "Friend 11",      // 13
        "Friend 12",      // 14
        "Friend 13",      // 15
        "Friend 14",      // 16
        "Friend 15",      // 17
        "Friend 16",      // 18
        "Kevin Bacon"     // 19
    };

    for (const auto& person : people)
        graph.addNode(person);

    assert(graph.getNodes().size() == 20);

    // Main connection chain.
    addFriendship(graph, "Matthew", "Friend 1");
    addFriendship(graph, "Friend 1", "Friend 2");
    addFriendship(graph, "Friend 2", "Actor A");
    addFriendship(graph, "Actor A", "Actor B");
    addFriendship(graph, "Actor B", "Kevin Bacon");

    // Additional connections in the social network.
    for (int i = 5; i <= 18; ++i)
        addFriendship(graph, people[i], "Friend 1");

    vector<string> path;

    bool connected = connectedToKevinBacon(
        graph, string("Matthew"), string("Kevin Bacon"), path);

    assert(connected);
    assert(path.front() == "Matthew");
    assert(path.back() == "Kevin Bacon");
    assert(path.size() == 6);

    // Number of connections (edges), not number of people.
    cout << "Kevin Bacon number: " << path.size() - 1 << '\n';

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i > 0)
            cout << " -> ";
        cout << path[i];
    }
    cout << '\n';

    // Verify the disconnected case.
    graph.addNode("Disconnected Person");
    path = {"Old result"};

    assert(!connectedToKevinBacon(
        graph, string("Disconnected Person"),
        string("Kevin Bacon"), path));
    assert(path.empty());
}

int main()
{
    AdjListGraph<int> listGraph;
    testCycles(listGraph);
    cout << "Adjacency-list cycle tests passed!\n";

    AdjMatrixGraph<int> matrixGraph;
    testCycles(matrixGraph);
    cout << "Adjacency-matrix cycle tests passed!\n";

    AdjListGraph<string> socialList;
    cout << "\nAdjacency-list social graph:\n";
    testSocialGraph(socialList);

    AdjMatrixGraph<string> socialMatrix;
    cout << "\nAdjacency-matrix social graph:\n";
    testSocialGraph(socialMatrix);

    cout << "\nAll Assignment 7 tests passed!\n";
    return 0;
}
