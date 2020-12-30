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

//Operator::Operator(int t){
//    type = t;
//}

int Operator::get_type(){
    return type;
}



//the following function checks if the substring is a given function
bool is_function_(string s, string f){
    for (int i= 0; i < int(f.size()); i++){
        if (s[i] != f[i]){
            return false;
        }
    }
    return true;
}

//the following function checks if the substring contains any function
string find_function(string s){
    for (int j=0; j<(int(functions.size())); j++){
        string elem = functions[j];
        if (is_function_(s, elem)){
            return elem;
        }
    }
    return "";
}

//The following function takes as input a function under the form of a string and outputs a vector of tokens
vector<Token> simplify(string s, char variable){
    //cout << s << endl;
    vector <Token> new_vector;
    int i = 0;
    string digits = "";
    while (i < int(s.size())){
        //We ignore spaces of all types
        if ((s[i] != ' ') && (s[i] != '\t') && (s[i] != '\n')){
            //Case 1 : a digit
            if (isdigit(s[i])){
                string c(1, s[i]);
                digits += c;
                }
            else {
                if (digits != ""){
                    new_vector.push_back(Num(digits));
                    digits = "";
                }
                //Case 2 : a letter
                if (isalpha(s[i])){
                    //Case 2.a : beginning of a function
                    string s1 = s.substr(i, i+5);
                    string potential_function = find_function(s1);

                    //If it is the beginning of a function, we add the corresponding
                    //token function to the new_vector
                    if (potential_function != ""){
                           new_vector.push_back(Function(potential_function));
                           //We introduce a composition operator
                           new_vector.push_back(Operator("~"));
                           i = int(potential_function.size());
                           int opening_index = i;
                           i++;
                           string supertoken = "";

                           while (i != closing_pare(s, opening_index)){
                               string c(1, s[i]);
                               supertoken +=  c;
                               i++;
                           }
                         //cout << i << " " << supertoken<< '\n';
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
               else {
               //Case 5 : operators
                  if (is_in_vector(str_operators, string(1,s[i]))){
                         if (s[i] == '('){
                            string supertoken = "";
                            int opening_index = i;
                            i++;
                            while (i != closing_pare(s,opening_index)){
                                string c(1, s[i]);
                                supertoken += c;
                                i++;
                                }
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
        i++;
    }
    if (digits != ""){
        new_vector.push_back(Num(digits));
    }
    return new_vector;
};



