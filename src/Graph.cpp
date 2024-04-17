#include "Graph.hpp"
#include <string>
#include <iostream>
#include <fstream>

/**
 * Saves a graph to a serialized .graph file.
 */
bool serializeGraphToFile(Graph &graph, const std::string &file)
{
    // Create an output file stream
    std::ofstream outputFile(file);
    // Check to make sure the point is valid
    if (!outputFile)
    {
        // Print to the error stream
        std::cerr << "Could not output graph file";
        return false;
    }

    // First line will be graph size.
    outputFile << graph.adjList.size() << std::endl;
    // Now for each edge, we'll add a new line

    // We'll now go through the adjacency list
    for (int i = 0; i < graph.adjList.size(); i++)
    {
        for (const auto &edge : graph.adjList[i])
        {
            // Our graphs are undirected so we can disregard the duplicate edges
            if (i < edge.first)
            {
                outputFile << i << " " << edge.first << " " << edge.second << std::endl;
            }
        }
    }
    // Close the file stream to avoid memory leaks
    outputFile.close();
    return true;
}

/**
 * Loads a graph from a file for easy use, if the file can't be loaded
 * it will be output a Graph with zero verts, so make sure to add a check
 * for this after using the vertNumber() function.
 */
Graph loadGraphFromFile(const std::string &file)
{
    std::ifstream inputFile(file);
    if (!inputFile)
    {
        std::cerr << "Error loading graph file.";
        return Graph(0);
    }

    int verts, src, dest, weight;
    // Get number of verticies
    inputFile >> verts;

    Graph graph(verts);
    while (inputFile >> src >> dest >> weight)
    {
        graph.addEdge(src, dest, weight);
    }

    inputFile.close();
    return graph;
}