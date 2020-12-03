#include<iostream>
#include "step.h"
using namespace std;


void linear_step()
{
    int n;
    std::cout<<"the number of unknows n=";
    std::cin >>n;
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

        cout<<"the equation "<< i << " is " ;
        for (int j=0; j<n-1 ; j++)
        {
            cout<< a[i][j] << "x_"<< j << " + " ;
        }
        cout<< a[i][n-1] << "x_"<< n-1 << " = "<<b[i] <<endl;
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

    cout << "Using Gaussin Elimation The equations is:" << endl;
    for (i = 0; i < n; i++)
    {
        for (j=0; j<n-1; j++)
        {
            cout << a[i][j] << "x_" << j << " + " ;
        }
        cout << a[i][n-1] << "x_" << n-1 << " = "<< b[i] <<endl;
    }
    int js=0;
    bool flag=true;
    bool nsol=false;
    for (i=0; i<n; i++)
    {
        bool f=false;
        for (j=0; j<n; j++)
        {
            if (a[i][j]!=0)
            {
                f=true;
                break;
            }
        }
        if (not f)
        {
            flag=false;
            if (b[i]!=0)
            {
                js=i;
                nsol=true;
            }
        }

    }

    if (flag)
    {
        cout<<"the equations have one solution"<<endl;
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
    else
    {
        if (nsol)
        {
            cout<<"the equations have no solution as "<< b[js]<<" = 0"<<endl;
        }
        else
        {
            cout<<"the equations have infinite solutions"<<endl;
        }
    }

}

int main()
{
   linear_step();
   return 0;
}
