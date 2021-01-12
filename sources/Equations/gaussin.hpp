#ifndef GAUSSIN_HPP
#define GAUSSIN_HPP

#include "Include_libraries.h"
#include "matrix.hpp"

using namespace std;

template <typename T> vector<string> gaussian(Matrix<T> A, Matrix<T>  Y){
    int n = A.height();
    int m = A.width();
    vector<string> res = display_system(A, Y);
    res[0] = "Solving " + res[0];
    for (int j = 0; j < m-1; j++) {
        for(int i = j+1; i < n; i++) {
            if (A.get_element(j, j) != Rational(0, 1) && A.get_element(i, j) != Rational(0, 1)) {
                T k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                Y.mult_row(j, k);
                A.sub_row(i, j);
                Y.sub_row(i, j);
                res.push_back("We have multiplied equation " + to_str(j+1) + " by " + to_str(k) + ", and have substracted equation " + to_str(j+1) + " to equation " + to_str(i+1) + ", we obtain this ");
                vector<string> disp = display_system(A, Y);
                res.insert(res.end(), disp.begin(), disp.end());
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
                res.push_back("We have multiplied equation " + to_str(j+1) + " by " + to_str(k) + ", and have substracted equation " + to_str(j+1) + " to equation " + to_str(i+1) + ", we obtain this ");
                vector<string> disp = display_system(A, Y);
                res.insert(res.end(), disp.begin(), disp.end());
            }
        }
    }
    for (int i = 0; i < n; i++) {
        Y.mult_row(i, Rational(1,1)/A.get_element(i, i));
    }
    res.push_back("r");
    res.push_back("Solution of the system of equations");
    res.push_back(":");
    res.push_back("n");
    for (int i = 0; i < n; i++) {
        if (Y.get_element(i, 0) == 0) {
            res.push_back("x" + to_str(i) + " = 0");
        } else {
            res.push_back("x" + to_str(i) + " = " + to_str(Y.get_element(i, 0)));
        }
    }

    return res;

}

template <typename T> vector<string> display_system(Matrix<T>  A, Matrix<T>  Y){
    int n = A.width();
    vector<string> steps;
    steps.push_back("System of size " + to_string(n) + ":\n");
    //steps.push_back("");
    for (int i = 0; i < n; i++) {
        steps[(int)steps.size() - 1] += "Equation " + to_string(i+1) + ": ";
        int cache = 0;
        for (int j = 0; j < n; j++) {
            if (A.get_element(i, j) != Rational(0,1)) {
                if (A.get_element(i, j) == Rational(1,1) || A.get_element(i, j) == Rational(-1,1)) {
                    if (A.get_element(i, j) ==  Rational(-1,1)) {
                        steps[(int)steps.size() - 1] += "-x" + to_string(j) + " ";
                        cache = 1;
                    } else if (cache ==  0) {
                        steps[(int)steps.size() - 1] += "x" + to_string(j) + " ";
                        cache = 1;
                    } else {
                        steps[(int)steps.size() - 1] += "+x" + to_string(j) + " ";
                        cache = 1;
                    }
                }
                else {
                    if (A.get_element(i, j) < 0 || (A.get_element(i, j) > 0 && cache ==  0)) {
                        steps[(int)steps.size() - 1] +=  to_str(A.get_element(i, j))+ "x" + to_string(j) + " ";
                        cache = 1;
                    } else {
                        steps[(int)steps.size() - 1] += "+" + to_str(A.get_element(i, j)) + "x" + to_string(j) + " ";
                        cache = 1;
                    }
                }
            }
        }
        steps[(int)steps.size() - 1] +=  "= " + to_str(Y.get_element(i, 0)) + "\n";
    }

    steps[(int)steps.size() - 1] = steps[(int)steps.size() - 1].substr(0, (int)steps[(int)steps.size() - 1].size() - 1);
    return steps;
}

bool is_not_round(Matrix<double> Y);

#endif // GAUSSIN_HPP
