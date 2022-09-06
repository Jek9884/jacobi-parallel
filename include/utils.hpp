#include <iostream>
#include <vector>
#include <ctime> //seed for rand()
#include <cstdlib> //rand numbers
#include <cmath> //sqrt
#include <numeric> //inner_product
#include <string>

const int rand_max = 10;

void print_matrix(std::vector<std::vector<float>> matrix);
void print_vec(std::vector<float> vec);
std::vector<float> init_vec(int n);