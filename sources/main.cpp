#include "mainwindow.h"
#include <QApplication>
#include "ImageRecognition/imagePre-processing.hpp"

#include<iostream>
#include<string>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string path = "C:\\Users\\Korisnik\\Desktop\\Ecole Polytechnique\\DSC_7797-18.jpg";  // testing path, you may change or delete this line

    Mat image = upload_img(path);
    image = convert_toGray(image);

    imshow("Test image", image);
    waitKey(0);

    return a.exec();
}
