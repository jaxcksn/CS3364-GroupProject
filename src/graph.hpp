#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>

/**
 * @brief Represents a graph data structure.
 * 
 * This class provides functionality to create and manipulate a graph using an adjacency list representation.
 */
class Graph {
public:
    /**
     * @brief Represents an edge in the graph.
     */
    struct Edge {
        int src; /**< The source vertex of the edge. */
        int dest; /**< The destination vertex of the edge. */
        int weight; /**< The weight of the edge. */

        /**
         * @brief Constructs an Edge object.
         * 
         * @param s The source vertex of the edge.
         * @param d The destination vertex of the edge.
         * @param w The weight of the edge.
         */
        Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

        /**
         * @brief Checks if two edges are equal.
         * 
         * Two edges are considered equal if they have the same source, destination, and weight.
         * 
         * @param other The other edge to compare with.
         * @return True if the edges are equal, false otherwise.
         */
        bool operator==(const Edge &other) const {
            return (src == other.src && dest == other.dest && weight == other.weight) || 
                   (src == other.dest && dest == other.src && weight == other.weight);
        };

        /**
         * @brief Compares two edges.
         * 
         * Edges are compared based on their weights. If the weights are equal, the source vertex is compared.
         * If the source vertices are equal, the destination vertex is compared.
         * 
         * @param other The other edge to compare with.
         * @return True if this edge is less than the other edge, false otherwise.
         */
        bool operator<(const Edge &other) const {
            if (weight != other.weight) {
                return weight < other.weight;
            }
            if (src != other.src) {
                return src < other.src;
            }
            return dest < other.dest;
        }

        /**
         * @brief Compares two edges.
         * 
         * Edges are compared based on their weights. If the weights are equal, the source vertex is compared.
         * If the source vertices are equal, the destination vertex is compared.
         * 
         * @param other The other edge to compare with.
         * @return True if this edge is greater than the other edge, false otherwise.
         */
        bool operator>(const Edge &other) const {
            if (weight != other.weight) {
                return weight > other.weight;
            }
            if (src != other.src) {
                return src > other.src;
            }
            return dest > other.dest;
        }
    };

    std::string name; /**< An optional name for the graph. */
    std::vector<std::vector<std::pair<int, int>>> adjList; /**< The adjacency list representation of the graph. */

    /**
     * @brief Constructs a Graph object with the specified number of vertices and an optional name.
     * 
     * @param verts The number of vertices in the graph.
     * @param graphName The name of the graph (optional).
     */
    explicit Graph(int verts, const std::string &graphName = "") : name(graphName), adjList(verts) {}

    /**
     * @brief Adds an edge to the graph.
     * 
     * @param src The source vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @param weight The weight of the edge.
     */
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back({dest, weight});
        adjList[dest].push_back({src, weight});
    }

    /**
     * @brief Gets the number of vertices in the graph.
     * 
     * @return The number of vertices in the graph.
     */
    int vertNumber() const {
        return adjList.size();
    }

    /**
     * @brief Gets the number of edges in the graph.
     * 
     * @return The number of edges in the graph.
     */
    int edgeCount() const {
        int count = 0;
        for (const auto &neighbors : adjList) {
            count += neighbors.size();
        }
        return count / 2;
    }
};

/**
 * Shared minimum spanning tree representation
 */
struct MST
/**
 * @brief Represents a graph with a minimum spanning tree (MST).
 */
{
    std::vector<Graph::Edge> edges; /**< The edges of the graph. */
    int totalWeight = 0; /**< The total weight of the minimum spanning tree. */

    /**
     * @brief Prints the minimum spanning tree (MST) information.
     */
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

/**
 * Serializes the Minimum Spanning Tree (MST) into a string representation.
 * 
 * @param mst The Minimum Spanning Tree to be serialized.
 * @return A string representation of the MST.
 */
inline std::string serializeMST(const MST &mst)
{
    std::stringstream ss;
    ss << "[ ";
    for (size_t i = 0; i < mst.edges.size(); ++i)
    {
        const auto &edge = mst.edges[i];

        ss << edge.src << " " << edge.dest << " " << edge.weight;
        if (i < mst.edges.size() - 1)
        {
            ss << ", ";
        }
        else
        {
            ss << " ]";
        }
    }
    return ss.str();
}

/**
 * Converts a graph to a DOT string representation.
 * 
 * @param graph The graph to convert.
 * @param graphName The name of the graph (optional).
 * @return The DOT string representation of the graph.
 */
inline std::string graphToDot(const Graph &graph, const std::string &graphName = "G")
{
    std::stringstream stream;
    stream << "graph " << graphName << "{\n";
    stream << "graph [overlap=false, scale=2, size=\"8.5!,\", splines=true]; node [fontname=Aptos, fontsize=12, height=0.25, margin=0, shape=circle, width=0.25,]; edge [color=grey38, fontname=\"Aptos bold\",fontsize=5];" << std::endl;
    for (size_t i = 0; i < graph.adjList.size(); i++)
    {
        for (const auto &edge : graph.adjList[i])
        {
            if (i < edge.first)
            {
                stream << "    " << i << " -- " << edge.first << " [label=\"" << edge.second << "\"];\n";
            }
        }
    }
    stream << "}\n";
    return stream.str();
}


/**
 * Loads a graph from a file.
 * 
 * @param file The path to the file containing the graph data.
 * @return The loaded graph.
 */
inline Graph loadGraphFromFile(const std::string &file)
{
    std::ifstream inputFile(file);
    if (!inputFile)
    {
        std::cerr << "Error loading graph file.";
        return Graph(0);
    }
    std::string graphName;
    inputFile >> graphName;

    int verts, src, dest, weight;
    // Get number of verticies
    inputFile >> verts;

    Graph graph(verts, graphName);
    while (inputFile >> src >> dest >> weight)
    {
        graph.addEdge(src, dest, weight);
    }

    inputFile.close();
    return graph;
}


/**
 * Generates a Graphviz representation of the Minimum Spanning Tree (MST) of a given graph.
 * The generated representation can be used to visualize the MST using Graphviz tools.
 *
 * @param graph The graph for which the MST is generated.
 * @param mst The Minimum Spanning Tree of the graph.
 * @param mstName The name of the MST (optional). Default value is "MST".
 * @return A string containing the Graphviz representation of the MST.
 */
inline std::string mstToDot(const Graph &graph, const MST &mst, const std::string &mstName = "MST")
{   
    //NOTE: This function is complicated, and requires an understanding of graphviz syntax.
    std::stringstream stream;
    stream << "graph " << mstName << " {\n";
    stream << "graph [overlap=false, scale=2, size=\"8.5!,\", splines=true]; node [fontname=Aptos, fontsize=12, height=0.25, margin=0, shape=circle, width=0.25,]; edge [color=grey38, fontname=\"Aptos bold\",fontsize=5];" << std::endl;

    // Create a set of MST edges for quick lookup
    std::set<Graph::Edge> mstEdges(mst.edges.begin(), mst.edges.end());

    // Vector to store all edges for sorting
    std::vector<std::tuple<size_t, size_t, int>> edges;

    // Iterate over all vertices and their adjacency list to collect edges
    for (size_t i = 0; i < graph.adjList.size(); i++)
    {
        for (const auto &edge : graph.adjList[i])
        {
            if (i < edge.first)
            { // Ensure each edge is added only once
                edges.emplace_back(i, edge.first, edge.second);
            }
        }
    }

    // Sort edges
    std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b)
              { return std::tie(std::get<0>(a), std::get<1>(a)) < std::tie(std::get<0>(b), std::get<1>(b)); });

    // Generate Graphviz output for sorted edges
    for (const auto &edge : edges)
    {
        size_t from = std::get<0>(edge), to = std::get<1>(edge);
        int weight = std::get<2>(edge);
        Graph::Edge tempEdge(from, to, weight);
        bool isMstEdge = mstEdges.count(tempEdge) > 0;

        // Output edge with specific formatting if it's part of the MST
        stream << "    " << from << " -- " << to;
        stream << " [label=\"" << (isMstEdge ? std::to_string(weight) : "") << "\", color=" << (isMstEdge ? "firebrick;" : "gray70;") << (isMstEdge ? " fontcolor=black, fontsize=7," : "") << "];\n";
    }

    stream << "}\n";
    return stream.str();
}



#endif
