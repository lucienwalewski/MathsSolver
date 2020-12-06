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
        //Matrix printer
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                std::cout << elements[i][j] << std::endl;
            }
        }
    }

    void set_element(int i, int j, T element) {
        elements[i][j] = element;
    };

    void copy(Matrix<T> a) {
        //Copies a matrix into another one.
        for (int i = 0; i < n; i ++) {
            for (int j =0; j < m; j++) {
                a.set_element(i, j, elements[i][j]);
            }
        }
    }

    void id() {
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

    Matrix<T> mult_row(int i, T k) {
        //Multiplifies a row of the matrix by a scalar k. Useful for the gaussian elimination.
        Matrix<T> res(n, m);
        this->copy(res);
        for (int j = 0; j < m; j++) {
            res.set_element(i, j, k * elements[i][j]);
        }
    }

    Matrix<T> sub_row(int i, int j) {
        //Substarct a row j from a row i. Useful for gaussian eliminaton.
        Matrix<T> res(n, m);
        this->copy(res);
        for (int k = 0; k < m; k++) {
            res.set_element(i, k, elements[i][k] - elements[j][k]);
        }
    }

    Matrix<T> operator()(T i,T j) {return elements[i][j];}; //A member function that makes the matrices more user friendly.

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
                Matrix cropped = this->crop(i, 0);
                cropped.print_mat();
                d += pow(-1, i) * cropped.det() * this->get_element(i, 0);
            }
            return d;
        }
    };

    Matrix<T> gaussian() {
        //A gaussian implementation for matrix inversion, determinant assumed to be non nul.
        Matrix<T> A(n, m), B(n, m);
        this->copy(A);
        B.id();
        T C[n];
            for (int k = 0; k < n - 1; k++)
            {
                for (int i = k + 1; i < n; i++)
                    C[i] = A[i][k] / A[k][k];
                for (int i = k + 1; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        A[i][j] = A[i][j] - C[i] * A[k][j];
                    }
                    B.mult_row(k, C[i]);
                    B.sub_row(i, k);
                    //B[i] = B[i] - C[i] * B[k];
                }
            }
        return B;
    }

    Matrix<T> inverse(){
    //Computes the inverse of a matrix, assuming it is a square matrix.
       int d = this->det();
       if (d == 0) {
           return 0;
       } else {
           return this->gaussian();
       }
    };

};


#endif // MATRIX_HPP
