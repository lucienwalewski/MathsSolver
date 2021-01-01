#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#define MAX_ITER 1000000
#define EPS 0.00001
#include "Tokenizer.hpp"
#include "Equations/polynomial.hpp"

#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

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
        this->type = 10;
    };

    AF(AF left, AF right, Operator operation);
    AF(int type, Token end_token);
   // ~AF(){delete left;delete right;};

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
    string get_in_str_label();
    string display(int i);
    bool is_none();

    vector<double> get_roots(double start = -100, double end = 100);
    double regula_falsi(double a, double b);
    double get_integral_value(double a, double b);
    bool is_polynomial();
    PolynomialRational get_polynomial(bool neg = false);
    int get_type();
    void set_type(int type);
    bool get_end(){return end;}
    void set_end(bool end){this->end = end;}
    void assign_type();
    virtual double get_value(double x, bool  neg = false, bool div = false);
    double get_leaf_value(double x, int n, string value);
   // virtual string get_derivative(); return can be string or Token
    int leaf_mark = -1;
protected:
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

class ExpAF: public AF{
public:
    ExpAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class LnAF: public AF{
public:
    LnAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class LogAF: public AF{
public:
    LogAF(double a);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
    double get_base();
private:
    Token value;
    double base;
};

class CosAF: public AF{
public:
    CosAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class SinAF: public AF{
public:
    SinAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class TanAF: public AF{
public:
    TanAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class SqrtAF: public AF{
public:
    SqrtAF();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class NumAF: public AF{
public:
    NumAF(Token T);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class VarAF: public AF{
public:
    VarAF(Token T);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

AF* assign(Token fun);
string vect_to_str(vector<Token> fun);


#endif // DERIVATIVES_HPP
