#include "../src/utimer.cpp"
#include "mapClass.hpp"
#include <omp.h>

std::vector<float> jacobiSeq(Matrix A, std::vector<float> b, std::vector<float>& sol, int threshold);
void jacobiThrs(Matrix mat, std::vector<float> b, std::vector<float>& sol, int threshold, int nw);
std::vector<float> jacobiOpenmp(Matrix A, std::vector<float> b, std::vector<float> sol, int threshold, int nw);