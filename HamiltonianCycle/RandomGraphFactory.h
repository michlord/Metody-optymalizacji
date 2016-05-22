#pragma once

#include "Graph.h"


class RandomGraphFactory
{
public:
    static Graph generate(unsigned int vertexCount, unsigned int edgeCount);
};
