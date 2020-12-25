#include <QApplication>
#include <QtTest>
//#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
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
#include<string>
#include<math.h>
#include<vector>

using namespace std;

int main(int argc, char *argv[]){
    QApplication  a(argc, argv);

     /*string f;
     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     f = upload_function();
     cout<< f;*/

     Rational c[6] = {Rational(-280, 1), Rational(634, 1), Rational(-357, 1), Rational(46, 1), Rational(14, 1), Rational(-3, 1)};
     Rational c1[3] = {Rational(-1, 1), Rational(1, 1), Rational(-1, 1)};
     PolynomialRational P(c, 5);
     PolynomialRational P1(c1, 2);

     //divisionR(P, P1, true);

    //P.print();
     //cout<<P.get_value(Rational(4, 1))<<"\n";

     solutionPolynomial res = solveRational(P);

     if (res.roots.empty())
     {
         std::cout<<"No Solution"<<std::endl;
         return 0;
     }

     printf("The roots are\n");
     for (auto i : res.roots)
     {
         std::cout<<i<<std::endl;
     }

     printf("The complex roots are\n");
     for (auto i : res.complex){
         cout<<i<<"\n";
     }

     string s = "";
     for (auto i : res.factors){
         s += i.first;
         if(i.second > 1){
             s += "^"+ to_string(i.second);
         }
     }

     cout<<s<<"\n";

     //w.show();
     return a.exec();
}
