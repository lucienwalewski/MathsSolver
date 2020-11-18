#include "mainwindow.h"
#include <QApplication>
#include "ImageRecognition/imagePre-processing.hpp"
#include "Equations/matrix.hpp"

#include<iostream>
#include<string>

using namespace std;

int main(int argc, char *argv[])
{
    printf("bbxx");

    QCoreApplication a(argc, argv);

    Matrix<int> I(3, 3);
    I.set_element(0, 0, 1);
    I.set_element(1, 1, 1);
    I.set_element(2, 2, 1);

    Matrix<int> O(3, 3);

    Matrix<int> I1(3, 3);
    I1.set_element(0, 0, -1);
    I1.set_element(1, 1, -1);
    I1.set_element(2, 2, -1);

    Matrix<int> A(2, 3);
    A.set_element(0, 0, 1);
    A.set_element(0, 1, 2);
    A.set_element(0, 2, 3);
    A.set_element(1, 0, 4);
    A.set_element(1, 1, 5);
    A.set_element(1, 2, 6);

    Matrix<int> B(3, 2);
    B.set_element(0, 0, 7);
    B.set_element(0, 1, -2);
    B.set_element(1, 0, -3);
    B.set_element(1, 1, -5);
    B.set_element(2, 0, 4);
    B.set_element(2, 1, 1);

    Matrix<int> AB(2, 2);
    AB.set_element(0, 0, 13);
    AB.set_element(0, 1, -9);
    AB.set_element(1, 0, 37);
    AB.set_element(1, 1, -27);

    Matrix<int> BA(3, 3);
    BA.set_element(0, 0, -1);
    BA.set_element(0, 1, 4);
    BA.set_element(0, 2, 9);
    BA.set_element(1, 0, -23);
    BA.set_element(1, 1, -31);
    BA.set_element(1, 2, -39);
    BA.set_element(2, 0, 8);
    BA.set_element(2, 1, 13);
    BA.set_element(2, 2, 18);

    //Tests for the equality
    if(A == A) {
        std::cout << "Test_eq1 passed." << std::endl;
    } else {
        std::cout << "Test_eq1 failed." << std::endl;
    }
    if(A == B) {
        std::cout << "Test_eq2 failed." << std::endl;
    } else {
        std::cout << "Test_eq2 passed." << std::endl;
    }

    //Tests for column ansd row

    //Test for the multiplications
    if(AB == A*B) {
        std::cout << "Test_mult1 passed." << std::endl;
    } else {
        std::cout << "Test_mult1 failed." << std::endl;
    }
    if(BA == B*A) {
        std::cout << "Test_mult2 passed." << std::endl;
    } else {
        std::cout << "Test_mult2 failed." << std::endl;
    }
    if (A*I == I*A) {
        std::cout << "Test_mult3 passed." << std::endl;
    } else {
        std::cout << "Test_mult3 failed." << std::endl;
    }
    if (A*O == O*A) {
        std::cout << "Test_mult4 passed." << std::endl;
    } else {
        std::cout << "Test_mult4 failed." << std::endl;
    }
    if (I*(-1) == I1) {
        std::cout << "Test_mult5 passed." << std::endl;
    } else {
        std::cout << "Test_mult5 failed." << std::endl;
    }

    //Tests for the sums
    if (A + B == B + A) {
        std::cout << "Test_sum1 passed." << std::endl;
    } else {
        std::cout << "Test_sum1 failed." << std::endl;
    }
    if (A + O == A) {
        std::cout << "Test_sum2 passed." << std::endl;
    } else {
        std::cout << "Test_sum2 failed." << std::endl;
    }

    //Tests for rows and columns

    //Tests for crop

    //Tests for the determinant

    return a.exec();
}
