#include "testSolve.hpp"
#include "Derivatives/derivatives.hpp"

testDerivatives::testDerivatives()
{

}

testDerivatives::~testDerivatives()
{

}

void testDerivatives::initTestCase()
{

}

void testDerivatives::cleanupTestCase()
{

}

void testDerivatives::test_cos()
{
    Token x = Token("x");
    CosFunction c = CosFunction(x);
    AbstractFunction abstr = c.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "-sin(x)");
}

void testDerivatives::test_sin()
{
    Token x = Token("x");
    SinFunction s = SinFunction(x);
    CosFunction abstr = s.solve<CosFunction>();

    QVERIFY(abstr.get_str_label() == "cos(x)");
}

void testDerivatives::test_constant()
{
    Token x = Token("4");
    ConstantFunction c = ConstantFunction(x);
    ConstantFunction abstr = c.solve<ConstantFunction>();

    QVERIFY(abstr.get_str_label() == "0");
}

void testDerivatives::test_exponential()
{
    Token x = Token("x");
    Token b = Token("5");
    ExponentialFunction e = ExponentialFunction(x, b);
    AbstractFunction abstr = e.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "5^x*ln(5)");
}

void testDerivatives::test_exponential_e()
{
    Token x = Token("x");
    Token b = Token("e");
    ExponentialFunction e = ExponentialFunction(x, b);
    AbstractFunction abstr = e.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "e^x");
}

void testDerivatives::test_polynomial()
{
    Token x = Token("x");
    Token ex = Token("5");
    PolynomialFunction p = PolynomialFunction(x, ex);
    AbstractFunction abstr = p.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "5*x^4");
}

void testDerivatives::test_logarithmic()
{
    Token x = Token("x");
    Token base = Token("10");
    LogarithmicFunction l = LogarithmicFunction(x, base);
    AbstractFunction abstr = l.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "1/(ln(10)*x)");
}

void testDerivatives::test_logarithmic_ln()
{
    Token x = Token("x");
    Token base = Token("e");
    LogarithmicFunction ln = LogarithmicFunction(x, base);
    AbstractFunction abstr = ln.solve<AbstractFunction>();

    QVERIFY(abstr.get_str_label() == "1/x");
}

void testDerivatives::test_addition(){
    Token x = Token("x");
    SinFunction s = SinFunction(x);
    Token base = Token("e");
    LogarithmicFunction ln = LogarithmicFunction(x, base);

    CosFunction abstr = s.solve<CosFunction>();
}
void testDerivatives::test_subtraction(){}
void testDerivatives::test_multiplication(){}
void testDerivatives::test_division(){}
void testDerivatives::test_composition(){}


