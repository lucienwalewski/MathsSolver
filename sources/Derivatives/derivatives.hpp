#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"

#include <string>
#include <vector>
using namespace std;




class AbstractFunction {
public:
    AbstractFunction(vector<Token> fun);

    template <typename Function1, typename Function2> AbstractFunction(Function1 left, Function2 right, Operator operation){
        this-> left = left;
        this-> right = right;
        this-> operation = operation;
        this->str_label = left->str_label + get_string_operation()  + right->str_label;
    };


    AbstractFunction(AbstractFunction left, AbstractFunction right, Operator operation);
    ~AbstractFunction(){};


    AbstractFunction();

    void op_to_enum(char op,Operator &operation);

    AbstractFunction get_left();
    void set_left(AbstractFunction *left);
    AbstractFunction get_right();
    void set_right(AbstractFunction *right);

    Operator get_operation();
    void set_operation(Operator operation);
    string get_string_operation();

    string get_str_label();
    string get_in_str_label();
    string display();
    bool is_none();


    template <typename Function1> Function1 solve();

    template <typename Function1, typename Function2> AbstractFunction add(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction subtract(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction multiply(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction divide(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction chain_rule(Function1 function1, Function2 function2);



private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    string in_str_label;
    vector<Token> vect_label;

};




class SinFunction : public AbstractFunction{
public:
    SinFunction(Token val);
    template <typename Function1> Function1 solve();
    Token get_value();
private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    Token value;
};



class CosFunction : public AbstractFunction{
public:
    CosFunction(Token val);
    template <typename Function1> Function1 solve();
    Token get_value();
private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    string in_str_label;
    Token value;
};



class ExponentialFunction : public AbstractFunction{
public:
    ExponentialFunction(Token base, Token val);
    template <typename Function1> Function1 solve();

    Token get_base();
    Token get_value();
private:
    Token base;
    Token value;
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string in_str_label;
    string str_label;
};



class LogarithmicFunction : public AbstractFunction{
public:
    LogarithmicFunction(Token val, Token base);
    template <typename Function1> Function1 solve();

    Token get_base();
    Token get_value();
private:
    Token base;
    Token value;

    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string in_str_label;
    string str_label;
};




class PolynomialFunction : public AbstractFunction{
public:
    PolynomialFunction(Token val, Token exponent);
    template <typename Function1> Function1 solve();

    Token get_exponent();
    Token get_value();
private:
    Token exponent;
    Token value;

    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string in_str_label;
    string str_label;
};



class ConstantFunction : public AbstractFunction{
public:
    ConstantFunction(Token c);
    template <typename Function1> Function1 solve();

    Token get_c();
private:
    Token c;

    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string in_str_label;
    string str_label;
};

string vect_to_str(vector<Token> fun);

#endif // DERIVATIVES_HPP
