#ifndef IMAGEPREPROCESSING_HPP
#define IMAGEPREPROCESSING_HPP

#include<iostream>
#include<string>
#include<QString>

#include "Include_OpenCV.h"

using namespace std;
using namespace cv;

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

void save_contoursQS(QString path, string outputPath);


#endif // IMAGEPREPROCESSING_HPP
