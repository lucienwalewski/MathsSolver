#include "testderivative.hpp"
#include <QtTest>
#include <QCoreApplication>
#include "Derivatives/Tokenizer.hpp"
// add necessary includes here


testDerivative::testDerivative()
{

}

testDerivative::~testDerivative()
{

}

void testDerivative::initTestCase()
{

}

void testDerivative::cleanupTestCase()
{

}

void testDerivative::test_tokenizer()
{
    string s = "5 + sin(exp(x))";
    char variable = 'x';
    vector <Token> v = simplify(s, variable);
    vector <Token> w;
    w.push_back(Num("5"));
    w.push_back(Operator("+"));
    w.push_back(Function("sin"));
    w.push_back(Operator("("));
    w.push_back(Function("exp"));
    w.push_back(Operator("("));
    w.push_back(Variable("x"));
    w.push_back(Operator(")"));
    w.push_back(Operator(")"));
    for (int i=0; i < v.size(); i++){
       cout << "The value of the token is" << v[i].get_value() << endl;
       cout << "You should have the following value" << w[i].get_value() << endl;
    }
    QVERIFY(v == w);
}

void testDerivative::test_case2()
{
    int a = 1, b = 1;
    QVERIFY(a == b);
}
