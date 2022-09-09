#include "../../include/jacobi.hpp"

mv::Vector jacobiSeq(mv::Matrix A, mv::Vector b, mv::Vector &sol, int threshold) {

    mv::Vector res(A.size());
    {
        std::string message = "Jacobi sequential with " + std::to_string(threshold) + " steps";
        utimer timer(message);
        int dim = static_cast<int>(A.size());
        for (int k = 0; k < threshold; k++) {
            for (int i = 0; i < dim; i++) {
                double sigma = 0;
                for (int j = 0; j < dim; j++) {
                    if (i != j) {
                        sigma = sigma + A[i][j] * sol[j];
                    }
                }
                res[i] = (1.0/ A[i][i]) * (b[i] - sigma);
            }

            sol = res;
        }
    }

    return res;

}