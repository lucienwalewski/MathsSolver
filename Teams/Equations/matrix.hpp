#include <bits/stdc++.h>

template <typename T>
class Matrix
{
public:
    T det();
    T invers();
    Matrix(int n, int m);
    ~Matrix();
    Matrix operator + (const Matrix& a);
    Matrix operator - (const Matrix& a);
    Matrix operator * (const Matrix& a);
private:
    int n, m;
    T **elements;
}
