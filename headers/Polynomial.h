#ifndef POLYNOMS_POLYNOMIAL_H
#define POLYNOMS_POLYNOMIAL_H

#include <vector>

class Polynomial {

public:
    explicit Polynomial(double degree, ...);
    explicit Polynomial(std::vector<double> &coeficients);
    void printExpression();
    void printDerivate();
    double getDegree();
    double getCoeficient(int i);
    double operator[](double x);
    double operator()(double x);
    double radius1();
    double radius2();
    std::vector<double> positiveRoots();

private:
    int degree;
    double* coeficients;
    int signChange();
};

#endif //POLYNOMS_POLYNOMIAL_H
