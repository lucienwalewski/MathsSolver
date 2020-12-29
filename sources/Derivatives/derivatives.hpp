#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"

#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SF{
public:
    SF(Token Fun){fun = Fun;}
    ~SF(){}
    SF(){};
    int get_type(){return type;}
protected:
    Token fun;
    int type = 0;
};

class Fvar : public  SF{
public:
    Fvar(string str);
    Fvar(Token leaf){value = leaf.get_value();cout << "SF string is " << value << ""<<'\n';type = 1;}
    ~Fvar(){}
private:
    string value;
};
class Fcons : public SF{
public:
    Fcons(string str){value = str;}
    Fcons(Token leaf){value = leaf.get_value();type = 2;}
    ~Fcons(){}
private:
    string value;
};

class Fnum : public SF{
public:
    Fnum(string str){value = str;}
    Fnum(Token leaf){value = leaf.get_value(); stringstream new_num(value);new_num >> num;type = 3;}
    ~Fnum(){}
private:
    string value;
    int num;
};

class Fexp : public SF {
public:
    Fexp(string str){value = str;}
    Fexp(Token leaf){value = leaf.get_value();type = 4;}
    ~Fexp(){};
private:
    string value;
    //special exponent stuff.
};

class Flog : public SF {
public:
    Flog(string str){value = str;}
    Flog(Token leaf){value = leaf.get_value();type = 5;}
    ~Flog(){};
private:
    string value;
};

class Fcos : public SF {
public:
    Fcos(string str){value = str;}
    Fcos(Token leaf){value = leaf.get_value();type = 6;}
    ~Fcos(){};
private:
    string value;
};

class Fsin : public SF {
public:
    Fsin(string str){value = str;}
    Fsin(Token leaf){value = leaf.get_value();type = 7;}
    ~Fsin(){};
private:
    string value;
};

class Ftan : public SF {
public:
    Ftan(string str){value = str;}
    Ftan(Token leaf){value = leaf.get_value();type = 8;}
    ~Ftan(){};
private:
    string value;
};

class Fln : public SF {
public:
    Fln(string str){value = str;}
    Fln(Token leaf){value = leaf.get_value();type = 9;}
    ~Fln(){};
private:
    string value;
};

class Fsqrt : public SF {
public:
    Fsqrt(string str){value = str;}
    Fsqrt(Token leaf){value = leaf.get_value();type = 10;}
    ~Fsqrt(){};
private:
    string value;
};

class Fcomp : public SF {
public:
    Fcomp(string str){value = str;}
    Fcomp(Token leaf){value = leaf.get_value();type = 11;}
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
        this->leaf = SF();
        this->base_type = 10;
    };

    AF(AF left, AF right, Operator operation);
    AF(int type, string str);
    ~AF(){delete left;delete right;};

    void op_to_enum(char op,Operator &operation);

    AF get_left();
    vector<Token> get_vect_label(){return vect_label;}
    void set_left(AF *left);
    AF get_right();
    void set_right(AF *right);

    Operator get_operation();
    void set_operation(Operator operation);
    string get_string_operation();

    string get_str_label();
    string display();
    bool is_none();

    int get_base_type();
    void set_base_type(int type);
    SF get_leaf(){return leaf;}
    void set_leaf(SF leaf){this->leaf = leaf;}
    bool get_end(){return end;}
    void set_end(bool end){this->end = end;}
    void assign_type();


private:
    Operator operation;
    class AF *left;
    class AF *right;
    string str_label;
    vector<Token> vect_label;
    int base_type;
    bool end;
    SF leaf;
    Token end_token;
};


AF solve(AF func);
void build_tree(vector<Token>);
void assign(Token fun,SF &leaf);







class LeafFunc{
public:
    LeafFunc(string func);
    LeafFunc(){};
    ~LeafFunc(){};
    AF solve();
    int get_base_type();
    string get_str_label();
    AF to_AF();
protected:
    string str_label;
    int base_type = 0;
};

class VarF : public LeafFunc{
public:
    VarF(string var);
    ~VarF(){};
    AF solve();
    AF to_AF();
};

class ConsF : public LeafFunc{
public:
    ConsF(string cons);
    ~ConsF(){};
    AF solve();
    AF to_AF();
};


class NumF : public LeafFunc{
public:
    NumF(string c);
    ~NumF(){};
    AF solve();
    AF to_AF();
};

class ExpF : public LeafFunc{
public:
    ExpF();
    ~ExpF(){};
    AF solve();
    AF to_AF();
};

class LogaF : public LeafFunc{
public:
    LogaF();
    ~LogaF(){};
    AF solve();
    AF to_AF();
};

class CosF : public LeafFunc{
public:
    CosF();
    ~CosF(){};
    AF solve();
    AF to_AF();
};

class SinF : public LeafFunc{
public:
    SinF();
    ~SinF(){};
    AF solve();
    AF to_AF();
};

class TanF : public LeafFunc{
public:
    TanF();
    ~TanF(){};
    AF solve();
    AF to_AF();
};

class LnF : public LeafFunc{
public:
    LnF();
    ~LnF(){};
    AF solve();
    AF to_AF();
};

class SqrtF : public LeafFunc{
public:
    SqrtF();
    ~SqrtF(){};
    AF solve();
    AF to_AF();
};

class SubF : public LeafFunc{
public:
    SubF(string func);
    ~SubF(){};
    AF solve();
    AF to_AF();
};




AF sf_derivatives(SF &leaf);
AF derive(AF Func);
string vect_to_str(vector<Token> fun);




#endif // DERIVATIVES_HPP
