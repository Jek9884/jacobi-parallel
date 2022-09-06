#include "utils.hpp"

void print_vec(std::vector<float> vec){

    for(int i=0; i<vec.size(); i++){
        std::cout << std::to_string(vec[i]) + "\t";
    }

    std::cout << std::endl;
}

std::vector<float> init_vec(int n){


    std::vector<float> vec(n);

    for(int i=0; i<n; i++){
        vec[i] = (rand() % rand_max) + 1;
    }

    return vec;
}