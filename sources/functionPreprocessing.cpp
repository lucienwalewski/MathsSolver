#include "functionPreprocessing.hpp"

// matrix, inversion, multiplication, power, transponse and determinantes
// check for multiplications of the polynomials
// checking if sign * is missing
// adding var varibale as mandatory in the code

string upload_function(string f){
    /*uploading of the given function*/
    string s="";

    for(int i=0; i<(int)f.size(); i++){
        if(f[i]==' ' || f[i]=='\t' || f[i]=='\n')
            continue;
        s+=f[i];
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
    if (f.size()<6)
        return false;
    if (f.substr(0,3) == "int")
        return true;
    else
        return false;
}

vector<string> derivative(string f){
    return vector<string>();
}

vector<string> equation(string f){
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
    cout<< solve << "\n";
    vector<Token> tokens = simplify(solve, 'x');
    //AF function(tokens);
    Rational c[6] = {Rational(-280, 1), Rational(634, 1), Rational(-357, 1), Rational(46, 1), Rational(14, 1), Rational(-3, 1)};
    PolynomialRational P(c, 5);

         solutionPolynomial res = solveRational(P);
         for(auto i : res.step_solution)
             cout<< i<< "\n";
         if (res.roots.empty())
         {
             std::cout<<"No Solution"<<std::endl;
         }

         printf("The roots are\n");
         for (auto i : res.roots)
         {
             std::cout<<i<<std::endl;
         }

         printf("The complex roots are\n");
         for (auto i : res.complex){
             cout<<i<<"\n";
         }

         string s = "";
         for (auto i : res.factors){
             s += i.first;
             if(i.second > 1){
                 s += "^"+ to_string(i.second);
             }
          }

         cout<<s << "\n";

    return vector<string>();
}
vector<string> inetgral(string f){
    return vector<string>();
}
vector<string> system(string f){
    return vector<string>();
}
vector<string> division(string f){
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


