#ifndef IMAGEPREPROCESSING_HPP
#define IMAGEPREPROCESSING_HPP

#include<iostream>
#include<string>

#include "Include_OpenCV.h"

using namespace std;
using namespace cv;
//using namespace Eigen;

/// Uploads image and returns it
Mat upload_img(string path);

/// Binarises the image
Mat binarisation(Mat image);

/// Removes noise from the image
Mat noise_removal(Mat image);

/// Crops the image
Mat crop(Mat image);

///
void extract_contours(Mat image);

/// Applies all the preprocessing techniques
void display_prepocessing(string path);

void save_contours(string path, string outputPath);


#endif // IMAGEPREPROCESSING_HPP
