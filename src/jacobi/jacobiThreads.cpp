#include "../../include/jacobi.hpp"

void jacobiThrs(mv::Matrix mat, mv::Vector b, mv::Vector& sol, int threshold, int nw, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol){

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

    #if defined(OVERHEAD)
        std::string sepOver = ",";
        std::string headerOver = "thread"+sepOver+std::to_string(nw)+sepOver+std::to_string(threshold)+sepOver+std::to_string(b.size())+";";
        writeOnFile(headerOver, RESULTS_FOLDER, OVERHEAD_IN_FILENAME);
        utimer* overheadTimer = new utimer("Map creation overhead", overhead);
    #endif

    Map map(static_cast<int>(mat.size()), map_mode::Chunk, nw, computeRow);

    #if defined(OVERHEAD)
        delete overheadTimer;
    #endif

    map.execute(threshold, sol, stoppingCriteria, tol);
    
    #if defined(OVERHEAD)
        writeOnFile("\n", RESULTS_FOLDER, OVERHEAD_IN_FILENAME);
        extractTime(RESULTS_FOLDER, OVERHEAD_IN_FILENAME, OVERHEAD_OUT_FILENAME);
    #endif
}