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

int gcd(int a, int b);
bool Miller_Rabin(long long x, long long p);
bool is_prime(long long x);
long long power(long long x, long long y, long long p);
long long mul_with_mod(unsigned long long x, unsigned long long y, long long p);

void FFT(Complex *y, int len, bool flag);
