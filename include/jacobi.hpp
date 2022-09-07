#include "../src/utimer.cpp"
#include "mapClass.hpp"
#include <omp.h>

mv::Vector jacobiSeq(mv::Matrix A, mv::Vector b, mv::Vector& sol, int threshold);
void jacobiThrs(mv::Matrix mat, mv::Vector b, mv::Vector& sol, int threshold, int nw);
mv::Vector jacobiOpenmp(mv::Matrix A, mv::Vector b, mv::Vector sol, int threshold, int nw);