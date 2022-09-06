#include "matrix.hpp"

std::vector<std::vector<float>> Matrix::init_square_matrix(int n){

    std::vector<std::vector<float>> matrix(n);
    srand(time(NULL));


    for(int i=0; i<n; i++){
        matrix[i].resize(n);
        for(int j=0; j<n; j++){
            matrix[i][j] = (rand() % rand_max) + 1;
        }
    }

    return matrix;
}

void Matrix::init_values(){
    grid = this->init_square_matrix(this->n);
}

Matrix::Matrix(int n, bool init=false)
        : n(n){
    if(init){
        init_values();
    }
}

void Matrix::print(){

    for(int i=0; i<this->n; i++){
        for(int j=0; j<this->n; j++){
            std::cout << std::to_string(grid[i][j]) + "\t";
        }
        std::cout << std::endl;
    }
}