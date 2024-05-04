#define CATCH_CONFIG_MAIN
#include "Catch2.hpp"
#include "algorithm"
#include "../src/prim.hpp"
#include "../src/graph.hpp"

using namespace std;

TEST_CASE("Prim's Algorithm: Sparse Graph", "[prim_mst]")
{
    Graph graph(10);
    graph.addEdge(0, 9, 9);
    graph.addEdge(0, 8, 8);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 7, 6);
    graph.addEdge(1, 5, 4);
    graph.addEdge(2, 6, 10);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 5, 5);
    graph.addEdge(2, 7, 6);
    graph.addEdge(3, 5, 10);
    graph.addEdge(3, 7, 10);
    graph.addEdge(4, 8, 9);
    graph.addEdge(5, 9, 4);
    graph.addEdge(6, 7, 4);

    int expectedWeight = 50;

    vector<Graph::Edge> mstEdges{
        Graph::Edge(0, 8, 8),
        Graph::Edge(0, 2, 8),
        Graph::Edge(1, 5, 4),
        Graph::Edge(2, 3, 2),
        Graph::Edge(2, 5, 5),
        Graph::Edge(2, 7, 6),
        Graph::Edge(4, 8, 9),
        Graph::Edge(5, 9, 4),
        Graph::Edge(6, 7, 4),
    };

    auto mst = prim_mst(graph);

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
