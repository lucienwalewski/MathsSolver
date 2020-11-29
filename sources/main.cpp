#include <QApplication>

#include "MainWindow/mainwindow.h"
//#include "Derivatives/derivatives.hpp"
#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"

#include<iostream>
#include<string>
//#include<opencv2/opencv.hpp>


using namespace std;
//using namespace cv;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    string s;
    cin>>s;


    return a.exec();

//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
