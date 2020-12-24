#include <QApplication>
#include <QtTest>
//#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Derivatives/derivatives.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>
//#include<opencv2/opencv.hpp>



using namespace std;

int main(int argc, char *argv[])
{

    QApplication  a(argc, argv);
    vector<Token> vect = {Variable("x"),Operator("^"),Num("5"),Operator("+"),Num("3")};
    AF af = AF(vect);
    cout << af.display()<<'\n';
    cout << af.get_type();

    //w.show();
    return a.exec();

}
