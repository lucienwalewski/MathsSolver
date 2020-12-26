#include "gaussin.hpp"
#include "matrix.hpp"

bool is_not_round(Matrix<double> Y) {
    for (int i = 0; i < Y.height(); i++) {
        double diff = abs(round(Y.get_element(i, 0)) - Y.get_element(i, 0));
        if (diff < pow(10, -7) && Y.get_element(i, 0) != Y.get_element(i, 0)) {
            return true;
        }
    }
    return false;
}
