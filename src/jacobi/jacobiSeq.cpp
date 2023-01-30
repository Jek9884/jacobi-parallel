#include "../../include/jacobi.hpp"

/**
 * @brief Compute Jacobi method with a sequential implementation
 * 
 * @param A matrix
 * @param b vector 
 * @param sol solution vector
 * @param maxIter maximum nuber of iterations
 * @param stoppingCriteria stopping criteria to use
 * @param tol tolerance to check equality betweed computed and real solution
 * @return mv::Vector solution vector
 */
auto jacobiSeq(mv::Matrix A, mv::Vector b, mv::Vector &sol, int maxIter, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol) -> mv::Vector {

    mv::Vector res(A.size(), 0);
    std::string message = "Jacobi sequential with " + std::to_string(maxIter) + " steps";
    int dim = static_cast<int>(A.size());
    int iter = 0;

    while(!stoppingCriteria(sol, tol) && (iter < maxIter)){
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
        iter++;
    }

    std::cout << "Number of effective iterates: " << iter << std::endl;

    return res;

}