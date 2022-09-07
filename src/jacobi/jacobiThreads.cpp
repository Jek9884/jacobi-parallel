#include "../../include/jacobi.hpp"

void jacobiThrs(mv::Matrix mat, mv::Vector b, mv::Vector& sol, int threshold, int nw){

    auto computeRow = [&](mv::Vector &res, int startIdx, int endIdx){

        for(int i=startIdx; i<endIdx+1; i++){
            mv::Vector vec = mat[i];
            int dim = (int) vec.size();
            double sigma = 0;

            for(int j=0; j<dim; j++){
                if(i != j){
                    sigma = sigma + vec[j]*sol[j];
                }
            }
            res[i] = (1 / vec[i]) * (b[i] - sigma);
        }

    };

    std::string message = "Jacobi threads with " + std::to_string(threshold) + " steps";

    {
        utimer timer(message);
        Map map((int) mat.size(), map_mode::Chunk, nw, computeRow);
        map.execute(threshold, sol);
    }

}