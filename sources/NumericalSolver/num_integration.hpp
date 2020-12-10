#ifndef NUM_INTEGRATION_HPP
#define NUM_INTEGRATION_HPP

#include <cmath>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Xarray {
public:
  Xarray(){length = 0; std::vector<double> array; this->array = array;}
  Xarray(int len, vector<double> x){length = len; array = x;};

  int get_length() {return length;}
  vector<double> get_array() {return array;}

  Xarray operator+(Xarray xarray){
      std::vector<double> l;
      vector<double> new_array = xarray.get_array();
      for (int i =0;i!=length;i++){
          l.push_back(array[i]+new_array[i]);
      }
      return Xarray(length, l);
  };

  Xarray operator-(Xarray xarray){
      std::vector<double> l;
      vector<double> new_array = xarray.get_array();
      for (int i =0;i!=length;i++){
          l.push_back(array[i]-new_array[i]);
      }
      return Xarray(length, l);
  };

  Xarray operator-(){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(-array[i]);
      }
      return Xarray(length, l);
  };

  Xarray operator*(Xarray xarray){
      std::vector<double> l;
      vector<double> new_array = xarray.get_array();
      for (int i =0;i!=length;i++){
          l.push_back(array[i]*new_array[i]);
      }
      return Xarray(length, l);
  };

  Xarray operator/(Xarray xarray){
      std::vector<double> l;
      vector<double> new_array = xarray.get_array();
      for (int i =0;i!=length;i++){
          l.push_back(array[i]/new_array[i]);
      }
      return Xarray(length, l);
  };

  Xarray operator+(double a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(array[i]+a);
      }
      return Xarray(length, l);
  };
  Xarray operator-(double a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(array[i]-a);
      }
      return Xarray(length, l);
  };
  Xarray operator*(double a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(array[i]*a);
      }
      return Xarray(length, l);
  };
  Xarray operator*(int a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(array[i]*a);
      }
      return Xarray(length, l);
  };
  Xarray operator/(int a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(array[i]/a);
      }
      return Xarray(length, l);
  };
  Xarray power(int a){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(pow(array[i],a));
      }
      return Xarray(length, l);
  };
  Xarray inverse(){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(1/array[i]);
      }
      return Xarray(length, l);
  };
  Xarray apply_function(double f(double)){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(f(array[i]));
      }
      return Xarray(length, l);
  };

  Xarray apply_legendre(double f(int,double), int N){
      std::vector<double> l;
      for (int i =0;i!=length;i++){
          l.push_back(f(N,array[i]));
      }
      return Xarray(length, l);
  };

  double sum(){
      double N;
      for (int i =0;i!=length;i++){
          N = N+array[i];
      }
      return N;
  };

  int length;
  vector<double> array;

};

double Legendre(int n,double x);

double DLegendre(int n,double x);

vector<double> LegendreRoots(int polyorder);

Xarray GaussLegendreWeights(int polyorder);

double GaussLegendreQuadrature(double func(double), double a, double b);

#endif // NUM_INTEGRATION_HPP
