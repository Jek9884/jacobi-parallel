#include "../../include/jacobi.hpp"

void jacobiThrs(mv::Matrix mat, mv::Vector b, mv::Vector& sol, int threshold, int nw){

    auto computeRow = [&](mv::Vector &res, int startIdx, int endIdx){

        for(int i=startIdx; i<endIdx+1; i++){
            mv::Vector vec = mat[i];
            int dim = static_cast<int>(vec.size());
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
        #if defined(OVERHEAD)
            std::string sep = ",";
            std::string header = std::to_string(nw)+sep+std::to_string(threshold)+sep+std::to_string(b.size());
            writeOnOverheadFile(header, "OverheadTime.csv");
            utimer* overheadTimer = new utimer("Map creation overhead", true);
        #endif
        Map map(static_cast<int>(mat.size()), map_mode::Chunk, nw, computeRow);
        #if defined(OVERHEAD)
            delete overheadTimer;
        #endif
        map.execute(threshold, sol);
    }

}