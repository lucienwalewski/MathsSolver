#include <QApplication>
#include <QtTest>

#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"
#include "Derivatives/Operators.hpp"


#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

    /* MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();*/

     //display_prepocessing("C:\\Users\\Korisnik\\Desktop\\reference.jpg");

     //string s = "sqrt(x)";
     string s = "x^5-14/3*x^4-46/3*x^3+357/3*x^2-634/3*x+280/3";
     //string s = "(cos(x) + 8986)";
     //string s = "cos(6x+ 5)";
     //string s =  "(8986 + cos(x))";
     //string s = "-exp(x+5)-x";
     //string s = "exp(x)";
     //string s = "1/(2*sqrt(x))*(exp(x)+8*x^2)";
     //string s= "x/4";
    // string s = "(exp(x) + 8*x^2)*sqrt(x)";
     //string s = "(x+5)*(x^2-4+2x)*(x-6)";
     //string s = "(x+5)/(x^2-8x+9)";
     //string s = "(x+8)*(x^2-8x)";
     //string s ="exp(x^2)^(x^2-4)";
     //string s = "-1/(2*sqrt(x))*(exp(x)+8*x^2)";
     //cout<< s<< "\n";

     vector<Token> v = simplify(s, 'x');
     for (auto i : v)
         cout<< i.get_value()<<" "<<i.get_type()<< "\n";
     AbstractFunction f(v);
     cout<<f.get_str_label()<<"\n";
     cout<<f.display()<<"\n";
     cout<<f.get_value(1)<<"\n";
     cout<<f.get_derivative()<<"\n";



     /*string s5;
     cin >> s5;
     vector<Token> v5 = simplify(s5, 'x');
     AbstractFunction f5 = AbstractFunction(v5);
     cout<<f5.get_str_label()<<"\n";
     cout<< f5.get_derivative()<< "\n"*/;
     return a.exec();
}
