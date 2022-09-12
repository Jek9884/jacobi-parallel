#include "../include/jacobi.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

void test_performance_jacobi(int nw, int dim, int threshold, int nRuns) {

    std::tuple data = mv::generateSystem(dim);
    mv::Matrix a = std::get<0>(data);
    mv::Vector b = std::get<1>(data);
    mv::Vector x = std::get<2>(data);
    mv::Vector expected = std::get<3>(data);

    for (int i = 0; i < nRuns; i++) {

        x = std::get<2>(data);
        x = jacobiSeq(a, b, x, mv::checkRes,threshold, 1e-8);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }


        x = std::get<2>(data);
        jacobiThrs(a, b, x, threshold, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }

        x = std::get<2>(data);
        x = jacobiOpenmp(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }

        x = std::get<2>(data);
        x = jacobiFF(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }
}

int main(int argc, char *argv[]){

    assertm((argc == 5), "Number of workers, matrix dimension, number of iterations and threshold are required");

    int nw = (int) strtol(argv[1], nullptr, 10);
    int n = (int) strtol(argv[2], nullptr, 10);
    int iter = (int) strtol(argv[3], nullptr, 10);
    int threshold = (int) strtol(argv[4], nullptr, 10);

    test_performance_jacobi(nw, n, threshold, iter);

    return 0;
}
