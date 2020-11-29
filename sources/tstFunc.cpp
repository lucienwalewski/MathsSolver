#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "ImageRecognition/imagePreprocessing.hpp"
#include "ImageRecognition/cnn.hpp"

class testFunc : public QObject
{
    Q_OBJECT

public:
    testFunc();
    ~testFunc();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

testFunc::testFunc()
{

}

testFunc::~testFunc()
{

}

void testFunc::initTestCase()
{

}


void testFunc::cleanupTestCase()
{

}

void testFunc::test_case1()
{
    QVERIFY(true);
}


//QTEST_MAIN(testFunc)

//#include "tst_testmatrix_copy.moc"
