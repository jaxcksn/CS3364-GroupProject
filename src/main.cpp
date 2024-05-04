// This is the main C++ file, do not delete me or else the build system breaks.
#include "graph.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include "CLI11.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <random>
#include "spinner.hpp"

using namespace std;

void createImage(const string &type, const string &algorithm, const string &graphFile, const string &outputPath)
{
    const string tempFilePath("temp.dot");
    ofstream outFile(tempFilePath);
    Graph testGraph = loadGraphFromFile(graphFile);
    MST mst;

    if (algorithm == "kruskal")
    {
        mst = kruskal_mst(testGraph);
    }
    else
    {
        mst = prim_mst(testGraph);
    }

    if (type == "graph")
    {
        outFile << graphToDot(testGraph);
    }
    else
    {
        outFile << mstToDot(testGraph, mst);
    }

    outFile.close();

    stringstream command;
    command << "sfdp -Tpng temp.dot"
            << " -o " << outputPath;

    system(command.str().c_str());

    // Delete the DOT file
    if (remove(tempFilePath.c_str()) != 0)
    {
        perror("Error deleting DOT file");
    }
    else
    {
        cout << "Temporary DOT file deleted successfully." << endl;
    }

    cout << "Graph image generated at: " << outputPath << endl;

    cout << "Raw Output:" << endl;
    cout << "MST: " << serializeMST(mst) << "\nTotal Weight: "
         << mst.totalWeight << endl;
}

void generateRandGraph(Graph &g, int V, int E)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, V - 1); // Adjusted to ensure valid vertex indices

    for (int i = 0; i < E; ++i)
    {
        int u = dis(gen);
        int v = dis(gen);
        while (u == v)
        { // Ensure that u and v are not the same to avoid self-loop
            v = dis(gen);
        }
        int w = dis(gen); // Random weight
        g.addEdge(u, v, w);
    }
}

/**
 * This is the main benchmark driver, we use a template so that we can use either Prim or Kruskals as needed
 */
template <typename Func>
long long benchmarkMST(Func mstFunc, Graph &graph)
{
    auto start = chrono::high_resolution_clock::now();
    auto mst = mstFunc(graph);
    auto end = chrono::high_resolution_clock::now();
    long long duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    return duration;
}

void runBenchmark(const string &outputFile)
{
    jms::Spinner s("Running Benchmark (This may take some time)", jms::classic);
    s.start();
    ofstream results(outputFile);
    results << "Vertices,Edges,Kruskal,Prim\n";

    for (int i = 10; i <= 1000; i += 5)
    {
        // Max number for a dense graph
        int e = i * (i - 1) / 2;
        // Initialize a graph with i verts
        Graph g(i);
        // Randomize it
        generateRandGraph(g, i, e);

        long long timeKruskal = benchmarkMST(kruskal_mst, g);

        results << i << "," << e << "," << timeKruskal << "," << 0.0 << "\n";
    }
    results.close();
    s.finish(jms::FinishedState::SUCCESS, "Finished Benchmark!");
}

int main(int argc, char *argv[])
{
    // Initialize CLI app
    CLI::App app;

    // One of the sub commands should be used
    app.require_subcommand(1);

    // The MST image generator subcommand
    CLI::App *mstGenApp = app.add_subcommand("mst", "REQUIRES GRAPHVIZ - Create an image of a graph file's MST");
    // The Graph image generator subcommand
    CLI::App *graphGenApp = app.add_subcommand("graph", "REQUIRES GRAPHVIZ - Create an image of a graph file");
    // The benchmark subcommand
    CLI::App *benchmarkApp = app.add_subcommand("benchmark", "Run the benchmarking analysis for the algorithms");

    // SECTION - CLI Options
    string algorithm = "kruskal";
    mstGenApp->add_option("-a,--algo,algo", algorithm, "The algorithm can be 'kruskal' or 'prim'")->default_str("kruskal");
    graphGenApp->add_option("-a,--algo,algo", algorithm, "The algorithm can be 'kruskal' or 'prim'")->default_str("kruskal");

    string inputGraph;
    mstGenApp->add_option("-g,--graph,graphP", inputGraph, "The path to the input .graph file")->required();
    graphGenApp->add_option("-g,--graph,graphP", inputGraph, "The path to the input .graph file")->required();

    string outputFile = "output.csv";
    mstGenApp->add_option("-o,--output,output", outputFile, "The image file to output (should end with .png)")->required();
    graphGenApp->add_option("-o,--output,output", outputFile, "The image file to output (should end with .png)")->required();
    benchmarkApp->add_option("-o,--output,output", outputFile, "The csv file that should be created")->default_str("output.csv");

    // SECTION - Subcommand Callbacks
    mstGenApp->callback([&]()
                        { createImage("mst", algorithm, inputGraph, outputFile); });

    graphGenApp->callback([&]()
                          { createImage("graph", algorithm, inputGraph, outputFile); });

    benchmarkApp->callback([&]()
                           { runBenchmark(outputFile); });

    CLI11_PARSE(app, argc, argv);
    return 0;
}
