#ifndef GAUSSIN_HPP
#define GAUSSIN_HPP

#include "matrix.hpp"

void gaussian(Matrix A, Matrix Y);

void display_system(Matrix A, Matrix Y);

bool is_not_round(Matrix Y);

#endif // GAUSSIN_HPP
