#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "Graph.hpp"
#include "algorithm"
#include "unordered_map"

MST kruskal_mst(Graph &graph);

class UnionFind
{
public:
    std::unordered_map<int, int> parent;

    int find(int u)
    {
        if (parent.find(u) == parent.end())
        {
            return u;
        }

        if (parent[u] != u)
        {
            parent[u] = find(parent[u]);
        }

        return parent[u];
    }

    void merge(int u, int v)
    {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV)
        {
            parent[rootU] = rootV;
        }
    }
};

#endif