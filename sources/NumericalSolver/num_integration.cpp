#include "num_integration.hpp"

double Legendre(int n,double x){
    if (n==0){
        return x*0+1.0;
    }
    else if (n==1){
        return x;
    }
    else{
        return (x*Legendre(n-1,x)*(2*n-1)-Legendre(n-2,x)*(n-1))/n;
    }
};

double pi = 3.1415;

double DLegendre(int n,double x){
    if (n==0){
        return x*0;
    }
    else if (n==1){
        return x*0+1.0;
    }
    else{
        return ((n/(pow(x,2)-1.0))*(x*Legendre(n,x)-Legendre(n-1,x)));
    }
};

vector<double> LegendreRoots(int polyorder){
    double tolerance=1e-20;
    std::vector<double> roots;
    if (polyorder<2){
        std::vector<double> l;
        return l;
    }
    else{for (int i=1; i != int(polyorder/2)+1;i++){
            double x = cos(pi*(i-0.25)/(polyorder+0.5));
            double error=10*tolerance;
            int iters=0;
            while (error>tolerance and iters<1000){
                        double dx=-Legendre(polyorder,x)/DLegendre(polyorder,x);
                        x=x+dx;
                        iters=iters+1;
                        error=abs(dx);
            }
            roots.push_back(x);
        }
        if (polyorder%2 == 0){
            vector<double> final_roots;
            for (std::vector<double>::iterator i=roots.begin(); i!=roots.end(); i++){
                final_roots.push_back(-(*i));
            }
            for (std::vector<double>::iterator i=roots.end()-1; i!= roots.begin()-1; i--){
                final_roots.push_back((*i));
            }
            return final_roots;
        }
        else{
            vector<double> final_roots;
            for (std::vector<double>::iterator i=roots.begin(); i!=roots.end(); i++){
                final_roots.push_back(-(*i));
            }
            final_roots.push_back(0);
            for (std::vector<double>::iterator i=roots.end()-1; i!= roots.begin()-1; i--){
                if (i!=roots.begin()){
                    final_roots.push_back((*i));
                }
            return final_roots;
            }
        }
    }
    return roots;
};

Xarray GaussLegendreWeights(int polyorder){
    std::vector<double> W;
    vector<double> final_roots =LegendreRoots(polyorder);
    double N=0;
    for (std::vector<double>::iterator i=final_roots.begin(); i!=final_roots.end(); i++){
        N++;
    }
    Xarray roots = Xarray(N,final_roots);
    if (W == final_roots){
        return Xarray();
    }
    else{
        Xarray W = ((-roots.power(2)+1)*(roots.apply_legendre(DLegendre, polyorder).power(2))).inverse()*2;
        return W;
    }
};

double GaussLegendreQuadrature(double func(double), double a, double b){
    std::vector<double> W;
    vector<double> final_roots =LegendreRoots(10);
    double N=0;
    for (std::vector<double>::iterator i=final_roots.begin(); i!=final_roots.end(); i++){
        N++;
    }
    Xarray roots = Xarray(N,final_roots);
    if (N == 0){
        return 0;
    }
    else{
        Xarray W = GaussLegendreWeights(10);
        return (b-a)*0.5*(W*( roots*(b-a)*0.5+ (b+a)*0.5 ).apply_function(func)).sum();
    };
};
