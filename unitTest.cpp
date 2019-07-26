#include <iostream>
#include <cstdarg>
#include "headers/Polynomial.h"
#include <vector>
#include <string>
#include "headers/Solver.h" 


void testAll(Solver solver, Polynomial p, bool print, double mult, int cons) {

    std::cout << "--------------------------------------------------------------\n";
    std::cout << "---------------------------TESTING----------------------------\n";
    std::cout << "--------------------------------------------------------------\n";  
    solver.setPolynomial(&p);
    std::cout << "multiplicidade = " << mult << "\n";
    solver.printInfo();

    double x = 0;
 
    if(cons == 1)
        std::cout << "PARA Polynomial(n, ...):\n";
    if(cons == 2)
        std::cout << "PARA Polynomial({an,...,a0})\n";
        
    // x = solver.byBisection(print);
    // std::cout << "byBisection : root = "<< x << " -> P(root) = " << p[x] << "\n\n";

    // x = solver.byFalsePosition(print);
    // std::cout << "byFalsePosition : root = "<< x << " -> P(root) = " << p[x] << "\n\n";

    std::cout << "--------------------------------------------------------------\n";
    x = solver.byNewtonRaphson(print, mult);
    std::cout << "byNewton : root = "<< x << " -> P(root) = " << p[x] << "\n\n";

    std::cout << "--------------------------------------------------------------\n";
    x = solver.byNewtonForPoly(print, mult);
    std::cout << "byNewtonForPoly : root = "<< x << " -> P(root) = " << p[x] << "\n\n";
        
    std::cout << "--------------------------------------------------------------\n";
    x = solver.bySecant(print, mult);
    std::cout << "bySecant : root = "<< x << " -> P(root) = " << p[x] << "\n\n";

    // std::cout << "Polinômio p troca de sinal " << x << " vezes\n\n\n";
    std::vector<double> pRoots = p.positiveRoots();
    for(int i = 0; i < pRoots.size(); i++)
        std::cout << "podem haver " << pRoots[i] << " raízes positivas\n";
    
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "--------------------------ENDING_TEST-------------------------\n";
    std::cout << "--------------------------------------------------------------\n\n"; 
}


int main() {

    // construtor 1 de Polynomial:
    // Polynomial([int|double] grau, double An, double A(n-1), ..., double A1, double A0)
    Polynomial p = Polynomial(4, 1.,-5.,6.,4.,-8.);

    // construtor 2 de Polynomial:
    // Polynomial(std::vector<double> {An, A(n-1), ..., A1, A0})
    std::vector<double> coef = {1.,-5.,6.,4.,-8.};
    Polynomial q = Polynomial(coef);

    // p = q
    // p[double x] = f(x)
    // p(double x) = f'(x)

    p.printExpression();
    p.printDerivate();
    std::cout << "\n";

    std::vector<double> test = {-10.,-9.,-8.,-6.,-5.,-4.,-3.,-2.,-1.,0,
                                1.,2.,3.,4.,5.,6.,7.,8.,9.,10.};

    for(int i = 0; i < test.size(); i++) {
        std::cout << "P(" << test[i] << ") = " << p[test[i]] << "  |  ";
        std::cout << "P'(" << test[i] << ") = " << p(test[i]) << "\n";
    }
    // construtor 1 de Solver:
    // Solver(double a, double b, double precision, Polynomial* p)
    double a = 0.;
    double b = 9.;
    Solver solver1 = Solver(a, b, .0001, &p);
    
    // construtor 2 de Solver:
    // Solver(double a, double b, double precision, int iterMax, Polynomial* p)
    Solver solver2 = Solver(a, b, .0001, 10, &p);
    // solver2 = Solver(-9.,0.,.0001, 100, &p);

    // construtor 3 de Solver:
    // Solver(double a, double b, double precision)
    Solver solver3 = Solver(a, b, .0001);

    bool print = true;
    double mult = 3.;

    testAll(solver2, p, print, mult, 1);
    testAll(solver2, q, print, mult, 2);

    return 0;
}