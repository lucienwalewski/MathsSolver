#include "fft.hpp"
#include <complex>
#include <iostream>
#include <valarray>

const double PI = 3.141592653589793238460;

void FFT(int *x,
    std::complex<double> *new_x,
    int N) {
    for (int i = 0; i < N; i++) {
        new_x[i] = std::complex<double>(x[i], 0);
        new_x[i] *= 1;
    }
    FFT_rec(new_x,N);
}

void FFT_rec(std::complex<double> *x, int N) {
    if (N <= 1) {
        return;
    }
    std::complex<double> odd[N/2];
    std::complex<double> even[N/2];
    for (int i = 0; i < N/2; i++) {
        even[i] = x[i*2];
        odd[i] = x[i*2+1];
    }
    FFT_rec(even, N/2);
    FFT_rec(odd, N/2);
    for (int k = 0; k < N/2; k++) {
        std::complex<double> t = exp(std::complex<double>(0,-2*PI*k/N)) * odd[k];
        x[k] = even[k] + t;
        x[(N/2)+k] = even[k] - t;
    }
}
