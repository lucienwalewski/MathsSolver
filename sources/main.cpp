#include <QApplication>
#include <QtTest>

#include <QApplication>
#include <QPushButton>
//#include "MainWindow/mainwindow.h"

//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"
#include "Derivatives/Operators.hpp"


#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

     /*MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();*/

     string s;
     cin >> s;
     vector<Token> v = simplify(s, 'x');
     AbstractFunction f = AbstractFunction(v);
     cout<<f.get_str_label()<<"\n";
     cout<<f.display()<<"\n";
     cout<< f.get_derivative()<< "\n";

     string s1;
     cin >> s1;
     vector<Token> v1 = simplify(s1, 'x');
     AbstractFunction f1 = AbstractFunction(v1);
     cout<<f1.get_str_label()<<"\n";
     cout<< f1.get_derivative()<< "\n";

     string s2;
     cin >> s2;
     vector<Token> v2 = simplify(s2, 'x');
     AbstractFunction f2 = AbstractFunction(v2);
     cout<<f2.get_str_label()<<"\n";
     cout<< f2.get_derivative()<< "\n";

     string s3;
     cin >> s3;
     vector<Token> v3 = simplify(s3, 'x');
     AbstractFunction f3 = AbstractFunction(v3);
     cout<<f3.get_str_label()<<"\n";
     cout<< f3.get_derivative()<< "\n";

     string s4;
     cin >> s4;
     vector<Token> v4 = simplify(s4, 'x');
     AbstractFunction f4 = AbstractFunction(v4);
     cout<<f4.get_str_label()<<"\n";
     cout<< f4.get_derivative()<< "\n";

     string s5;
     cin >> s5;
     vector<Token> v5 = simplify(s5, 'x');
     AbstractFunction f5 = AbstractFunction(v5);
     cout<<f5.get_str_label()<<"\n";
     cout<< f5.get_derivative()<< "\n";
     return a.exec();
}
