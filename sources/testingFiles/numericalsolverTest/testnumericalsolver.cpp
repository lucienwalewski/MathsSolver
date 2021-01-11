#include "testnumericalsolver.hpp"
#include <QtTest>
#include <QCoreApplication>
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_ODE.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "NumericalSolver/num_derivation.cpp"
#include "NumericalSolver/num_integration.cpp"
#include "NumericalSolver/num_ODE.cpp"
#include "NumericalSolver/num_roots.cpp"

double f1(double x){
    return x*x-1;
}

double f2(double x){
    return x*sin(x*x)+1;
}

double f3(double x){
    return exp(sin(3*x+2)-3*pow(cos(x),3)+1);
}

double f4(double x){
    return exp(pow(2,x))+3*cos(x*x+10);
}

double f5(double x){
    return -x*log(x) + x + 1;
}

double f6(double x){
    return -x*x*x*log(x) + x*x + 1;
}

double f7(double x){
    return -x*log(x) + 0.5 +3*pow(cos(x),2);
}

double g1(double x,double y){
    return (x-3)*(x-1);
}

double g1_solution(double x){
    return pow(x,3)/3-2*x*x+3*x;
}

double g2(double x,double y){
    return y + x;
}

double g2_solution(double x){
    return -x-1+exp(x);
}

double g3(double x,double y){
    return 1/(2*y);
}

double g3_solution(double x){
    return pow(x+1,0.5);
}

double g4(double x,double y,double dy){
    return -3*y;
}

double g4_solution(double x){
    return sin(pow(3,0.5)*x);
}

double g5(double x,double y,double dy){
    return (2*x*x+1)*exp(x*x)+x;
}

double g5_solution(double x){
    return 0.5*exp(x*x)+x*x*x/6+x+0.5;
}

double g6(double x,double y,double dy){
    return -dy;
}

double g6_solution(double x){
    return 1+3*exp(-x);
}

double g7(double x,double y,double dy, double d2y){
    return x*(x-10);
}

double g7_solution(double x){
    return pow(x,5)/60 - 5*pow(x,4)/12+2*x*x-3*x-5;
}

double g8(double x,double y,double dy, double d2y){
    return -3*dy+x;
}

double g8_solution(double x){
    return -1/9+cos(sqrt(3)*x)/9+sqrt(3)*sin(sqrt(3)*x)+x*x/6;
}

double g9(double x,double y,double dy, double d2y){
    return -3*dy+d2y;
}

double g9_solution(double x){
    return 1 + exp(x/2)*(cos(sqrt(11)*x/2)+sin(sqrt(11)*x/2));
}

testNumericalsolver::testNumericalsolver()
{

}

testNumericalsolver::~testNumericalsolver()
{

}

void testNumericalsolver::initTestCase()
{

}

void testNumericalsolver::cleanupTestCase()
{

}

void testNumericalsolver::test_derivation(){
    double df1_1 = derivative(f1,1);
    cout << "The value of the derivative is " << df1_1 << endl;
    cout << "You should have the following value " << 2 << endl;
    double df1_4 = derivative(f1,4);
    cout << "The value of the derivative is " << df1_4 << endl;
    cout << "You should have the following value " << 8 << endl;
    double df2_1 = derivative(f2,1);
    cout << "The value of the derivative is " << df2_1 << endl;
    cout << "You should have the following value " << 1.92207 << endl;
    double df2_10 = derivative(f2,-10);
    cout << "The value of the derivative is " << df2_10 << endl;
    cout << "You should have the following value " << 171.957 << endl;
    double df3_0 = derivative(f3,0);
    cout << "The value of the derivative is " << df3_0 << endl;
    cout << "You should have the following value " << -0.419451 << endl;
    double df3_10 = derivative(f3,10);
    cout << "The value of the derivative is " << df3_10 << endl;
    cout << "You should have the following value " << -26.2192 << endl;
    double df4_2 = derivative(f4,2);
    cout << "The value of the derivative is " << df4_2 << endl;
    cout << "You should have the following value " << 139.4909 << endl;
    double df4_0 = derivative(f4,0);
    cout << "The value of the derivative is " << df4_0 << endl;
    cout << "You should have the following value " << 1.88417 << endl;
    QVERIFY(abs(df1_1 - 2) < 0.00001
            and abs(df1_4 - 8) < 0.00001
            and abs(df2_1 - 1.92207) < 0.00001
            and abs(df2_10 - 171.9574) < 0.0001
            and abs(df3_0 - (-0.419451)) < 0.00001
            and abs(df3_10 - (-26.2192)) < 0.001
            and abs(df4_2 - 139.4909) < 0.001
            and abs(df4_0 - 1.88417) < 0.00001);
}

void testNumericalsolver::test_integration(){
    double i1 = integral(f1,0,1);
    cout << "The value of the integral is " << i1 << endl;
    cout << "You should have the following value " << -0.666666 << endl;
    double i2 = integral(f2,0,7);
    cout << "The value of the integral is " << i2 << endl;
    cout << "You should have the following value " << 7.3497 << endl;
    double i3 = integral(f3,0,20);
    cout << "The value of the integral is " << i3 << endl;
    cout << "You should have the following value " << 144.49825 << endl;
    double i4 = integral(f4,-4,2);
    cout << "The value of the integral is " << i4 << endl;
    cout << "You should have the following value " << 31.2718 << endl;
    QVERIFY(abs(i1 - (-0.66666)) < 0.00001
            and abs(i2 - 7.3497) < 0.00001
            and abs(i3 - 144.49825) < 0.00001
            and abs(i4 - 31.2718) < 0.0001);
}

void testNumericalsolver::test_roots(){
    bool b = true;
    list<double> roots_1 = rootfinding(f1);
    vector<double> roots1;
    roots1.push_back(-1);
    roots1.push_back(1);
    int j1 = 0;
    cout << "The values of the roots are {";
    for (std::list<double>::iterator i=roots_1.begin(); i!= roots_1.end(); i++){
        cout<<*i<<", ";
        if (abs(*i-roots1[j1]) > 0.0001){
            b = false;
        }
        j1++;
    }
    cout << "}"<< endl;
    cout << "You should have the following values {-1, 1}."<< endl;

    list<double> roots_5 = rootfinding(f5);
    vector<double> roots5;
    roots5.push_back(3.59112);
    int j2 = 0;
    cout << "The values of the roots are {";
    for (std::list<double>::iterator i=roots_5.begin(); i!= roots_5.end(); i++){
        cout<<*i;
        if (abs(*i-roots5[j2]) > 0.0001){
            b = false;
        }
        j2++;
    }
    cout << "}"<< endl;
    cout << "You should have the following values {3.59112}."<< endl;

    list<double> roots_6 = rootfinding(f6);
    vector<double> roots6;
    roots6.push_back(1.9297);
    int j3 = 0;
    cout << "The values of the roots are {";
    for (std::list<double>::iterator i=roots_6.begin(); i!= roots_6.end(); i++){
        cout<<*i;
        if (abs(*i-roots6[j3]) > 0.0001){
            b = false;
        }
        j3++;
    }
    cout << "}"<< endl;
    cout << "You should have the following values {1.9297}."<< endl;

    list<double> roots_7 = rootfinding(f7);
    vector<double> roots7;
    roots7.push_back(1.452);
    roots7.push_back(2.373);
    roots7.push_back(3.093);
    int j4 = 0;
    cout << "The values of the roots are {";
    for (std::list<double>::iterator i=roots_7.begin(); i!= roots_7.end(); i++){
        cout<<*i<<", ";
        if (abs(*i-roots7[j4]) > 0.001){
            b = false;
        }
        j4++;
    }
    cout << "}"<< endl;
    cout << "You should have the following values {1.452, 2.373, 3.093}."<< endl;


    QVERIFY(b);
}

void testNumericalsolver::test_ODE_1st(){
    bool b = true;

    vector<double> values_1;
    for (int i = 1; i<11; i++){
        values_1.push_back(g1_solution(i));
    }
    int i1 = 0;
    for (std::vector<double>::iterator i=values_1.begin(); i!= values_1.end(); i++){
        double y = ODE_1st_order_solver(0,0,i1+1,g1);
        cout << "The value of the solution at x = "<< i1+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_1[i1] << endl;
        if (abs(y-values_1[i1]) > 0.5){
            b = false;
        }
        i1++;
    }

    vector<double> values_2;
    for (int i = 1; i<11; i++){
        values_2.push_back(g2_solution(i));
    }
    int i2 = 0;
    for (std::vector<double>::iterator i=values_2.begin(); i!= values_2.end(); i++){
        double y = ODE_1st_order_solver(0,0,i2+1,g2);
        cout << "The value of the solution at x = "<< i2+1 << " is " << y << endl;
        cout << "You should have the following value " << values_2[i2] << endl;
        if (abs(values_2[i2]/y -1) > 0.1){
            b = false;
        }
        i2++;
    }

    vector<double> values_3;
    for (int i = 1; i<11; i++){
        values_3.push_back(g3_solution(i));
    }
    int i3 = 0;
    for (std::vector<double>::iterator i=values_3.begin(); i!= values_3.end(); i++){
        double y = ODE_1st_order_solver(0,1,i3+1,g3);
        cout << "The value of the solution at x = "<< i3+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_3[i3] << endl;
        if (abs(values_3[i3]/y -1) > 0.01){
            b = false;
        }
        i3++;
    }

    QVERIFY(b);
}

void testNumericalsolver::test_ODE_2nd(){
    bool b = true;

    vector<double> values_1;
    for (int i = 1; i<11; i++){
        values_1.push_back(g4_solution(i));
    }
    int i1 = 0;
    for (std::vector<double>::iterator i=values_1.begin(); i!= values_1.end(); i++){
        double y = ODE_2nd_order_solver(0,sqrt(3),0,i1+1,g4);
        cout << "The value of the solution at x = "<< i1+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_1[i1] << endl;
        if (abs(values_1[i1]/y - 1) > 0.1){
            b = true;
        }
        i1++;
    }

    vector<double> values_2;
    for (int i = 1; i<11; i++){
        values_2.push_back(g5_solution(i));
    }
    int i2 = 0;
    for (std::vector<double>::iterator i=values_2.begin(); i!= values_2.end(); i++){
        double y = ODE_2nd_order_solver(0,1,1,i2+1,g5);
        cout << "The value of the solution at x = "<< i2+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_2[i2] << endl;
        if (abs(values_2[i2]/y - 1) > 0.1){
            b = false;
        }
        i2++;
    }

    vector<double> values_3;
    for (int i = 1; i<11; i++){
        values_3.push_back(g6_solution(i));
    }
    int i3 = 0;
    for (std::vector<double>::iterator i=values_3.begin(); i!= values_3.end(); i++){
        double y = ODE_2nd_order_solver(0,-3,4,i3+1,g6);
        cout << "The value of the solution at x = "<< i3+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_3[i3] << endl;
        if (abs(values_3[i3]/y - 1) > 0.1){
            b = false;
        }
        i3++;
    }
    QVERIFY(b);
}

void testNumericalsolver::test_ODE_3rd(){
    bool b = true;

    vector<double> values_1;
    for (int i = 1; i<11; i++){
        values_1.push_back(g7_solution(i));
    }
    int i1 = 0;
    for (std::vector<double>::iterator i=values_1.begin(); i!= values_1.end(); i++){
        double y = ODE_3rd_order_solver(0,4,-3,-5,i1+1,g7);
        cout << "The value of the solution at x = "<< i1+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_1[i1] << endl;
        if (abs(values_1[i1]/y - 1) > 0.1){
            b = false;
        }
        i1++;
    }

    vector<double> values_2;
    for (int i = 1; i<11; i++){
        values_2.push_back(g8_solution(i));
    }
    int i2 = 0;
    for (std::vector<double>::iterator i=values_2.begin(); i!= values_2.end(); i++){
        double y = ODE_3rd_order_solver(0,0,3,0,i2+1,g8);
        cout << "The value of the solution at x = "<< i2+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_2[i2] << endl;
        if (abs(values_2[i2]/y - 1) > 0.1 and abs(values_2[i2]) + abs(y) > 0.1){
            b = false;
        }
        i2++;
    }

    vector<double> values_3;
    for (int i = 1; i<8; i++){
        values_3.push_back(g9_solution(i));
    }
    int i3 = 0;
    for (std::vector<double>::iterator i=values_3.begin(); i!= values_3.end(); i++){
        double y = ODE_3rd_order_solver(0,(2*sqrt(11)-10)/4,(sqrt(11)+1)/2,2,i3+1,g9);
        cout << "The value of the solution at x = "<< i3+1 <<" is " << y << endl;
        cout << "You should have the following value " << values_3[i3] << endl;
        if (abs(values_3[i3]/y - 1) > 0.15){
            b = false;
        }
        i3++;
    }

    QVERIFY(b);
}
