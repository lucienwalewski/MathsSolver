#include <bits/stdc++.h>

#include "polynomial.hpp"
#include "numbers.hpp" 

int main()
{
    Rational a(3.141592653589793);
    Rational ab(-1.33333333333);
    std::cout<<a.get_string()<<std::endl;
    std::cout<<ab.get_string()<<std::endl;
    Rational c[4] = {Rational(-5, 2), Rational(-9, 2), Rational(5, 2), Rational(3, 1)};
    PolynomialRational b(c, 3);
    Rational ce[2] = {Rational(1, 2), Rational(1, 1)};
    PolynomialRational d(ce, 1);
    PolynomialRational now = divisionR(b, d);
    now.print();
    std::vector<std::string> ans_s = solveRational(b);

    if (ans_s.empty())
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }

    printf("The roots are\n");
    for (auto i : ans_s)
    {
        std::cout<<i<<std::endl;
    }
} 
