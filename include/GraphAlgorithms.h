
#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include "Graph.hpp"
#include <algorithm>
#include <set>
#include <vector>

// Part 2: Check whether a path is a simple cycle.
inline bool isSimpleCycle(
    const Graph<int>& graph,
    const std::vector<int>& path)
{
    // At least two distinct vertices plus the return to start.
    if (path.size() < 3 || path.front() != path.back())
        return false;

    std::set<int> visited;

    for (std::size_t i = 0; i + 1 < path.size(); ++i)
    {
        if (!graph.hasNode(path[i]))
            return false;

        // Only the final element may repeat the start.
        if (!visited.insert(path[i]).second)
            return false;

        if (!graph.adjacent(path[i], path[i + 1]))
            return false;
    }

    return true;
}

// Part 3: Find the shortest social-graph connection.
// The output path includes both the starting person
// and Kevin Bacon. Returns false with an empty path
// when no connection exists.
template <typename N>
bool connectedToKevinBacon(
    const Graph<N>& graph,
    const N& person,
    const N& kevinBacon,
    std::vector<N>& path)
{
    path.clear();

    if (!graph.hasNode(person) || !graph.hasNode(kevinBacon))
        return false;

    // Use the BFS implementation from the professor's Graph class.
    auto parents = graph.bfs(person);

    if (parents.find(kevinBacon) == parents.end())
        return false;

    N current = kevinBacon;
    path.push_back(current);

    while (current != person)
    {
        current = parents.at(current);
        path.push_back(current);
    }

    std::reverse(path.begin(), path.end());
    return true;
}

#endif
