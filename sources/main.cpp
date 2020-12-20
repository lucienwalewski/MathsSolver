#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
//#include "Derivatives/derivatives.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

     string f;
     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     f = upload_function();



//    MainWindow w;
//    w.show();*/
    return a.exec();

}
