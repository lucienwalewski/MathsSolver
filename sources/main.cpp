#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
//#include "NumericalSolver/num_derivation.hpp"
//#include "Derivatives/derivatives.hpp"


#include<iostream>
#include<string>
//#include<opencv2/opencv.hpp>
//#include<tensorflow/c/c_api.h>



using namespace std;
//using namespace cv;

/*double f(double x){
    return 2*x*x*x;
}*/

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    string f;

    cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
    cin>>f;
    cout<<"The function is: "<<f<<"\n";

    return a.exec();

//    cout<<"Hello the result is "<<derivative(f, 1);

//    printf("Hello from TensorFlow C library version %s\n", TF_Version());
//    return 0;

//    string path= "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year 2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference2.jpg";
//    display_prepocessing(path);

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

}
