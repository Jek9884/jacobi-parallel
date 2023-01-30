# JacobiParallel
Various parallel implementations of the Jacobi method for linear systems solution.

# Building instructions

To build the project use the following commands

```
mkdir
cd build
cmake ..
make
```

# Run

The program offers two different interfaces. The first one is formatted as

```
./JacobiParallel 2 1024 10000 5 1 1 1 1
```
Where 2 is the number of workers to use, 1024 is the matrix dimension, 10000 is the maximum number of iterations and the ones are boolean flag to execute respectively the sequential code, C++ threads, OpenMP and FastFlow. It is useful to run experiment on a single configuration with one or more methods.

The second one is formatted as

```
./JacobiParallel 0
```
Where 0 is an integer value. If it is 0, it runs an exhaustive test with different configurations over all the implementations. If 1, it performs an exhaustive computation of the overhead time for different configurations of the C++ threads implementation. If 2, it performs a serial fraction time evaluation. Otherwise it performs a thread initialization time evaluation.


