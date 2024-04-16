#define CATCH_CONFIG_MAIN
#include "Catch2.hpp"
#include "../src/prim.hpp"
#include "../src/kruskal.hpp"
#include "algorithm"
#include "../src/Graph.hpp"

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

    auto mst = prim_mst(graph, 0);

    SECTION("Check Total Weight for Sparse Graph")
    {
        int totalWeight = mst.totalWeight;
        REQUIRE(totalWeight == expectedWeight);
    }

    SECTION("Check MST Edges for Sparse Graph")
    {
        REQUIRE(is_permutation(mstEdges.begin(), mstEdges.end(), mst.edges.begin(), mst.edges.end()));
    }
}

TEST_CASE("Prim's Algorithm: Dense Graph", "[prim_mst]")
{
    Graph graph(10);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 4);
    graph.addEdge(0, 3, 6);
    graph.addEdge(0, 4, 4);
    graph.addEdge(0, 5, 6);
    graph.addEdge(0, 6, 4);
    graph.addEdge(0, 8, 7);
    graph.addEdge(0, 9, 8);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, 5);
    graph.addEdge(1, 5, 5);
    graph.addEdge(1, 9, 1);
    graph.addEdge(2, 3, 7);
    graph.addEdge(2, 4, 6);
    graph.addEdge(2, 6, 9);
    graph.addEdge(2, 7, 9);
    graph.addEdge(2, 8, 4);
    graph.addEdge(3, 4, 4);
    graph.addEdge(3, 6, 4);
    graph.addEdge(3, 7, 3);
    graph.addEdge(3, 8, 5);
    graph.addEdge(3, 9, 10);
    graph.addEdge(4, 5, 9);
    graph.addEdge(4, 6, 5);
    graph.addEdge(4, 7, 10);
    graph.addEdge(4, 9, 9);
    graph.addEdge(5, 6, 4);
    graph.addEdge(5, 7, 6);
    graph.addEdge(5, 8, 1);
    graph.addEdge(6, 7, 1);
    graph.addEdge(6, 8, 8);
    graph.addEdge(7, 8, 3);
    graph.addEdge(7, 9, 6);
    graph.addEdge(8, 9, 3);

    int expectedWeight = 22;

    vector<Graph::Edge> mstEdges{
        Graph::Edge(0, 2, 4),
        Graph::Edge(0, 4, 4),
        Graph::Edge(1, 2, 2),
        Graph::Edge(1, 9, 1),
        Graph::Edge(3, 7, 3),
        Graph::Edge(5, 8, 1),
        Graph::Edge(6, 7, 1),
        Graph::Edge(7, 8, 3),
        Graph::Edge(8, 9, 3),
    };

    auto mst = prim_mst(graph, 0);

    SECTION("Check Total Weight for Sparse Graph")
    {
        int totalWeight = mst.totalWeight;
        REQUIRE(totalWeight == expectedWeight);
    }

    SECTION("Check MST Edges for Sparse Graph")
    {
        REQUIRE(is_permutation(mstEdges.begin(), mstEdges.end(), mst.edges.begin(), mst.edges.end()));
    }
}