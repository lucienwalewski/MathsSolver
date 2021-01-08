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

vector<string> derivative(string f);
vector<string> equation(string f);
vector<string> inetgral(string f);
vector<string> system(string f);
vector<string> division(string f);


vector<string> start_process(string f);

#endif // FUNCTIONPREPROCESSING_HPP
