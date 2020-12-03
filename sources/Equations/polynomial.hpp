#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <bits/stdc++.h>
class Polynomial
{
public:
    int deg;
    long long *coefficient;
    Polynomial(long long c[], int d);
    Polynomial(){deg = -1, coefficient = NULL;}
    Polynomial(const Polynomial &b);
    ~Polynomial()
    {
        delete[] coefficient;
    }
//    Polynomial derivative();
//    Polynomial integral();
//    Polynomial exp();
//    Polynomial ln();
    Polynomial operator + (const Polynomial& a) const;
    Polynomial operator - (const Polynomial& a) const;
    Polynomial operator * (const Polynomial& a);
    void print()
    {
        for (int i = 0; i <= deg; i++)
        {
            std::cout << coefficient[i] << "*x^" << i;
            if (i != deg)
            {
                printf("+");
            }
        }
        printf("\n");
    }
};

Polynomial mul_with_mod_po(Polynomial x, Polynomial y, long long mod); // return x * y % mod with mod = 469762049 or 998244353 or 1004535809
Polynomial mul_with_armod(Polynomial x, Polynomial y, long long mod); // return x * y % mod with arbitary mod

void NTT(long long *cp,long long cnt,long long inv,long long mod);

long long CRT(long long r1,long long r2,long long r3,long long mod);

#endif // POLYNOMIAL_HPP
