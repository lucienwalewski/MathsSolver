#include <QApplication>
#include <QtTest>

#include <QApplication>
#include <QPushButton>
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
#include "functionPreprocessing.hpp"

#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

//     MainWindow w;
//     w.setWindowState(Qt::WindowMaximized);
//     w.setWindowTitle("Maths Solver");
//     w.show();

     cout<<"x^2 +5/2x - 5 -9/4 \n";
     vector<Token> v = simplify("x^2 +5/2x - 5 -9/4 ", 'x');
     for (auto i : v){
         cout<<i.get_value() << ' '<< i.get_type() << "\n";
     }

     return a.exec();
}
