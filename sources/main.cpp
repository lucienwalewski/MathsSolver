#include <QProcess>
#include <QDir>
#include "MainWindow/mainwindow.h"
#include "ImageRecognition/imagePreprocessing.hpp"
#include "ImageRecognition/imagePrediction.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

//     MainWindow w;
//     w.setWindowState(Qt::WindowMaximized);
//     w.setWindowTitle("MathsSolver");
//     w.show();

//     return a.exec();


    // String prediction demo

    QString pathname ; // path for the Image to be recognised
    pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year 2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference6.jpg";
    string predictedString = makePredictionQ(pathname);
    cout << "The predicted string is: " << predictedString << endl;
    return 0;
}
