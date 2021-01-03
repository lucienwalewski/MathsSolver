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
     vector<Token> t = simplify("4*x", 'x');
     AF ft = AF(t);
     if(ft.get_operation().get_type() == -1){
        cout<<"yes \n";
     }
     cout<< ft.get_derivative()<< "\n";
     cout<<"done \n";
     string s;
     cin >> s;
     vector<Token> v = simplify(s, 'x');
     AF f = AF(v);
     cout<<f.get_str_label()<<"\n";
     cout<< f.get_derivative()<< "\n";

     /*vector<Token> v = simplify("sin(x^2)", 'x');
     AF f = AF(v);
     cout<<f.get_str_label()<<"\n";
     cout<< f.get_derivative()<< "\n";

     vector<Token> v2 = simplify("exp(x^2)", 'x');
     AF f2 = AF(v2);
     cout<<f2.get_str_label()<<"\n";
     cout<< f2.get_derivative()<< "\n";

     vector<Token> v3 = simplify("ln(x^2)", 'x');
     AF f3 = AF(v3);
     cout<<f3.get_str_label()<<"\n";
     cout<< f3.get_derivative()<< "\n";

     vector<Token> v4 = simplify("log(x^2)", 'x');
     AF f4 = AF(v4);
     cout<<f4.get_str_label()<<"\n";
     cout<< f4.get_derivative()<< "\n";

     vector<Token> v5 = simplify("tan(x^2)", 'x');
     AF f5 = AF(v5);
     cout<<f5.get_str_label()<<"\n";
     cout<< f5.get_derivative()<< "\n";
     return a.exec();*/
}
