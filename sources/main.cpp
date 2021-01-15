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


     return a.exec();
}
