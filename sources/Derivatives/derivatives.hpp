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
    ~AbstractFunction();
    AbstractFunction();

    void op_to_enum(char op,Operator &operation);

    AbstractFunction* get_left();
    void set_left(AbstractFunction *left);
    AbstractFunction* get_right();
    void set_right(AbstractFunction *right);

    Operator get_operation();
    void set_operation(Operator operation);
    string get_string_operation();

    string get_str_label();


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

};




class SinFunction : public AbstractFunction{
public:
    SinFunction();
    template <typename Function1> Function1 solve();
private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



class CosFunction : public AbstractFunction{
public:
    CosFunction();
    template <typename Function1> Function1 solve();
private:
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



class ExponentialFunction : public AbstractFunction{
public:
    ExponentialFunction(int base);
    template <typename Function1> Function1 solve();

    int get_base();
private:
    int base;
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



class LogarithmicFunction : public AbstractFunction{
public:
    LogarithmicFunction(int base);
    template <typename Function1> Function1 solve();

    int get_base();
private:
    int base;
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};




class PolynomialFunction : public AbstractFunction{
public:
    PolynomialFunction(int exponent);
    template <typename Function1> Function1 solve();

    int get_exponent();
private:
    int exponent;
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



class ConstantFunction : public AbstractFunction{
public:
    ConstantFunction(int c);
    template <typename Function1> Function1 solve();

    int get_c();
private:
    int c;
    Operator operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};


















#endif // DERIVATIVES_HPP
