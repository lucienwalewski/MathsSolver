#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "Include_libraries.h"
#include "numbers.hpp"

#define ZERO 0.000001

using namespace std;

class Polynomial
{
public:
    int deg;
    long long *coefficient;
    Polynomial(long long c[], int d);
    Polynomial(){deg = -1, coefficient = NULL;}
    Polynomial(int n)
    {
        deg = n;
        coefficient = new long long[n + 1];
        for (int i = 0; i <= n; i++)
            coefficient[i] = 0;
    }
    Polynomial(const Polynomial &b);
    ~Polynomial()
    {
        delete[] coefficient;
    }
    Polynomial operator + (const Polynomial& b) const;
    Polynomial operator - (const Polynomial& b) const;
    long long operator [] (const int &i) const {return coefficient[i];}
    long long& operator [] (const int &i) {return coefficient[i];}
    void print()
    {
        for (int i = 0; i <= deg; i++)
        {
            cout << coefficient[i] << "*x^" << i;
            if (i != deg)
            {
                printf("+");
            }
        }
        printf("\n");
    }
};


class PolynomialRational
{
public:
    int deg;
    Rational *coefficient;
    PolynomialRational(Rational* c, int d);
    PolynomialRational();
    PolynomialRational(int n);
    PolynomialRational(const PolynomialRational &b);
    ~PolynomialRational();
    PolynomialRational operator + (const PolynomialRational& b) const;
    PolynomialRational operator - (const PolynomialRational& b) const;
    Rational operator [] (const int &i) const {return coefficient[i];}
    Rational& operator [] (const int &i) {return coefficient[i];}
    PolynomialRational operator * (const PolynomialRational& b) const;
    PolynomialRational operator * (const Rational& b) const;
    PolynomialRational operator / (const PolynomialRational& b) const;
    PolynomialRational operator / (const Rational& b) const;
    PolynomialRational copy();
    bool is_divisible(PolynomialRational P);
    string get_string();
    void print();
    double get_value(Rational x);
};

struct solutionPolynomial{
    map<string, int> factors;
    vector<double> roots;
    vector<string> complex;
    vector<string> step_solution;
};

struct divPolynomial{
    PolynomialRational Quotient;
    PolynomialRational Reminder;
    bool ReminderZero = false;
    vector<string> step_solution;
};

Polynomial mul_with_mod_po(Polynomial x, Polynomial y, long long mod); // return x * y % mod with mod = 469762049 or 998244353 or 1004535809
Polynomial mul_with_armod(Polynomial x, Polynomial y, long long mod); // return x * y % mod with arbitary mod

Polynomial linear_re(Polynomial a, long long *f, int k, long long P, int b);
Polynomial ksm(Polynomial a, long long *f, int k, long long P, int b);

Polynomial division(Polynomial a, Polynomial b);
divPolynomial divisionR(PolynomialRational A, PolynomialRational B);

long long linear_res(int n, int k, long long *f, long long *h, long long P);
void NTT(long long *cp,long long cnt,long long inv,long long mod);
long long CRT(long long r1,long long r2,long long r3,long long mod);

vector<string> solve(Polynomial a);

solutionPolynomial solveRationalAux(PolynomialRational P, vector<int> fa, vector<int> fb);
solutionPolynomial solveRational(PolynomialRational P);

vector<string> integral(PolynomialRational z, PolynomialRational m);
vector<string> integralSimpl(PolynomialRational z, PolynomialRational m);

#endif // POLYNOMIAL_HPP
