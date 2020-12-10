#ifndef testDerivative_HPP
#define testDerivative_HPP

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

class testDerivative : public QObject
{
    Q_OBJECT
public:
    testDerivative();
    ~testDerivative();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_tokenizer();
    void test_case2();

};

#endif // testDerivative_HPP
