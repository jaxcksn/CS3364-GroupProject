# CS3364-GroupProject

[![Build](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-build.yml/badge.svg)](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-build.yml)
[![Test](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-test.yml/badge.svg)](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-test.yml)

## Getting Started

The first thing you need to do is install meson and ninja, which will handle all of the building for you. The easiest way to do this is to just run:

```bash
pip install meson ninja
```

Once you have installed meson and ninja, run the following command from the root directory of the repository:

```bash
python build.py
```

If everything builds correctly, you should be set to run the program, which can be found in the build directory.

## Usage

### Command Syntax

```bash
./Task2 <subcommand> [options]
```

### Subcommands

#### 1. MST Image Generation

Generate an image of the minimum spanning tree (MST) for a given graph.

```bash
./Task2 mst -g <path_to_graph_file> -o <output_image.png> -a <algorithm>
```

##### Options:

-g, --graph, graphP: Specify the path to the input graph file.
-o, --output, output: Specify the output image file name (must end with .png).
-a, --algo, algo: Select the algorithm (kruskal or prim). Default is kruskal.

#### 2. Graph Image Generation

Create an image of the original graph.

```bash
./Task2 graph -g <path_to_graph_file> -o <output_image.png>
```

##### Options:

-g, --graph, graphP: Specify the path to the input graph file.
-o, --output, output: Specify the output image file name (must end with .png).

#### 3. Benchmarking

Run performance benchmarks for the MST algorithms and output the results to a CSV file.

```bash
./Task2 benchmark -o <output_file.csv>
```

##### Options:

-o, --output, output: Specify the output CSV file name. Default is output.csv.

### Examples

#### Generating an MST image using Kruskal's algorithm:

```bash
./Task2 mst -g example.graph -o mst_output.png -a kruskal
```

#### Creating a graph image:

```bash
./Task2 graph -g example.graph -o graph_output.png
```

#### Running benchmarks and saving the results:

```bash
./your_program benchmark -o benchmark_results.csv
```

#### Additional Information

Ensure Graphviz is installed and properly configured on your system as it is required for the image generation features.
For detailed error logs or additional information, consider implementing verbose or log options in your CLI.

## Editing the Source Code

The main files you should be editing are the implementations of [Prim's Algorithm](src/prim.cpp) and [Kruskal's Algorithm](src/kruskal.cpp)

You can also edit the header files for each one too!

There is also a shared header file called Graph that has been created, and contains the Graph class that should be shared by both algorithms for testing purposes.

## Testing

When you are ready to test the algorithms, run the following, you should see what results where passed, and which ones were not.

```bash
python test.py
```

When you submit a commit, it will also run the tests.
