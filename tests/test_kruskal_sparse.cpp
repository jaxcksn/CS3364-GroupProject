#define CATCH_CONFIG_MAIN
#include "Catch2.hpp"
#include "../src/kruskal.hpp"
#include "algorithm"
#include "../src/Graph.hpp"

using namespace std;

TEST_CASE("Kruskals's Algorithm: Sparse Graph", "[kruskal_mst]")
{
    Graph graph(10);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 8, 10);
    graph.addEdge(1, 6, 9);
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 5);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 6, 10);
    graph.addEdge(3, 4, 8);
    graph.addEdge(3, 6, 9);
    graph.addEdge(4, 7, 10);
    graph.addEdge(4, 6, 4);
    graph.addEdge(5, 9, 4);
    graph.addEdge(7, 8, 7);
    graph.addEdge(7, 9, 2);

    int expectedWeight = 51;

    vector<Graph::Edge> mstEdges{
        Graph::Edge(0, 1, 10),
        Graph::Edge(0, 8, 10),
        Graph::Edge(1, 2, 4),
        Graph::Edge(2, 3, 2),
        Graph::Edge(3, 4, 8),
        Graph::Edge(4, 6, 4),
        Graph::Edge(5, 9, 4),
        Graph::Edge(7, 9, 2),
        Graph::Edge(7, 8, 7),
    };

    auto mst = kruskal_mst(graph);

    SECTION("Check Total Weight for Sparse Graph")
    {
        int totalWeight = mst.totalWeight;
        REQUIRE(totalWeight == expectedWeight);
    }

    SECTION("Check MST Edges for Sparse Graph")
    {
        if (!is_permutation(mstEdges.begin(), mstEdges.end(), mst.edges.begin(), mst.edges.end()))
        {
            WARN("MST Compairson Failed: A graph can have many MST values, so you may want to check the result.");
        }
    }
}
