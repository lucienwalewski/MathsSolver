#include<iostream>
#include<string>

#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat upload_img(string path){
    Mat image = imread(path, IMREAD_COLOR);

    if(!image.data){
        cout<<"Image path is not valid\n";
    }

    return image;
}

Mat convert_toGray(Mat image){
    Mat gray_image;

    if(!image.data){
        cout<<"Image path is not valid\n";
    }

    cvtColor(image, gray_image, COLOR_BGR2GRAY);

    return gray_image;
}
