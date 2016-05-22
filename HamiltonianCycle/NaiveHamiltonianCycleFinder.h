#pragma once

#include "HamiltonianCycleFinder.h"

#include <vector>


class NaiveHamiltonianCycleFinder : public HamiltonianCycleFinder
{
public:
    NaiveHamiltonianCycleFinder(std::string name) : HamiltonianCycleFinder(name) { }
    virtual ~NaiveHamiltonianCycleFinder() { }

    std::vector<unsigned int> findFirstIn(const Graph& G);
    std::vector<std::vector<unsigned int>> findAllIn(const Graph& G);

private:
    bool isPath(const Graph& G, const std::vector<unsigned int>& path);
    bool isExtendableToCycle(const Graph& G, const std::vector<unsigned int>& path);

    void iterativeImplementation(
        const Graph& G,
        std::vector<std::vector<unsigned int>>& results,
        const std::vector<unsigned int>& path,
        bool stopOnFirst);
};
