#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
//#include "Derivatives/derivatives.hpp"


#include<iostream>
#include<string>
//#include<opencv2/opencv.hpp>
//#include<tensorflow/c/c_api.h>



using namespace std;
//using namespace cv;

double f(double x){
    return pow(x,7);
}

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

//    string f;

//    cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
//    cin>>f;
//    cout<<"The function is: "<<f<<"\n";

//    cout<<"Hello the result is "<<derivative(f, 9.99)<<"\n";

//    cout<<"Newton"<<Newton(f,9.99,1e-6,100)<<"\n";

    cout<<"The area of f from -10 to 10 is " <<GaussLegendreQuadrature(f, -10, 10)<<"\n";

//    vector<double> l = GaussLegendreWeights(10).array;

//    for (std::vector<double>::iterator i=l.begin(); i!= l.end(); i++){
//        cout<<*i<<'\n';
//    }

//    vector<double> r = LegendreRoots(10);

//    for (std::vector<double>::iterator i=r.begin(); i!= r.end(); i++){
//        cout<<*i<<'\n';
//    }

//    cout<<"The roots are:"<<"\n";

//    list<double> roots = rootfinding(f);for (std::list<double>::iterator i=roots.begin(); i!= roots.end(); i++){cout<<*i<<"\n";};

    return a.exec();



//    printf("Hello from TensorFlow C library version %s\n", TF_Version());
//    return 0;

//    string path= "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year 2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference2.jpg";
//    display_prepocessing(path);

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

}
