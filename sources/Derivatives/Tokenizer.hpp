#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

//enum operator_type {
//    other = 0,
//    none,
//    comp,
//    divi,
//    power,
//    mul,
//    sub,
//    addition,
//    pare,
//    base,};


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
};



class Operator: public Token{
private :
    int type;

public :
    Operator();
    Operator(string t);
//    Operator(int t);
    int get_type();
};


class Num: public Token {
public :

    Num(string t):Token(t){
        type = -1;
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




vector<Token> simplify(string s, char variable);


#endif // TOKENIZER_HPP
