#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <iostream>

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

        // This is what it means for two edges to be equal
        bool operator==(const Edge &other) const
        {
            return (src == other.src && dest == other.dest && weight == other.weight) || (src == other.dest && dest == other.src && weight == other.weight);
        };

        bool operator<(const Edge &other) const
        {
            if (weight != other.weight)
            {
                return weight < other.weight;
            }
            if (src != other.src)
            {
                return src < other.src;
            }
            return dest < other.dest;
        }
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

    void print() const
    {
        std::cout << "Minimum Spanning Tree (MST) - Total Weight: " << totalWeight << "\n";
        std::cout << "Edges:\n";
        for (const auto &edge : edges)
        {
            std::cout << "Edge from " << edge.src << " to " << edge.dest << " with weight " << edge.weight << "\n";
        }
    }
};

#endif