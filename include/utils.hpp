#include <iostream>
#include <vector>
#include <cmath> //ceil
#include <string>
#include<tuple>

namespace mv{

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    inline Matrix genUnaryMatrix(int n){

        Matrix mat(n, Vector(n,1));
        return mat;
    }

    inline Matrix genDiagonallyDominantMatrix(int matDim){

        auto mat = genUnaryMatrix(matDim);
        for(int i=0;i<matDim;i++){
            mat[i][i] += matDim;
        }

        return mat;
    }

    inline Vector genVec(int dim){

        Vector vec(dim, 2*dim);
        return vec;
    }

    inline std::tuple<Matrix, Vector, Vector, Vector> generateSystem(int matDim){

        auto mat = genDiagonallyDominantMatrix(matDim);
        auto b = genVec(matDim);
        Vector sol(matDim, 0);
        Vector expectedSol(matDim, 1);

        return std::make_tuple(mat, b, sol, expectedSol);

    }

    inline void printVec(const mv::Vector& vec){

        for(double i : vec){
            std::cout << std::to_string(i) + "\t";
        }

        std::cout << std::endl;
    }

    inline void printMat(const mv::Matrix& mat){

        for(const mv::Vector& vec : mat){
            for(double elem : vec){
                std::cout << std::to_string(elem) + "\t";
            }
            std::cout << std::endl;
        }

    }

    inline bool equalsVec(mv::Vector a, mv::Vector b, double tol = 1e-8){

        bool equals = true;
        int size = static_cast<int>(a.size());

        for(int i=0;i<size;i++){
            if(std::abs(a[i]-b[i]) > tol){
                equals = false;
            }
        }

        return equals;
    }

}