#pragma once

#include <list>
#include <stdexcept>
#include <vector>


class Graph
{
public:
    Graph(unsigned int vertexCount);

    void addEdge(unsigned int v, unsigned int u) throw(std::out_of_range);
    void removeEdge(unsigned int v, unsigned int u) throw(std::out_of_range);

    bool hasEdge(unsigned int v, unsigned int u) const throw(std::out_of_range);
    std::vector<unsigned int> neighboursOf(unsigned int v) const throw(std::out_of_range);

    const unsigned int vertexCount;

private:
    void setEdge(unsigned int v, unsigned int u, bool value) throw(std::out_of_range);

    std::vector<std::vector<bool>> edges;
};


std::ostream& operator<<(std::ostream& stream, const Graph& G);
