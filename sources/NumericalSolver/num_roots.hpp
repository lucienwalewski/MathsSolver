#ifndef NUM_ROOTS_HPP
#define NUM_ROOTS_HPP

#include "Include_libraries.h"
#include "num_derivation.hpp"

using namespace std;

double Newton(double f(double),double x0,double eps,double K);

vector<double> rootfinding(double f(double));

#endif // NUM_ROOTS_HPP
