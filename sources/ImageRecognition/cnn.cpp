#pragma once
#include "cnn.hpp"
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

/* This function takes two 2d matrices of the same dimensions,
 * convolves them and adds a bias */
double CNN::conv_single_step(MatrixXd slice_prev, MatrixXd W, double b) {
    MatrixXd conv = slice_prev.cwiseProduct(W);
    double Z = conv.sum();
    Z += b;
    return Z;
}

MatrixXd CNN::zero_pad(MatrixXd image, int pad) {
    return image;
}
