#include <QProcess>
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


//     display_prepocessing("C:\\Users\\Korisnik\\Desktop\\reference4.jpg");

     return a.exec();
//    const char* pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference3.jpg";
//    const char* pathname = "/Users/lucienwalewski/OneDrive/Polytechnique/Work/Year2/CSE201/Project/MathsSolver/sources/ImageRecognition/Images/reference3.jpg";

//    //    const char* contoursFolder = "/ImageRecognition/extractedImages/";
//    bool developmentV = false;  // true when on dev version
//    const char* contoursFolderV = "/users/lucienwalewski/OCR/outputImages/";
//    const char* contoursFolder = "./ImageRecognition/extractedImages/";
//    string predictedString;
//    if (developmentV) {
//        predictedString = makePrediction(pathname, contoursFolderV, developmentV);
//    }
//    else {
//        predictedString = makePrediction(pathname, contoursFolder, developmentV);
//    }
//    cout << "The predicted string is: " << predictedString << endl;
//    cout << CONDAPATH;
//    return 0;

}
