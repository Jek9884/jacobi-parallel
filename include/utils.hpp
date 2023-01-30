#include <iostream>
#include <vector>
#include <cmath> //ceil
#include <string>
#include <tuple>
#include "../src/utimer.cpp"

namespace mv {

    using Vector = std::vector<double>;
    using Matrix = std::vector<Vector>;

    /**
     * @brief Generate a square matrix of size n with all ones
     * 
     * @param n dimension of the matrix
     * @return Matrix generated matrix
     */
    inline Matrix genUnaryMatrix(int n) {

        Matrix mat(n, Vector(n, 1));
        return mat;
    }

    /**
    * @brief Generate a diagonally dominant matrix (square)
    * 
    * @param matDim dimension of the square matrix
    * @return Matrix the generated matrix
    */
    inline Matrix genDiagonallyDominantMatrix(int matDim) {

        auto mat = genUnaryMatrix(matDim);
        for (int i = 0; i < matDim; i++) {
            mat[i][i] += matDim;
        }

        return mat;
    }

    /**
    * @brief Generate a vector of the indicated dim
    * 
    * @param matDim dimension of the vector
    * @return Vector the generated vector
    */
    inline Vector genVec(int dim) {

        Vector vec(dim, 2 * dim);
        return vec;
    }

    /**
    * @brief Generate a system of equations with a diagonally dominant matrix (square)
    * 
    * @param matDim dimension of the square matrix
    * @return std::tuple the generated system
    */
    inline std::tuple<Matrix, Vector, Vector, Vector> generateSystem(int matDim) {

        auto mat = genDiagonallyDominantMatrix(matDim);
        auto b = genVec(matDim);
        Vector sol(matDim, 0);
        Vector expectedSol(matDim, 1);

        return std::make_tuple(mat, b, sol, expectedSol);

    }

    /**
    * @brief Print on the console a vector
    * 
    * @param vec vector to print
    */
    inline void printVec(const mv::Vector &vec) {

        for (double i: vec) {
            std::cout << std::to_string(i) + "\t";
        }

        std::cout << std::endl;
    }

    /**
    * @brief Print on the console a matrix
    * 
    * @param mat matrix to print
    */
    inline void printMat(const mv::Matrix &mat) {

        for (const mv::Vector &vec: mat) {
            for (double elem: vec) {
                std::cout << std::to_string(elem) + "\t";
            }
            std::cout << std::endl;
        }

    }

    /**
     * @brief Perform an equals between two vector of size n w.r.t. a tolerance
     * 
     * @param a first vector to compare
     * @param b second vector to compare
     * @param tol tolerance to define two vector equals
     * @return true if the vectors are the same
     * @return false if the vectors are different
     */
    inline bool equalsVec(mv::Vector a, mv::Vector b, double tol = 1e-8) {

        bool equals = true;
        int size = static_cast<int>(a.size());

        for (int i = 0; i < size; i++) {
            if (std::abs(a[i] - b[i]) > tol) {
                equals = false;
            }
        }

        return equals;
    }

    /**
     * @brief Perform a difference element-wise between two vectors
     * 
     * @param a vector from which subtract
     * @param b vector to subtract
     * @return mv::Vector difference vector
     */
    inline mv::Vector diffVec(mv::Vector a, mv::Vector b) {

        int n = static_cast<int>(a.size());
        mv::Vector c(n);

        for (int i = 0; i < n; i++) {
            c[i] = a[i] - b[i];
        }

        return c;
    }

    /**
     * @brief Perform the norm of a vector
     * 
     * @param a vector to compute
     * @return double norm of the vector
     */
    inline double normVec(mv::Vector a) {

        double prod = 0;
        int n = static_cast<int>(a.size());

        for (int i = 0; i < n; i++) {
            prod += a[i]*a[i];
        }

        return sqrt(prod);
    }

    /**
     * @brief Check if the solution vector is equals to the real solution
     * 
     * @param a vector to compare
     * @param tol tolerance to define two vector equals
     * @return true if the solution vector is equal to the real solution
     * @return false if the solution vector differ from the real solution
     */
    inline auto checkRes(const mv::Vector& a, double tol) -> bool{

        bool equals = true;
        for(double elem : a){
            if(std::fabs(elem-1) > tol){
                equals = false;
            }
        }

        return equals;
    }
}