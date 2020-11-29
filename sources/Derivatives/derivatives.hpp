#ifndef DERIVATIVES_HPP
#define DERIVATIVES_HPP

#include <string>
using namespace std;

enum Operation{
    addition = 5,
    subtraction = 4,
    multiplication = 3,
    division = 2,
    composition = 1,
    none = 0
};

string operators = "+-*/^~";
class AbstractFunction {
public:
    AbstractFunction(string our_function);
    AbstractFunction(AbstractFunction *left, AbstractFunction *right, Operation operation);
    ~AbstractFunction();
    AbstractFunction();
    void op_to_enum(char op,Operation &operation);
    AbstractFunction get_left();
    void set_left(AbstractFunction *left);
    AbstractFunction get_right();
    void set_right(AbstractFunction *right);
    Operation get_operation();
    void set_operation(Operation operation);
    AbstractFunction solve();
    string get_str_label();

    AbstractFunction add(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction subtract(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction multiply(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction divide(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction chain_rule(AbstractFunction function1, AbstractFunction function2);
private:
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;

};

class SinFunction : public AbstractFunction{
public:
    SinFunction();
    AbstractFunction solve();
private:
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};

class CosFunction : public AbstractFunction{
public:
    CosFunction();
    AbstractFunction solve();
private:
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};
class ExponentialFunction : public AbstractFunction{
public:
    ExponentialFunction(int base);
    AbstractFunction solve();
    int get_base();
private:
    int base;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};

class LogarithmicFunction : public AbstractFunction{
public:
    LogarithmicFunction(int base);
    AbstractFunction solve();
    int get_base();
private:
    int base;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};

class PolynomialFunction : public AbstractFunction{
public:
    PolynomialFunction(int exponent);
    AbstractFunction solve();
    int get_exponent();
private:
    int exponent;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};

class ConstantFunction : public AbstractFunction{
public:
    ConstantFunction(int c);
    AbstractFunction solve();
    int get_c();
private:
    int c;
    Operation operation;
    AbstractFunction *left;
    AbstractFunction *right;
    string str_label;
};



#endif // DERIVATIVES_HPP
