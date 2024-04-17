project('CS3364-GroupProject','cpp',default_options: ['cpp_std=c++17'])
executable('Task2',sources: ['src/main.cpp', 'src/kruskal.cpp', 'src/prim.cpp','src/graph.cpp'],install: false, build_by_default: true)

prim_test_d = executable('prim_tests_d', sources: ['tests/test_prim_dense.cpp','src/prim.cpp','tests/Catch2.cpp','src/graph.cpp'], dependencies: [])
kruskal_test_d = executable('kruskal_tests_d', sources: ['tests/test_kruskal_dense.cpp','src/kruskal.cpp','tests/Catch2.cpp','src/graph.cpp'], dependencies: [])
prim_test_s = executable('prim_tests_s', sources: ['tests/test_prim_sparse.cpp','src/prim.cpp','tests/Catch2.cpp','src/graph.cpp'], dependencies: [])
kruskal_test_s = executable('kruskal_tests_s', sources: ['tests/test_kruskal_sparse.cpp','src/kruskal.cpp','tests/Catch2.cpp','src/graph.cpp'], dependencies: [])


test('prim_tests_d', prim_test_d)
test('kruskal_tests_d',kruskal_test_d)
test('prim_tests_s',prim_test_s)
test('kruskal_tests_s',kruskal_test_s)