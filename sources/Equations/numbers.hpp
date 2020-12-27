#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include <bits/stdc++.h>
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
    bool sign;
    unsigned z, m;
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
            double d = fr.toDouble();
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
    double toDouble()
    {
        return (double)a / b;
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
        return Rational(a * c.b / gcd(abs(a * c.b), abs(b * c.a)), abs(b * c.a) / gcd(abs(a * c.b), abs(b * c.a)));
    }
    void operator = (const Rational &c)
    {
        a = c.a;
        b = c.b;
    }
    std::string get_string()
    {
        if (b == 1)
        {
            return std::to_string(a);
        }
        return std::to_string(a) + "/" + std::to_string(b);
    }
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
#endif
