#include "Tokenizer.hpp"
#include "Operators.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>


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

vector <Token> add_multiplication(vector<Token> v){
    vector <Token> new_vector;
    for (int i = 0; i < int(v.size())-1; i += 2){
        new_vector.push_back(v[i]);
        //case 1 : num followed by "("
        if ((v[i].get_type() == -1) || (v[i+1].get_type() == 7)){
            new_vector.push_back(Operator("*"));
        }
        //case 2 : num followed by function
        else if ((v[i].get_type() == -1) || (v[i+1].get_type() == -2)){
            new_vector.push_back(Operator("*"));
        }
        //case 3 : num followed by variable
        else if ((v[i].get_type() == -1) || (v[i+1].get_type() == -3)){
            new_vector.push_back(Operator("*"));
        }
        //case 4 : ")" followed by "("
        else if ((v[i].get_type() == 8) || (v[i+1].get_type() == 7)){
            new_vector.push_back(Operator("*"));
        }
        new_vector.push_back(v[i+1]);
    }
    v.clear();
    v.shrink_to_fit();
    return new_vector;
};


