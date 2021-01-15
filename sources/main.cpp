#include <QProcess>
#include <QDir>
#include "MainWindow/mainwindow.h"
//#include "ImageRecognition/imagePreprocessing.hpp"
//#include "ImageRecognition/imagePrediction.hpp"
#include "Derivatives/Operators.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
  
    QApplication  a(argc, argv);

     MainWindow w;
     w.setWindowState(Qt::WindowMaximized);
     w.setWindowTitle("MathsSolver");
     w.show();
     string q = "cos(exp(x))+c";
     string z = "()";
     cout << is_valid(q) << endl;
     cout << valid_parentheses(q) << endl;
     cout << missing_parentheses(z) << endl;
     cout << one_variable(q) << endl;
     cout << is_valid(q) << endl;
     return a.exec();

    // String prediction demo

//    QString pathname ; // path for the Image to be recognised
//    pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year 2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference6.jpg";
//    string predictedString = makePredictionQ(pathname);
//    cout << "The predicted string is: " << predictedString << endl;
//    return 0;

//    MainWindow w;
//    w.setWindowState(Qt::WindowMaximized);
//    w.setWindowTitle("MathsSolver");
//    w.show();

//    return a.exec();

}
//system/integrals
