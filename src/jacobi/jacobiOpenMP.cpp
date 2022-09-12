#include "../../include/jacobi.hpp"

auto jacobiOpenmp(mv::Matrix A, mv::Vector b, mv::Vector sol, const std::function<bool(mv::Vector, double)>& stoppingCriteria, int nIter, double tol, int nw) -> mv::Vector{


    mv::Vector res(A.size());

    {
        std::string message = "Jacobi openmp with " + std::to_string(nIter) + " steps";
        utimer timer(message);

        int dim = static_cast<int>(A.size());

        int iter = 0;

        while(!stoppingCriteria(sol, tol) && (iter < nIter)){
            #pragma omp parallel for num_threads(nw)
            for(int i=0; i<dim; i++){
                double sigma = 0;
                for(int j=0; j<dim; j++){
                    if(i != j){
                        sigma = sigma + A[i][j]*sol[j];
                    }
                }
                res[i] = (1/A[i][i])*(b[i]-sigma);
            }

            sol = res;
            iter++;
        }

        std::cout << "Number of effective iterates: " << iter << std::endl;
    }

    return res;

}