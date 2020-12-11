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
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"


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

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

     string f;

     cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
     cin>>f;
     cout<<"The function is: "<<f<<"\n";

//    cout<<"Hello the result is "<<derivative(f, 9.99)<<"\n";

//    cout<<"Newton"<<Newton(f,9.99,1e-6,100)<<"\n";

    //the main process for solving the problem


  //  cout<<"The function is: "<<f<<"\n";
//    string f;

//    cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
//    cin>>f;
//    cout<<"The function is: "<<f<<"\n";

//    cout<<"Hello the result is "<<derivative(f, 9.99)<<"\n";

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

    //cout<<"Hello the result of the integral is "<<integral(F, 1.2, 1.6)<<"\n";
    //cout<<"Hello the result of the derivative is "<<derivative(F, 1)<<"\n";


    //string path= "C:\\Users\\Korisnik\\Desktop\\Ecole Polytechnique\\CSE201 - Final project\\MathsSolver\\sources\\ImageRecognition\\Images\\reference.jpg";
    //display_prepocessing(path);

/*    vector<Token> v;
    v= simplify(f, 'x');

    long long c[4] = {-1,0,2,1};
    Polynomial b(c, 3);
    long long ce[2] = {1, 1};
    Polynomial d(ce, 1);
    Polynomial now = division(b, d);
    std::vector<std::string> ans_s = solve(b);

    if (ans_s.empty())
    {
        std::cout<<"No Solution"<<std::endl;
        return 0;
    }

    printf("The roots are\n");
    for (auto i : ans_s)
    {
        std::cout<<i<<std::endl;
    }
    for(int i=0; i<(int)v.size(); i++)
        cout<<v[i].get_value()<<" "<<"\n";*/
//    MainWindow w;
//    w.show();
    return a.exec();

}
