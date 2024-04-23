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

inline std::string serializeMST(const MST &mst) {
    std::stringstream ss;
    ss << "[ ";
    for (size_t i = 0; i < mst.edges.size(); ++i) {
        const auto& edge = mst.edges[i];
        
        ss << edge.src << " " << edge.dest << " " << edge.weight;
        if (i < mst.edges.size() - 1) {
            ss << ", ";
        } else {
            ss << " ]";
        }
    }
    return ss.str();
}


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



inline std::string mstToDot(const Graph &graph, const MST &mst, const std::string &mstName = "MST")
{
    std::stringstream stream;
    stream << "graph " << mstName << " {\n";
    stream << "graph [overlap=false, scale=2, size=\"8.5!,\", splines=true]; node [fontname=Aptos, fontsize=12, height=0.25, margin=0, shape=circle, width=0.25,]; edge [color=grey38, fontname=\"Aptos bold\",fontsize=5];" << std::endl;

   // Create a set of MST edges for quick lookup
    std::set<Graph::Edge> mstEdges(mst.edges.begin(), mst.edges.end());

    // Vector to store all edges for sorting
    std::vector<std::tuple<size_t, size_t, int>> edges;

    // Iterate over all vertices and their adjacency list to collect edges
    for (size_t i = 0; i < graph.adjList.size(); i++) {
        for (const auto &edge : graph.adjList[i]) {
            if (i < edge.first) {  // Ensure each edge is added only once
                edges.emplace_back(i, edge.first, edge.second);
            }
        }
    }

    // Sort edges
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return std::tie(std::get<0>(a), std::get<1>(a)) < std::tie(std::get<0>(b), std::get<1>(b));
    });

    // Generate Graphviz output for sorted edges
    for (const auto& edge : edges) {
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

Graph loadGraphFromFile(const std::string &file);
bool serializeGraphToFile(Graph &graph, std::string &graphName, const std::string &file);

#endif
