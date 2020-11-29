#include <QApplication>
#include <QtTest>

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

 //   QApplication a(argc, argv);

 //   string s;
 //   cin>>s;


//    QApplication  a(argc, argv);

//    string path= "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year 2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference2.jpg";

  
  
//    display_prepocessing(path);

//    return a.exec();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
