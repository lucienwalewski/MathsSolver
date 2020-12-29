#include <QApplication>
#include <QtTest>

#include <QApplication>
#include <QPushButton>
#include "MainWindow/mainwindow.h"
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
#include "functionPreprocessing.hpp"


#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

     /*MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();*/

     string s = "3*x^5+4*x^4+x^3-7*x^2-4*x-2";
     vector<Token> v = simplify(s, 'x');
     /*for (auto i : v)
         cout<< i.get_value() << " " <<i.get_type() << '\n';
     cout<< "--------\n";*/
     AF f(v);
     cout<<f.get_str_label()<<"\n";
     //VarAF e = VarAF(Variable("x"));
     //cout<< e.get_value(1);
     cout<<"Value: "<< f.get_value(2)<<"\n";


     return a.exec();
}
