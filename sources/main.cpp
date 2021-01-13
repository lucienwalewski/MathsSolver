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

     //display_prepocessing("C:\\Users\\Korisnik\\Desktop\\reference4.jpg");

     return a.exec();
//    string pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference3.jpg";
//    string predictedString = makePrediction(pathname);
//    cout << "The predicted string is: " << predictedString;
//    return 0;

}
