#include "../src/utimer.cpp"
#include "mapClass.hpp"
#include <omp.h>

auto jacobiSeq(mv::Matrix A, mv::Vector b, mv::Vector &sol, const std::function<bool(mv::Vector, double)>& stoppingCriteria, int nIter, double tol) -> mv::Vector;
void jacobiThrs(mv::Matrix mat, mv::Vector b, mv::Vector& sol, int threshold, int nw);
auto jacobiOpenmp(mv::Matrix A, mv::Vector b, mv::Vector sol, const std::function<bool(mv::Vector, double)>& stoppingCriteria, int nIter, double tol, int nw) -> mv::Vector;
auto jacobiFF(mv::Matrix A, mv::Vector b, mv::Vector &sol, const std::function<bool(mv::Vector, double)>& stoppingCriteria, int nIter, double tol, int nw) -> mv::Vector;