#ifndef GAUSSIN_HPP
#define GAUSSIN_HPP

#include <iostream>
#include "matrix.hpp"

using namespace std;

template <typename T> void gaussian(Matrix<T> A, Matrix<T>  Y){
    // cases when there is no solution or when there is infinitely many ones should be covered
    int n = A.height();
    int m = A.width();
    cout << "Solving ";
    display_system(A, Y);
    for (int j = 0; j < m-1; j++) {
        for(int i = j+1; i < n; i++) {
            if (A.get_element(j, j) != Rational(0, 1) && A.get_element(i, j) != Rational(0, 1)) {
                T k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                Y.mult_row(j, k);
                A.sub_row(i, j);
                Y.sub_row(i, j);
                cout << "We have multiplied equation " << j+1 << " by " << to_str(k) << ", and have substracted equation " << j+1 << " to equation " << i+1 << ", we obtain this ";
                display_system(A, Y);
            }
        }
    }
    for (int j = m-1; j > 0; j--) {
        for (int i = j-1; i >= 0; i--) {
            if (A.get_element(j, j) != 0 && A.get_element(i, j) != 0) {
                T k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                Y.mult_row(j, k);
                A.sub_row(i, j);
                Y.sub_row(i, j);
                cout << "We have multiplied equation " << j+1 << " by " << to_str(k) << ", and have substracted equation " << j+1 << " to equation " << i+1 << ", we obtain this ";
                display_system(A, Y);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Y.mult_row(i, Rational(1,1)/A.get_element(i, i));
    }
    cout << "Solutions:\n";
    for (int i = 0; i < n; i++) {
        if (Y.get_element(i, 0) == 0) {
            cout << "x" << i << " = " << 0 << "\n";
        } else {
            cout << "x" << i << " = " << to_str(Y.get_element(i, 0)) << "\n";
        }
    }
   /* if (is_not_round(Y)) {
        cout << "It is likely that there were a mistake of computations, these are the correct solutions:" << "\n";
        for (int i = 0; i < n; i++) {
            cout << "x" << i << " = " << round(Y.get_element(i, 0)) << "\n";
        }
    }*/
}

template <typename T> void display_system(Matrix<T>  A, Matrix<T>  Y){
    int n = A.width();
    cout << "System of size " << n << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Equation " << i+1 << ": ";
        int cache = 0;
        for (int j = 0; j < n; j++) {
            if (A.get_element(i, j) != Rational(0,1)) {
                if (A.get_element(i, j) == Rational(1,1) || A.get_element(i, j) == Rational(-1,1)) {
                    if (A.get_element(i, j) ==  Rational(-1,1)) {
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
                        cout << to_str(A.get_element(i, j)) << "x" << j << " ";
                        cache = 1;
                    } else {
                        cout << "+" << to_str(A.get_element(i, j)) << "x" << j << " ";
                        cache = 1;
                    }
                }
            }
        }
        cout << "= " << to_str(Y.get_element(i, 0)) << "\n";
    }
    cout << "\n";
}

bool is_not_round(Matrix<double> Y);

#endif // GAUSSIN_HPP
