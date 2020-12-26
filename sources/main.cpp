#include <QApplication>
#include <QtTest>
//#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Equations/numbers.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"
#include "Equations/step.hpp"
#include "functionPreprocessing.hpp"

#include<iostream>

using namespace std;

int main(int argc, char *argv[]){

  QApplication  a(argc, argv);

     string f;
     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     f = upload_function();
     cout<< f;

     //w.show();
     return a.exec();
}
