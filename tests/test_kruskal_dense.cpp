#define CATCH_CONFIG_MAIN
#include "Catch2.hpp"
#include "../src/kruskal.hpp"
#include <algorithm>
#include <set>
#include "../src/Graph.hpp"

using namespace std;

TEST_CASE("Kruskal's Algorithm: Dense Graph", "[kruskal_mst]")
{
    Graph graph(10);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 2);
    graph.addEdge(0, 3, 1);
    graph.addEdge(0, 4, 8);
    graph.addEdge(0, 6, 2);
    graph.addEdge(0, 7, 7);
    graph.addEdge(0, 8, 4);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 4);
    graph.addEdge(1, 5, 1);
    graph.addEdge(1, 6, 3);
    graph.addEdge(1, 7, 8);
    graph.addEdge(1, 8, 9);
    graph.addEdge(1, 9, 3);
    graph.addEdge(2, 4, 5);
    graph.addEdge(2, 5, 10);
    graph.addEdge(2, 7, 7);
    graph.addEdge(2, 8, 9);
    graph.addEdge(2, 9, 1);
    graph.addEdge(3, 4, 9);
    graph.addEdge(3, 5, 1);
    graph.addEdge(3, 7, 10);
    graph.addEdge(3, 8, 7);
    graph.addEdge(3, 9, 5);
    graph.addEdge(4, 5, 7);
    graph.addEdge(4, 6, 4);
    graph.addEdge(4, 7, 9);
    graph.addEdge(4, 8, 10);
    graph.addEdge(4, 9, 3);
    graph.addEdge(5, 6, 3);
    graph.addEdge(5, 8, 8);
    graph.addEdge(5, 9, 2);
    graph.addEdge(6, 7, 10);

    int expectedWeight = 22;

    vector<Graph::Edge> mstEdges{
        Graph::Edge(0, 3, 1),
        Graph::Edge(0, 2, 2),
        Graph::Edge(0, 6, 2),
        Graph::Edge(0, 8, 4),
        Graph::Edge(0, 7, 7),
        Graph::Edge(1, 5, 1),
        Graph::Edge(2, 9, 1),
        Graph::Edge(3, 5, 1),
        Graph::Edge(4, 9, 3),
    };

    auto mst = kruskal_mst(graph);

    SECTION("Check Total Weight for Dense Graph")
    {
        int totalWeight = mst.totalWeight;
        REQUIRE(totalWeight == expectedWeight);
    }

    SECTION("Check MST Edges for Dense Graph")
    {
        if (!is_permutation(mstEdges.begin(), mstEdges.end(), mst.edges.begin(), mst.edges.end()))
        {
            WARN("MST Compairson Failed: A graph can have many MST values, so you may want to check the result.");
        }
    }
}
