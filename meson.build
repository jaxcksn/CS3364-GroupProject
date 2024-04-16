project('CS3364-GroupProject','cpp',default_options: ['cpp_std=c++17'])
executable('Task2',sources: ['src/main.cpp'],install: false, build_by_default: true)

test_exe = executable('unit_tests', sources: ['tests/test_main.cpp','src/prim.cpp','src/kruskal.cpp','tests/Catch2.cpp'], dependencies: [])
test('unit_tests', test_exe)

