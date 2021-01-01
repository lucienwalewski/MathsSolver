#include "num_roots.hpp"

double Newton(double f(double),double x0,double eps,double K){
    double x_0 = x0;
    double x_1 = x_0 - f(x_0)/derivative(f,x_0);
    double k = 1;
    while (f(x_0) != 0 and k < K and abs(x_0-x_1)>eps){
        k = k+1;
        x_0 = x_1;
        x_1 =x_0 - f(x_0)/derivative(f,x_0);
    }
    return x_1;
};


vector<double> rootfinding(double f(double)){
    vector<double> x0;
    double i=-10000;
    while (i<10000){
        if (f(i)*f(i+0.01) <= 0){
            x0.push_back(i);
        }
        i=i+0.01;
    }
    vector<double> roots;
    for (vector<double>::iterator i=x0.begin(); i!= x0.end(); i++){
        if (abs(derivative(f,*i)) >1e-5){roots.push_back(Newton(*f,*i,1e-6,100));}
        else{
            roots.push_back((int)((*i)*1000000)/1000000);
        }
    }

    return roots;

};
