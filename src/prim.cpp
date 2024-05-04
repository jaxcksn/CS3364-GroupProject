#include "graph.hpp"
#include "prim.hpp"
#include <vector>
#include <queue>
#include <limits>
using namespace std;

/**
 * Implementation of Prim's Algorithm
 *
 * @param graph The graph to perform the algorithm on
 * @return A `MST` object with the minimum spanning tree of the graph
 */
MST prim_mst(const Graph& graph) {
    // Declare the MST
    MST mst;

    // Create a vector to store the minimum weight edges
    vector<Graph::Edge> minEdges(graph.vertNumber());

    // Create a priority queue to store the edges
    priority_queue<Graph::Edge, vector<Graph::Edge>, greater<Graph::Edge>> edgeQueue;

    // Initialize all minimum weights to infinity
    for (int i = 0; i < graph.vertNumber(); ++i) {
        minEdges[i].weight = numeric_limits<double>::infinity();
    }

    // Start with vertex 0
    minEdges[0].weight = 0;
    edgeQueue.push({ 0, 0, 0.0 });  // Dummy edge for vertex 0

    while (!edgeQueue.empty()) {
        // Get the minimum weight edge
        Graph::Edge edge = edgeQueue.top();
        edgeQueue.pop();

        // If the vertex is already in the MST, skip it
        if (minEdges[edge.dest].weight < numeric_limits<double>::infinity()) {
            continue;
        }

        // Add the edge to the MST
        mst.edges.push_back(edge);
        mst.totalWeight += edge.weight;

        // Update the minimum weights for the adjacent vertices
        for (const auto& adj : graph.adjList[edge.dest]) {
            int adjVertex = adj.first;
            int weight = adj.second;
            if (minEdges[adjVertex].weight == numeric_limits<double>::infinity()) {
                minEdges[adjVertex].src = edge.dest;
                minEdges[adjVertex].dest = adjVertex;
                minEdges[adjVertex].weight = weight;
                edgeQueue.push(minEdges[adjVertex]);
            }
        }
    }

    return mst;
}
