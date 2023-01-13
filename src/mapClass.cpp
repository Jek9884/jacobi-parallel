#include "../include/mapClass.hpp"

/**
 * @brief Generate chunks for data computation
 * 
 * @return std::vector<std::tuple<int, int>> vector of tuples. Each tuple is composed respectively by start index and end index of the chunck.
 */
std::vector<std::tuple<int, int>> Map::generateBlocks(){

    int n = this->dim;
    std::vector<std::tuple<int, int>> indexes(this->nw);

    if(this->mode == map_mode::Chunk){
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
Map::Map(int dim, map_mode mode, int pardegree, const std::function<void(mv::Vector&, int, int)>& f){
    this->dim = dim;
    this->mode = mode;
    this->nw = pardegree;
    this->f = f;
    this->idxs = this->generateBlocks();
}

/**
 * @brief Perform Map computation 
 * 
 * @param nIter max number of iterations that each thread can perform
 * @param xk solution vector
 */
void Map::execute(int nIter, mv::Vector &xk){

    mv::Vector xk1(xk.size());
    auto sync_f = [&](){
        //Update solution vector
        xk = xk1;
    };

    std::barrier syncPoint(this->nw, sync_f);

    //Compute overhead for thread init
    #if defined(OVERHEAD)
        utimer* threadTimer = new utimer("Thread init ", overhead);
    #endif
    
    auto *thrs = new std::thread[this->nw];
    
    #if defined(OVERHEAD)
        delete threadTimer;
    #endif

    //Lambda function passed to a thread
    auto executeChunck = [this, &syncPoint, &xk1](int n, int thrIdx){
        for(int j=0; j<n; j++) {
            int startIdx = std::get<0>(this->idxs[thrIdx]);
            int endIdx = std::get<1>(this->idxs[thrIdx]);

            this->f(xk1, startIdx, endIdx);
            
            //Compute time passed in a sync point
            #if defined(OVERHEAD)
                utimer* barrierTimer = new utimer("Barrier time iter " + j, overhead);
            #endif
            
            syncPoint.arrive_and_wait();
            
            #if defined(OVERHEAD)
                delete barrierTimer;
            #endif
        }
    };

    //Perform parallel computation
    for(int j=0; j<this->nw; j++){
        thrs[j] = std::thread(executeChunck, nIter, j);
    }
    for(int i=0; i<this->nw; i++){
        thrs[i].join();
    }


    delete[] thrs;
}




