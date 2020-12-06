#include <QApplication>
#include <QtTest>

//#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "Derivatives/Tokenizer.hpp"
//#include "NumericalSolver/num_derivation.hpp"
//#include "NumericalSolver/num_integration.hpp"
//#include "Derivatives/derivatives.hpp"
#include "Equations/polynomial.hpp"


#include<iostream>
#include<string>
#include<math.h>
//#include<opencv2/opencv.hpp>



using namespace std;
//using namespace cv;

/*double F(double x){
    return sin(2*x-2.1)/(x*x+1);
}*/

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    //string f;

    //cout<<"Hello MathSolver!"<<" Enter the function we are solving: ";
    //cin>>f;
    //cout<<"The function is: "<<f<<"\n";

    //cout<<"Hello the result of the integral is "<<integral(F, 1.2, 1.6)<<"\n";
    //cout<<"Hello the result of the derivative is "<<derivative(F, 1)<<"\n";

    //string path= "C:\\Users\\Korisnik\\Desktop\\Ecole Polytechnique\\CSE201 - Final project\\MathsSolver\\sources\\ImageRecognition\\Images\\reference2.jpg";
    //display_prepocessing(path);

    long long f[5] = {0, 3, -1, 0, 4};
    long long h[5] = {-2, 3, 1, 5, 0};
    long long ans = linear_res(6, 4, f, h, 998244353);
    printf("%lld\n",ans);

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

//    MainWindow w;
//    w.show();
    return a.exec();

}
