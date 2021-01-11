#include "MainWindow/mainwindow.h"
#include "ImageRecognition/imagePreprocessing.hpp"
#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
     QApplication  a(argc, argv);

//     MainWindow w;
//     w.setWindowState(Qt::WindowMaximized);
//     w.setWindowTitle("MathsSolver");
//     w.show();

     display_prepocessing("C:\\Users\\Korisnik\\Desktop\\reference.jpg");

     return a.exec();
}
