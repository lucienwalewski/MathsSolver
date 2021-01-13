#include "imagePrediction.hpp"
#include "imagePreprocessing.hpp"

#include<iostream>
#include<string>
#include<vector>

#include "Include_OpenCV.h"

using namespace std;
using namespace cv;

const string contoursFolder = "/Users/lucienwalewski/OCR/outputImages/";

/* Takes a shell comand and returns the outputted
 * string
 */
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/* Takes a string that is the location of the image
 * and returns a prediction
 */
string makePrediction(string inputpathname) {
    save_contours(inputpathname, contoursFolder);
    const char* cmd = "conda activate OCR; cd /Users/lucienwalewski/OCR; python3 modelPredict.py; conda deactivate";
//    const char* cmd = ". /Users/lucienwalewski/opt/anaconda3/bin/activate && conda activate /Users/lucienwalewski/opt/anaconda3/envs/OCR; cd /Users/lucienwalewski/OCR; python3 modelPredict.py; conda deactivate";
    string outputString = exec(cmd);
    return outputString;
}
