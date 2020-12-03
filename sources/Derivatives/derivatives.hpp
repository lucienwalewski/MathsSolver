#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP
#include "Tokenizer.hpp"

#include <string>
using namespace std;

enum Operation{
    addition = 5,
    subtraction = 4,
    multiplication = 3,
    division = 2,
    composition = 1,
    no_op = 0
};


string operators = "+-*/^~";
class AbstractFunction {
public:
    AbstractFunction(string our_function);

    template <typename Function1, typename Function2> AbstractFunction(Function1 left, Function2 right, Operation operation){
        this-> left = left;
        this-> right = right;
        this-> operation = operation;
        this->str_label = left->str_label + get_string_operation()  + right->str_label;
    };

    AbstractFunction(AbstractFunction left, AbstractFunction right, Operation operation);
    ~AbstractFunction();
    AbstractFunction();

    void op_to_enum(char op,Operation &operation);

    AbstractFunction get_left();
    void set_left(AbstractFunction *left);
    AbstractFunction get_right();
    void set_right(AbstractFunction *right);

    Operation get_operation();
    void set_operation(Operation operation);
    string get_string_operation();

    string get_str_label();

    bool is_none();


    template <typename Function1> Function1 solve();

    template <typename Function1, typename Function2> AbstractFunction add(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction subtract(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction multiply(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction divide(Function1 function1, Function2 function2);

    template <typename Function1, typename Function2> AbstractFunction chain_rule(Function1 function1, Function2 function2);



private:
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;

};




class SinFunction : public AbstractFunction{
public:
    SinFunction(Token val);
    template <typename Function1> Function1 solve();
    Token get_value();
private:
    Operation operation;
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
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
    Token value;
};



class ExponentialFunction : public AbstractFunction{
public:
    ExponentialFunction(Token base);
    template <typename Function1> Function1 solve();

    Token get_base();
private:
    Token base;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
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
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};




class PolynomialFunction : public AbstractFunction{
public:
    PolynomialFunction(Token base, Token exponent);
    template <typename Function1> Function1 solve();

    Token get_exponent();
    Token get_base();
private:
    Token exponent;
    Token base;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



class ConstantFunction : public AbstractFunction{
public:
    ConstantFunction(Token c);
    template <typename Function1> Function1 solve();

    Token get_c();
private:
    Token c;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};


















#endif // DERIVATIVES_HPP
