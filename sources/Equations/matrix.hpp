#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <iostream>

using namespace std;

template <typename T> class Matrix
{
private:
    int n, m;
    vector< vector<T> > elements;

public:

    Matrix(int height, int width){
        n = height;
        m = width;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                elements[i][j] = 0;
            }
        }
    };

    T height() const {return n;};
    T width() const {return m;};

    //T get_element(int i, int j) {
      //  return elements[i][j];
    //}

    T get_element(int i, int j) const {
        return elements[i][j];
    };


    void set_element(int i, int j, T element) {
        elements[i][j] = element;
    };

    Matrix<T> column(T j) {
        //Returns the j-th column of the matrix, we assume j < m.
        Matrix<T> res(n, 1);
        for (T i = 0; i < n; i++){
            res.set_element(i, 1, elements[i][j]);
        }
        return res;
    };

    Matrix<T> row(T i) {
        //Returns the i-th row of the matrix, we assume i < n.
        Matrix<T> res(1, m);
            for (T j = 0; j < n; j++){
                res.set_element(1, j, elements[i][j]);
            }
        return res;
    };

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
        //An operator for the multiplications between two matrices, we assume that width = a.height.
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
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++) {
                if (elements[i][j] != a.get_element(i, j)) {
                    return 0;
                }
            }
        }
        return 1;
    };

    Matrix<T> crop_row(int r) {
    //Returns a matrix where the 1st column and the i-th row were removed.
        Matrix<T> cropped(n-1, m-1);
        if (r > 0){
            for (int i = 0; i < r; i++) {
                for (int j = 1; j < m; j++){
                    cropped.set_element(i, j, elements[i][j]);
                }
            }
        }
        if (r+1 < m) {
            for (int i = r+1; i < m; i++) {
                for (int j = 1; j < m; j++){
                    cropped.set_element(i, j, elements[i][j]);
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
                Matrix cropped = (*this).crop_row(i);
                if (i%2) {
                    d += cropped.det() * elements(i, 1);
                } else {
                    d -= cropped.det() * elements(i, 1);
                }
            }
            return d;
        }
    };

    Matrix<T> adj() {
    //Computes the adjacent matrix of a matrix, assuming it is a square matrix.
    };
    Matrix<T> inverse(){
    //Computes the inverse of a matrix, assuming it is a square matrix.
    };

};

template <class num> Matrix<num> mat_mult(Matrix <num> A, Matrix <num> B){

}

template <class num> Matrix<num> crop(Matrix <num> A, int , int j) {

}

template <class num> int det(Matrix <num> A) {

}

template <class num> Matrix<num> adj(Matrix <num> A) {

}

template <class num> Matrix<num> invert(Matrix <num> A) {

}



#endif // MATRIX_HPP
