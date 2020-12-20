#ifndef FUNCTIONPREPROCESSING_HPP
#define FUNCTIONPREPROCESSING_HPP

#include<string>
#include<iostream>
#include<vector>

using namespace std;

//class could be implemented

string upload_function();

//checking processes
bool check_derivative(string f);
bool check_equation(string f);
bool check_integral(string f);

string start_process(string f);

#endif // FUNCTIONPREPROCESSING_HPP
