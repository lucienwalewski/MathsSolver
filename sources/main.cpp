#include "MainWindow/mainwindow.h"
#include "Derivatives/derivatives.hpp"
#include <QApplication>

#include<iostream>
#include<string>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
