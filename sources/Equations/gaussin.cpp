#include<iostream>
#include "gaussin.hpp"
#include "matrix.hpp"
\
using namespace std;

void gaussian(Matrix A, Matrix Y) {
    int n = A.height();
    int m = A.width();
    cout << "Solving ";
    display_system(A, Y);
    for (int j = 0; j < m-1; j++) {
        for(int i = j+1; i < n; i++) {
            if (A.get_element(j, j) != 0 && A.get_element(i, j) != 0) {
                double k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                Y.mult_row(j, k);
                A.sub_row(i, j);
                Y.sub_row(i, j);
                cout << "We have multiplied equation " << j+1 << " by " << k << ", and have substracted equation " << j+1 << " to equation " << i+1 << ", we obtain this ";
                display_system(A, Y);
            }
        }
    }
    for (int j = m-1; j > 0; j--) {
        for (int i = j-1; i >= 0; i--) {
            if (A.get_element(j, j) != 0 && A.get_element(i, j) != 0) {
                double k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                Y.mult_row(j, k);
                A.sub_row(i, j);
                Y.sub_row(i, j);
                cout << "We have multiplied equation " << j+1 << " by " << k << ", and have substracted equation " << j+1 << " to equation " << i+1 << ", we obtain this ";
                display_system(A, Y);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Y.mult_row(i, 1/A.get_element(i, i));
    }
    cout << "Solutions:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = " << Y.get_element(i, 0) << endl;
    }
}

void display_system(Matrix A, Matrix Y) {
    int n = A.width();
    cout << "System of size " << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Equation " << i+1 << ": ";
        int cache = 0;
        for (int j = 0; j < n; j++) {
            if (A.get_element(i, j) != 0) {
                if (A.get_element(i, j) == 1 || A.get_element(i, j) == -1) {
                    if (A.get_element(i, j) == -1) {
                        cout << "-" << "x" << j << " ";
                        cache = 1;
                    } else if (cache ==  0) {
                        cout << "x" << j << " ";
                        cache = 1;
                    } else {
                        cout << "+" << "x" << j << " ";
                        cache = 1;
                    }
                } else {
                    if (A.get_element(i, j) < 0 || (A.get_element(i, j) > 0 && cache ==  0)) {
                        cout << A.get_element(i, j) << "x" << j << " ";
                        cache = 1;
                    } else {
                        cout << "+" << A.get_element(i, j) << "x" << j << " ";
                        cache = 1;
                    }
                }
            }
        }
        cout << "= " << Y.get_element(i, 0) << endl;
    }
    cout << endl;
}
