#ifndef CNN_HPP
#pragma once
#define CNN_HPP

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;


class CNN
{
public:
    CNN();
    int train();
    double validate();
    void info();
    MatrixXd zero_pad(MatrixXd image, int pad);
    vector
    bool test_zero_pad();

private:
    double conv_single_step(MatrixXd slice_prev, MatrixXd W, double b);
    int forward_prop();
    int backword_prop();
    double cross_entropy();

};

#endif // CNN_HPP
