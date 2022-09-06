#include "../../include/jacobi.hpp"

std::vector<float> jacobiSeq(Matrix A, std::vector<float> b, std::vector<float>& sol, int threshold){

    std::vector<float> res(A.grid.size());
    {
        std::string message = "Jacobi sequential with " + std::to_string(threshold) + " steps";
        utimer timer(message);
        int dim = (int) A.grid.size();
        for(int k=0; k<threshold; k++){
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