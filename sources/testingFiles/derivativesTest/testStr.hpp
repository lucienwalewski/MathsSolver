#ifndef TESTSTR_HPP
#define TESTSTR_HPP



#include <QObject>
#include <QtTest>
#include <QCoreApplication>

#include "Derivatives/derivatives.hpp"

class testStr : public QObject
{
    Q_OBJECT
public:
    testStr();
    ~testStr();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_str1();


};

#endif // TESTSTR_HPP
