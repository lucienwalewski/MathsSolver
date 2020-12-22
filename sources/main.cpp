#include <QApplication>
#include <QtTest>
#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
<<<<<<< HEAD
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
//#include "Derivatives/derivatives.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
=======
#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Derivatives/derivatives.hpp"
>>>>>>> main
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>

using namespace std;

int main(int argc, char *argv[]){
    QApplication  a(argc, argv);

     string f;
     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     f = upload_function();
     cout<< f;


    return a.exec();

<<<<<<< HEAD
=======
using namespace std;

int main(int argc, char *argv[])
{

    QApplication  a(argc, argv);


    w.show();
    return a.exec();

>>>>>>> main
}
