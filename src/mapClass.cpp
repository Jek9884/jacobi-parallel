#include "../include/mapClass.hpp"

/**
 * @brief Generate chunks for data computation
 * 
 * @return std::vector<std::tuple<int, int>> vector of tuples. Each tuple is composed respectively by start index and end index of the chunck.
 */
std::vector<std::tuple<int, int>> Map::generateBlocks(){

    int n = this->dim;
    std::vector<std::tuple<int, int>> indexes(this->nw);

    if(this->mode == mapMode::Chunk){
        int j=0;
        int block_size = (n % this->nw != 0) ? ceil(n/this->nw) : n/this->nw;
        for(int i=0; i<this->nw; i++){
            if(i == nw-1){
                indexes[i] = std::make_tuple(j, n-1);
            }
            else{
                indexes[i] = std::make_tuple(j, j+block_size-1);
            }

            j += block_size;
        }
    }

    return indexes;
}

/**
 * @brief Map object constructor
 */
Map::Map(int dim, mapMode mode, int nw, const std::function<void(mv::Vector&, int, int)>& f){
    this->dim = dim;
    this->mode = mode;
    this->nw = nw;
    this->f = f;
    this->idxs = this->generateBlocks();
    this->converged = false;
}

/**
 * @brief 
 * 
 * @param nIter 
 * @param xk 
 */

/**
 * @brief Perform Map computation 
 * 
 * @param maxIter max number of iterations that each thread can perform 
 * @param xk solution vector
 * @param stoppingCriteria to stop the iterative process
 * @param tol to use to check the equality between real solution vector and the computed solution vector
 */
void Map::execute(int maxIter, mv::Vector &xk, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol){

    bool converged = false;
    int iter = 0;

    mv::Vector xk1(xk.size());

    auto sync_f = [this, &xk, &xk1, &tol, stoppingCriteria, &iter, &maxIter](){
        //Update solution vector
        xk = xk1;
        iter++;
        this->converged = stoppingCriteria(xk, tol) || (iter >= maxIter);
    };

    std::barrier syncPoint(this->nw, sync_f);

    auto *thrs = new std::thread[this->nw];

    //Lambda function passed to a thread
    auto executeChunck = [this, &syncPoint, &xk1, converged](int n, int thrIdx){
        while(!this->converged){
            
            int startIdx = std::get<0>(this->idxs[thrIdx]);
            int endIdx = std::get<1>(this->idxs[thrIdx]);

            this->f(xk1, startIdx, endIdx);
            
            syncPoint.arrive_and_wait();

        }

    };

    //Compute overhead for thread init
    #if defined(OVERHEAD)
        utimer* threadTimer = new utimer("Thread init ", overhead);
    #endif

    //Perform parallel computation
    for(int j=0; j<this->nw; j++){
        thrs[j] = std::thread(executeChunck, maxIter, j);
    }

    #if defined(OVERHEAD)
        delete threadTimer;
    #endif

    for(int i=0; i<this->nw; i++){
        thrs[i].join();
    }

    std::cout << "Number of effective iterates: " << iter << std::endl;

    delete[] thrs;
}




