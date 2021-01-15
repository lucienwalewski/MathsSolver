#ifndef IMAGEPREDICTION_HPP
#define IMAGEPREDICTION_HPP

#include<QString>
#include<QDir>

#include "Include_OpenCV.h"
#include "imagePreprocessing.hpp"

using namespace std;
using namespace cv;

string makePrediction(const char* pathname, const char* contoursFolder, bool devV);

string makePredictionQ(QString pathname);

string reformatString(string &prediction);


#endif // IMAGEPREDICTION_HPP
