#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"
#include "Equations/polynomial.hpp"

#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

const int MAX_ITER =1000000;
const double EPS =  0.00001;

using namespace std;

class AbstractFunction {
public:
    AbstractFunction(vector<Token> fun);
    AbstractFunction(){
        this->left = nullptr;
        this->right = nullptr;
        this->operation = Operator();
        this->str_label = "";
        this->type = 0;
    };

    AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation);
   // ~AbstractFunction(){delete left;delete right;};

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

    vector<double> get_roots(double start = -100, double end = 100);
    double regula_falsi(double a, double b);
    double get_integral_value(double a, double b);
    bool is_polynomial();
    PolynomialRational get_polynomial(bool neg = false);
    int get_type();
    void set_type(int type);
    double get_value(double x, bool  neg = false);
    double get_leaf_value(double x, int n, string value);
    string  get_derivative();
    string  get_leaf_derivative(int n);
    int leaf_mark = -1;

private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    vector<Token> vect_label;
    int type;
};


int assign(Token fun);
string add_strings(string l, string r);
string sub_strings(string l, string r);
string mult_strings(string l, string r);
string div_strings(string l, string r);
string pow_strings(string l, string r);
bool check_par(vector<Token> fun);

#endif // DERIVATIVES_HPP
