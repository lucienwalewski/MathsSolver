#include <QApplication>
#include <QtTest>

#include <QApplication>
#include <QPushButton>
#include "MainWindow/mainwindow.h"

//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"
#include "Derivatives/Operators.hpp"
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

     MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();

     /*//string s = "1/x";
     //string s = "x^5-14/3*x^4-46/3*x^3+357/3*x^2-634/3*x+280/3";
     //string s = "(cos(x) + 8986)";//works
     //string s = "cos(6*x+ 5)";
     // but with  string s =  (8986 + cos(x)); it doesn't not even without the parentheses
     // or s = exp(x)-ln(x); we get nothing
     //cout<< s<< "\n";
     vector<Token> v = simplify(s, 'x');
     for (auto i : v){
         cout<< i.get_value()<<" "<<i.get_type()<< "\n";
     }
     cout<< "-----------\n";

     AF f(v);
     cout<<f.get_str_label()<<"\n";
     cout<< f.get_value(-5.0)<< "\n";
     cout<<f.is_polynomial()<< "\n";
     cout<<f.get_integral_value(0.1, 2)<<"\n";

     vector<double> sol = f.get_roots();
     for (auto i : sol)
         cout<< i << " ";*/

     return a.exec();
}
