#include "utils.hpp"

class Matrix{
public:
    std::vector<std::vector<float>> grid;
    Matrix(int n, bool init);
    void init_values();
    void print();


private:
    int n;
    std::vector<std::vector<float>> init_square_matrix(int n);
};
