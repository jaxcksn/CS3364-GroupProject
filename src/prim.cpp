#include "graph.hpp"
#include "prim.hpp"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <unordered_set>
using namespace std;

// Used in the minimum heap to compare the weight of two edges.
class edgeCompare
{
public:
    // Compare the weight of two edges
    int operator()(const Graph::Edge &a, const Graph::Edge &b)
    {
        return a.weight > b.weight;
    }
};

/**
 * Implementation of Prim's Algorithm
 *
 * @param graph The graph to perform the algorithm on
 * @return A `MST` object with the minimum spanning tree of the graph
 */
MST prim_mst(Graph &graph)
{
    // Declare the MST
    MST mst;

    // Initialize the visited set (unordered for O(1) lookup time)
    unordered_set<int> visited;

    // Needed for the min binary heap
    vector<int> key(graph.vertNumber(), INT_MAX);
    vector<Graph::Edge> edges;

    // Pick random vertex to Start
    int start = rand() % graph.vertNumber();
    key[start] = 0;

    // Add a dummy edge to the queue to start the algorithm
    edges.push_back(Graph::Edge(-1, start, 0));

    // Loop until the MST is full or our queue is empty.
    while (!edges.empty())
    {
        // Get the minimum weight edge
        Graph::Edge edge = edges.front();
        // Remove the edge from the queue
        pop_heap(edges.begin(), edges.end(), edgeCompare());
        edges.pop_back();

        // If the vertex is already in the MST, skip it
        if (visited.count(edge.dest) == 0)
        {
            // Add the edge to our MST
            // Per our minimum spanning tree spec, the edge should always be from the lower vertex to the higher vertex.
            if (edge.src != -1)
            {
                if (edge.src > edge.dest)
                    mst.edges.push_back(Graph::Edge(edge.dest, edge.src, edge.weight));
                else
                    mst.edges.push_back(edge);
            }

            mst.totalWeight += edge.weight;
            // Mark the destination vertex as visited.
            visited.insert(edge.dest);
            // For all adjacent edges from the edge destination vertex
            for (const auto &[dest, weight] : graph.adjList[edge.dest])
            {
                // The destination of adjacent edge is not in the visited set
                if (visited.count(dest) == 0 && weight < key[dest])
                {
                    // If we have a new minimum weight to reach a vertex, update the key and add the edge to the queue
                    key[dest] = weight;
                    edges.push_back(Graph::Edge(edge.dest, dest, weight));
                    push_heap(edges.begin(), edges.end(), edgeCompare());
                }
            }
        }
    }
    return mst;
}
