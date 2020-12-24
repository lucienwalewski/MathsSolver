#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"

#include <string>
#include <vector>
#include <sstream>
using namespace std;


class SF{
public:
    SF(Token Fun){fun = Fun;}
    ~SF(){}
    SF(){};
private:
    Token fun;
};
class Fvar : public  SF{
public:
    Fvar(string str);
    Fvar(Token leaf){value = leaf.get_value();cout << "SF string is " << value << ""<<'\n';}
    ~Fvar(){}
private:
    string value;
    int type;
};
class Fcons : public SF{
public:
    Fcons(string str){value = str;}
    Fcons(Token leaf){value = leaf.get_value();}
    ~Fcons(){}
private:
    string value;
};
class Fnum : public SF{
public:
    Fnum(string str){value = str;}
    Fnum(Token leaf){value = leaf.get_value(); stringstream new_num(value);new_num >> num;}
    ~Fnum(){}
private:
    string value;
    int num;
};
class Fexp : public SF {
public:
    Fexp(string str){value = str;}
    Fexp(Token leaf){value = leaf.get_value();}
    ~Fexp(){};
private:
    string value;
    //special exponent stuff.
};
class Flog : public SF {
public:
    Flog(string str){value = str;}
    Flog(Token leaf){value = leaf.get_value();}
    ~Flog(){};
private:
    string value;
};
class Fcos : public SF {
public:
    Fcos(string str){value = str;}
    Fcos(Token leaf){value = leaf.get_value();}
    ~Fcos(){};
private:
    string value;
};
class Fsin : public SF {
public:
    Fsin(string str){value = str;}
    Fsin(Token leaf){value = leaf.get_value();}
    ~Fsin(){};
private:
    string value;
};
class Ftan : public SF {
public:
    Ftan(string str){value = str;}
    Ftan(Token leaf){value = leaf.get_value();}
    ~Ftan(){};
private:
    string value;
};
class Fln : public SF {
public:
    Fln(string str){value = str;}
    Fln(Token leaf){value = leaf.get_value();}
    ~Fln(){};
private:
    string value;
};
class Fsqrt : public SF {
public:
    Fsqrt(string str){value = str;}
    Fsqrt(Token leaf){value = leaf.get_value();}
    ~Fsqrt(){};
private:
    string value;
};
class Fcomp : public SF {
public:
    Fcomp(string str){value = str;}
    Fcomp(Token leaf){value = leaf.get_value();}
    ~Fcomp(){};
private:
    string value;
};


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
    SF leaf;
    Token end_token;


};


void assign(Token fun,SF &leaf);


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
