#include <QApplication>
#include <QtTest>
#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Derivatives/derivatives.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>
//#include<opencv2/opencv.hpp>



using namespace std;

int main(int argc, char *argv[])
{

    QApplication  a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("Math Solver");
    AbstractFunction Fun = AbstractFunction({Variable("x")});
    cout << Fun.display()<<'\n';
    cout << "yes";
//    vector<Token> easy_example = {Variable("x"),Operator("+"),Num("5"),Operator("*"),Variable("x"),Operator("^"),Num("3")};
//    AbstractFunction Fun = AbstractFunction(easy_example);
//    cout << "bruh" << '\n';
//    cout << Fun.display()<<'\n';
//    MainWindow w;
//    w.show();*/

    Matrix A(3, 3), Y(3, 1);
    A.set_element(0, 0, 2);
    A.set_element(0, 1, 5);
    A.set_element(0, 2, 2);
    A.set_element(1, 0, 3);
    A.set_element(1, 1, -2);
    A.set_element(1, 2, 4);
    A.set_element(2, 0, -6);
    A.set_element(2, 1, 1);
    A.set_element(2, 2, -7);
    Y.set_element(0, 0, -38);
    Y.set_element(1, 0, 17);
    Y.set_element(2, 0, -12);

    gaussian(A, Y);

    w.show();
    return a.exec();

}
