#include <QApplication>
#include <QtTest>

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
    AbstractFunction Fun = AbstractFunction({Variable("x")});
    cout << Fun.display()<<'\n';
    cout << "yes";
//    vector<Token> easy_example = {Variable("x"),Operator("+"),Num("5"),Operator("*"),Variable("x"),Operator("^"),Num("3")};
//    AbstractFunction Fun = AbstractFunction(easy_example);
//    cout << "bruh" << '\n';
//    cout << Fun.display()<<'\n';
//    MainWindow w;
//    w.show();*/
    return a.exec();
}
