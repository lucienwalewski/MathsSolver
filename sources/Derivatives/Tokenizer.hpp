#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

enum operator_type {
    none = 0,
    addition = 5,
    sub = 4,
    mul = 3,
    divi = 2,
    power = 6,
    comp = 1,
    pare = 7};


bool is_letter(char s){
    if ((s>='0' && s<='9') or  ( (s>='A' && s<='Z'))){
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
    return (find(v.begin(), v.end(), elem) != v.end());
};

vector <string> constants{"pi", "e"};

vector <string> functions{"cos", "sin", "exp", "tan", "sqrt", "ln"};

vector <string> str_operators{"+", "-", "/", "^", "sqrt", "(", ")"};


class Token {
protected :
    string value;
    operator_type type;
public :
    Token(string s){
        value = s;
     }
    Token(){
        value = "";
    }
    string get_value(){
            return value;
        }
    operator_type get_type(){
        return type;
    }
};



class Operator: public Token{
private :
    operator_type type;

public :
    Operator():Token(){
        type = none;
    }
    Operator(string t): Token(t){
        if (t == "+"){
            type = addition;

        };
        if (t == "-"){
            type = sub;
        };
        if (t == "*"){
            type = mul;
        };
        if (t == "/"){
            type = divi;
        };
        if (t == "^"){
            type = power;

        };
        if (t == "~"){
                type = comp;
            };
        if (t == "(" or t == ")"){
            type = pare;
        };
        if (t == ""){
            type = none;
        }
    };

    Operator(operator_type t){
        type = t;
    }

    operator_type get_type(){
        return type;
    }


};


class Num: public Token {
public :
    Num(string t):Token(t){
        }
};

class Function: public Token{
public :
    Function(string t): Token(t){
        }
};

class Variable: public Token{
public:
    Variable(string t): Token(t){
    }
};


vector<Token> simplify(string s, char variable){
    vector <Token> new_vector;
    string current;
    //std::string::iterator i = s.begin();
    for (int i=0; i < int(s.size()); i++){
        if ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')){
            continue;
        }
        else if ((s[i] == variable) || (!is_letter(s[i])) ){
            if (is_in_vector(constants, current)){
                new_vector.push_back(Num(current));
                current = "";
            }
            else if (is_in_vector(functions, current)){
                new_vector.push_back(Function(current));
                current = "";
            }
            else {
                new_vector.push_back(Num(current));
                current = "";
            }
            if (is_in_vector(str_operators, string(1,s[i]))){

                string c(1, s[i]);
                new_vector.push_back(Operator(c));
            }
            else if (is_number(s[i])){
                string c(1, s[i]);
                new_vector.push_back(Num(c));
            }
            else if (s[i] == variable){
                string c(1, s[i]);
                new_vector.push_back(Variable(c));
                }
         }
        else {
             current.push_back(s[i]);
    }
}
    return new_vector;
};


#endif // TOKENIZER_HPP

