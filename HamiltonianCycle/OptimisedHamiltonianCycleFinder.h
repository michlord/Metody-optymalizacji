#pragma once

#include "HamiltonianCycleFinder.h"

#include <vector>


class OptimisedHamiltonianCycleFinder : public HamiltonianCycleFinder
{
public:
    OptimisedHamiltonianCycleFinder(std::string name) : HamiltonianCycleFinder(name) { }
    virtual ~OptimisedHamiltonianCycleFinder() { }

    std::vector<unsigned int> findFirstIn(const Graph& G);
    std::vector<std::vector<unsigned int>> findAllIn(const Graph& G);

private:
    bool isAlreadyVisited(
        const std::vector<unsigned int>& cycle,
        unsigned int vertex,
        unsigned int currentVertex);

    void recursiveImplementation(
        const Graph& G,
        std::vector<std::vector<unsigned int>>& results,
        std::vector<unsigned int>& cycle,
        unsigned int currentVertex,
        unsigned int vertices,
        bool stopOnFirst);

    bool foundFirst;
};
