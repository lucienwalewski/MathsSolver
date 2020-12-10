#ifndef NUM_ROOTS_HPP
#define NUM_ROOTS_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include <list>
#include "num_derivation.hpp"

double Newton(double f(double),double x0,double eps,double K);


list<double> rootfinding(double f(double));

#endif // NUM_ROOTS_HPP
