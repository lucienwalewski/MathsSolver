#ifndef UTIL_HPP
#define UTIL_HPP

namespace fns {
    double relu(double x);
    double tan(double x);
    double sigmoid(double x);
    double relu_grad(double x);
    double tan_grad(double x);
    double sigmoid_grad(double x);
}


class util
{
public:
    util();
};

#endif // UTIL_HPP
