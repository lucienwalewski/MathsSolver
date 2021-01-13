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
    string s = "cos(x) + 5^2 + sin(exp(x))";
    char variable = 'x';
    vector <Token> v = simplify(s, variable);
    vector <Token> w;
    w.push_back(Function("cos"));
    w.push_back(Operator("("));
    w.push_back(Variable("x"));
    w.push_back(Operator(")"));
    w.push_back(Operator("+"));
    w.push_back(Num("5"));
    w.push_back(Operator("+"));
    w.push_back(Function("sin"));
    w.push_back(Operator("~"));
    w.push_back(SuperToken("exp(x)"));
    for (int i= 0; i < int(v.size()); i++){
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
    string s = "(((8)cos((6))))";
    string v = "(8)cos((6))";
    string u = del_exterior_parentheses(s);
    QVERIFY(v == u);
}

void testDerivative::test_add_multiplication()
{   string s = "(83)cos(6x)(3(x^2(ln(x))))";
    string v = "(83)*cos(6*x)(3*(x^2*(ln(x)))";
    string u = add_multiplication(s);
    QVERIFY(v == u);
}

void testDerivative::test_delete_layers_pare()
{
    string a_1 = "exp(((x^2))) + ((3+4))";
    string b_1 = "(((exp(((x^2))) + ((3+4)))))";
    string c_1 = "(1 + ((exp(((x^2))) + ((3+4)))))";
    string a_2 = delete_layers_pare(a_1);
    string b_2 = delete_layers_pare(b_1);
    string c_2 = delete_layers_pare(c_1);
    string a_3 = "exp(x^2) + (3+4)";
    string b_3 = "exp(x^2) + (3+4)";
    string c_3 = "1 + exp(x^2) + (3+4)";
    QVERIFY(a_2 == a_3);
    QVERIFY(b_2 == b_3);
    QVERIFY(c_2 == c_3);
}

