#include <QApplication>
#include <QtTest>

#include <QApplication>
#include <QPushButton>
//#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
//#include "Derivatives/derivatives.hpp"
#include "Derivatives/Operators.hpp"
//#include "NumericalSolver/num_derivation.hpp"
//#include "NumericalSolver/num_integration.hpp"
//#include "NumericalSolver/num_roots.hpp"
//#include "Equations/numbers.hpp"
//#include "Equations/polynomial.hpp"
//#include "Equations/matrix.hpp"
//#include "Equations/gaussin.hpp"
//#include "functionPreprocessing.hpp"

#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

//     MainWindow w;
//     w.setWindowState(Qt::WindowMaximized);
//     w.setWindowTitle("Maths Solver");
//     w.show();
     string s = "((5x+345))";
     cout << del_exterior_parentheses(s) << endl;

     string q = "ln(378x+4) + (8986 + cos(x))";
     vector<Token> w = simplify(q, 'x');
     for (int j=0; j < int(w.size()); j++){
        cout<< w[j].get_value() << ' '<< w[j].get_type() << "\n";
     }

     return a.exec();
}
