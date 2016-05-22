#pragma once

#include "Graph.h"

#include <string>
#include <vector>


class HamiltonianCycleFinder
{
public:
    HamiltonianCycleFinder(std::string name) : name(name) { }
    virtual ~HamiltonianCycleFinder() { }

    virtual std::vector<unsigned int> findFirstIn(const Graph& G) = 0;
    virtual std::vector<std::vector<unsigned int>> findAllIn(const Graph& G) = 0;

    const std::string name;
};
