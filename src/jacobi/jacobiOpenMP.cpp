#include "../../include/jacobi.hpp"

std::vector<float> jacobiOpenmp(Matrix A, std::vector<float> b, std::vector<float> sol, int threshold, int nw){


    std::vector<float> res(A.grid.size());

    {
        std::string message = "Jacobi openmp with " + std::to_string(threshold) + " steps";
        utimer timer(message);

        int dim = A.grid.size();
        for(int k=0; k<threshold; k++){
#pragma omp parallel for num_threads(nw)
            for(int i=0; i<dim; i++){
                float sigma = 0;
                for(int j=0; j<dim; j++){
                    if(i != j){
                        sigma = sigma + A.grid[i][j]*sol[j];
                    }
                }
                res[i] = (1/A.grid[i][i])*(b[i]-sigma);
            }
        }
    }

    return res;

}