#include "mainwindow.h"
#include <QApplication>

#include<iostream>
#include<string>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "Hello world";

    return a.exec();
}
