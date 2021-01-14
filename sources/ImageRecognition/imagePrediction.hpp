#ifndef IMAGEPREDICTION_HPP
#define IMAGEPREDICTION_HPP

#include "Include_OpenCV.h"

using namespace std;
using namespace cv;

string makePrediction(const char* pathname, const char* contoursFolder, bool devV);

string reformatString(string &prediction);


#endif // IMAGEPREDICTION_HPP
