#include <bits/stdc++.h>

#include "polynomial.hpp"
#include "numbers.hpp" 

int main()
{
	long long coeff[6] = {0, 1, 2, 3, 4, 5};
    Polynomial x(coeff, 5);
	long long coeff1[7] = {0, 1, 2, 3, 4, 5, 6};
    Polynomial y(coeff1, 6);
    Polynomial z((x + y));
    z.print();
    Polynomial z1(mul_with_armod(x, y, 100));
    z1.print();
} 
