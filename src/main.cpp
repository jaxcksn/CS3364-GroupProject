// This is the main C++ file, do not delete me or else the build system breaks.
#include <iostream>
#include "Graph.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include <chrono>
using namespace std;

/**
 * Main function for the program, which takes several arguments:
 * PROGRAM_NAME graphFile algo
 *
 * Where:
 * file is the path to the graph to load
 * algo is either "prim" or "kruskal"
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "ERROR: Invalid number of arguments, must pass file and algo arguments." << endl;
        return 1;
    }

    // Load the graph from a file
    Graph graph = loadGraphFromFile(argv[1]);

    // These are error conditions
    if (graph.vertNumber() == 0 || graph.edgeCount() == 0)
    {
        cerr << "ERROR: Could not load graph from file" << endl;
        return 1;
    }

    // Some information for us
    cout << "\nGraph Size: " << graph.vertNumber() << " nodes | " << graph.edgeCount() << " edges" << endl;

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    if (strcmp(argv[2], "kruskal") == 0)
    {
        cout << "Running Kruskal's Algorithm on Graph" << endl;
        // Start the clock
        start = chrono::high_resolution_clock::now();
        MST output = kruskal_mst(graph);
        // End the clock
        end = chrono::high_resolution_clock::now();
    }
    else
    {
        cout << "Running Prim's Algorithm on Graph" << endl;
        // Start the clock
        start = chrono::high_resolution_clock::now();
        MST output = prim_mst(graph);
        // End the clock
        end = chrono::high_resolution_clock::now();
    }

    // We'll change the duration to nanoseconds
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    // Output the results
    cout << "Execution Time: " << duration.count() << " ns" << endl;

    return 0;
}
