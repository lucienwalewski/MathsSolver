#ifndef MATRIX_HPP
#define MATRIX_HPP
#include "Equations/numbers.hpp"
#include "Include_libraries.h"

using namespace std;

template <typename T> class Matrix {

private:
    int n, m;
    vector< vector<T> > elements;

public:
    Matrix(int n, int m){
        this->elements = vector<vector<T>>(n);
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++) {
            this->elements[i] = vector<T>(m);
            for (int j = 0; j < m; j++) {
                elements[i][j] = Rational(0, 1);
            }
        }
    }

    Matrix(int n, int m,  vector<vector<T>> v){
        this->elements = vector<vector<T>>(n);
        this->n = n;
        this->m = m;
        for (int i = 0; i < n; i++) {
            this->elements[i] = vector<T>(m);
            for (int j = 0; j < m; j++) {
                elements[i][j] = v[i][j];
            }
        }
    }

    Matrix(vector<vector<T>> v){
        n = v.size();
        m = v[0].size();
        this->elements = vector<vector<T>>(n);
        for (int i = 0; i < n; i++) {
            this->elements[i] = vector<T>(m);
            for (int j = 0; j < m; j++) {
                elements[i][j] = v[i][j];
            }
        }
    }

    int height() const {return n;};
    int width() const {return m;};

    T get_element(int i, int j) const {return elements[i][j];};

    string get_string(){
        //String representation of the matrix
        string s = "";
        for (int i = 0; i < n; i++) {
            s += "|";
            for (int j = 0; j < m; j++){
                if (this->get_element(i, j) >= 0)
                    s += " " + to_str(this->get_element(i, j)) + " ";
                else
                    s += to_str(this->get_element(i, j)) + " ";
            }
            s += "|\n";
        }

        return s.substr(0, s.size() - 1);
    }

    void print_mat(){
        //Matrix printer
        cout<< get_string() << "\n";
    }

    void set_element(int i, int j, T element){
        elements[i][j] = element;
    }

    void copy(Matrix<T> &a){
        //Copies a matrix into another one.
        if ((n != a.height()) || (m != a.width())){
            cout << "Error matrces are of diiferent size!\n";
            return;
        }
        for (int i = 0; i < n; i ++) {
            for (int j =0; j < m; j++) {
                a.set_element(i, j, elements[i][j]);
            }
        }
    }

    void id(){
        //Sets the identity matrix.
        /*if (n != m){
            cout<< "Height and width are of different size\n";
            return;
        }*/
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++){
                if (i == j)
                    this->set_element(i, i, Rational(1, 1));
                else
                    this->set_element(i, j, Rational(0, 1));
            }

    }

    Matrix<T> col(int j){
        //Returns the j-th column of the matrix, we assume j < m.
        Matrix<T> res(n, 1);
        for (int i = 0; i < n; i++){
            res.set_element(i, 0, elements[i][j]);
        }
        return res;
    }

    Matrix<T> row(int i){
        //Returns the i-th row of the matrix, we assume i < n.
        Matrix<T> res(1, m);
            for (int j = 0; j < m; j++){
                res.set_element(0, j, elements[i][j]);
            }
        return res;
    }

    void mult_row(int i, T k){
        //Multiplifies a row of the matrix by a scalar k. Useful for the gaussian elimination.
        for (int j = 0; j < m; j++) {
            elements[i][j] = elements[i][j] * k;
        }
    }

    void sub_row(int i, int j){
        //Substarct a row j from a row i. Useful for gaussian eliminaton.
        for (int k = 0; k < m; k++) {
            elements[i][k] = elements[i][k] - elements[j][k];
        }
    }

    Matrix<T>  operator + (const Matrix<T>& a){
        //An operator for the additions between two matrices.
        if ((n != a.height()) || (m != a.width())){
            cout << "Error matrces are of diiferent size!\n";
            return Matrix(n, m);
        }
        Matrix<T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.set_element(i, j, elements[i][j] + a.get_element(i, j));
            }
        }
        return res;
    }

    Matrix<T> operator - (const Matrix<T>& a){
        //An operator for the substractions between two matrices.
        if ((n != a.height()) || (m != a.width())){
            cout << "Error matrces are of diiferent size!\n";
            return Matrix(n, m);
        }
        Matrix<T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.set_element(i, j, elements[i][j] - a.get_element(i, j));
            }
        }
        return res;
    }

    Matrix<T> operator * (const T& k){
        //An operator for the multiplications between a matrix and a scalar, which will be useful to compute the determinant.
        Matrix<T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.set_element(i, j, k * elements[i][j]);
            }
        }
        return res;
    }

    Matrix<T> operator * (const Matrix<T>& a){
        //An operator for the multiplications between two matrices
        if (m != a.height()){
            cout << "Error matrices are of wrong size!\n";
            return Matrix(n, m);
        }
        Matrix<T> res(n, a.width());
        //think about making a more effincent algorithm
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < a.width(); j++) {
                T elm = Rational(0, 1);
                for (int k = 0; k < m; k++) {
                    elm += elements[i][k] * a.get_element(k, j);
                }
                res.set_element(i, j, elm);
            }
        }
        return res;
    }

    Matrix<T> power(int k){
        //A method that raises a matrix to the power k.
        Matrix<T> res(n, m);
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
        else {
            return res.power((k-1)/2).power(2) * res;
        }
    }

    bool operator == (const Matrix<T>& a){
        //Equality operator.
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++) {
                if (elements[i][j] != a.get_element(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    Matrix<T> crop(int r){
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
    }

    T det(){
        //Computes the determinant of a matrix, assuming it is a square matrix.
            if (n == 1) {
                return elements[0][0];
            } else {
                T d = 0;
                for (int i = 0; i < n; i++) {
                    Matrix<T> cropped = this->crop(i);
                    if (i % 2 == 0)
                        d += cropped.det() * this->get_element(i, 0);
                    else
                        d += Rational(-1, 1)* cropped.det() * this->get_element(i, 0);
                }
                return d;
            }
    }

    Matrix<T>  gaussian(){
        //A gaussian implementation for matrix inversion, determinant assumed to be non nul.
        if (this->det() == Rational(0, 1)){
            cout<< "Error, impossible to perform!\n";
            return Matrix(n, m);
        }

        Matrix<T> A(n, m), I(n, m);
        this->copy(A);
        I.id();
        for (int j = 0; j < m-1; j++) {
            for(int i = j+1; i < n; i++) {
                if (A.get_element(j, j) != Rational(0, 1) && A.get_element(i, j) != Rational(0, 1)) {
                    T k = A.get_element(i, j)/A.get_element(j, j);
                    A.mult_row(j, k);
                    I.mult_row(j, k);
                    A.sub_row(i, j);
                    I.sub_row(i, j);
                }
            }
        }
        for (int j = m-1; j > 0; j--) {
            for (int i = j-1; i >= 0; i--) {
                if (A.get_element(j, j) != Rational(0, 1) && A.get_element(i, j) != Rational(0, 1)) {
                    T k = A.get_element(i, j)/A.get_element(j, j);
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

    Matrix<T>  inverse(){
        //Computes the inverse of a matrix, assuming it is a square matrix. If the matrix is not invertible, then it returns the null matrix.
           T d = this->det();
           if ((n != m) || (d == Rational(0, 1))) {
               cout<< "Error matrix not invertible!\n";
               return Matrix(n, m);
           } else
               return this->gaussian();

    }
};

string to_str(Rational value);
template <typename T>  string to_str(T value){
     return to_string(value);
}


#endif // MATRIX_HPP
