#include "graph.hpp"
#include "kruskal.hpp"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Implementation of Kruskal's Algorithm
 *
 * @param graph The graph to perform the algorithm on
 * @return A `MST` object with the minimum spanning tree of the graph
 */
MST kruskal_mst(Graph &graph)
{
    // Declare the MST
    MST mst;
    // Change the Graph class to an EdgeList
    EdgeList edges(graph);
    // Create a union find data structure
    UnionFind unionFind(graph.vertNumber());

    // We'll sort the edge list by weight, using the sort function
    sort(edges.list.begin(), edges.list.end(), [](const Graph::Edge &a, const Graph::Edge &b)
         { return a.weight < b.weight; });

    // For every edge in the edge list
    for (const auto &edge : edges.list)
    {
        /*
        This is the check to see if we have already connected the to the MST, since we are going from smallest weight,
        if we have already have an edge in the MST going to the node, we should skip it since it will
        create a cycle.
        */
        if (unionFind.find(edge.src) != unionFind.find(edge.dest))
        {
            // Union their sets together
            unionFind.merge(edge.src, edge.dest);
            // Add the edge to the MST
            mst.edges.push_back(edge);
            // Increment the total weight
            mst.totalWeight += edge.weight;

            if (mst.edges.size() == graph.vertNumber() - 1)
            {
                // We've reached full size for the MST, we can exit now.
                break;
            }
        }
    }

    // Return our MST
    return mst;
}
