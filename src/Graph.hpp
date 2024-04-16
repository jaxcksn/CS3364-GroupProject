#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>

/**
 * Representation of a graph as an adjacency list. Might prove useful to convert this to
 * an edge list or adjacency matrix as needed.
 */
class Graph
{
public:
    struct Edge
    {
        int src, dest, weight;
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

        bool operator==(const Edge &other) const
        {
            return (src == other.src && dest == other.dest && weight == other.weight);
        };
    };

    // Create an adjacency list.
    std::vector<std::vector<std::pair<int, int>>> adjList;

    explicit Graph(int verts) : adjList(verts) {}

    void addEdge(int src, int dest, int weight)
    {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight});
    }

    int vertNumber() const
    {
        return adjList.size();
    }
};

/**
 * Shared minimum spanning tree representation
 */
struct MST
{
    std::vector<Graph::Edge> edges;
    int totalWeight = 0;
};

#endif