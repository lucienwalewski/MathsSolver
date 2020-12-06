#include<iostream>
#include "gaussin.hpp"
\
using namespace std;

void gaussin(int n)
{
    double a[n][n];
    double b[n];
    double xin;
    for (int i=0;i<n;i++)
    {
        for (int j=0; j<n;j++)
        {
            std::cin>>xin;
            a[i][j]=xin;
        }
        std::cin>>xin;
        b[i]=xin;
    }


    int i, j, k;
    double c[n];

    for (k = 0; k < n - 1; k++)
    {

        for (i = k + 1; i < n; i++)
            c[i] = a[i][k] / a[k][k];


        for (i = k + 1; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                a[i][j] = a[i][j] - c[i] * a[k][j];
            }
            b[i] = b[i] - c[i] * b[k];
        }
    }


    double x[n];
    x[n - 1] = b[n - 1] / a[n - 1][n - 1];
    for (i = n - 2; i >= 0; i--)
    {
        double sum = 0;
        for (j = i + 1; j < n; j++)
        {
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
    }

    std::cout << "The solution of the equations is:" << std::endl;
    for (i = 0; i < n; i++)
        std::cout <<"x"<<i+1<<"="<< x[i] << std::endl;
}


