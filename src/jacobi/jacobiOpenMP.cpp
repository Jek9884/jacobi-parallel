#include "../../include/jacobi.hpp"

mv::Vector jacobiOpenmp(mv::Matrix A, mv::Vector b, mv::Vector sol, int threshold, int nw){


    mv::Vector res(A.size());

    {
        std::string message = "Jacobi openmp with " + std::to_string(threshold) + " steps";
        utimer timer(message);

        int dim = (int) A.size();
        for(int k=0; k<threshold; k++){
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
        }
    }

    return res;

}