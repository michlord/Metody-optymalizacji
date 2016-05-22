#include "NaiveHamiltonianCycleFinder.h"

#include <algorithm>
#include <vector>

#include <iostream> ///////////////////////////////////////////////////////////////////


std::vector<unsigned int> NaiveHamiltonianCycleFinder::findFirstIn(const Graph& G)
{
    std::vector<std::vector<unsigned int>> results;
    std::vector<unsigned int> path(G.vertexCount);

    for(unsigned int i = 0; i < path.size(); ++i)
        path[i] = i;

    iterativeImplementation(G, results, path, true);

    if(results.empty())
        return {};
    else
        return results.front();
}

std::vector<std::vector<unsigned int>> NaiveHamiltonianCycleFinder::findAllIn(const Graph& G)
{
    std::vector<std::vector<unsigned int>> results;
    std::vector<unsigned int> path(G.vertexCount);

    for(unsigned int i = 0; i < path.size(); ++i)
        path[i] = i;

    iterativeImplementation(G, results, path, false);

    return results;
}

bool NaiveHamiltonianCycleFinder::isPath(const Graph& G, const std::vector<unsigned int>& path)
{
    for(std::size_t index = 0; index < path.size() - 1; ++index)
        if(G.hasEdge(path[index], path[index + 1]) == false)
            return false;

    return true;
}

bool NaiveHamiltonianCycleFinder::isExtendableToCycle(const Graph& G, const std::vector<unsigned int>& path)
{
    return G.hasEdge(path.back(), path.front());
}

void NaiveHamiltonianCycleFinder::iterativeImplementation(
    const Graph& G,
    std::vector<std::vector<unsigned int>>& results,
    const std::vector<unsigned int>& path,
    bool stopOnFirst)
{
    auto currentPath = path;

    do
    {
        if(isPath(G, currentPath) && isExtendableToCycle(G, currentPath)) {
            auto currentCycle = currentPath;
            currentCycle.push_back(currentPath.front());

            results.push_back(currentCycle);

            if(stopOnFirst)
                return;
        }

    } while(std::next_permutation(++currentPath.begin(), currentPath.end()));
}
