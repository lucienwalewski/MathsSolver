#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#define MAX_ITER 1000000
#define EPS 0.00001
#include "Tokenizer.hpp"
//#include "Equations/polynomial.hpp"

#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class AbstractFunction {
public:
    AbstractFunction(vector<Token> fun);
    AbstractFunction(){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        end = true;
        this->str_label = "";
        this->type = 10;
    };

    AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation);
    AbstractFunction(int type, Token end_token);
   // ~AbstractFunction(){delete left;delete right;};

    void op_to_enum(char op,Operator &operation);

    AbstractFunction get_left();
    vector<Token> get_vect_label(){return vect_label;}
    void set_left(AbstractFunction *left);
    AbstractFunction get_right();
    void set_right(AbstractFunction *right);

    Operator get_operation();
    void set_operation(Operator operation);
    string get_string_operation();

    string get_str_label();
    string display();
    bool is_none();

    vector<double> get_roots(double start = -100, double end = 100);
    double regula_falsi(double a, double b);
    double get_integral_value(double a, double b);
    bool is_polynomial();
//    PolynomialRational get_polynomial(bool neg = false);
    int get_type();
    void set_type(int type);
    bool get_end(){return end;}
    void set_end(bool end){this->end = end;}
    void assign_type();
    virtual double get_value(double x, bool  neg = false, bool div = false);
    double get_leaf_value(double x, int n, string value);
    virtual string  get_derivative();
    string  get_leaf_derivative(int n, string val);
    int leaf_mark = -1;

protected:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    vector<Token> vect_label;
    int type;
    bool end;
    Token end_token;

};

class ExpAbstractFunction: public AbstractFunction{
public:
    ExpAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class LnAbstractFunction: public AbstractFunction{
public:
    LnAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class LogAbstractFunction: public AbstractFunction{
public:
    LogAbstractFunction(double a);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
    double get_base();

private:
    Token value;
    double base;
};

class CosAbstractFunction: public AbstractFunction{
public:
    CosAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class SinAbstractFunction: public AbstractFunction{
public:
    SinAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class TanAbstractFunction: public AbstractFunction{
public:
    TanAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class SqrtAbstractFunction: public AbstractFunction{
public:
    SqrtAbstractFunction();
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);

private:
    Token value;
};

class NumAbstractFunction: public AbstractFunction{
public:
    NumAbstractFunction(Token T);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

class VarAbstractFunction: public AbstractFunction{
public:
    VarAbstractFunction(Token T);
    string get_derivative();
    double get_value(double x, bool  neg = false, bool div = false);
private:
    Token value;
};

AbstractFunction* assign(Token fun);
string vect_to_str(vector<Token> fun);

string add_strings(string l, string r);
string sub_strings(string l, string r);
string mult_strings(string l, string r);
string div_strings(string l, string r);
string pow_strings(string l, string r);

#endif // DERIVATIVES_HPP
