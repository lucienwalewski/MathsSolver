#include "testderivative.hpp"
#include <QtTest>
#include <QCoreApplication>
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/Operators.hpp"
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

void testDerivative::test_find_function()
{
    string s = "cos(5x)";
    string f = find_function(s);
    QVERIFY(f == "cos");
    string t = "ln(4)";
    string g = find_function(s);
    QVERIFY(g == "ln");
}

void testDerivative::test_simplify()
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
    for (int i=0; i < int(v.size()); i++){
       cout << "The value of the token is" << v[i].get_value() << endl;
       cout << "You should have the following value" << w[i].get_value() << endl;
    }
    QVERIFY(v == w);
}

void testDerivative::test_corresponding_pare()
{
     string s = "(83)cos(6x)(3(x^2(ln(x))))";
     int closing_1 = 3;
     int closing_2 = 25;
     int corres_1 = closing_pare(s, 0);
     int corres_2 = closing_pare(s, 11);
     QVERIFY(closing_1 == corres_1);
     QVERIFY(closing_2 == corres_2);
}

void testDerivative::test_del_useless_parentheses()
{
    vector <Token> s{Operator("("),Operator("("), Num("8"),Operator(")"), Function("cos"),
                Operator("("), Num("6"), Operator(")"), Operator(")")};
    vector <Token> v{Num("8"), Function("cos"), Operator("("), Num("6"), Operator(")")};
    vector <Token> u = del_useless_parentheses(s);
    QVERIFY(v == u);
}

void testDerivative::test_add_multiplication()
{   vector <Token> s{ Operator("("), Num("8"), Num("3"), Operator(")"), Function("cos"),
                Operator("("), Num("6"), Variable("x"), Operator(")"), Operator("("),
                Num("3"), Operator("("), Variable("x"), Operator(")"), Operator(")")};
    vector <Token> v{ Operator("("), Num("8"), Num("3"), Operator(")"), Operator("*"),
                    Function("cos"), Operator("("), Num("6"), Operator("*"), Variable("x"),
                    Operator(")"), Operator("*"), Operator("("), Num("3"), Operator("*"),
                    Operator("("), Variable("x"), Operator(")"), Operator(")")};
    vector <Token> u = add_multiplication(s);
    QVERIFY(v == u);
}
