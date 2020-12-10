#ifndef TESTSOLVE_HPP
#define TESTSOLVE_HPP

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

#include "Derivatives/derivatives.hpp"

class testDerivatives : public QObject
{
    Q_OBJECT
public:
    testDerivatives();
    ~testDerivatives();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_cos();
    void test_sin();
    void test_constant();
    void test_exponential();
    void test_exponential_e();
    void test_logarithmic();
    void test_logarithmic_ln();
    void test_polynomial();





};

#endif // TESTSOLVE_HPP
