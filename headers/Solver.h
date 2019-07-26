#ifndef POLYNOMS_SOLVER_H
#define POLYNOMS_SOLVER_H

#include "Polynomial.h"

class Solver {

public:
    explicit Solver(double a, double b, double precision, Polynomial* p);
    explicit Solver(double a, double b, double precision, int iterMax, Polynomial* p);
    explicit Solver(double a, double b, double precision);
    explicit Solver(double precision, int maxIter, Polynomial* p);
    void printInfo();
    void setPolynomial(Polynomial* p);
    void setA(double a);
    void setB(double b);
    double byBisection(bool print);
    double byFalsePosition(bool print);
    double byNewtonRaphson(bool print, double mult);
    double byNewtonForPoly(bool print, double mult);
    double bySecant(bool print, double mult);

private:
    double a;
    double b;
    double precision;
    int maxIter;
    Polynomial* p = nullptr;
};

#endif