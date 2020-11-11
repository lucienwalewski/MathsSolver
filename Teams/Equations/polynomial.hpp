#include <bits/stdc++.h>
template <typename T>
class Polynomial
{
public:
    Polynomial(string S);
    ~Polynomial();
    T root();
    string symbolic_root();
    Polynomial derivative();
    Polynomial integral();
    Polynomial exp();
    Polynomial ln();
    Polynomial operator + (const Matrix& a);
    Polynomial operator - (const Matrix& a);
    Polynomial operator * (const Matrix& a); # Try to use FFT here 
    Polynomial operator / (const Matrix& a);
    Polynomial operator % (const Matrix& a);
private:
    int deg;
    T *coefficient;
}