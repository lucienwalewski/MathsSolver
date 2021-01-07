#include "Tokenizer.hpp"
#include "Operators.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stack>

//The following function deletes layers of exterior parentheses
// ex : "((5x))" -> "5x"
string del_exterior_parentheses(string v){
    string s ;
    int i = 0;
    int j = v.size()-1;
    while ((v[i] == '(') and (closing_pare(v, i) == j)){
        i++;
        j--;
    }
    for (int l = i; l < j+1 ;  l++){
             s.push_back(v[l]);
    }
    return s;
};


//The following function associates an open parenthesis to its corresponding closed one
int closing_pare(string t, int i){
    int counter = 1;
    int j = i + 1;
    while (counter != 0){
        if (t[j] == '('){
            counter++;
        }
        else if (t[j] == ')'){
            counter--;
        }
        j++;
    }
    return j-1;
};


//The following function allows to add multiplication signs where they are ommittes
//(ex : [Num("5"), Variable("x")] -> [Num("5"), Operator("*"), Variable("x")])

string add_multiplication(string v){
    string new_string;
    for (int i = 0; i < int(v.size())-1; i ++){
        new_string.push_back(v[i]);
        //case 1 : num followed by "("
        if ((isdigit(v[i]) && (v[i+1] == '('))){
            new_string.push_back('*');
        }
        //case 2 : num followed by function, variable, constant, ...
        else if ((isdigit(v[i])) && (isalpha(v[i+1]))){
            new_string.push_back('*');
        }
        //case 3 : ")" followed by "("
        else if ((v[i] == '(') && (v[i+1] == '(')){
            new_string.push_back('*');
        }
        if (i== int(v.size()) -2){
            new_string.push_back(v[i+1]);
        }
    }
    v.clear();
    v.shrink_to_fit();
    return new_string;
};

//The following function returns the string inside parentheses
string inside_parentheses(string s, int i){
    string inside = "";
    i++;
    int counter = 1;
    while (counter > 0){
        if (s[i] == '(')
            counter++;
        else if (s[i] == ')')
            counter--;

        if (counter > 0)
            inside += s[i];

        i++;
    }

    return inside;
};


