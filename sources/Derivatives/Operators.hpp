#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include "Tokenizer.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

string del_exterior_parentheses(string v);

int closing_pare(string t, int i);

vector<Token> add_multiplication(vector<Token> v);


#endif // OPERATORS_HPP

