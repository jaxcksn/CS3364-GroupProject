#include "Graph.hpp"
#include "kruskal.hpp"
#include <vector>
#include <algorithm>

using namespace std;

MST kruskal_mst(Graph &graph)
{
    MST mst;
    EdgeList edges(graph);
    UnionFind unionFind(graph.vertNumber());

    // We'll sort the edge list by weight, using the sort function
    sort(edges.list.begin(), edges.list.end(), [](const Graph::Edge &a, const Graph::Edge &b)
         { return a.weight < b.weight; });

    for (const auto &edge : edges.list)
    {
        if (unionFind.find(edge.src) != unionFind.find(edge.dest))
        {
            unionFind.merge(edge.src, edge.dest);
            mst.edges.push_back(edge);
            mst.totalWeight += edge.weight;

            if (mst.edges.size() == graph.vertNumber() - 1)
            {
                // We've reached full size for the MST, we can exit now.
                break;
            }
        }
    }

    return mst;
}
