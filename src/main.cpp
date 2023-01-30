#include "../include/jacobi.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))


//Test sequential implementation of the Jacobi method
void testSequentialJacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int maxIter, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "sequential"+sepPer+"1"+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i = 0; i <nRuns; i++){
        mv::Vector x = sol;
        
        #if defined(PERFORMANCE)
            utimer* seqTimer = new utimer("Jacobi sequential performance", performance);
        #endif

        jacobiSeq(a, b, x, maxIter, mv::checkRes, 1e-8);
        
        #if defined(PERFORMANCE)
            delete seqTimer;
        #endif
        
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
    
}

//Test C++ threads implementation of the Jacobi method
void testThreadJacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int maxIter, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "thread"+sepPer+std::to_string(nw)+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){

        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* performanceTimer = new utimer("Jacobi thread performance", performance);
        #endif

        jacobiThrs(a, b, x, maxIter, mv::checkRes, 1e-8, nw);

        #if defined(PERFORMANCE)
            delete performanceTimer;
        #endif
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
}

//Test OpenMP implementation of the Jacobi method
void testOpenmpJacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int maxIter, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "openmp"+sepPer+std::to_string(nw)+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){
        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* openmpTimer = new utimer("Jacobi openMP performance", performance);
        #endif

        jacobiOpenmp(a, b, x, maxIter, mv::checkRes, 1e-8, nw);

        #if defined(PERFORMANCE)
            delete openmpTimer;
        #endif

        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif
}

//Test FastFlow implementation of the Jacobi method
void testFFJacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int maxIter, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "ff"+sepPer+std::to_string(nw)+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif
    
    for(int i=0; i<nRuns; i++){
        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* ffTimer = new utimer("Jacobi FastFlow performance", performance);
        #endif

        jacobiFF(a, b, x, maxIter, mv::checkRes, 1e-8, nw);
        
        #if defined(PERFORMANCE)
            delete ffTimer;
        #endif
        
        if(mv::equalsVec(x, expected)){
            std::cout << "true" << std::endl;
        }
        else{
            std::cout << "false" << std::endl;
        }
    }

    #if defined(PERFORMANCE)
        writeOnFile("\n", RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
        extractTime(RESULTS_FOLDER, PERFORMANCE_IN_FILENAME, PERFORMANCE_OUT_FILENAME);
    #endif

}

//Perform tests on different combination of number of workers and matrix dimensions
void evalPerformance(int mode){

    std::vector<int> nws = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    std::vector<int> dim = {128,256,512,1024,2048,4096,8192};
    std::vector<int> maxIter = {100000};
    std::vector<int> nRuns = {5};

    for(int l=0; l<nRuns.size(); l++){
        for(int j=0; j<dim.size(); j++){

            std::tuple data = mv::generateSystem(dim[j]);
            mv::Matrix a = std::get<0>(data);
            mv::Vector b = std::get<1>(data);
            mv::Vector sol = std::get<2>(data);
            mv::Vector expected = std::get<3>(data);
            int maxIt = 1000;

            for(int k=0; k<maxIter.size(); k++){

                mv::Vector x = sol;
                if(dim[j] < 1024){
                    maxIt = maxIter[k];
                }
		
                if(mode == 0){
                        testSequentialJacobi(a, b, x, expected, maxIt, nRuns[l]);
                }

                for(int i=0; i<nws.size(); i++){
                    
                    x = sol;
                    testThreadJacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);

                    if(mode == 0){
                        x = sol;
                        testOpenmpJacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);
                        x = sol;
                        testFFJacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);
                    }
                }
            }
        }
    }
}

//Evaluate the time spent with the serial fraction
void evalSerialFraction(){

    std::vector<int> dim = {128,256,512,1024,2048,4096,8192, 16384};
    int nRuns = 5;
    int iter = 0;
    int maxIter = 10000;

    for(int i=0; i<nRuns; i++){
        for(int j=0; j<dim.size(); j++){

            std::tuple data = mv::generateSystem(dim[j]);
            mv::Vector sol = std::get<2>(data);
            mv::Vector expected = std::get<3>(data);
            {
                utimer timer("Serial time ");
                sol = expected;
                (mv::checkRes(sol, 1e-8) && (iter < maxIter));
                iter++;
            }
        }
    }
}

//Evaluate the time spent for the threads initialization
void evalThreadOverhead(){

    //Dummy lambda function passed to a thread
    auto executeThr = [](int nIter){
        int x=0;
        for(int i=0; i<nIter; i++){
            x++;
        }
    };
    
    std::vector<int> nws = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    for(int i=0; i<nws.size(); i++){
        {
            utimer timer("Thread init time ");
            auto *thrs = new std::thread[nws[i]];
            for(int j=0; j<nws[i]; j++){
                thrs[j] = std::thread(executeThr, 100);
            }   
        }

    }
}

int main(int argc, char *argv[]){

    assertm((argc == 9 || argc == 2 ), "Missing parameters");
    if(argc == 9){
        int nw = (int) strtol(argv[1], nullptr, 10);
        int dim = (int) strtol(argv[2], nullptr, 10);
        int maxIter = (int) strtol(argv[3], nullptr, 10);
        int nRuns = (int) strtol(argv[4], nullptr, 10);
        int seqRun = (int) strtol(argv[5], nullptr, 10);
        int thrRun = (int) strtol(argv[6], nullptr, 10);
        int openmpRun = (int) strtol(argv[7], nullptr, 10);
        int ffRun = (int) strtol(argv[8], nullptr, 10);

        std::tuple data = mv::generateSystem(dim);
        mv::Matrix a = std::get<0>(data);
        mv::Vector b = std::get<1>(data);
        mv::Vector sol = std::get<2>(data);
        mv::Vector expected = std::get<3>(data);

        if(seqRun == 1){
            mv::Vector x = sol;
            printf("Sequential\n");
            testSequentialJacobi(a, b, x, expected, maxIter, nRuns);
        }

        if(thrRun == 1){
            mv::Vector x = sol;
            printf("Thread\n");
            testThreadJacobi(a, b, x, expected, nw, maxIter, nRuns);  
        }

        if(openmpRun == 1){
            mv::Vector x = sol;
            printf("OpenMP\n");
            testOpenmpJacobi(a, b, x, expected, nw, maxIter, nRuns);
        }

        if(ffRun == 1){
            mv::Vector x = sol;
            printf("Fast Flow\n");
            testFFJacobi(a, b, x, expected, nw, maxIter, nRuns);
        }
    }
    else if(argc == 2){
	int mode = (int) strtol(argv[1], nullptr, 10);
        if(mode < 2){
            evalPerformance(mode);    
        }
        else if(mode == 2){
            evalSerialFraction();
        }
        else{
            evalThreadOverhead();
        }
        
    }
    
    return 0;
}
