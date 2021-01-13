#include <QProcess>
#include "MainWindow/mainwindow.h"
#include "ImageRecognition/imagePreprocessing.hpp"
#include "ImageRecognition/imagePrediction.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

     MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();

//     AbstractFunction f(simplify("x^5-14/3*x^4-46/3*x^3+357/3*x^2-634/3*x+280/3"));
//     cout<< f.display()<<"\n";
//     cout<<"-----------\n";
//     cout<< f.is_polynomial()<<"\n";
//     cout<< f.get_polynomial().get_string()<<"\n";

//     solveRational(f.get_polynomial());

//     cout<<"ddd";

     //display_prepocessing("C:\\Users\\Korisnik\\Desktop\\reference4.jpg");

     return a.exec();
//    string pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference3.jpg";
//    string predictedString = makePrediction(pathname);
//    cout << "The predicted string is: " << predictedString;
//    return 0;

}


// equations/destrucror AF/ pre processes for Determiante
