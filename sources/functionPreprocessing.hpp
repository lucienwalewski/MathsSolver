#ifndef FUNCTIONPREPROCESSING_HPP
#define FUNCTIONPREPROCESSING_HPP

#include "Include_libraries.h"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"
#include "Equations/numbers.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"


using namespace std;


//class could be implemented

string upload_function();

//checking processes
bool check_derivative(string f);
bool check_equation(string f);
bool check_integral(string f);
bool check_system(string f);
bool check_divisonPolynomials(string f);
bool check_multiplication(string f);

vector<string> derivative(string f, char var);
vector<string> equation(string f, char var);
vector<string> inetgral(string f, char var);
vector<string> system(string f, char var);
vector<string> division(string f, char var);
vector<string> multiplication_poly(string f, char var);

vector<string> start_process(string f, char var = 'x');

#endif // FUNCTIONPREPROCESSING_HPP
