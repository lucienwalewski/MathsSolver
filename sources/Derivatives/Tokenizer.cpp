#include "Tokenizer.hpp"
#include "derivatives.hpp"
#include "Operators.hpp"

map<string, int> type_map = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

bool is_in_vector(vector< string > v, string elem){
    return (find(v.begin(), v.end(), elem) != v.end());
};

vector <string> functions{"cos", "sin", "exp", "tan", "sqrt", "log", "ln"};


vector <string> str_operators{"+", "-", "*" , "/", "^", "sqrt", "(", ")", "_", "~"};


Token::Token(){
    value = "";
    type = -1;
}

Token::Token(string s){
    value = s;
}

string Token::get_value(){
        return value;
}

int Token::get_type(){
    return type;
}

Operator::Operator():Token(){
    type = -1;
}
Operator::Operator(string t): Token(t){
    type = type_map[t];
};


int Operator::get_type(){
    return type;
}



//the following function checks if the substring is a given function
bool is_function_(string s, string f){
    for (int i= 0; i < (int)f.size(); i++)
        if (s[i] != f[i])
            return false;

    return true;
}

//the following function checks if the substring contains any function
string find_function(string s){
    for (int i=0; i<(int)functions.size(); i++)
        if (is_function_(s, functions[i]))
            return functions[i];

    return "";
}

//The following function takes as input a function under the form of a string and outputs a vector of tokens
//The string is assumed to be valid.
vector<Token> simplify(string v, char variable){
    string t = replace_e(v);
    string w = del_exterior_parentheses(t);
    string s = add_multiplication(w);

    vector <Token> new_vector;
    string digits = "";
    for (int i = 0; i < (int)s.size(); i++){
        //Case 1 : a digit
        if (isdigit(s[i]) || s[i] == '.')
            digits += s[i];

        else {
            if (digits != ""){
                new_vector.push_back(Num(digits));
                digits = "";
            }
            //Case 2 : a letter
            if (isalpha(s[i])){
                //cout<< s[i] <<"\n";
                //Case 2.a : beginning of a function
                string s1 = s.substr(i, 4);
                string potential_function = find_function(s1);

                //If it is the beginning of a function, we add the corresponding
                //token function to the new_vector
                if (potential_function != ""){
                       new_vector.push_back(Function(potential_function));
                       //We introduce a composition operator
                       new_vector.push_back(Operator("~"));
                       i += (int)potential_function.size();
                       string supertoken = inside_parentheses(s, i);
                       i += (int)supertoken.size() + 1;
                       new_vector.push_back(SuperToken(supertoken));
                }
                else {
                    //Case 3 : variable
                    if (s[i] == variable){
                        string c(1, s[i]);
                        new_vector.push_back(Variable(c));
                    }
                    //Case 4 : any constant
                    else {
                        string c(1, s[i]);
                        new_vector.push_back(Num(c));
                    }
                }
           }
           else{
            //Case 5 : operators
                  if (is_in_vector(str_operators, string(1,s[i]))){
                     if (s[i] == '('){
                        string supertoken = inside_parentheses(s, i);
                        i += int(supertoken.size()) + 1;
                        new_vector.push_back(SuperToken(supertoken));
                     }
                     else {
                         string c(1, s[i]);
                         new_vector.push_back(Operator(c));
                     }
                  }
            }
        }
    }

    if (digits != "")
        new_vector.push_back(Num(digits));

    return new_vector;
};


//If no variable is mentionned, the default variable is 'x'.
vector<Token> simplify(string s){
    return simplify(s, 'x');
}
string simplify_polynomial(string s,map<string, int> &poly_map){
    bool repeat = false;
    poly_map = {{"x",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};
    vector<Token> tok = simplify(s);
    for (int i = 0; i < int(tok.size());i++){

    }
    if (repeat) {s = simplify_polynomial(s, poly_map);}
    return s;
}
int find_next_plus(vector<Token> t, int i){
    int j = i;
    while (j < int(t.size())){
        if (t[j].get_value() == "x"){
            return j;
        }
        j += 1;
    }
    if (j != i){
        return j;
    }else {return -1;}
}

