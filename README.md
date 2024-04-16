# CS3364-GroupProject

[![Check](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-build.yml/badge.svg)](https://github.com/jaxcksn/CS3364-GroupProject/actions/workflows/meson-build.yml)

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

## Editing the Source Code

The main files you should be editing are the implementations of [Prim's Algorithm](src/prim.cpp) and [Kruskal's Algorithm](src/kruskal.cpp)

You can also edit the header files for each one too!

There is also a shared header file called Graph that has been created, and creates Graph class that should be shared by both algorithms for testing purposes.

## Testing

When you are ready to test the algorithms, run the following, you should see what results where passed, and which ones were not.

```bash
python test.py
```

When you submit a commit, it will also run the tests.
