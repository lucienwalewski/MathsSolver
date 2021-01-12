#include "functionPreprocessing.hpp"

string upload_function(string f){
    /*uploading of the given function*/
    string s="";

    for(int i=0; i<(int)f.size(); i++){
        if(f[i]==' ' || f[i]=='\t' || f[i]=='\n')
            continue;
        s += f[i];
    }

    return s;
}

bool check_derivative(string f){
    /*check if program should perform derivation: potential idea - checking multiple derivation*/
    return ((int)f.size()>=3 && f[0]=='(' && f[(int)f.size()-1]=='\'' && f[(int)f.size()-2]==')');
}

bool check_equation(string f){
    /*checking if equation solving should be performed*/
    bool find=false;

    for(int i=0; i<(int)f.size(); i++){
        if(!find && f[i]=='=' && (i+1)<(int)f.size())
            find = true;
        else if(find && f[i]=='='){
            find=false;
            break;
        }
    }

    return find;
}

bool check_system(string f){
    /*checking if system of equations solving should be performed*/
    if (f.size()<6)
        return false;
    if (f.substr(0,3) == "sys"){
        int j = 3;
        if (f[j] != '{')
            return false;

        while (j < (int)f.size()){
            if (f[j] == '}')
                return true;
            j++;
        }

        return false;
    }
    else
        return false;
}

bool check_divisonPolynomials(string f){
    /*checking if divison of the polynomials should be performed*/
    if (f[0] != '(')
        return false;

    int i=1;
    for (; i < (int)f.size(); i++)
        if (f[i]==')')
            break;
    if (i == (int)f.size())
        return false;

    i++;
    if ((i == (int)f.size()) || (i < (int)f.size() && f[i] != ':'))
        return false;

    i++;
    if ((i == (int)f.size()) || (i < (int)f.size() && f[i] != '('))
        return false;

    for (; i < (int)f.size(); i++)
        if (f[i]==')')
            return true;

    return false;
}

bool check_multiplication(string f){
    /*checking if multiplication of the polynomials should be performed*/
    if (f[0] != '(')
        return false;

    int i=1;
    for (; i < (int)f.size(); i++)
        if (f[i]==')')
            break;
    if (i == (int)f.size())
        return false;

    i++;
    if ((i == (int)f.size()) || (i < (int)f.size() && f[i] != '*'))
        return false;

    i++;
    if ((i == (int)f.size()) || (i < (int)f.size() && f[i] != '('))
        return false;

    for (; i < (int)f.size(); i++)
        if (f[i]==')')
            return true;

    return false;
}

bool check_integral(string f){
    /*checking if integral solving should be performed*/
    if (f.size()<12)
        return false;
    if (f.substr(0,3) == "int"){
        int j = 3;
        for (int i = 0; i < 3; i++){
            if (f[j] != '{')
                return false;
            j++;
            bool find = false;
            while (j < (int)f.size()){
                if (f[j] == '}'){
                    find = true;
                    break;
                }
                j++;
            }
            if (!find)
                return false;
            j++;
        }
        return true;
    }
    else
        return false;
}

vector<string> derivative(string f, char var){
    return AbstractFunction(simplify(f.substr(1, (int)f.size() - 3), var)).derive();
}

vector<string> equation(string f, char var){
    vector<string> solution;
    string solve = "";
    int i = 0;
    while (f[i++] != '=');

    solve = f.substr(0, i-1);
    vector<Token> tokens = simplify(f.substr(i), var);
    int j = 0;
    if (tokens[0].get_type() == 5){
        solve += '+';
        j++;

        if ((int)tokens.size() == 1)
            return vector<string>{"i"};
    }
    else
        solve += '-';

    for (; j < (int)tokens.size(); j++){
        if (tokens[j].get_type() == 5)
            solve += '+';
        else if (tokens[j].get_type() == 6)
            solve += '-';
        else if (tokens[j].get_type() == -4)
            solve += '(' + tokens[j].get_value() + ')';
        else
            solve += tokens[j].get_value();
    }

    AbstractFunction function(simplify(solve, var), var);
    vector<double> sol = function.get_roots();
    if (function.is_polynomial()){
        solutionPolynomial res = solveRational(function.get_polynomial());
        solution = res.step_solution;
        solution.push_back("r");
        if (res.roots.empty() && res.complex.empty())
             solution.push_back("No steps solution found.");

        else{

            if (!res.roots.empty()){
                solution.push_back("The roots are");
                solution.push_back(":");
            }
            solution.push_back("n");


            for (int i = 0; i < (int)res.roots.size(); i++)
                solution.push_back(to_string(res.roots[i]));
            solution.push_back("n");

            if(!res.complex.empty()){
                solution.push_back("The complex roots are");
                solution.push_back(":");
            }

            for (int i = 0; i < (int)res.complex.size(); i++)
                solution.push_back(res.complex[i]);
            solution.push_back("n");
        }


         string s = "";
         for (map<string,int>::iterator it=res.factors.begin(); it != res.factors.end(); it++){
             s += it->first;
             if(it->second > 1){
                 s += "^"+ to_string(it->second);
             }
         }

         solution.push_back("Factorization");
         solution.push_back(":");
         solution.push_back(s);
         solution.push_back("n");
    }
    else
        solution.push_back("r");


    if (!sol.empty()){
        solution.push_back("Numerical roots obtained");
        solution.push_back(":");

        for (auto i : sol)
            solution.push_back(to_string(i));
    }
    else
        solution.push_back("No numerical solution found.");


    return solution;
}
vector<string> inetgral(string f, char var){
    f = f.substr(3, f.size() - 3);
    int i =1;
    string a = "";
    while (f[i] != '}')
        a += f[i++];

    double down;
    if (a == "-inf")
        down = -10000;
    else
        down = AbstractFunction(simplify(a, var)).get_value(0);

    i++;
    string b = "";
    while (f[i] != '}')
        b += f[i++];

    double up;
    if (b == "inf")
        up = 10000;
    else
        up = AbstractFunction(simplify(b, var)).get_value(0);
    i++;

    vector<string> res{"r", "Result", ":"};
    res.push_back(to_string(AbstractFunction(simplify(f.substr(i, f.size() - i - 1), var)).get_integral_value(down, up)));
    return res;
}
vector<string> system(string f, char var){
    f = f.substr(4, f.size() - 5);
    vector< vector <Rational> > X;
    vector< vector <Rational> > Y;
    string num = "";
    int x = 0;
    X.push_back(vector<Rational>());
    for (int i = 0; i < (int)f.size(); i++){
        if (f[i] == ';'){
            X[x].push_back(Rational(AbstractFunction(simplify(num, var))(0)));
            num = "";
        }
        else if (f[i] == '='){
            X[x].push_back(Rational(AbstractFunction(simplify(num, var))(0)));
            num = "";
            Y.push_back(vector<Rational>());
        }
        else if (f[i] == '|'){
            Y[x].push_back(Rational(AbstractFunction(simplify(num, var))(0)));
            num = "";
            x++;
            X.push_back(vector<Rational>());
        }
        else
            num += f[i];
    }

    Y[x].push_back(Rational(AbstractFunction(simplify(num, var))(0)));

    int m = X[0].size();
    int n = X.size();

    for (int i = 1; i < n; i++)
        if ((int)X[i].size() != m)
            return vector<string>{"i"};


    return gaussian(Matrix<Rational>(X), Matrix<Rational>(Y));
}
vector<string> division(string f, char var){
    string make_poly[2];
    make_poly[0] = "";
    make_poly[1] = "";
    int cnt = 0;
    for (int i = 0; i < (int)f.size(); i++){
        if(f[i] == '(' || f[i] == ')')
            continue;
        else if (f[i] == ':')
            cnt++;
        else
            make_poly[cnt] += f[i];
    }
    AbstractFunction P(simplify(make_poly[0], var), var);
    AbstractFunction Q(simplify(make_poly[1], var), var);

    if (!P.is_polynomial() || !Q.is_polynomial())
        return vector<string>{"i"};

    divPolynomial res =  divisionR(P.get_polynomial(), Q.get_polynomial());
    res.step_solution.push_back("r");
    res.step_solution.push_back("Quotient");
    res.step_solution.push_back(":");
    res.step_solution.push_back(res.Quotient.get_string());
    res.step_solution.push_back("n");
    if (res.ReminderZero)
        res.step_solution.push_back("Reminder is 0");
    else{
        res.step_solution.push_back("Reminder");
        res.step_solution.push_back(":");
        res.step_solution.push_back(res.Reminder.get_string());
    }

    return res.step_solution;
}

vector<string> multiplication_poly(string f, char var){
    string make_poly[2];
    make_poly[0] = "";
    make_poly[1] = "";
    int cnt = 0;
    for (int i = 0; i < (int)f.size(); i++){
        if(f[i] == '(' || f[i] == ')')
            continue;
        else if (f[i] == '*')
            cnt++;
        else
            make_poly[cnt] += f[i];
    }
    AbstractFunction P(simplify(make_poly[0], var), var);
    AbstractFunction Q(simplify(make_poly[1], var), var);

    if (!P.is_polynomial() || !Q.is_polynomial())
        return vector<string>{"i"};

    PolynomialRational R = P.get_polynomial()* Q.get_polynomial();

    return vector<string> {"r", R.get_string()};
}

bool (*checkProcess[])(string) = {
        check_derivative,
        check_equation,
        check_integral,
        check_system,
        check_divisonPolynomials,
        check_multiplication
};

vector<string> (*solve_problem[])(string, char){
    derivative,
    equation,
    inetgral,
    system,
    division,
    multiplication_poly
};

vector<string> start_process(string f, char var){
    f = upload_function(f);
    int cnt=0;
    for (int i = 0; i < 6; i++)
        if (checkProcess[i](f))
            cnt++;

    if(cnt>1 || cnt == 0)
        return vector<string>{"i"};

    vector<string> res;
    for (int i = 0; i < 6; i++)
        if (checkProcess[i](f))
            res = solve_problem[i](f, var);

    return res;
}


