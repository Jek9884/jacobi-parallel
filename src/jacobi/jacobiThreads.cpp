#include "../../include/jacobi.hpp"

void jacobiThrs(Matrix mat, std::vector<float> b, std::vector<float>& sol, int threshold, int nw){

    auto computeRow = [&](std::vector<float> &res, int startIdx, int endIdx){

        for(int i=startIdx; i<endIdx+1; i++){
            std::vector<float> vec = mat.grid[i];
            int dim = vec.size();
            float sigma = 0;

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
        Map map(mat.grid.size(), map_mode::Chunk, nw, computeRow);
        map.execute(threshold, sol);
    }

}