#include "numbers.hpp"
#include "polynomial.hpp"

typedef long long int ll;
const ll MAXN = 4e5 + 51, G = 3;
const ll MOD1 = 469762049, MOD2 = 998244353, MOD3 = 1004535809;
const ll MOD = 468937312667959297;

Polynomial::Polynomial(long long c[], int d)
{
    deg = d;
    coefficient = new long long [deg + 1];
    for (int i = 0; i <= deg; i++)
    {
        coefficient[i] = c[i];
    }
}

Polynomial::Polynomial(const Polynomial &b)
{
    deg = b.deg;
    coefficient = new long long [deg + 1];
    for (int i = 0; i <= deg; i++)
    {
        coefficient[i] = b.coefficient[i];
    }
}

Polynomial Polynomial::operator+(const Polynomial&b)const
{
    int l = std::max(deg, b.deg);
    long long a[l];
    for (int i = 0; i <= std::min(deg, b.deg); i++)
        a[i] = coefficient[i] + b.coefficient[i];
    if (deg < l)
    {
        for (int i = deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    }
    else
        for (int i = b.deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    return Polynomial(a,l);
}

void NTT(long long *cp,long long cnt,long long inv,long long mod)
{
    long long lim = 0, cur = 0, res = 0, omg = 0;
    while ((1 << lim) < cnt)
    {
    	lim++;
    }
    for (int i = 0; i < cnt; i++)
    {
        cur = 0;
        for (int j = 0; j < lim; j++)
        {
            if ((i >> j) & 1)
            {
                cur |= (1 << (lim - j - 1));
            }
        }
        if (i < cur)
        {
            std::swap(cp[i], cp[cur]);
        }
    }
    for (int i = 2; i <= cnt; i <<= 1)
    {
        cur = i >> 1, res = mul_with_mod(G, (mod - 1) / i, mod);
        for (long long * p = cp; p != cp + cnt; p += i)
        {
            omg = 1;
            for (int j = 0; j < cur; j++)
            {
                long long t = omg * p[j + cur] % mod;
                p[j + cur] = min_with_mod(p[j], t, mod);
                p[j] = add_with_mod(p[j], t, mod);
                omg = omg * res % mod;
            }
        }
    }
}

ll CRT(ll r1,ll r2,ll r3,ll mod)
{
    ll inv1 = 208783132, inv2 = 395249030;
    ll r = add_with_mod(mul_with_mod(mul_with_mod(min_with_mod(r1,r2,MOD1),inv1,MOD1),MOD2,MOD),r2,MOD);
    ll k = mul_with_mod(min_with_mod(r3,r,MOD3),inv2,MOD3);
    return ((k % mod) * (MOD % mod) % mod + r) % mod;
}

Polynomial mul_with_mod_po(Polynomial x, Polynomial y, long long mod)
{
    ll cnt = 1, inv;
    static ll cpx[MAXN], cpy[MAXN];
    memset(cpx,0,sizeof(cpx)), memset(cpy,0,sizeof(cpy));
    for (int i = 0; i <= x.deg; i++)
    {
        cpx[i] = x.coefficient[i];
    }
    for (int i = 0; i <= y.deg; i++)
    {
        cpy[i] = y.coefficient[i];
    }
    while (cnt <= x.deg + y.deg)
    {
        cnt<<=1;
    }
    NTT(cpx, cnt, 1, mod), NTT(cpy, cnt, 1, mod);
    for (int i = 0; i <= cnt; i++)
    {
        cpx[i] = cpx[i] * cpy[i] % mod;
    }
    NTT(cpx, cnt, -1, mod);
    int deg = x.deg + y.deg;
    inv = mul_with_mod(cnt, mod - 2, mod);
    cpx[0] = cpx[0] * inv % mod;
    for (int i = 1; i <= cnt >> 1; i++)
    {
        cpx[i] = cpx[i] * inv % mod;
        if (i != cnt - i)
        {
            cpx[cnt - i] = cpx[cnt - i] * inv % mod;
        }
        std::swap(cpx[i], cpx[cnt - i]);
    }
    ll coeff[deg + 1];
    for(int i = 0; i <= deg; i++)
    {
        coeff[i] = min_with_mod(cpx[i], 0, mod);
    }
    return Polynomial(coeff, deg);
}

Polynomial mul_with_armod(Polynomial x, Polynomial y, long long mod)
{
    Polynomial res1(mul_with_mod_po(x, y, MOD1));
    Polynomial res2(mul_with_mod_po(x, y, MOD2));
    Polynomial res3(mul_with_mod_po(x, y, MOD3));
    ll coeff[res1.deg + 1];
    for (int i = 0; i <= res1.deg; i++)
    {
        coeff[i] = CRT(res1.coefficient[i], res2.coefficient[i], res3.coefficient[i],mod);
    }
    return Polynomial(coeff, res1.deg);
}


