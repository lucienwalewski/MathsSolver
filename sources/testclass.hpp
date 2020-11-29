#ifndef TESTCLASS_HPP
#define TESTCLASS_HPP

#include <QObject>
#include <QtTest>
#include <QCoreApplication>

class testClass : public QObject
{
    Q_OBJECT
public:
    testClass();
    ~testClass();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

//class testFunc : public QObject
//{
//    Q_OBJECT

//public:
//    testFunc();
//    ~testFunc();

//private slots:
//    void initTestCase();
//    void cleanupTestCase();
//    void test_case1();
//};

#endif // TESTCLASS_HPP
