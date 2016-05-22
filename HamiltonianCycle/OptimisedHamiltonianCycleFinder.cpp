#include "OptimisedHamiltonianCycleFinder.h"

#include <vector>
#include <iostream> /////////////////////////


std::vector<unsigned int> OptimisedHamiltonianCycleFinder::findFirstIn(const Graph& G)
{
    std::vector<std::vector<unsigned int>> results;
    std::vector<unsigned int> cycle(G.vertexCount + 1, 0);

    foundFirst = false;
    recursiveImplementation(G, results, cycle, 1, G.vertexCount, true);

    if(results.empty())
        return {};
    else
        return results.front();
}

std::vector<std::vector<unsigned int>> OptimisedHamiltonianCycleFinder::findAllIn(const Graph& G)
{
    std::vector<std::vector<unsigned int>> results;
    std::vector<unsigned int> cycle(G.vertexCount + 1, 0);

    foundFirst = false;
    recursiveImplementation(G, results, cycle, 1, G.vertexCount, false);

    return results;
}

bool OptimisedHamiltonianCycleFinder::isAlreadyVisited(
    const std::vector<unsigned int>& cycle,
    unsigned int vertex,
    unsigned int currentVertex)
{
    for(unsigned int i = 0; i < currentVertex; ++i)
        if(cycle[i] == vertex)
            return true;

    return false;
}

void OptimisedHamiltonianCycleFinder::recursiveImplementation(
    const Graph& G,
    std::vector<std::vector<unsigned int>>& results,
    std::vector<unsigned int>& cycle,
    unsigned int currentVertex,
    unsigned int vertices,
    bool stopOnFirst)
{
    if(foundFirst && stopOnFirst)
        return;

    auto neighbours = G.neighboursOf(cycle[currentVertex - 1]);
    auto nextVertex = currentVertex + 1u;

    for(const auto& neighbour : neighbours)
    {
        cycle[currentVertex] = neighbour;

        if(currentVertex == vertices && neighbour == cycle.front())
        {
            results.push_back(cycle);

            if(stopOnFirst)
            {
                foundFirst = true;
                return;
            }
        }

        if(!isAlreadyVisited(cycle, neighbour, currentVertex))
            recursiveImplementation(G, results, cycle, nextVertex, vertices, stopOnFirst);
    }
}
