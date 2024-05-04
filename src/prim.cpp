#include "graph.hpp"
#include "prim.hpp"
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <iostream>
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

    // Create a min heap to store the edges
    priority_queue<Graph::Edge, vector<Graph::Edge>, edgeCompare> edgeQueue;

    // Pick random vertex to Start
    int start = rand() % graph.vertNumber();
    // Initialize the visited set
    set<int> visited;
    // Add our starting vertex to the visited set
    visited.insert(start);

    cout << "Start: " << start << endl;

    // For each edge in the adjacency list for the start vertex
    for (const auto &[dest, weight] : graph.adjList[start])
    {
        // We'll add it to the min heap
        edgeQueue.emplace(Graph::Edge(start, dest, weight));
    }

    // Loop until the MST is full or our queue is empty.
    while (mst.edges.size() < graph.vertNumber() - 1)
    {
        // Get the minimum weight edge
        Graph::Edge edge = edgeQueue.top();
        // Remove the edge from the queue
        edgeQueue.pop();

        // If the vertex is already in the MST, skip it
        if (visited.count(edge.dest) == 0)
        {
            // Add the edge to our MST
            // Per our minimum spanning tree spec, the edge should always be from the lower vertex to the higher vertex.
            if (edge.src > edge.dest)
                mst.edges.push_back(Graph::Edge(edge.dest, edge.src, edge.weight));
            else
                mst.edges.push_back(edge);

            mst.totalWeight += edge.weight;
            // Mark the destination vertex as visited.
            visited.insert(edge.dest);
            // For all adjacent edges from the edge destination vertex
            for (const auto &[dest, weight] : graph.adjList[edge.dest])
            {
                // The destination of adjacent edge is not in the visited set
                if (visited.count(dest) == 0)
                {
                    // Add the edge to the min heap
                    edgeQueue.emplace(Graph::Edge(edge.dest, dest, weight));
                }
            }
        }
    }
    return mst;
}
