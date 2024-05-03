#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "graph.hpp"
#include "algorithm"
#include "unordered_map"
#include <numeric>

using namespace std;
MST kruskal_mst(Graph &graph);

/**
 * This is just a simplier version of the Graph representation,
 * since Kruskal's algorithm really just needs an edge list only.
 */
class EdgeList
{

public:
    // The list of edges
    vector<Graph::Edge> list;
    explicit EdgeList(Graph g)
    {
        // For each vertex in the adjacency list
        for (int i = 0; i < g.vertNumber(); i++)
        {
            // For each edge in the vertex list
            for (const auto &[dest, weight] : g.adjList[i])
            {
                // Only include the first instance of the edge
                if (i < dest)
                {
                    // We'll add it to the vector
                    list.emplace_back(i, dest, weight);
                }
            }
        }
    }
};

/**
 * Implementation of a Union Find data structure, used by Kruskal's algorithm.
 */
class UnionFind
{
private:
    // The parent vector
    vector<int> parent;
    // The rank vector
    vector<int> rank;

public:
    // Constructor
    explicit UnionFind(int numElements) : parent(numElements), rank(numElements, 0)
    {
        // Fill the parent with integers.
        iota(parent.begin(), parent.end(), 0);
    }

    /**
     * Recursive implementation of Find algorithm for the Union Find
     */
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    /**
     * Rank based set union, called "merge" since `union` is a reserved word in C++
     */
    void merge(int x, int y)
    {
        int xRoot = find(x);
        int yRoot = find(y);

        if (rank[xRoot] > rank[yRoot])
        {
            parent[yRoot] = xRoot;
        }
        else if (rank[xRoot] < rank[yRoot])
        {
            parent[xRoot] = yRoot;
        }
        else
        {
            parent[yRoot] = xRoot;
            rank[xRoot] += 1;
        }
    }
};

#endif