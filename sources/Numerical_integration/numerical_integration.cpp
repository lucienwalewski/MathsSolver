#include "numerical_integration.hpp"

double derivative(double f(double), double a){
    return (int)((f(a+1e-10)-f(a-1e-10))/(2e-10) * 100000.0)/100000.0;
};
