#include "num_ODE.hpp"
#include <iostream>
using namespace std;


double ODE_1st_order_solver(double x0, double y, double x, double f(double,double)) {
    double temp = 0;
    double h = 0.01;
    while (x0 < x) {
        temp = y;
        y = y +  h* f(x0, y);
        x0 = x0 + h;
    }
    temp = y;
    return temp;
}

double ODE_2nd_order_solver(double x0, double dy, double y, double x, double f(double,double,double)){
    double v = dy;
    double h = 0.01;
    while (x0 < x) {
        y=y+h*v;
        v=v+h*f(x0,y,v);
        x0 = x0 + h;
    }
    return y;
}

double ODE_3rd_order_solver(double x0, double d2y, double dy, double y, double x, double f(double,double,double,double)){
    double h = 0.01;
    while (x0 < x) {
        y=y+h*dy;
        dy=dy+h*d2y;
        d2y=d2y+h*f(x0,y,dy,d2y);
        x0 = x0 + h;
    }
    return y;
}
