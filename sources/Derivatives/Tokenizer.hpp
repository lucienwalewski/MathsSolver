#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include "Include_libraries.h"

using namespace std;

bool is_in_vector(vector< string > v, string elem);

bool is_function_(string s, string f);

string find_function(string s);


//definition of the Token class with its four subclasses : Operator, Num, Function, Variable
class Token {
protected:
    int type;
    string value;
public :
    Token(string s);
    Token();
    string get_value();
    int get_type();
    bool is_super_token(){return false;}
};


class Operator: public Token{
public :
    Operator();
    Operator(string t);
    int get_type();
};


class Num: public Token {
public:
    Num(string t):Token(t){
        type = -5;
    };
private:
};


class Function: public Token{
public :
    Function(string t): Token(t){
        type = -2;
    };
};


class Variable: public Token{
public:

    Variable(string t): Token(t){
        type = -3;
    };
private:
};


class SuperToken : public Token {
public:
    SuperToken(string t):Token(t){
        type = -4;
    }
    bool is_super_token(){return true;}
};


string find_function(string s);
bool is_function_(string s, string f);

vector<Token> simplify(string s, char variable);
vector<Token> simplify(string s);

bool one_variable(string s, char variable);
bool one_variable(string s);

#endif // TOKENIZER_HPP
