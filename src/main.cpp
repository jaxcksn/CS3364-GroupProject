// This is the main C++ file, do not delete me or else the build system breaks.
#include <iostream>
#include "graph.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

using namespace std;

/**
 * Tests the algorithm against multiple graphs, outputing the average runtime.
 */
void testAlgorithm(Graph &graph, ofstream &outputFile, int times = 10)
{
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;
    chrono::nanoseconds kruskalTotal(0);
    chrono::nanoseconds primTotal(0);
    MST mst;

    outputFile << "Testing Graph: " << graph.name << endl;
    outputFile << "\nGraph Size: " << graph.vertNumber() << " nodes | " << graph.edgeCount() << " edges" << endl;
    outputFile << "Running " << times << " runs per algorithm.\n"
               << endl;

    for (int i = 0; i < times; i++)
    {
        start = chrono::high_resolution_clock::now();
        mst = kruskal_mst(graph);
        end = chrono::high_resolution_clock::now();
        kruskalTotal += chrono::duration_cast<chrono::nanoseconds>(end - start);
    }

    for (int i = 0; i < times; i++)
    {
        start = chrono::high_resolution_clock::now();
        mst = prim_mst(graph);
        end = chrono::high_resolution_clock::now();
        primTotal += chrono::duration_cast<chrono::nanoseconds>(end - start);
    }

    chrono::nanoseconds avgKruskalTime = kruskalTotal / times;
    chrono::nanoseconds avgPrimTime = primTotal / times;

    outputFile << "Average Kruskal's Algorithm Runtime: " << avgKruskalTime.count() << " ns" << endl;
    outputFile << "Average Prim's Algorithm Runtime: " << avgPrimTime.count() << " ns" << endl
               << endl;
}

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "test") == 0)
    {
        Graph testGraph = loadGraphFromFile(argv[2]);
        MST mst = kruskal_mst(testGraph);

        if (strcmp(argv[3], "graphonly") == 0)
        {
            cout << graphToDot(testGraph);
        }
        else if (strcmp(argv[3], "mst_string") == 0)
        {
            cout << "MST: " << serializeMST(mst) << "\nTotal Weight: "
                 << mst.totalWeight << endl;
        }
        else
        {
            cout << mstToDot(testGraph, mst);
        }
    }
    else
    {
        if (argc >= 3)
        {
            ofstream outputFile("out.txt");
            // We want more than one argument
            for (size_t i = 1; i < argc; i++)
            {
                cout << "Testing: " << argc << " " << argv[i];
                Graph testGraph = loadGraphFromFile(argv[i]);

                // We couldn't load this one
                if (testGraph.vertNumber() == 0)
                {
                    continue;
                }

                // Run the algorithm text
                testAlgorithm(testGraph, outputFile, 10);
            }
        }
        cout << "Results have been saved to out.txt";
    }
}
