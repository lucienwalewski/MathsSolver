#include "Tokenizer.hpp"
#include "Operators.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "Include_libraries.h"

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
    if ((int)v.size() <= 1)
        return v;

    string new_string = "";
    for (int i = 0; i < (int)v.size()-1; i ++){
        new_string.push_back(v[i]);
        //case 1 : num followed by "("
        if ((isdigit(v[i]) && (v[i+1] == '(')))
            new_string.push_back('*');   
        //case 2 : num followed by function, variable, constant, ...
        else if ((isdigit(v[i])) && (isalpha(v[i+1])))
            new_string.push_back('*');
        //case 3 : ")" followed by "("
        else if ((v[i] == ')') && (v[i+1] == '('))
            new_string.push_back('*');

        if (i + 2 == (int)v.size()){
            new_string.push_back(v[i+1]);
        }
    }
    v.clear();
    v.shrink_to_fit();
    if (new_string[0] == '*')
        new_string = new_string.substr(1);

    return new_string;
};

//The following function returns the string inside parentheses.
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

//String validity (operators issues)

//Check if every opening parenthesis has a closing one and
//that there are in the right order : opening first and closing second
bool valid_parentheses(string s){
    vector <char> v;
    for (int i=0; i < int(s.size()); i++){
        if (s[i] == '('){
            v.push_back(s[i]);
        }
        else if (s[i] ==')'){
            if (v.empty()){
                return false;
            }
            else {
                v.pop_back();
                }
           }
         }
    if (v.empty()){
        return true;
    }
    else {
        return false;
    }
   };

//The following function returns false if there are no missing parentheses
//It returns true if there are missing parentheses
bool missing_parentheses(string s){
    if (not valid_parentheses(s)){
        return true;
    }
    for (int i=0; i < int(s.size())-1; i++){
        if (isalpha(s[i])){
            string s1 = s.substr(i, 4);
            string potential_function = find_function(s1);
            if ((potential_function != "") && (s[i+potential_function.size()] != '(')){
                return true;
            }
        }
     }
    return false;
   };


vector <string> modified_str_operators{"+", "-", "*" , "/", "^", "sqrt", "_", "~"};


//The following function returns true if there are no operators in the above vector next to each other.
bool valid_operators(string s){
    if (is_in_vector(modified_str_operators, string(1,s[1]))){
        return false;
    }
    for (int i=2; i < int(s.size())-1; i++){
        if(is_in_vector(modified_str_operators, string(1,s[i]))){
            if (is_in_vector(modified_str_operators, string(1,s[i-1])) || is_in_vector(modified_str_operators, string(1,s[i+1]))){
                return false;
            }
            else if (s[i] == '^' && s[i+1] == '0'){
                return false;
            }
        }
    }
    return true;
    };


//The following function deletes useless layers of parentheses inside a string on some simple cases.
// ex : "exp(((x)))" -> "exp(x)"
string delete_layers_pare(string t){
    string new_s;
    string s = del_exterior_parentheses(t);
    for (int i = 0; i < int(s.size()); i++){
        if (s[i] == '('){
            new_s += "(";
            string inside = inside_parentheses(s, i);
            new_s += del_exterior_parentheses(inside);
            i += int(inside.size());
        }
       else {
            string c(1, s[i]);
            new_s += c;
        }
    }
    return new_s;
}

bool is_valid(string s){
    if (s.empty()){
        cout << "The input is empty. Please enter it again." << endl;
        return false;
    }
    if (valid_parentheses(s) == false){
        cout << "Error : The parentheses are not valid." << endl;
        return false;
    }
    if (missing_parentheses(s) == true){
        cout << "Error : There are missing parentheses." << endl;
        return false;
    }
    if (valid_operators(s) == false){
        cout << "Error : The operators are not valid." << endl;
    }
    return true;
};


string replace_e(string s){
    string sub = "e^";
    int len = int(s.length());
    for (int i = 0; i<len;i++){
        if (s.substr(i,2) == sub){
            if (s[i + 2] == '('){
                int c = closing_pare(s,i+2);
                int mids = c -i -3;
                string l = s.substr(0,i);
                string middle = "exp(" + s.substr(i + 3, mids) + ")";
                string r = s.substr(c+1,len-c);
                s = l + middle + r;

            } else {
            string l = s.substr(0,i);
            string middle = "exp(" + s.substr(i+2,1) + ")";
            string r = s.substr(i + 3,len-i-3);
            s = l + middle + r;
            }
        }
    }
    return s;
};
