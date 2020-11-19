#include "util.hpp"

#include <cmath>

using namespace std;


namespace fns {
double relu(double x) {
    if (x > 0) {
        return x;
    }
    return (double) 0;
}

double tan(double x) {
    return tanh(x);
}

double sigmoid(double x) {
    // Verify that this solution is stable enough
    return (1.0/(1.0 + exp(x)));
}

double relu_grad(double x) {
    if (x > 0) {
        return 1;
    }
    return (double) 0;
}

double sigmoid_grad(double x) {
    return sigmoid(x) * (1 - sigmoid(x));
}


}

util::util()
{

}
