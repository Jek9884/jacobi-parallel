#include "../include/jacobi.hpp"
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))

void test_sequential_jacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int maxIter, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "sequential"+sepPer+std::to_string(maxIter)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i = 0; i <nRuns; i++){
        mv::Vector x = sol;
        
        #if defined(PERFORMANCE)
            utimer* seqTimer = new utimer("Jacobi sequential performance", performance);
        #endif

        jacobiSeq(a, b, x, mv::checkRes, maxIter, 1e-8);
        
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

void test_thread_jacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int threshold, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "thread"+sepPer+std::to_string(nw)+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){

        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* performanceTimer = new utimer("Jacobi thread performance", performance);
        #endif

        jacobiThrs(a, b, x, threshold, nw, mv::checkRes, 1e-8);

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

void test_openmp_jacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int threshold, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "openmp"+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif

    for(int i=0; i<nRuns; i++){
        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* openmpTimer = new utimer("Jacobi openMP performance", performance);
        #endif

        jacobiOpenmp(a, b, x, mv::checkRes, threshold, 1e-8, nw);

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

void test_ff_jacobi(mv::Matrix a, mv::Vector b, mv::Vector sol, mv::Vector expected, int nw, int threshold, int nRuns){

    #if defined(PERFORMANCE)
        std::string sepPer = ",";
        std::string headerPer = "ff"+sepPer+std::to_string(threshold)+sepPer+std::to_string(b.size())+";";
        writeOnFile(headerPer, RESULTS_FOLDER, PERFORMANCE_IN_FILENAME);
    #endif
    
    for(int i=0; i<nRuns; i++){
        mv::Vector x = sol;

        #if defined(PERFORMANCE)
            utimer* ffTimer = new utimer("Jacobi FastFlow performance", performance);
        #endif

        jacobiFF(a, b, x, mv::checkRes, threshold, 1e-8, nw);
        
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

void eval_performance(){

    std::vector<int> nws = {1,2,3,4,5,6,7,8};
    std::vector<int> dim = {128, 256, 512, 1024, 2048, 4096, 8192};
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
                if(dim[j] <= 2048){
                    maxIt = maxIter[k];
                }
                test_sequential_jacobi(a, b, x, expected, maxIt, nRuns[l]);

                for(int i=0; i<nws.size(); i++){
                    
                    x = sol;
                    test_thread_jacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);
                    x = sol;
                    test_openmp_jacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);
                    x = sol;
                    test_ff_jacobi(a, b, x, expected, nws[i], maxIt, nRuns[l]);

                }
            }
        }
    }
}

int main(int argc, char *argv[]){

    //assertm((argc == 8), "Number of workers, matrix dimension, max number of iterations and number of runs are required");

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
            test_sequential_jacobi(a, b, x, expected, maxIter, nRuns);
        }

        if(thrRun == 1){
            mv::Vector x = sol;
            printf("Thread\n");
            test_thread_jacobi(a, b, x, expected, nw, maxIter, nRuns);  
        }

        if(openmpRun == 1){
            mv::Vector x = sol;
            printf("OpenMP\n");
            test_openmp_jacobi(a, b, x, expected, nw, maxIter, nRuns);
        }

        if(ffRun == 1){
            mv::Vector x = sol;
            printf("Fast Flow\n");
            test_ff_jacobi(a, b, x, expected, nw, maxIter, nRuns);
        }
    }
    else if(argc == 1){
        eval_performance();
    }

    return 0;
}
