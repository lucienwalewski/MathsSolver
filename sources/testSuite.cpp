#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "testingFiles/sampleTestClass.hpp"

int main(int argc, char *argv[]) {
    int status = 0;
    {
        testClass ta;
        status |= QTest::qExec(&ta, argc, argv);
    }
    return status;
}

