#include "Tokenizer.hpp"
#include "Operators.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


//The following function deletes useless parentheses (layers of exterior parentheses and with only one digit in it)
// ex : [Operator("("), Num("5"), Variable("x"), Operator(")")] -> [Num("5"), Variable("x")]
vector<Token> del_useless_parentheses(vector <Token> v){
    vector <Token> new_vector;
    int i = 0;
    while (v[i].get_type() == 7){
        i++;
    }
    for (int j = i; j < int(v.size())-i ;  j++){
         //if ((v[i].get_type() != 7) && (v[i+2].get_type() != 8)){
             new_vector.push_back(v[i]);
         //}
    }
    v.clear();
    v.shrink_to_fit();
    return new_vector;
};


//The following function associates an open parenthesis to its corresponding closed one
int closing_pare(string t, int i){
    int counter = 1;
    int j = i;
    while (counter != 0){
        if (t[i] == '('){
            counter += 1;
            j++;
        }
        if (t[i] == ')'){
            counter -= 1;
            j++;
        }
    }
    return j;
};


//The following function allows to add multiplication signs where they are ommittes
//(ex : [Num("5"), Variable("x")] -> [Num("5"), Operator("*"), Variable("x")])

vector <Token> add_multiplication(vector<Token> v){
    vector <Token> new_vector;
    for (int i = 0; i < int(v.size())-1; i += 2){
        new_vector.push_back(v[i]);
        //case 1 : num followed by "("
        if ((v[i].get_type() == -1) || (v[i+1].get_type() == 7)){
            new_vector.push_back(Operator("*"));
        }
        //case 2 : num followed by function
        if ((v[i].get_type() == -1) || (v[i+1].get_type() == -2)){
            new_vector.push_back(Operator("*"));
        }
        //case 3 : num followed by variable
        if ((v[i].get_type() == -1) || (v[i+1].get_type() == -3)){
            new_vector.push_back(Operator("*"));
        }
        //case 4 : ")" followed by "("
        if ((v[i].get_type() == 8) || (v[i+1].get_type() == 7)){
            new_vector.push_back(Operator("*"));
        }
        new_vector.push_back(v[i+1]);
    }
    v.clear();
    v.shrink_to_fit();
    return new_vector;
};


