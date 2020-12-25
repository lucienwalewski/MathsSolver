#include <vector>
#include <iostream>
#include <math.h>

#include "matrix.hpp"

using namespace std;

Matrix::Matrix(int n, int m) {
    this->elements = vector<vector<double>>(n);
    this->n = n;
    this->m = m;
    for (int i = 0; i < n; i++) {
        this->elements[i] = vector<double>(m);
        for (int j = 0; j < m; j++) {
            elements[i][j] = 0;
        }
    }
};


void Matrix::print_mat() {
    //Clean Matrix printer
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << this->get_element(i, j) << " ";
        }
        cout << "" << endl;
    }
}

void Matrix::set_element(int i, int j, double element) {
    elements[i][j] = element;
};

void Matrix::copy(Matrix &a) {
    //Copies a matrix into another one.
    for (int i = 0; i < n; i ++) {
        for (int j =0; j < m; j++) {
            a.set_element(i, j, elements[i][j]);
        }
    }
}

void Matrix::id() {
    //Sets the identity matrix.
    for (int i = 0; i < n; i++) {
        this->set_element(i, i, 1);
    }
}

Matrix Matrix::col(int j) {
    //Returns the j-th column of the matrix, we assume j < m.
    Matrix res(n, 1);
    for (int i = 0; i < n; i++){
        res.set_element(i, 0, elements[i][j]);
    }
    return res;
};

Matrix Matrix::row(int i) {
    //Returns the i-th row of the matrix, we assume i < n.
    Matrix res(1, m);
        for (int j = 0; j < m; j++){
            res.set_element(0, j, elements[i][j]);
        }
    return res;
};

void Matrix::mult_row(int i, double k) {
    //Multiplifies a row of the matrix by a scalar k. Useful for the gaussian elimination.
    for (int j = 0; j < m; j++) {
        elements[i][j] *= k;
    }
}

void Matrix::sub_row(int i, int j) {
    //Substarct a row j from a row i. Useful for gaussian eliminaton.
    for (int k = 0; k < m; k++) {
        elements[i][k] -= elements[j][k];
    }
}

Matrix Matrix::operator + (const Matrix& a) {
    //An operator for the additions between two matrices.
    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res.set_element(i, j, elements[i][j] + a.get_element(i, j));
        }
    }
    return res;
};

Matrix Matrix::operator - (const Matrix& a) {
    //An operator for the substractions between two matrices.
    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res.set_element(i, j, elements[i][j] - a.get_element(i, j));
        }
    }
    return res;
};

Matrix Matrix::operator * (const double& k) {
    //An operator for the multiplications between a matrix and a scalar, which will be useful to compute the determinant.
    Matrix res(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res.set_element(i, j, k * elements[i][j]);
        }
    }
    return res;
};

Matrix Matrix::operator * (const Matrix& a) {
    //An operator for the multiplications between two matrices, we assume that m = a.height() and n = a.width().
    Matrix res(n, a.width());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a.width(); j++) {
            double elm = 0;
            for (int k = 0; k < m; k++) {
                elm += elements[i][k] * a.get_element(k, j);
            }
            res.set_element(i, j, elm);
        }
    }
    return res;
};

Matrix Matrix::power(int k) {
    //A method that raises a matrix to the power k.
    Matrix res(n, m);
    this->copy(res);
    if(k == 1) {
        return res;
    }
    if (k == 2) {
        return res*res;
    }
    if (k % 2 == 0) {
        return res.power(k/2).power(2);
    }
    if (k % 2 == 1) {
        return res.power((k-1)/2).power(2) * res;
    }
};

bool Matrix::operator == (const Matrix& a) {
    //Equality operator.
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            if (elements[i][j] != a.get_element(i, j)) {
                return 0;
            }
        }
    }
    return 1;
};

Matrix Matrix::crop(int r) {
//Returns a matrix where the 1st column and the r-th row were removed.
    Matrix cropped(n-1, m-1);
    if (r > 0){
        for (int i = 0; i < r; i++) {
            for (int j = 1; j < m; j++){
                cropped.set_element(i, j-1, elements[i][j]);
            }
        }
    }
    if (r+1 < m) {
        for (int i = r+1; i < n; i++) {
            for (int j = 1; j < m; j++){
                cropped.set_element(i-1, j-1, elements[i][j]);
            }
        }
    }
    return cropped;
};

double Matrix::det(){
//Computes the determinant of a matrix, assuming it is a square matrix.
    if (n == 1) {
        return elements[0][0];
    } else {
        double d = 0;
        for (int i = 0; i < n; i++) {
            Matrix cropped = this->crop(i);
            d += pow(-1, i) * cropped.det() * this->get_element(i, 0);
        }
        return d;
    }
};

Matrix Matrix::gaussian() {
    //A gaussian implementation for matrix inversion, determinant assumed to be non nul.
    Matrix A(n, m), I(n, m);
    this->copy(A);
    I.id();
    for (int j = 0; j < m-1; j++) {
        for(int i = j+1; i < n; i++) {
            if (A.get_element(j, j) != 0 && A.get_element(i, j) != 0) {
                double k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                I.mult_row(j, k);
                A.sub_row(i, j);
                I.sub_row(i, j);
            }
        }
    }
    for (int j = m-1; j > 0; j--) {
        for (int i = j-1; i >= 0; i--) {
            if (A.get_element(j, j) != 0 && A.get_element(i, j) != 0) {
                double k = A.get_element(i, j)/A.get_element(j, j);
                A.mult_row(j, k);
                I.mult_row(j, k);
                A.sub_row(i, j);
                I.sub_row(i, j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        I.mult_row(i, 1/A.get_element(i, i));
    }

    return I;
}

Matrix Matrix::inverse(){
//Computes the inverse of a matrix, assuming it is a square matrix. If the matrix is not invertible, then it returns the null matrix.
   int d = this->det();
   if (d == 0) {
       return Matrix (n, m);
   } else {
       return this->gaussian();
   }
};
