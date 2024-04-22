#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <set>
#include <sstream>

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

    // An optional name for the graph
    std::string name;
    // Create an adjacency list.
    std::vector<std::vector<std::pair<int, int>>> adjList;

    explicit Graph(int verts, const std::string &graphName = "") : adjList(verts), name(graphName) {}

    void addEdge(int src, int dest, int weight)
    {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight});
    }

    int vertNumber() const
    {
        return adjList.size();
    }

    int edgeCount() const
    {
        int count = 0;
        for (const auto &neighbors : adjList)
        {
            count += neighbors.size();
        }
        return count / 2;
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

inline std::string graphToDot(const Graph &graph, const std::string &graphName = "Graph"){
    std::stringstream stream;
    stream << "graph "<< graphName << "{\n";
    for(size_t i=0; i < graph.adjList.size(); i++) {
        for (const auto& edge : graph.adjList[i]) {
            if(i < edge.first) {
                stream << "    " << i << " -- " << edge.first << " [label=\"" << edge.second << "\"];\n";
            }
        }
    }
    stream << "}\n";
    return stream.str();
}

inline std::string mstToDot(const Graph& graph, const MST& mst, const std::string& mstName = "MST") {
    std::stringstream stream;
    stream << "graph " << mstName << " {\n";
    stream << "    label=\"Minimum Spanning Tree (Total Weight: " << mst.totalWeight << ")\";\n";

    // Create a set of MST edges for quick lookup
    std::set<Graph::Edge> mstEdges(mst.edges.begin(), mst.edges.end());

    // Iterate over all vertices and their adjacency list
    for(size_t i = 0; i < graph.adjList.size(); i++) {
        for (const auto& edge : graph.adjList[i]) {
            if(i < edge.first) { // This check ensures each edge is added only once (undirected graph)
                // Check if this edge is in the MST
                Graph::Edge tempEdge(i, edge.first, edge.second);
                bool isMstEdge = mstEdges.count(tempEdge) > 0;

                // Output edge with color red if it's part of the MST, otherwise default (black)
                stream << "    " << i << " -- " << edge.first;
                stream << " [label=\"" << edge.second << "\", color=" << (isMstEdge ? "red" : "black") << "];\n";
            }
        }
    }

    stream << "}\n";
    return stream.str();
}


Graph loadGraphFromFile(const std::string &file);
bool serializeGraphToFile(Graph &graph, std::string &graphName, const std::string &file);

#endif
