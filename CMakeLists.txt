cmake_minimum_required(VERSION 3.21)
project(JacobiParallel)

add_compile_definitions(PRINT_ITER)
add_compile_definitions(CHECK_ONES)

set(CMAKE_CXX_FLAGS "-O3 -pthread -fopenmp")

set(CMAKE_CXX_STANDARD 20)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(include)

add_executable(JacobiParallel
        include/jacobi.hpp
        include/mapClass.hpp
        include/matrix.hpp
        include/utils.hpp
        src/jacobi/jacobiFF.cpp
        src/jacobi/jacobiOpenMP.cpp
        src/jacobi/jacobiSeq.cpp
        src/jacobi/jacobiThreads.cpp
        src/mapClass.cpp
        src/main.cpp
        src/matrix.cpp
        src/utils.cpp
        src/utimer.cpp)
