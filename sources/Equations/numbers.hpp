#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b);

class Rational
{
public:
    int a, b;
    Rational()
    {
        a = 0;
        b = 1;
    }
    Rational(int a, int b)
    {
        this -> a = a / gcd(abs(a), abs(b));
        this -> b = b / gcd(abs(a), abs(b));
        if (negative()){
            this->a = - abs(this->a);
            this->b = abs(this->b);
        }
        else{
            this->a = abs(this->a);
            this->b = abs(this->b);
        }
    }
    Rational(const Rational& c)
    {
        a = c.a;
        b = c.b;
    }
    double get_a()
    {
        return a;
    }
    double get_b()
    {
        return b;
    }
    Rational operator + (const Rational &c)
    {
        return Rational((a * c.b + c.a * b) / gcd(abs(a * c.b + c.a * b), abs(b * c.b)), (b * c.b) / gcd(abs(a * c.b + c.a * b), abs(b * c.b)));
    }
    Rational operator - (const Rational &c)
    {
        return Rational((a * c.b - c.a * b) / gcd(abs(a * c.b - c.a * b), abs(b * c.b)), (b * c.b) / gcd(abs(a * c.b - c.a * b), abs(b * c.b)));
    }
    Rational operator * (const Rational &c)
    {
        return Rational(a * c.a / gcd(abs(a * c.a), abs(b * c.b)), abs(b * c.b) / gcd(abs(a * c.a), abs(b * c.b)));
    }
    Rational operator / (const Rational &c)
    {
        if (c.a > 0)
            return Rational(a * c.b / gcd(abs(a * c.b), abs(b * c.a)), abs(b * c.a) / gcd(abs(a * c.b), abs(b * c.a)));
        else
            return Rational(- a * c.b / gcd(abs(a * c.b), abs(b * c.a)), abs(b * c.a) / gcd(abs(a * c.b), abs(b * c.a)));
    }
    double get_value();
    void operator = (const Rational &c)
    {
        a = c.a;
        b = c.b;
    }
    bool negative (){
        if(a*b>=0)
            return false;
        else
            return true;
    }
    std::string get_string()
    {
        std:: string sgn= "";
        if(this->negative())
            sgn+='-';
        if (abs(b) == 1)
        {
            return sgn+std::to_string(abs(a));
        }
        return sgn+std::to_string(abs(a)) + "/" + std::to_string(abs(b));
    }
    //double to Rational
};

class Complex
{
public:
    Complex(double r, double i)
    {
        this->r = r;
        this->i = i;
    }
    double get_r()
    {
        return r;
    }
    double get_i()
    {
        return i;
    }
    Complex operator + (const Complex &a)
    {
        return Complex(r + a.r, i + a.i);
    }
    Complex operator - (const Complex &a)
    {
        return Complex(r - a.r, i - a.i);
    }
    Complex operator * (const Complex &a)
    {
        return Complex(r * a.r - i * a.i, r * a.i + i * a.r);
    }
    Complex operator / (const double &a)
    {
        return Complex(r / a, i / a);
    }
    Complex conj()
    {
        return Complex(r, -i);
    }
    string get_string(){
        string s=to_string(r);
        if (i == 0)
            return  s;
        else if (i > 0)
            return s+"+i"+to_string(i);
        else
            return s+"-i"+to_string(abs(i));
    }
private:
    double i, r;
};

bool Miller_Rabin(long long x, long long p);
bool is_prime(long long x);
long long power(long long x, long long y, long long p);
long long mul_with_mod(long long x, long long y, long long p);
long long min_with_mod(long long x, long long y, long long p);
long long add_with_mod(long long x, long long y, long long p);
std::vector<int> factorization(int n);
vector<int> divisors(int n);
#endif
