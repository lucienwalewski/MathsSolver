#ifndef TESTNUMERICALSOLVER_HPP
#define TESTNUMERICALSOLVER_HPP

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

double f(double);
double df(double);

class testNumericalsolver : public QObject
{
    Q_OBJECT
public:
    testNumericalsolver();
    ~testNumericalsolver();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_derivation();
    void test_integration();
    void test_roots();
    void test_ODE_1st();
    void test_ODE_2nd();
    void test_ODE_3rd();

};

#endif // TESTNUMERICALSOLVER_HPP
