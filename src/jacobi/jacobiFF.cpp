#include "../../include/jacobi.hpp"
#include <ff/parallel_for.hpp>

/**
 * @brief Compute Jacobi method with the FastFlow implementation
 * 
 * @param A matrix
 * @param b vector 
 * @param sol solution vector
 * @param maxIter maximum nuber of iterations
 * @param stoppingCriteria stopping criteria to use
 * @param tol tolerance to check equality between computed and real solution
 * @param nw number of workers to use
 * @return mv::Vector solution vector
 */
auto jacobiFF(mv::Matrix A, mv::Vector b, mv::Vector &sol, int maxIter, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol, int nw) -> mv::Vector {

    mv::Vector res(A.size(), 0);
    std::string message = "Jacobi fastflow with " + std::to_string(maxIter) + " steps";

    int dim = static_cast<int>(A.size());
    int iter = 0;
    ff::ParallelFor pf(nw);

    auto func =  [A, b, dim, &sol, &res](const int i){
        double sigma = 0;
        for (int j = 0; j < dim; j++) {
            if (i != j) {
                sigma = sigma + A[i][j] * sol[j];
            }
        }
        res[i] = (1.0/ A[i][i]) * (b[i] - sigma);
    };

    while(!stoppingCriteria(sol, tol) && (iter < maxIter)){
        pf.parallel_for(0, dim, 1, func, nw);
        sol = res;
        iter++;
    }

    std::cout << "Number of effective iterates: " << iter << std::endl;

    return res;

}