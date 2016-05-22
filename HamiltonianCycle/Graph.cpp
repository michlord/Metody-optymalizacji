#include "Graph.h"

#include <string>


Graph::Graph(unsigned int vertexCount) : vertexCount(vertexCount), edges({})
{
    edges.resize(vertexCount);

    for(auto& edgesRow : edges)
        edgesRow.resize(vertexCount, false);
}

void Graph::addEdge(unsigned int v, unsigned int u) throw(std::out_of_range)
{
    setEdge(v, u, true);
}

void Graph::removeEdge(unsigned int v, unsigned int u) throw(std::out_of_range)
{
    setEdge(v, u, false);
}

bool Graph::hasEdge(unsigned int v, unsigned int u) const throw(std::out_of_range)
{
    if(v < vertexCount && u < vertexCount)
        return edges[v][u];
    else
        throw std::out_of_range { "Out of range vertices: " + std::to_string(v) + ", " + std::to_string(u) };
}

std::vector<unsigned int> Graph::neighboursOf(unsigned int v) const throw(std::out_of_range)
{
    std::vector<unsigned int> neighbours;

    if(v >= vertexCount)
        throw std::out_of_range { "Out of range vertex: " + std::to_string(v) };

    for(std::size_t u = 0; u < edges[v].size(); ++u)
    {
        if(edges[v][u])
            neighbours.push_back(u);
    }

    return neighbours;
}

void Graph::setEdge(unsigned int v, unsigned int u, bool value) throw(std::out_of_range)
{
    if(v < vertexCount && u < vertexCount)
        edges[v][u] = value;
    else
        throw std::out_of_range { "Out of range vertices: " + std::to_string(v) + ", " + std::to_string(u) };
}

std::ostream& operator<<(std::ostream& stream, const Graph& G)
{
    for(unsigned int i = 0; i < G.vertexCount; ++i)
    {
        for(unsigned int j = 0; j < G.vertexCount; ++j)
            stream << (G.hasEdge(i, j) ? 1 : 0) << std::string(" ");

        stream << std::string("\n");
    }

    stream << std::string("\n");

    return stream;
}
