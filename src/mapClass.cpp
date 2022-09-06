#include "../include/mapClass.hpp"

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

Map::Map(int dim, map_mode mode, int pardegree, std::function<void(std::vector<float>&, int, int)> f){
    this->dim = dim;
    this->mode = mode;
    this->nw = pardegree;
    this->f = std::move(f);
    this->idxs = this->generateBlocks();
}

void Map::execute(int nIter, std::vector<float> &xk){

    std::vector<float> xk1(xk.size());
    auto sync_f = [&](){
        xk = xk1;
    };

    std::barrier syncPoint(this->nw, sync_f);

    auto *thrs = new std::thread[this->nw];


    auto executeChunck = [this, &syncPoint, &xk1](int n, int thrIdx){


        for(int j=0; j<n; j++) {
            int startIdx = std::get<0>(this->idxs[thrIdx]);
            int endIdx = std::get<1>(this->idxs[thrIdx]);
            this->f(xk1, startIdx, endIdx);
            syncPoint.arrive_and_wait();
        }
    };

    for(int j=0; j<this->nw; j++){
        thrs[j] = std::thread(executeChunck, nIter, j);
    }
    for(int i=0; i<this->nw; i++){
        thrs[i].join();
    }


    delete[] thrs;
}




