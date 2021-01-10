#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "NumericalSolver/num_ODE.hpp"

//#include "Derivatives/derivatives.hpp"
//#include "Equations/polynomial.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>
//#include<opencv2/opencv.hpp>



using namespace std;
//using namespace cv;

/*double F(double x){
    return sin(2*x-2.1)/(x*x+1);
}*/

double f(double x, double y){
    return 1/y;
}

double g(double x,double y,double dy){
    return -3*y;
}

double h(double x,double y,double dy, double d2y){
    return x;
}

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    for (int i=1; i<5; i=i+0.5){
        cout<<ODE_1st_order_solver(0,1,i,f)<<'\n';
    }

//    cout<<ODE_2nd_order_solver(0, 1, 0, 1, g)<<'\n';

//    cout<<ODE_3rd_order_solver(0, 0, 0, 1, 1, h);

//    string f;

//    cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
//    cin>>f;
//    cout<<"The function is: "<<f<<"\n";

//    cout<<"Hello the result is "<<derivative(f, 0)<<"\n";

//    cout<<"Newton"<<Newton(f,9.99,1e-6,100)<<"\n";


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

//    cout<<"Hello the result of the integral is "<<integral(f, 0, 1)<<"\n";
    //cout<<"Hello the result of the derivative is "<<derivative(F, 1)<<"\n";


    //string path= "C:\\Users\\Korisnik\\Desktop\\Ecole Polytechnique\\CSE201 - Final project\\MathsSolver\\sources\\ImageRecognition\\Images\\reference.jpg";
    //display_prepocessing(path);


//    MainWindow w;
//    w.show();
    return a.exec();

}
