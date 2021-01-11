#ifndef FFT_HPP
#define FFT_HPP

#include "Include_libraries.h"

extern void FFT(int *x,
    std::complex<double> *new_x,
    int N);

void FFT_rec(std::complex<double> *x, int N);

#endif // FFT_HPP
