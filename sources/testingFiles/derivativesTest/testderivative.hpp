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
    void test_find_function();
    void test_simplify();
    void test_corresponding_pare();
    void test_del_useless_parentheses();
    void test_add_multiplication();
    void test_delete_layers_pare();

};

#endif // testDerivative_HPP
