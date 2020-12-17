#include<iostream>
#include "gaussin.hpp"
#include "matrix.hpp"
\
using namespace std;

void gaussian(int n) {

    Matrix<double> A(n, n), Y(n, 1);
    double xin;
    for (int i=0;i<n;i++)
    {
        for (int j=0; j<n;j++)
        {
            std::cin>>xin;
            A.set_element(i, j, xin);
        }
        std::cin>>xin;
        Y.set_element(i, 0, xin);
    }
    Matrix<double> X(n, 1);
    X = A.inverse() * Y;
    std::cout << "The solution of the equations is:" << std::endl;
    for (int i = 0; i < n; i++) {
        cout <<"x"<<i+1<<"="<< X.get_element(i, 0) << endl;
    }

}
