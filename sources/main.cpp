#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
//#include "Derivatives/derivatives.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<opencv2/opencv.hpp>



using namespace std;
using namespace cv;

/*double F(double x){
    return sin(2*x-2.1)/(x*x+1);
}*/

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    string f;

    //cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
    //cin>>f;
    //cout<<"The function is: "<<f<<"\n";

    //cout<<"Hello the result of the integral is "<<integral(F, 1.2, 1.6)<<"\n";
    //cout<<"Hello the result of the derivative is "<<derivative(F, 1)<<"\n";

    string path= "C:\\Users\\Korisnik\\Desktop\\Ecole Polytechnique\\CSE201 - Final project\\MathsSolver\\sources\\ImageRecognition\\Images\\reference2.jpg";
    display_prepocessing(path);

//    MainWindow w;
//    w.show();
    return a.exec();

}
