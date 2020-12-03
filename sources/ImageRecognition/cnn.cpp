//#pragma once
#include "cnn.hpp"
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;


MatrixXd zero_pad(MatrixXd image, int pad) {
    int p = image.rows(), q = image.cols();
    MatrixXd res = MatrixXd::Zero(p + 2 * pad, q + 2 * pad);
    res.block(pad, pad, p, q) = image;
    return res;
}

CNN::CNN() {

}

/* This function takes two 2d matrices of the same dimensions,
 * convolves them and adds a bias */
double CNN::conv_single_step(MatrixXd slice_prev, MatrixXd W, double b) {
    MatrixXd conv = slice_prev.cwiseProduct(W);
    double Z = conv.sum();
    Z += b;
    return Z;
}

/* This function pads an input image with zeros of size pad
 */
//MatrixXd CNN::zero_pad(MatrixXd image, int pad) {
//    int p = image.rows(), q = image.cols();
//    MatrixXd res = MatrixXd(p + pad, q + pad);
//    res.block(p, q, pad, pad) = image;
//    return res;
//}

bool CNN::test_zero_pad() {
    MatrixXd M;
    CNN c;
    M << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    M = zero_pad(M, 2);
    cout << M;
    return true;
}
