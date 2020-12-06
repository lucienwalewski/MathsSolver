#include "num_integration.hpp"
#define DIV 10000

double integral(double f(double), double a, double b){
    double h = (b-a)/DIV;
    double T=0;
    double x=a;

    T=0.5*f(x);
    for(int i=1; i<DIV; i++){
        x+=h;
        //cout<<T<<"\n";
        T+= f(x);
    }
    x+=h;
    T+=0.5*f(x);
    T*=h;

    return T;
}
