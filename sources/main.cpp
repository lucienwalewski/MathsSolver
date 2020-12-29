#include <QApplication>
#include <QtTest>

#include <QPushButton>

#include "Derivatives/Operators.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "Derivatives/derivatives.hpp"


#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

     MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();

     cout<<"x^2 \n";
     vector<Token> v = simplify("x^2", 'x');
     cout<<"here \n";
     AF func = AF(v);
     cout<<"created af \n";
     AF derivation = derive(func);
     //cout<<"passed derivation";
     //cout<<derivation.get_str_label();



     return a.exec();
}
