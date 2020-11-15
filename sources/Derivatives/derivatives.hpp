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

class AbstractFunction {
public:
    AbstractFunction(string our_function);
    AbstractFunction(AbstractFunction left, AbstractFunction right, Operation operation);
    ~AbstractFunction();
    AbstractFunction();
    AbstractFunction get_left();
    void set_left(AbstractFunction left);
    AbstractFunction get_right();
    void set_right(AbstractFunction right);
    Operation get_operation();
    void set_operation(Operation operation);
    AbstractFunction solve();

    AbstractFunction add(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction subtract(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction multiply(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction divide(AbstractFunction function1, AbstractFunction function2);
    AbstractFunction chain_rule(AbstractFunction function1, AbstractFunction function2);
private:
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;

};

class SinFunction : public AbstractFunction{
public:
    SinFunction();
    AbstractFunction solve();
private:
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};

class CosFunction : public AbstractFunction{
public:
    CosFunction();
    AbstractFunction solve();
private:
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};
class ExponentialFunction : public AbstractFunction{
public:
    ExponentialFunction(int base);
    AbstractFunction solve();
    int get_base();
private:
    int base;
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};

class LogarithmicFunction : public AbstractFunction{
public:
    LogarithmicFunction(int base);
    AbstractFunction solve();
    int get_base();
private:
    int base;
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};

class PolynomialFunction : public AbstractFunction{
public:
    PolynomialFunction(int exponent);
    AbstractFunction solve();
    int get_exponent();
private:
    int exponent;
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};

class ConstantFunction : public AbstractFunction{
public:
    ConstantFunction(int c);
    AbstractFunction solve();
    int get_c();
private:
    int c;
    Operation operation;
    AbstractFunction left;
    AbstractFunction right;
};



#endif // DERIVATIVES_HPP
