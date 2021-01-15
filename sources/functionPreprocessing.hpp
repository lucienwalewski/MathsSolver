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
bool check_det(string f);
bool check_inv(string f);
bool check_mult(string f);

vector<string> derivative(string f);
vector<string> equation(string f);
vector<string> inetgral(string f);
vector<string> system(string f);
vector<string> division(string f);
vector<string> multiplication_poly(string f);
vector<string> determinant(string f);
vector<string> inverse(string f);
vector<string> mult_matrix(string f);


vector<string> start_process(string f);

#endif // FUNCTIONPREPROCESSING_HPP
