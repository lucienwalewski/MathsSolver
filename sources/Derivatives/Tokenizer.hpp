#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

enum operator_type {none = 0, add, sub, mul, divi, pow, comp, pare};


bool is_letter(char s){
    if ((s>='0' && s<='9') or ( (s>='A' && s<='Z'))){
        return true;
    }
    return false;
};

bool is_number(char s){
    if ((s>='0' && s<='9')){
        return true;
    }
    return false;
};

bool is_in_vector(vector< string > v, string elem){
    return (find(v.begin(), v.end(), elem));
};

vector <string> constants{"pi", "e"};

vector <string> functions{"cos", "sin", "exp", "tan", "sqrt"};

vector <string> operators{"+", "-", "/", "^", "sqrt"};

enum Types{Operator = 0, Num, Function, Variable};

class Operator {
private :
    operator_type value;
public :
    Operator(){
        value = none;
    }
    Operator(char t){
        if (t == '+'){
            value = add;
        };
        if (t == '-'){
            value = sub;
        };
        if (t == '*'){
            value = mul;
        };
        if (t == '/'){
            value = divi;
        };
        if (t == '^'){
            value = pow;
        };
        if (t == '(' or t == ')'){
            value = pare;
        };
    };

    operator_type get_type(){
        return value;
    }

  };

class Num {
private :
    string value;
public :
    Num(){
        value = none;
    }
    Num(string t){
            value = t;
        }
    string get_value(){
        return value;
    }
};

class Function {
private :
    string value;
public :
    Function(){
        value = none;
    }
    Function(string t){
            value = t;
        }
    string get_value(){
        return value;
    }
};

class Variable{
private :
    string value;
public:
    Variable(string s){
        value = s;
    }
    string get_value(){
        return value;
    }
};


template <typename T> class Token {
private :
    T elem;
    string value;
public :
    Token(T o){
        elem = o;
        value = o.value();
     }
    string get_value(){
            return value;
        }
};

vector< Token<double> > simplify(string s, string variable){
    vector<Token<template T>> new_vector;
    string current;
    std::string::iterator i = s.begin();
    for (i; i< s.end(); i++){
        if ((i* == variable) or (not is_letter(i*)) {
            if (is_in_vector(constants, current)){
                new_vector.push_back(Token(Num(current)));
            }
            else if (is_in_vector(functions, current)){
                new_vector.push_back(Token(Function(current)));
            }
            if (is_in_vector(operators, i*)){
                new_vector.push_back(Token(Operator(i*)));
            }
            else if (is_number(i*)){
                new_vector.push_back(Token(Num(i*)));
            }
            else if (i* == variable){
                new_vector.push_back(Token(Variable(i*)));
                }
         }
        else {
             current.pushback(i*);
    }
}
    return new_vector;
};


#endif // TOKENIZER_HPP
#endif // TOKENIZER_HPP
