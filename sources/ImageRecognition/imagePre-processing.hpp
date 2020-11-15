#ifndef IMAGEPREPROCESSING_HPP
#define IMAGEPREPROCESSING_HPP

#include<iostream>
#include<string>

#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;

Mat convert_toGray(Mat image);

Mat upload_img(string path);

#endif // IMAGEPREPROCESSING_HPP
