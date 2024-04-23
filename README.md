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

## Using the CLI

### Command Syntax

```bash
./Task2 [GRAPHFILES]
```

### Arguments

There is a single command line arguments the program requires

1. **GRAPHFILE**: This should be a space seperated lists of graph files to run.

### Output

The program will output a file called "out.txt" that has all the run time information for the program.

### Graph File Format

The graph file should be formatted as follows:

- The first line is the name of the graph (No spaces are allowed)
- The second line is the number of verticies in the graph
- Each subsequent line represents an edge with three integers: src, dest, and weight, where src and dest are the vertices connected by the edge, and weight is the weight of the edge.

Example of a graph file content:

```
example_graph
3
0 1 10
2 1 2
1 2 3
```

There are some sample graph files in the [examples folder](/examples/)

**NOTE**: Graphs are undirected in this program, so you only should specify an edge once, for example if you have the edge `0 1 2` you shouldn't add `1 0 2` since they are the same.

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
