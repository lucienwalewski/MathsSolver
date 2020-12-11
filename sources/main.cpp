#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
//#include "Derivatives/derivatives.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>
//#include<opencv2/opencv.hpp>



using namespace std;
using namespace cv;

/*double F(double x){
    return sin(2*x-2.1)/(x*x+1);
}*/

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

     string f;
     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     f = upload_function();


//    MainWindow w;
//    w.show();*/
    return a.exec();

}
