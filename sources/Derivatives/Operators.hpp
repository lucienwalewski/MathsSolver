#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include "Tokenizer.hpp"
#include "Include_libraries.h"

string del_exterior_parentheses(string v);

int closing_pare(string t, int i);

string add_multiplication(string v);

string inside_parentheses(string s, int i);

#endif // OPERATORS_HPP

