#include "imagePrediction.hpp"

#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<cstdio>
#include<cstdint>
#include<filesystem>

#include "Include_OpenCV.h"

using namespace std;
using namespace cv;

//const char* contoursFolder = "/Users/lucienwalewski/OCR/outputImages/";

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

string reformatString(string &prediction) {
    // Make x's lower case
    for (int i = 0; i < prediction.length(); i++) {
        if (prediction[i] == 'X') {
            prediction[i] = 'x';
        }
    }
    string res = "";
    // Add exponents
    for (int i = 0; i < prediction.length(); i++) {
        if (prediction[i] == 'x' && isdigit(prediction[i + 1])) {
            res.append("x");
            res.append("^");
            res += prediction[i + 1];
            i++;
        }
        else {
            res += prediction[i];
        }
    }
    return res;
}

/* Takes a string that is the location of the image
 * and returns a prediction
 */
string makePrediction(const char* inputpathname, const char* contoursFolder, bool devV) {
//    remove(contoursFolder);
    save_contours(inputpathname, contoursFolder);
    string cmd;
    char* cmdC;
    if (devV) {
        cmd = ". /Users/lucienwalewski/opt/anaconda3/bin/activate && conda activate /Users/lucienwalewski/opt/anaconda3/envs/OCR; cd /Users/lucienwalewski/OCR; python3 modelPredict.py; conda deactivate";
        cmdC = new char [cmd.length()+1];
        strcpy (cmdC, cmd.c_str());
    }
    else {
        cmd = ". ";
        cmd.append(CONDAPATH); cmd.append("/bin/activate && conda activate ");
        cmd.append(CONDAPATH); cmd.append("/envs/OCR;"); cmd.append("pwd;"); cmd.append("cd ImageRecognition; python3 modelPredict.py; conda deactivate");
//        string cmd = ". " + CONDAPATH + "/bin/activate && conda activate " + CONDAPATH + "/envs/OCR; cd /Users/lucienwalewski/OCR; python3 modelPredict.py; conda deactivate";
        cmdC = new char [cmd.length()+1];
        strcpy (cmdC, cmd.c_str());
    }
//    const char* cmd = ". /Users/lucienwalewski/opt/anaconda3/bin/activate && conda activate /Users/lucienwalewski/opt/anaconda3/envs/OCR; cd /Users/lucienwalewski/OCR; python3 modelPredict.py; conda deactivate";

    string outputString = exec(cmdC);
    cout << "The preformatted string is: " << outputString << endl;
    outputString = reformatString(outputString);
    return outputString;
}
