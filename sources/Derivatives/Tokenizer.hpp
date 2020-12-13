#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

enum operator_type {
    other = -1,
    none = 0,
    addition = 5,
    sub = 4,
    mul = 3,
    divi = 2,
    power = 6,
    comp = 1,
    pare = 7,
    base = 8};


bool is_in_vector(vector< string > v, string elem);

bool is_function_(string s, string f);

string find_function(string s);

//definition of the Token class with its four subclasses : Operator, Num, Function, Variable
class Token {
protected :
    operator_type type;
    string value;
public :
    Token(string s);
    Token();
    string get_value();
    operator_type get_type();
};



class Operator: public Token{
private :
    operator_type type;

public :
    Operator();
    Operator(string t);
    Operator(operator_type t);
    operator_type get_type();
};


class Num: public Token {
public :

    Num(string t):Token(t){};

};

class Function: public Token{
public :

    Function(string t): Token(t){};

};

class Variable: public Token{
public:

    Variable(string t): Token(t){};
};

vector<Token> simplify(string s, char variable);


#endif // TOKENIZER_HPP
