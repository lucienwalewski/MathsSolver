#include "sampleTestClass.hpp"
#include <QtTest>
#include <QCoreApplication>

// add necessary includes here


testClass::testClass()
{

}

testClass::~testClass()
{

}

void testClass::initTestCase()
{

}

void testClass::cleanupTestCase()
{

}

void testClass::test_case1()
{
    QVERIFY(true);
}

void testClass::test_case2()
{
    int a = 1, b = 1;
    QVERIFY(a == b);
}
