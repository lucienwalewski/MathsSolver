#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "testingFiles/sampleTestClass/sampleTestClass.hpp"

#include "testingFiles/derivativesTest/testderivative.hpp"
#include "testingFiles/numericalsolverTest/testnumericalsolver.hpp"


int main(int argc, char *argv[]) {
    int status = 0;
    {
        //testClass ta;
        //status |= QTest::qExec(&ta, argc, argv);

        //testDerivative td;
        //status |= QTest::qExec(&td, argc, argv);
        testNumericalsolver tn;
        status |= QTest::qExec(&tn, argc, argv);
    }
    return status;

}

