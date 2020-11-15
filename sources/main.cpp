#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Mat image = imread("/Users/lucienwalewski/Downloads/DSC_7821-28.jpg", IMREAD_COLOR);

    imshow("Test image", image);

    waitKey(0);

    return a.exec();
}
