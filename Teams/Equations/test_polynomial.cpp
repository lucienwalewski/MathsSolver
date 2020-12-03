#include <bits/stdc++.h>

#include "polynomial.hpp"
#include "numbers.hpp" 

int main()
{
    long long coeff[6] = {19, 32, 0, 182, 99, 95};
    Polynomial x(coeff, 5);
    long long coeff1[9] = {77, 54, 15, 3, 98, 66, 21, 20, 38};
    Polynomial y(coeff1, 8);
    Polynomial z((x + y));
    z.print();
    Polynomial z1(mul_with_armod(x, y, 28));
    z1.print();
    long long f[5] = {0, 3, -1, 0, 4};
    long long h[5] = {-2, 3, 1, 5, 0};
    long long ans = linear_res(6, 4, f, h, 998244353);
    printf("%lld\n",ans);
} 
