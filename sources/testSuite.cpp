#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
//#include "tstFunc.cpp"
#include "testclass.hpp"

int main(int argc, char *argv[]) {
    int status = 0;
    {
//        testFunc ta;
//        status |= QTest::qExec(&ta, argc, argv);

        testClass ta;
        status |= QTest::qExec(&ta, argc, argv);
    }
    return status;
}

//class testMatrix : public QObject
//{
//    Q_OBJECT

//public:
//    testMatrix();
//    ~testMatrix();

//private slots:
//    void initTestCase();
//    void cleanupTestCase();
//    void test_case1();
//   void test_pad();

//};

//testMatrix::testMatrix()
//{

//}

//testMatrix::~testMatrix()
//{

//}

//void testMatrix::initTestCase()
//{

//}

//void testMatrix::cleanupTestCase()
//{

//}

//void testMatrix::test_case1()
//{
//    QVERIFY(true);
//}

//void testMatrix::test_pad()
//{
//    MatrixXd A(2, 2);
//    A << 1, 2,
//         3, 4;
//    A = zero_pad(A, 1);
//    MatrixXd B(4, 4);
//    B << 0, 0, 0, 0,
//         0, 1, 2, 0,
//         0, 3, 4, 0,
//         0, 0, 0, 0;
//    QVERIFY(A.isApprox(B));
//}

//QTEST_MAIN(testMatrix)

//#include "tst_testmatrix.moc"
