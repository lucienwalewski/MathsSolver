#ifndef OPERATORS_HPP
#define OPERATORS_HPP
#include "Tokenizer.hpp"
#include "Include_libraries.h"

string del_exterior_parentheses(string v);

int closing_pare(string t, int i);

string add_multiplication(string v);

string inside_parentheses(string s, int i);

bool valid_parentheses(string s);

bool missing_parentheses(string s);

bool valid_operators(string s);

bool is_valid(string s);

#endif // OPERATORS_HPP

