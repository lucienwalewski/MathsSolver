#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
//#include "Derivatives/derivatives.hpp"
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
     long long h[5] = {1, -1, -2, 1, 1};
     int d = 4;
     Polynomial p(h, d);



//    MainWindow w;
//    w.show();*/
    return a.exec();

}
