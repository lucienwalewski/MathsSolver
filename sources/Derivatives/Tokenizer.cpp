
#include "Tokenizer.hpp"

//bool is_letter(char s){
//    if ((s>='0' && s<='9') or  ( (s>='A' && s<='Z'))){
//        return true;
//    }
//    return false;
//};

//bool is_number(char s){
//    if ((s>='0' && s<='9')){
//        return true;
//    }
//    return false;
//};

bool is_in_vector(vector< string > v, string elem){
    return (find(v.begin(), v.end(), elem) != v.end());
};


vector <string> constants{"pi", "e"};

vector <string> functions{"cos", "sin", "exp", "tan", "sqrt", "ln"};

vector <string> str_operators{"+", "-", "/", "^", "sqrt", "(", ")"};


Token::Token(){
    value = "";
}

Token::Token(string s){
    value = s;
 }

string Token::get_value(){
        return value;
    }

operator_type Token::get_type(){
    return type;
}

Operator::Operator():Token(){
    type = none;
}
Operator::Operator(string t): Token(t){
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

Operator::Operator(operator_type t){
    type = t;
}

operator_type Operator::get_type(){
    return type;
}


vector<Token> simplify(string s, char variable){
    vector <Token> new_vector;
    string current;
    for (int i=0; i < int(s.size()); i++){
        if ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')){
            continue;
        }
        else if ((s[i] == variable) || !isalpha(s[i])){
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
            else if (isdigit(s[i])){
                string c(1, s[i]);
                new_vector.push_back(Num(c));
            }
            else if (s[i] == variable){
                string c(1, s[i]);
                new_vector.push_back(Variable(c));
                }
         }
        else {
             current+=s[i];
    }
}
    return new_vector;
};

