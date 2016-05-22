#include "RandomGraphFactory.h"

#include <random>


Graph RandomGraphFactory::generate(unsigned int vertexCount, unsigned int edgeCount)
{
    Graph G { vertexCount };

    for(unsigned int edgeId = 0; edgeId < edgeCount; ++edgeId)
    {
        bool added = false;

        do {
            unsigned int v = rand() % vertexCount;
            unsigned int u = rand() % vertexCount;

            if(v != u && G.hasEdge(v, u) == false)
            {
                G.addEdge(v, u);
                added = true;
            }
        } while(!added);
    }

    return G;
}
