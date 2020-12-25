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
        coefficient[i] = b[i];
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
            a[i] = coefficient[i];
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
        cur = i >> 1, res = power(G, (mod - 1) / i, mod);
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

Polynomial mul_with_mod_po(Polynomial x, Polynomial y, ll mod)
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
    inv = power(cnt, mod - 2, mod);
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
    for (int i = 0; i <= x.deg; i++)
    {
        x.coefficient[i] %= mod;
    }
    for (int i = 0; i <= y.deg; i++)
    {
        y.coefficient[i] %= mod;
    }
    Polynomial res1(mul_with_mod_po(x, y, MOD1));
    Polynomial res2(mul_with_mod_po(x, y, MOD2));
    Polynomial res3(mul_with_mod_po(x, y, MOD3));
    ll coeff[res1.deg + 1];
    for (int i = 0; i <= res1.deg; i++)
    {
        coeff[i] = CRT(res1.coefficient[i], res2.coefficient[i], res3.coefficient[i], mod);
    }
    return Polynomial(coeff, res1.deg);
}

Polynomial linear_re(Polynomial a, Polynomial b, int k, long long f[], long long P)
{
    Polynomial res(20);
//    std::cout<<a[1]<<" "<<b[1]<<" "<<a[0]<<" "<<b[0]<<std::endl;
//    res.print();
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
        {
            (res[i + j] += 1ll * a[i] * b[j] % P) %= P;
//            res.print();
        }
    for (int i = 2 * k - 2; i >= k; res[i--] = 0)
        for (int j = 1; j <= k; j++)
        {
            (res[i - j] += 1ll * res[i] * f[j] % P) %= P;
//            res.print();
        }
//
//    res.print();
    return res;
}

Polynomial ksm(Polynomial a, long long f[],int k, long long P, int b)
{
    Polynomial res(20);
    res.coefficient[0] = 1;
    for (; b; b >>= 1)
    {
        if (b & 1)
        {
//            a.print();
            res = linear_re(res, a, k, f, P);
        }
//        printf("1\n");
        a = linear_re(a, a, k, f, P);
//        a.print();
//        std::cout<<2<<std::endl;
    }
    return res;
}

long long linear_res(int n, int k, long long f[], long long h[], long long P)
{
    for (int i = 1; i <= k; i++)
        f[i] = f[i] > 0 ? f[i] : f[i] + P;
    for (int i = 0; i < k; i++)
        h[i] = h[i] > 0 ? h[i] : h[i] + P;
    if (n < k)
    {
        return h[n];
    }
    Polynomial res(20);
    res[1] = 1;
    long long ans = 0;
    res = ksm(res, f, k, P, n);
    for (int i = 0; i < k; i++)
        ans = (ans + 1ll * res[i] * h[i] % P) % P;
    return ans;
}

Polynomial division(Polynomial a, Polynomial b)
{
    int n = a.deg, k = b.deg;
    long long coea[n];
    for (int i = 0; i <= n - 1; i++)
    {
        coea[i] = 0;
    }
    for (int i = n; i >= k; i--)
    {
        if (a[i])
        {
            a[i - k] = a[i - k] - a[i] * b[0];
            coea[i - 1] = a[i];
            a[i] = 0;
        }
    }
    if (a[0] == 0)
    {
        return Polynomial(coea, n - 1);
    }
    long long coe[2] = {9999999, 0};
    return Polynomial(coe, 1);
}


PolynomialRational PolynomialRational::operator+(const PolynomialRational&b)const
{
    int l = max(deg, b.deg);
    Rational a[l+1];
    for (int i = 0; i <= min(deg, b.deg); i++)
        a[i] = coefficient[i] + b.coefficient[i];

    if (deg < l)
    {
        for (int i = deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    }
    else
        for (int i = b.deg + 1; i <= l; i++)
            a[i] = coefficient[i];

    return PolynomialRational(a,l);
}

PolynomialRational PolynomialRational::operator-(const PolynomialRational&b)const
{
    int l = max(deg, b.deg);
    Rational a[l+1];
    for (int i = 0; i <= min(deg, b.deg); i++)
        a[i] = coefficient[i] - b.coefficient[i];

    if (deg < l)
    {
        for (int i = deg + 1; i <= l; i++)
            a[i] = b.coefficient[i];
    }
    else
        for (int i = b.deg + 1; i <= l; i++)
            a[i] = coefficient[i];

    return PolynomialRational(a,l);
}


void PolynomialRational::operator=(const PolynomialRational &c){
    if(deg != c.deg)
        return;

    for (int i = 0; i<= deg; i++)
        coefficient[i] = c.coefficient[i];
}

PolynomialRational divisionR(PolynomialRational A, PolynomialRational B, bool step=false)
{
    if(step){
        cout<< " ("<<A.get_string() <<") : ("<< B.get_string() << ") = ";
    }
    string steps = "";

    int n = A.deg, k = B.deg;
    Rational coea[n+1];
    for (int i = 0; i <= n - 1; i++){
        coea[i] = Rational(0, 1);
    }

    string spacing = "";
    for (int i = n; i >= k; i--){
        if (A[i].get_a()){
            coea[i-k] = A[i]/B[k];
            Rational c[i+2];
            for (int j = 0; j <= i; j++)
                c[j] = Rational(0, 1);

            for (int j = 0; j<=k; j++)
                c[j+i-k] = B[j] * coea[i-k];

            /*for (int j= 0; j< n-i; j++)
                steps+=' ';*/
            steps += spacing;
            c[i+1] = Rational(0, 1);
            int size;
            if (i == n)
                size = i;
            else
                size = i+1;
            PolynomialRational Q(c, size);
            steps +="-("+ Q.get_string()+")\n";
            PolynomialRational P = A-Q;
            steps += spacing;
            for (int j = 0; j< (int)Q.get_string().size()+3; j++)
                steps += '-';
            steps+= "\n";
            if (A[i].get_value() != 1){
                for (int j=0; j < (int)A[i].get_string().size(); j++){
                    spacing += ' ';
                }
            }

            if (i != n && A[i].get_value()>0)
                spacing += ' ';

            if (i == 1)
                spacing += ' ';
            else if (i > 1)
                spacing += "   ";

            steps += "  "+spacing + P.get_string()+"\n";

            for (int i = 0; i<= P.deg; i++)
                A[i] = P[i];

        }
    }

    bool zero = true;
    for (int i = 0; i <= A.deg; i++)
        if (A[i].get_a()){
            zero = false;
            break;
        }

    /*divPolynomial res;
    PolynomialRational P(coea, n-k);
    res.Quotient = P;
    res.Reminder = A;*/

    if (zero){
        if (step){
            cout<< PolynomialRational(coea, n-k).get_string()<<"\n";
            cout<< steps<<"\n";
        }

       //res.ReminderZero = true;
        return PolynomialRational(coea, n-k);
    }
    else{
        if (step){
            cout<< PolynomialRational(coea, n-k).get_string() <<" with the reminder "<<A.get_string()<<"\n";
            cout<<steps<<"\n";
        }

        return PolynomialRational(coea, n-k);
    }

}


solutionPolynomial solveRationalAux(PolynomialRational P, vector<int> fa, vector<int> fb, int step){
    solutionPolynomial ans;

    if (P.deg == 2){
        cout<<step<<". Solving a quadratic equation " << P.get_string() << " = 0\n";
        cout<<"Applying formula: (-b +/- sqrt{b^2-4ac})/(2a)\n";

        cout << "Discriminate d = "<< P[1].get_string()<<"^2-4*"<<P[0].get_string()<< "*"<<P[2].get_string();
        Rational x = P[1];
        x.a = - x.a;
        Rational y = P[2];
        y = Rational(2,1)*y;

        if ((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()==0){
            cout<<" is 0\n";
            cout<<"We have just one real solution:\n";

            double res = (-P[1].get_value()+sqrt((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()))/(2*P[2].get_value());
            cout<<"("<<x.get_string()<<"+sqrt(("<<P[1].get_string()<<")^2-4("<<P[0].get_string()<<")*("<<P[2].get_string()<<"))/("<<y.get_string()<<") = "<< res <<"\n";

            ans.roots.push_back(res);
            ans.roots.push_back(res);

            if (res > 0)
                ans.factors["(x-"+ to_string(res) + ")"] += 2;
            else
                ans.factors["(x+"+ to_string(abs(res)) + ")"] += 2;

        }
        else if ((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value() > 0){
            cout<<" is positive and equal to "<<((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()) <<"\n";
            cout<<"We have two distinct real solutions:\n";
            double res1, res2;

            res1 = (-P[1].get_value()+sqrt((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()))/(2*P[2].get_value());
            res2 = (-P[1].get_value()-sqrt((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()))/(2*P[2].get_value());
            cout<<"("<<x.get_string()<<"+sqrt(("<<P[1].get_string()<<")^2-4("<<P[0].get_string()<<")*("<<P[2].get_string()<<"))/("<<y.get_string()<<") = "<< res1 << "\n";
            cout<<"("<<x.get_string()<<"-sqrt(("<<P[1].get_string()<<")^2-4("<<P[0].get_string()<<")*("<<P[2].get_string()<<"))/("<<y.get_string()<<") = "<< res2 << "\n";

            ans.roots.push_back(res1);
            ans.roots.push_back(res2);

            if (res1 > 0)
                ans.factors["(x-"+ to_string(res1) + ")"] += 1;
            else
                ans.factors["(x+"+ to_string(abs(res1)) + ")"] += 1;

            if (res2 > 0)
                ans.factors["(x-"+ to_string(res2) + ")"] += 1;
            else
                ans.factors["(x+"+ to_string(abs(res2)) + ")"] += 1;
        }
        else {
            cout<<" is negative and equal to "<<((P[1]*P[1]).get_value()-4*(P[0]*P[2]).get_value()) <<"\n";
            cout<<"We have two distinct complex solutions:\n";
            Complex res1 = Complex((x/y).get_value(), sqrt(-(P[1]*P[1]).get_value()+4*(P[0]*P[2]).get_value())/y.get_value());
            Complex res2 = res1.conj();

            cout<<"("<<x.get_string()<<"+i*sqrt(-("<<P[1].get_string()<<")^2+4("<<P[0].get_string()<<")*("<<P[2].get_string()<<"))/("<<y.get_string()<<") = "<<res1.get_string() << "\n";
            cout<<"("<<x.get_string()<<"-i*sqrt(-("<<P[1].get_string()<<")^2+4("<<P[0].get_string()<<")*("<<P[2].get_string()<<"))/("<<y.get_string()<<") = "<<res2.get_string() <<"\n";

           ans.complex.push_back(res1.get_string());
           ans.complex.push_back(res2.get_string());

            ans.factors["("+ P.get_string() + ")"] += 1;
        }

        return ans;
    }
    if (P.deg == 1){
        cout<<step<<". Solving a linear equation "<< P.get_string()<<" = 0\n";
        Rational x = P[0];
        x.a = - x.a;
        cout<<"x = " << x.get_string()<< "/" << P[1].get_string()<<"\n";
        cout<<"x = " << (x / P[1]).get_string()<<"\n";

        double res = -(P[0]/P[1]).get_value();
        ans.roots.push_back(res);

        if (res > 0)
            ans.factors["(x-"+ to_string(res) + ")"] += 1;
        else
            ans.factors["(x+"+ to_string(abs(res)) + ")"] += 1;

        return ans;
    }

    if (P.deg == 0){
        cout<<"No solutions\n";
        return ans;
    }

   /* if(P[P.deg].get_value()!=1){
        cout<<"We devide the all the coefficients with "<<P[P.deg].get_string()<<"\n";

        for (int i = 0; i <= P.deg; i++){
            P[i] = P[i] / P[P.deg];
        }
        cout<<"We get "<<P.get_string()<<"\n";
    }*/

//    vector<int> fa = divisors(abs(P[0].get_a()));
//    vector<int> fb = divisors(abs(P[0].get_b()));

    bool end = false;
    for (auto j : fb){
        for (auto i : fa){
            Rational x = Rational(i, j);
            if(P.get_value(x) == 0){
                cout<<step<<". We have P("<<x.get_string()<<") = 0\n";


                Rational coe[2] = {Rational(-i, j), Rational(1, 1)};
                PolynomialRational Q = PolynomialRational(coe,1);

                PolynomialRational R = divisionR(P, Q, true);

                ans  = solveRationalAux(R, fa, fb, step+1);
                ans.roots.push_back(x.get_value());

                if (x.get_value() > 0)
                    ans.factors["(x-"+ x.get_string() + ")"] += 1;
                else if(x.get_value() < 0){
                    x.a = - x.a;
                    ans.factors["(x+"+ x.get_string() + ")"] += 1;
                }
                else
                    ans.factors["x"] += 1;

                end = true;
                break;
            }
        }
        if (end)
            break;
    }

    if(!end)
        ans.factors["("+P.get_string()+ ")"] += 1;

    return ans;
}

solutionPolynomial solveRational(PolynomialRational P){
    cout<< "Solving the equation "<< P.get_string()<< " = 0\n";

    int lcm = 1;
    for (int i = 0; i <= P.deg; i++)
        lcm = (lcm* P[i].get_b())/gcd(lcm, P[i].get_b());

    if (lcm != 1){
        cout<<"We multiply polynomial with lcm of denominators of its coefficients which is "<<lcm<< "\n";
        for (int i = 0; i <= P.deg; i++)
            P[i] = P[i]* Rational(lcm, 1);

        cout<<"We get "<< P.get_string()<<"\n";
    }


    vector<int> fa= divisors(abs(P[0].get_a()));
    vector<int> fb = divisors(abs(P[P.deg].get_a()));

   /* ask prof if this seems nice
    * if (P.deg >= 3){
        cout<<"By Bezout's theorem it can be divided with:\n";
        for (auto i : fb)
            for (auto j : fa)
                cout<<Rational(i, j).get_string()<<" ";
        cout<<"\n";
    }*/

    return solveRationalAux(P, fa, fb, 1);
}

std::vector<std::string> solve(Polynomial a)
{
    std::vector<std::string> ans;
    if (a.deg == 2){
        ans.push_back("frac{-"+std::to_string(a[1]) + "+sqrt{4"+std::to_string(a[0]*a[2])+"}}{2"+std::to_string(a[0])+"}");
        ans.push_back("frac{-"+std::to_string(a[1]) + "-sqrt{4"+std::to_string(a[0]*a[2])+"}}{2"+std::to_string(a[0])+"}");
        return ans;
    }
    if (a.deg == 1){
        ans.push_back("-"+std::to_string(a[0])+"/"+std::to_string(a[1]));
        return ans;
    }
    if (a.deg == 0){
        return ans;
    }

    std::vector<int> f = factorization(abs(a[0]));
    for (auto i : f)
    {
        long long coe[2] = {i, 1};
        Polynomial now = division(a, Polynomial(coe,1));
        if (now[0] == 9999999)
        {
            continue;
        }
        if (now.deg == 0)
        {
            ans.push_back(std::to_string(-i));
            return ans;
        }
        ans = solve(now);
        if (ans.empty())
        {
            return ans;
        }
        ans.push_back(std::to_string(-i));
        printf("after division with ");
        Polynomial(coe,1).print();
        printf("we get ");
        now.print();
        return ans;
    }
    for (auto i : f)
    {
        long long coe[2] = {-i, 1};
        Polynomial now = division(a, Polynomial(coe,1));
        if (now[0] == 9999999)
        {
            continue;
        }
        if (now.deg == 0)
        {
            ans.push_back(std::to_string(i));
            return ans;
        }
        ans = solve(now);
        if (ans.empty())
        {
            return ans;
        }
        ans.push_back(std::to_string(i));
        printf("after division with ");
        Polynomial(coe,1).print();
        printf("we get ");
        now.print();
        return ans;
    }
    return ans;
}

string PolynomialRational::get_string(){
    string s="";
    for(int i = deg; i>=0; i--){
        if(coefficient[i].get_a()==0)
            continue;

        if(i!=deg && !coefficient[i].negative())
            s+='+';
        if(abs(coefficient[i].get_a())==1 && abs(coefficient[i].get_b())==1){
            if(coefficient[i].negative())
                s+='-';
            if (i==0)
                s+="1";
            else if (i == 1)
                s+= "x";
            else
                s+= "x^"+to_string(i);
        }
        else{
            if (i==0)
                s+=coefficient[i].get_string();
            else if (i == 1)
                s+= coefficient[i].get_string()+ "x";
            else
                s+= coefficient[i].get_string()+ "x^"+to_string(i);
        }
    }

    if (s=="")
        return "0";
    else
        return s;
}

double PolynomialRational::get_value(Rational x){
    double res = 0;
    for (int i = 0; i<= deg; i++){
        res += coefficient[i].get_value()*pow(x.get_value(),i);
    }

    if (abs(res) < ZERO)
        return 0;
    else
        return res;
}


/*
Polynomial Polynomial::inverse()
{

}
*/
