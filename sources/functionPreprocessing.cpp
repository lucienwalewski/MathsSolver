#include "functionPreprocessing.hpp"
// matrix, inversion, multiplication, power, transponse and determinantes
// adding var varibale as mandatory in the code
// is double integer
// more dteialed checks
// finish check polynomials

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
    if (f.substr(0,3) == "sys")
        return true;
    else
        return false;

    // more checkings needed
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

bool check_integral(string f){
    /*checking if integral solving should be performed*/
    if (f.size()<12)
        return false;
    if (f.substr(0,3) == "int")
        return true;
    else
        return false;
}

vector<string> derivative(string f){
    AbstractFunction function(simplify(f.substr(1, (int)f.size() - 3), 'x'));
    //return = function.get_derivative();
    return vector<string>();
}

vector<string> equation(string f){
    vector<string> solution;
    bool find = false;
    string solve = "";
    for (int i = 0; i< (int)f.size(); i++){
        if (f[i] == '='){
            find = true;
            if (f[i+1] == '0')
                break;
            else if (f[i+1] != '-')
                solve += '-';
        }
        else if (find && (f[i] == '+'))
            solve += '-';
        else if (find && (f[i] == '-'))
            solve += '+';
        else
            solve += f[i];
    }

    solve += "=0";
    vector<Token> tokens = simplify(solve.substr(0, solve.size()-2), 'x');
    AbstractFunction function(tokens);
    vector<double> sol = function.get_roots();
    if (function.is_polynomial()){
        solutionPolynomial res = solveRational(function.get_polynomial());
        solution = res.step_solution;
        solution.push_back("r");
        if (res.roots.empty() && res.complex.empty()){
             solution.push_back("No Solution");
             std::cout<<"No Solution"<<std::endl;
        }
        else{

            if (!res.roots.empty())
                solution.push_back("The roots are:");

            for (int i = 0; i < (int)res.roots.size(); i++)
                solution.push_back(to_string(res.roots[i]));

            if(!res.complex.empty())
                solution.push_back("The complex roots are:");

            for (int i = 0; i < (int)res.complex.size(); i++)
                solution.push_back(res.complex[i]);
        }


         string s = "";
         for (map<string,int>::iterator it=res.factors.begin(); it != res.factors.end(); it++){
             s += it->first;
             if(it->second > 1){
                 s += "^"+ to_string(it->second);
             }
         }

         solution.push_back("Factorization:");
         solution.push_back(s);
    }
    else
        solution.push_back("r");


    if (!sol.empty())
        solution.push_back("Numerical roots obtained:");
    else
        solution.push_back("No numerical solution found");

    for (auto i : sol)
        solution.push_back(to_string(i));

    return solution;
}
vector<string> inetgral(string f){
    f = f.substr(3, f.size() - 3);
    int i =1;
    string a = "";
    while (f[i] != '}')
        a += f[i++];

    double down;
    if (a == "-inf")
        down = -10000;
    else
        down = AbstractFunction(simplify(a, 'x')).get_value(0);

    i++;
    string b = "";
    while (f[i] != '}')
        b += f[i++];

    double up;
    if (b == "inf")
        up = 10000;
    else
        up = AbstractFunction(simplify(b, 'x')).get_value(0);
    i++;

    string res = to_string(AbstractFunction(simplify(f.substr(i, f.size() - i - 1), 'x')).get_integral_value(down, up));
    cout<< res<<"\n";

    return vector<string>{res};
}
vector<string> system(string f){
    f = f.substr(4, f.size() - 5);
    vector< vector <Rational> > X;
    vector< vector <Rational> > Y;
    string num = "";
    int x = 0;
    int y = 0;
    int op = 0;
    bool eq = false;
    X.push_back(vector<Rational>());
    for (int i = 0; i < (int)f.size(); i++){
        //maybe token
        if (isdigit(f[i]) || (f[i] == '.') || (f[i] == '+') || (f[i] == '-'))
            num += f[i];
        else if (f[i] == '*'){
            if (eq)
                Y[x].push_back(Rational(stod(num)));
            else
                X[x].push_back(Rational(stod(num)));
            op = 1;
            num = "";
        }
        else if (f[i] == '/'){
            if (eq)
                Y[x].push_back(Rational(stod(num)));
            else
                X[x].push_back(Rational(stod(num)));
            op = 2;
            num = "";
        }
        else if (f[i] == ';'){
            if (op == 1)
                X[x][y] = X[x][y]*Rational(stod(num));
            else if (op == 2)
                X[x][y] = X[x][y]/Rational(stod(num));
            else
                X[x].push_back(Rational(stod(num)));

            op = 0;
            y++;
            num = "";
        }
        else if (f[i] == '|'){
            if (op == 1)
                Y[x][0] = Y[x][0]*Rational(stod(num));
            else if (op == 2)
                Y[x][0] = Y[x][0]/Rational(stod(num));
            else
                Y[x].push_back(Rational(stod(num)));

            op = 0;
            y = 0;
            x++;
            X.push_back(vector<Rational>());
            num = "";
            eq = false;
        }
        else if (f[i] == '='){
            if (op == 1)
                X[x][y] = X[x][y]*Rational(stod(num));
            else if (op == 2)
                X[x][y] = X[x][y]/Rational(stod(num));
            else
                X[x].push_back(Rational(stod(num)));

            op = 0;
            Y.push_back(vector<Rational>());
            eq = true;
            num = "";
        }
        else{
            cout << "Wrong input!\n";
            return vector<string>();
        }

    }

    if (op == 1)
        Y[x][0] = Y[x][0]*Rational(stod(num));
    else if (op == 2)
        Y[x][0] = Y[x][0]/Rational(stod(num));
    else
        Y[x].push_back(Rational(stod(num)));

    int m = X[0].size();
    int n = X.size();

    for (int i = 1; i < n; i++)
        if ((int)X[i].size() != m){
            cout<< n<<"\n";
            cout << "Wrong size input\n";
            return vector<string>();
        }

    gaussian(Matrix<Rational>(X), Matrix<Rational>(Y));

    return vector<string>();
}
vector<string> division(string f){
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
    AbstractFunction P(simplify(make_poly[0], 'x'));
    AbstractFunction Q(simplify(make_poly[1], 'x'));

    if (!P.is_polynomial() || !Q.is_polynomial()){
        cout<< "Not division between rationals polynomials!\n";
        return vector<string>();
    }
    divisionR(P.get_polynomial(), Q.get_polynomial(), true);

    return vector<string>();
}

bool (*checkProcess[])(string) = {
        check_derivative,
        check_equation,
        check_integral,
        check_system,
        check_divisonPolynomials
};

vector<string> (*solve_problem[])(string){
    derivative,
    equation,
    inetgral,
    system,
    division,
};

vector<string> start_process(string f){
    f = upload_function(f);
    int cnt=0;
    for (int i = 0; i < 5; i++)
        if (checkProcess[i](f))
            cnt++;

    if(cnt>1 || cnt == 0){
        cout<<"Invalid input.\n";
        return vector<string>();
    }

    vector<string> res;
    for (int i = 0; i < 5; i++)
        if (checkProcess[i](f))
            res = solve_problem[i](f);

    return res;
}


