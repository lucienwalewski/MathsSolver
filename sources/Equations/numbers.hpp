#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <math.h>
#include<map>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

int gcd(int a, int b);

class ContinuedFraction
{
private:
    std::vector<unsigned> nums;
    int m = -1;
    const double eps = 1e-12;
public:
    ContinuedFraction(double a);
    double toDouble();
    friend class Rational;
};

class Rational
{
private:
    bool sign = true;
    unsigned z = 0, m = 1;
    const double eps = 1e-12;

public:
    int a, b;
    Rational()
    {
        z = 0;
        m = 1;
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

        if (this->a == 0)
            this->b = 1;
    }
    Rational(const Rational& c)
    {
        a = c.a;
        b = c.b;
    }
    Rational(ContinuedFraction frac) : m(1), sign(false)
    {
        z = frac.nums.back();
        for (auto it = frac.nums.rbegin() + 1; it != frac.nums.rend(); it++)
        {
            Invert();
            z += m * *it;
        }
        a = sign ? -z : z;
        b = m;
    }
    void Invert()
    {
        std::swap(m,z);
        std::swap(a,b);
    }
    Rational(double c)
    {
        sign = c < 0;
        if (sign)
            c = -c;
        if (c < eps)
        {
            a = 0;
            b = 1;
            z = 0;
            m = 1;
            sign = 0;
            return ;
        }
        ContinuedFraction frac(c);
        std::vector<unsigned> nums = frac.nums;
        int m_now = frac.m - 4 >= 0 ? frac.m - 4 : 0;
        frac.nums.resize(m_now);

        std::vector<Rational> vfr;
        std::vector<double> vesp;
        for (size_t i = m_now; i < nums.size(); i++)
        {
            frac.nums.push_back(nums[i]);
            Rational fr(frac);
            double d = fr.get_value();
            vfr.push_back(fr);
            vesp.push_back(abs(d - c));
        }
        int min_pos = 0;
        double min_eps = 1e100;
        for (size_t i = 0; i < vesp.size(); i++)
        {
            if (vesp[i] < min_eps)
            {
                min_pos = i;
                min_eps = vesp[i];
            }
        }
        this -> z = vfr[min_pos].a;
        this -> m = vfr[min_pos].b;
        this -> a = sign ? -z : z;
        this -> b = this -> m;
        return;
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
    double operator * (const double c){
        return c*get_value();
    }
    bool operator == (Rational &c){
        return  this->get_value() == c.get_value() ;
    }
    bool operator != (Rational &c){
        return this->get_value() != c.get_value() ;
    }
    bool operator > (Rational &c){
        return get_value() > c.get_value();
    }
    bool operator >= (Rational &c){
        return get_value() >= c.get_value();
    }
    bool operator < (Rational &c){
        return get_value() < c.get_value();
    }
    bool operator <= (Rational &c){
        return get_value() <= c.get_value();
    }
    operator double () {
        return (double)a/(double)b;
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
vector<int> factorization(int n);
vector<int> divisors(int n);
#endif
