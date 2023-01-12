cmake_minimum_required(VERSION 3.16)
project(JacobiParallel)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)

# Fetch argparse from GitHub to parse arguments from command line
# in a modern C++ way.
message(STATUS "Fetching 'FastFlow' from GitHub...")
FetchContent_Declare(
        fastflow
        GIT_REPOSITORY https://github.com/fastflow/fastflow.git
)
FetchContent_MakeAvailable(fastflow)

# FastFlow is header-only
include_directories(${fastflow_SOURCE_DIR})

include_directories(include)

add_executable(JacobiParallel
        include/jacobi.hpp
        include/mapClass.hpp
        include/utils.hpp
        include/fileHandler.hpp
        src/jacobi/jacobiFF.cpp
        src/jacobi/jacobiOpenMP.cpp
        src/jacobi/jacobiSeq.cpp
        src/jacobi/jacobiThreads.cpp
        src/mapClass.cpp
        src/main.cpp
        src/utimer.cpp
        src/fileHandler.cpp)
