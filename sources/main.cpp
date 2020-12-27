#include <QApplication>
#include <QtTest>
//#include "mainwindow.h"

#include "MainWindow/mainwindow.h"
#include "ImageRecognition/imagePreprocessing.hpp"
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

     /*string f;
     cout<<"Hello MathSolver!"<<" Enter the problem we are solving: ";
     f = upload_function();
     cout<< f;*/

     Matrix <Rational> A(3, 3), Y(3, 1);
         A.set_element(0, 0, Rational (2, 1));
         A.set_element(0, 1, Rational (5, 1));
         A.set_element(0, 2, Rational (2, 1));
         A.set_element(1, 0, Rational (3, 1));
         A.set_element(1, 1, Rational (-2, 1));
         A.set_element(1, 2, Rational (4, 1));
         A.set_element(2, 0, Rational (-6, 1));
         A.set_element(2, 1, Rational (1, 1));
         A.set_element(2, 2, Rational (-7, 1));
         Y.set_element(0, 0, Rational (-38, 1));
         Y.set_element(1, 0, Rational (17, 1));
         Y.set_element(2, 0, Rational (-12, 1));

         gaussian<Rational>(A, Y);

     //w.show();
     return a.exec();
}
