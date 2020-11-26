#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <ImageRecognition/imagePreprocessing.cpp>

class testMatrix : public QObject
{
    Q_OBJECT

public:
    testMatrix();
    ~testMatrix();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testMatrix::testMatrix()
{

}

testMatrix::~testMatrix()
{

}

void testMatrix::initTestCase()
{

}

void testMatrix::cleanupTestCase()
{

}

void testMatrix::test_case1()
{

}

QTEST_MAIN(testMatrix)

#include "tst_testmatrix.moc"
