#ifndef NUM_ODE_HPP
#define NUM_ODE_HPP


double ODE_1st_order_solver(double x0, double y, double x, double f(double,double));

double ODE_2nd_order_solver(double x0, double dy, double y, double x, double f(double,double,double));

double ODE_3rd_order_solver(double x0, double d2y, double dy, double y, double x, double f(double,double,double,double));


#endif // NUM_ODE_HPP
