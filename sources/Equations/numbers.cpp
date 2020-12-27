#include "numbers.hpp"

int gcd(int a, int b)
{
    return b > 0 ? gcd(b, a % b) : a;
}

long long mul_with_mod(long long x, long long y, long long p)
{
    x %= p,y %= p;
    return ((x * y - (long long)((long long)((long double)x / p * y + 0.5) * p)) % p + p) % p;
}

long long power(long long x, long long y, long long p)
{
    long long res = 1;
    while (y)
    {
        if (y & 1)
            res = mul_with_mod(res, x, p);
        x = mul_with_mod(x, x, p);
        y >>= 1;
    }
    return res;
}

bool Miller_Rabin(long long x, long long p)
{
    if (power(x, p - 1, p) != 1)
        return 0;
    long long y = p - 1, z;
    while (!(y & 1))
    {
        y >>= 1;
        z = power(x, y, p);
        if (z != 1 && z != p - 1)
            return 0;
        if (z == p - 1)
            return 1;
    }
    return 1;
}

bool is_prime(long long x)
{
    if (x < 2)
        return 0;
    if (x == 2 || x == 3 || x == 5 || x == 7 || x == 43)
        return 1;
    return Miller_Rabin(2, x) && Miller_Rabin(3, x) && Miller_Rabin(5, x) && Miller_Rabin(7, x) && Miller_Rabin(43, x);
}

long long min_with_mod(long long x, long long y, long long p)
{
    return x - y < 0? x - y + p : x - y;
}

long long add_with_mod(long long x, long long y, long long p)
{
    return x + y > p? x + y - p : x + y;
}

std::vector<int> factorization(int n)
{
    std::vector<int> ans;
    ans.push_back(1);
    for (int i = 2; i <= n; i++)
    {
        if (is_prime(i) && n % i == 0)
        {
            ans.push_back(i);
        }
    }
    return ans;
}

ContinuedFraction::ContinuedFraction(double a)
{
    if (a < 1e-12)
    {
        nums.push_back(0);
        return;
    }
    double esp = 1e-12;
    for (int i = 0; m == -1 || i <= 2 * (m + 5); i++)
    {
        unsigned tr = (unsigned)a;
        nums.push_back(tr);
        a -= tr;
        if (a < 1e-12)
        {
            if (m == -1)
            {
                m = i;
            }
            return;
        }
        while (tr > 0)
        {
            tr /= 10;
            esp *= 10;
        }
        if (m == -1 && a < esp)
        {
            m = i;
        }
        a = 1 / a;
    }
}

double ContinuedFraction::toDouble()
{
    double a = nums.back();
    for (auto it = nums.rbegin() + 1; it != nums.rend(); it++)
    {
        a = 1 / a;
        a += *it;
    }
    return a;
}
