# libposidonia

## C Algorithms library

*libposidonia* is a C library implementing common algorithms on
different data structures. It uses
[*libds*](https://github.com/jotare/libds) as data structures
library.

### Implemented algorithms

- Graph
  - Breadth-First Search (BFS)
  - Depth-First Search (DFS)

## Use libposidonia

*libposidonia* can be used as a regular C library. Build and link it
to your project. You can use `include/libposidonia.h` header file to
access all algorithms.

Be aware that *libposidonia* depends on *libds*, so you'll have to
build and link it too.

## Build libposidonia

To build *libposidonia* library execute:
```
make lib
```

To build also its dependencies:
```
make deps
```

## Test libposidonia

Al testing is performed with CUnit framework. Al tests are inside the
test directory. There, the main file `test_libposidonia.c` joins all
test suites and execute them.

To run all tests execute:
```
make run-tests
```
it will build and link all necessary targets and run the tests.
