#include "Tokenizer.hpp"
#include "Operators.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "Include_libraries.h"


vector <string> modified_str_operators{"+", "-", "*" , "/", "^", "_", "~", ")"};
vector <string> modified_str_operators2{"+", "-", "*" , "/", "^", "_", "~"};

//The following function deletes layers of exterior parentheses.
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


//The following function associates an open parenthesis to its corresponding closed one.
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


//The following function allows to add multiplication signs where they are ommitted.
string add_multiplication(string v, char variable){
    if ((int)v.size() <= 1)
        return v;
    string new_string = "";
    for (int i = 0; i < (int)v.size()-1; i ++){
        new_string.push_back(v[i]);
        if ((isalpha(v[i]))){
            string c(1, v[i+1]);
            //It is either a variable, a function or a constant.

            // case 1 : variable not followed by an operator
            if (v[i] == variable && !is_in_vector(modified_str_operators, c)){
                new_string.push_back('*');
               }
            //case 2 : function
            else if (int(v.size()) - i > 4){
                    string v1 = v.substr(i, 4);
                    string potential_function = find_function(v1);
                    //If the function is log followed by _, special case of the base
                    if (potential_function == "log" && v[i+ int(potential_function.size())] == '_'){
                        new_string.pop_back();
                        new_string += "log_";
                        if (v[i+1+int(potential_function.size())] == '('){
                            new_string += "(";
                            i += 2+int(potential_function.size());
                        }
                        else {
                            i += 1+int(potential_function.size());
                        }
                        while (v[i] != '('){
                                new_string.push_back(v[i]);
                                i++ ;
                            }
                            i --;
                        }
                    //Other functions
                     else if (potential_function != ""){
                        new_string.pop_back();
                        new_string += potential_function;
                        while (v[i] != '('){
                                i++ ;
                            }
                            i --;
                        }
                    //variable
                    else {
                        string c(1, v[i+1]);
                        if (!is_in_vector(modified_str_operators, c)){
                            new_string.push_back('*');
                        }
                        }
            }
            //case 3 : variable
            else {
                    string c(1, v[i+1]);
                    if (!is_in_vector(modified_str_operators, c)){
                    new_string.push_back('*');
                        }
                  }
                    }
        //case 4 : num followed by "("
        else if ((isdigit(v[i]) && (v[i+1] == '('))){
            new_string.push_back('*');
        }
        //case 5 : num followed by function, variable, constant, ...
        else if ((isdigit(v[i])) && (isalpha(v[i+1]))){
            new_string.push_back('*');
        }
        //case 6 : ")" followed by "("
        else if ((v[i] == ')') && (v[i+1] == '(')){
            new_string.push_back('*');
        }
        //case 7 : ")" followed by a digit
        else if ((v[i] == ')') && (isdigit(v[i+1]))){
            new_string.push_back('*');
        }
        //case 8 : ")" followed by a letter
        else if ((v[i] == ')') && (isalpha(v[i+1]))){
            new_string.push_back('*');
        }
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


//The following function converts a log in base a in a log base 10 with a preceding factor of 1/log(a).
//In the following function, we assume the operators are present and valid.
string convert_log_base(string s){
    string new_s = "";
    for (int i= 0; i < int(s.size()); i++){
        if (s[i] == 'l'){
            string s1 = s.substr(i, 3);
            if (find_function(s1) == "log"){
                i+= 3;
                if (s[i] == '_'){
                    if (s[i+1] == '('){
                       new_s += "1/log(" + inside_parentheses(s, i+1) + ")*log";
                       i = closing_pare(s, i+1);
                    }
                    else {
                        cout << s[i] << endl;
                        i++;
                        string base = "";
                        while (s[i] != '('){
                            string c(1, s[i]);
                            base += c;
                            i++;
                        }
                        cout << base << endl;
                        cout << s[i] << endl;
                        if (base == "10"){
                            new_s += "log(" + inside_parentheses(s, i) + ")";
                            i = closing_pare(s,i);
                        }
                        else {
                            new_s += "1/log(" + base + ")*log(" + inside_parentheses(s, i) + ")";
                            i = closing_pare(s,i);
                        }
                    }
                }
                else if (s[i] == '('){
                    new_s += "log(";
                    i+= 3;
                    cout << i << endl;
                }
            }
        }
        else {
            string c(1, s[i]);
            new_s += c;
        }
    }
    return new_s;
}


//String validity (operators issues)

//Check if every opening parenthesis has a closing one and
//that there are in the right order : opening first and closing second.
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

//The following function returns false if there are no missing parentheses.
//It returns true if there are missing parentheses.
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


//The following function returns true if there are no operators in the above vector next to each other
//and no simple division by 0.
bool valid_operators(string s){
    if (s.size() > 1 && s[0] == '-')
        return  true;
    if (is_in_vector(modified_str_operators2, string(1,s[0]))){
        return false;
    }
    for (int i=2; i < int(s.size())-1; i++){
        if(is_in_vector(modified_str_operators2, string(1,s[i]))){
            if (is_in_vector(modified_str_operators2, string(1,s[i-1])) || is_in_vector(modified_str_operators2, string(1,s[i+1]))){
                return false;
            }
            else if (s[i] == '/' && s[i+1] == '0'){
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
        return false;
    }
    if (one_variable(s) == false){
        return false;
    }
    return true;
};


string replace_e(string s){
    bool repeat = false;
    string sub = "e^";
    int len = int(s.length());
    for (int i = 0; i<len;i++){
        if (s.substr(i,2) == sub){
            repeat = true;
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
    if (repeat){
        replace_e(s);
    }
    return s;
};
