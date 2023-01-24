//#include "../src/utimer.cpp"
#include "mapClass.hpp"
#include <omp.h>

auto jacobiSeq(mv::Matrix A, mv::Vector b, mv::Vector &sol, int maxIter, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol) -> mv::Vector;
void jacobiThrs(mv::Matrix A, mv::Vector b, mv::Vector& sol, int maxIter,  const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol, int nw);
auto jacobiOpenmp(mv::Matrix A, mv::Vector b, mv::Vector& sol, int maxIter, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol, int nw) -> mv::Vector;
auto jacobiFF(mv::Matrix A, mv::Vector b, mv::Vector &sol, int maxIter, const std::function<bool(mv::Vector, double)>& stoppingCriteria, double tol, int nw) -> mv::Vector;