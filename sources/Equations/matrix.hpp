#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Matrix {

private:
    int n, m;
    vector< vector<double> > elements;

public:

    Matrix(int n, int m);

    int height() const {return n;};
    int width() const {return m;};

    double get_element(int i, int j) const {return elements[i][j];};


    void print_mat();

    void set_element(int i, int j, double element);

    void copy(Matrix &a);

    void id();

    Matrix col(int j);

    Matrix row(int i);

    void mult_row(int i, double k);

    void sub_row(int i, int j);

    Matrix operator + (const Matrix& a);

    Matrix operator - (const Matrix& a);

    Matrix operator * (const double& k);

    Matrix operator * (const Matrix& a);

    bool operator == (const Matrix& a);

    Matrix crop(int r);

    double det();

    Matrix gaussian();

    Matrix inverse();
};



#endif // MATRIX_HPP
