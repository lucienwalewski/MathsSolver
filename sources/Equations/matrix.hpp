#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

template <typename T> class Matrix
{
private:
    int n, m;
    vector< vector<T> > elements;

public:

   Matrix(int n, int m): elements(n) {
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++) {
            this->elements[i] = vector<T>(m);
            for (int j = 0; j < m; j++) {
                elements[i][j] = 0;
            }
        }
    };

    T height() const {return n;};
    T width() const {return m;};

    T get_element(int i, int j) const {
        return elements[i][j];
    };

    void print_mat() {
        //Clean Matrix printer
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << this->get_element(i, j) << " ";
            }
            cout << "" << endl;
        }
    }

    void set_element(int i, int j, T element) {
        elements[i][j] = element;
    };

    void copy(Matrix<T> &a) {
        //Copies a matrix into another one.
        for (int i = 0; i < n; i ++) {
            for (int j =0; j < m; j++) {
                a.set_element(i, j, elements[i][j]);
            }
        }
    }

    void id() {
        //Sets the identity matrix.
        for (int i = 0; i < n; i++) {
            this->set_element(i, i, 1);
        }
    }

    Matrix<T> col(T j) {
        //Returns the j-th column of the matrix, we assume j < m.
        Matrix<T> res(n, 1);
        for (T i = 0; i < n; i++){
            res.set_element(i, 0, elements[i][j]);
        }
        return res;
    };

    Matrix<T> row(T i) {
        //Returns the i-th row of the matrix, we assume i < n.
        Matrix<T> res(1, m);
            for (T j = 0; j < m; j++){
                res.set_element(0, j, elements[i][j]);
            }
        return res;
    };

    void mult_row(int i, T k) {
        //Multiplifies a row of the matrix by a scalar k. Useful for the gaussian elimination.
        for (int j = 0; j < m; j++) {
            elements[i][j] *= k;
        }
    }

    void sub_row(int i, int j) {
        //Substarct a row j from a row i. Useful for gaussian eliminaton.
        for (int k = 0; k < m; k++) {
            elements[i][k] -= elements[j][k];
        }
    }

    Matrix<T> operator + (const Matrix& a) {
        //An operator for the additions between two matrices.
        Matrix<T> res(n, m);
        for (T i = 0; i < n; i++) {
            for (T j = 0; j < m; j++) {
                res.set_element(i, j, elements[i][j] + a.get_element(i, j));
            }
        }
        return res;
    };

    Matrix<T> operator - (const Matrix& a) {
        //An operator for the substractions between two matrices.
        Matrix<T> res(n, m);
        for (T i = 0; i < n; i++) {
            for (T j = 0; j < m; j++) {
                res.set_element(i, j, elements[i][j] - a.get_element(i, j));
            }
        }
        return res;
    };

    Matrix<T> operator * (const T& k) {
        //An operator for the multiplications between a matrix and a scalar, which will be useful to compute the determinant.
        Matrix<T> res(n, m);
        for (T i = 0; i < n; i++) {
            for (T j = 0; j < m; j++) {
                res.set_element(i, j, k * elements[i][j]);
            }
        }
        return res;
    };

    Matrix<T> operator * (const Matrix& a) {
        //An operator for the multiplications between two matrices, we assume that m = a.height() and n = a.width().
        Matrix<T> res(n, a.width());
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a.width(); j++) {
                T elm = 0;
                for (int k = 0; k < m; k++) {
                    elm += elements[i][k] * a.get_element(k, j);
                }
                res.set_element(i, j, elm);
            }
        }
        return res;
    };

    bool operator == (const Matrix& a) {
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

    Matrix<T> crop(int r) {
    //Returns a matrix where the 1st column and the r-th row were removed.
        Matrix<T> cropped(n-1, m-1);
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

    T det(){
    //Computes the determinant of a matrix, assuming it is a square matrix.
        if (n == 1) {
            return elements[0][0];
        } else {
            T d = 0;
            for (int i = 0; i < n; i++) {
                Matrix cropped = this->crop(i);
                d += pow(-1, i) * cropped.det() * this->get_element(i, 0);
            }
            return d;
        }
    };

    Matrix<T> gaussian() {
        //A gaussian implementation for matrix inversion, determinant assumed to be non nul.
        Matrix<T> A(n, m), I(n, m);
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

    Matrix<T> inverse(){
    //Computes the inverse of a matrix, assuming it is a square matrix. If the matrix is not invertible, then it returns the null matrix.
       int d = this->det();
       if (d == 0) {
           return Matrix<T> (n, m);
       } else {
           return this->gaussian();
       }
    };

};


#endif // MATRIX_HPP
