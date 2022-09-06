#include "../include/jacobi.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

std::tuple<Matrix, std::vector<float>, std::vector<float>, std::vector<float>> gen_test_data(){

    std::vector<float> vec1 = {10, -1, 2, 0};
    std::vector<float> vec2 = {-1, 11, -1, 3};
    std::vector<float> vec3 = {2, -1, 10, -1};
    std::vector<float> vec4 = {0, 3, -1, 8};

    Matrix matrix(4,true);

    matrix.grid[0].insert(matrix.grid[0].begin(), vec1.begin(), vec1.end());
    matrix.grid[1].insert(matrix.grid[1].begin(), vec2.begin(), vec2.end());
    matrix.grid[2].insert(matrix.grid[2].begin(), vec3.begin(), vec3.end());
    matrix.grid[3].insert(matrix.grid[3].begin(), vec4.begin(), vec4.end());

    std::vector<float> vec = {6, 25, -11, 15};

    std::vector<float> sol(4, 0);
    std::vector<float> expected_sol = {1, 2, -1, 1};

    int threshold = 1000;
    sol = jacobiSeq(matrix, vec, sol, threshold);

    return std::make_tuple(matrix, vec, sol, expected_sol);
}

void test_jacobi_seq(){

    std::tuple data = gen_test_data();
    Matrix matrix = std::get<0>(data);
    std::vector vec = std::get<1>(data);
    std::vector sol = std::get<2>(data);
    std::vector expected_sol = std::get<3>(data);

    int threshold = 10000;
    sol = jacobiSeq(matrix, vec, sol, threshold);

    std::cout << "Expected solution: " << std::endl;
    print_vec(expected_sol);
    std::cout << std::endl;
    std::cout << "Solution found: " << std::endl;
    print_vec(sol);
    std::cout << std::endl;

}

void test_jacobi_threads(int nw){

    std::tuple data = gen_test_data();
    Matrix matrix = std::get<0>(data);
    std::vector vec = std::get<1>(data);
    std::vector sol = std::get<2>(data);
    std::vector expected_sol = std::get<3>(data);

    int threshold = 10000;
    jacobiThrs(matrix, vec, sol, threshold, nw);

    std::cout << "Expected solution: " << std::endl;
    print_vec(expected_sol);
    std::cout << std::endl;
    std::cout << "Solution found: " << std::endl;
    print_vec(sol);
    std::cout << std::endl;

}

void test_jacobi_openmp(int nw){

    std::tuple data = gen_test_data();
    Matrix matrix = std::get<0>(data);
    std::vector vec = std::get<1>(data);
    std::vector sol = std::get<2>(data);
    std::vector expected_sol = std::get<3>(data);

    int threshold = 10000;
    sol = jacobiOpenmp(matrix, vec, sol, threshold, nw);

    std::cout << "Expected solution: " << std::endl;
    print_vec(expected_sol);
    std::cout << std::endl;
    std::cout << "Solution found: " << std::endl;
    print_vec(sol);
    std::cout << std::endl;

}

void test_performance_jacobi(int nw, int dim, int threshold, int nRuns) {

    for (int i = 0; i < nRuns; i++) {

        Matrix a(dim, true);
        auto b = init_vec(dim);
        std::vector<float> x(dim, 0);

        jacobiSeq(a, b, x, threshold);
        jacobiThrs(a, b, x, threshold, nw);
        jacobiOpenmp(a, b, x, threshold, nw);


    }
}

int main(int argc, char *argv[]){

    assertm((argc == 5), "Number of workers, matrix dimension, number of iterations and threshold are required");

    int nw = (int) strtol(argv[1], nullptr, 10);
    int n = (int) strtol(argv[2], nullptr, 10);
    int iter = (int) strtol(argv[3], nullptr, 10);
    int threshold = (int) strtol(argv[4], nullptr, 10);

    test_jacobi_seq();
    test_jacobi_threads(nw);
    test_jacobi_openmp(nw);

    test_performance_jacobi(nw, n, threshold, iter);

    return 0;
}
