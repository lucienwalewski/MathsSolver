#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"

#include <string>
#include <vector>
using namespace std;



class AF {
public:
    AF(vector<Token> fun);

    AF(){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        end = true;
        this->str_label = "";
        this->in_str_label = "";
    };

    AF(AF left, AF right, Operator operation);
    AF(int type, Token end_token);
    ~AF(){};

    void op_to_enum(char op,Operator &operation);

    AF get_left();
    void set_left(AF *left);
    AF get_right();
    void set_right(AF *right);

    Operator get_operation();
    void set_operation(Operator operation);
    string get_string_operation();

    string get_str_label();
    string get_in_str_label();
    string display();
    bool is_none();

    int get_type();
    void set_type(int type);





private:
    Operator operation;
    AF *left;
    AF *right;
    string str_label;
    string in_str_label;
    vector<Token> vect_label;
    int type;
    bool end;
    Token end_token;


};





class CosF{
public:
    CosF();
    ~CosF(){};
    CosF(Token val);
    AF solve();
    Token get_value();
    int get_type();
    string get_str_label();
    AF to_AF();
private:

    string str_label;
    string in_str_label;
    Token value;
    int type = 1;
};


class SinF{
public:
    SinF();
    ~SinF(){};
    SinF(Token val);
    AF solve();
    Token get_value();
    int get_type();
    string get_str_label();
    AF to_AF();
private:
    string str_label;
    Token value;
    int type = 2;
};







class Exp{
public:
    Exp(Token base, Token val);
    Exp();
    ~Exp(){};
    AF solve();

    Token get_base();
    Token get_value();
    int get_type();
    string get_str_label();

    AF to_AF();
private:

    Token base;
    Token value;

    string in_str_label;
    string str_label;
    int type = 3;
};



class Loga {
public:
    Loga(Token val, Token base);
    Loga();
    ~Loga(){};
    AF solve();

    Token get_base();
    Token get_value();
    int get_type();
    string get_str_label();

    AF to_AF();
private:
    Token base;
    Token value;

    string in_str_label;
    string str_label;
    int type = 4;
};




class Poly{
public:
    Poly(Token val, Token exponent);
    Poly();
    ~Poly(){};
    AF solve();

    Token get_exponent();
    Token get_value();
    int get_type();
    string get_str_label();

    AF to_AF();
private:
    Token exponent;
    Token value;

    string in_str_label;
    string str_label;
    int type = 5;
};



class Cons{
public:
    Cons(Token c);
    Cons();
    ~Cons(){};
    AF solve();

    Token get_c();
    int get_type();
    string get_str_label();

    AF to_AF();
private:
    Token c;

    string in_str_label;
    string str_label;
    int type = 6;
};

AF solve();
string vect_to_str(vector<Token> fun);



#endif // DERIVATIVES_HPP
