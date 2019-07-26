#include "../headers/Solver.h"
#include "../headers/Polynomial.h"
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>
#include <sys/time.h>
#include <ctime>


double sign(double x) {
    if(x < 0) return -1.;
    if(x > 0) return 1.;
    if(x == 0) return 0.;
}

void printIter(int iter, double x, double f_x, double interval) {
    std::cout << "iteracao " << std::setw(2) << iter << " :  ";
    std::cout << std::setw(12) << x << "  |  " << std::setw(12) << f_x;
    std::cout << "  |  " << std::setw(12) << interval << "\n";
}

void printTime(struct timeval* init) {
    double _time;
    double s, ms;
    struct timeval end;

    gettimeofday(&end, NULL);

    s = end.tv_sec - init->tv_sec;
    ms = end.tv_usec - init->tv_usec;
    _time = s*1000 + ms/1000;

    std::cout << "\nAlgoritmo executado em " << _time << " s \n";
}

// OK //
Solver::Solver(double a, double b, double precision, Polynomial* p) {
    
        if(b < a) {
            int aux = a;
            a = b;
            b = aux;
        }
    
        this->a = a;
        this->b = b;
        this->precision = precision;
        this->maxIter = INT_MAX;
        this->p = p;
}

// OK //
Solver::Solver(double a, double b, double precision,int maxIter, Polynomial* p) {

    if(b < a) {
        int aux = a;
        a = b;
        b = aux;
    }

    this->a = a;
    this->b = b;
    this->precision = precision;
    this->maxIter = maxIter;
    this->p = p;
}

// OK //
Solver::Solver(double a, double b, double precision) {

    if(b < a) {
        int aux = a;
        a = b;
        b = aux;
    }

    this->a = a;
    this->b = b;
    this->precision = precision;
}

// OK //
Solver::Solver(double precision, int maxIter, Polynomial* p) {

    this->precision = precision;
    this->p = p;
    this->maxIter = maxIter;
    this->a = -this->p->radius2();
    this->b = -this->a;
    std::vector<double> pRoots = this->p->positiveRoots();
    

    if(!pRoots.empty())
        if(*std::min_element(pRoots.begin(), pRoots.end()) != 0)
            this->a = 0;
}

// OK //
void Solver::printInfo() {
    std::cout << "a = " << this->a << "\n";
    std::cout << "b = " << this->b << "\n";
    std::cout << "maxIter = " << this->maxIter << "\n";
    std::cout << "precision = " << this->precision << "\n";
    if(this->p != nullptr)
        this->p->printExpression();
    else
        std::cout << "P(x) não definido\n";
    std::cout << "\n\n";
}

// OK //
void Solver::setPolynomial(Polynomial* p) {
    this->p = p;
}

// OK //
void Solver::setA(double a) {
    this->a = a;
}

// OK //
void Solver::setB(double b) {
    this->b = b;
}

// OK //
double Solver::byBisection(bool print) {

    double a = this->a;
    double b = this->b;
    double f_a = this->p->operator[](a);
    double x, f_x;

    if(print) std::cout << "\t\t\t  BISSECCAO\n";
    if(print) std::cout << "\t\t     x\t\t  f(x)\t\t   b-a\n\n";

    if(b - a < this->precision) return (a + b)/2.;

    for(int k = 1; ;k++) {    
        x = (a + b) / 2.;
        f_x = this->p->operator[](x);

        if (sign(f_a) * sign(f_x) > 0) a = x;
        else b = x;

        if(print) printIter(k, x, f_x, b-a);

        if(b - a < this->precision)
            return (a + b)/2.;

    }
}

// OK //
double Solver::byFalsePosition(bool print) {
    double x, f_x;
    double a = this->a;
    double erro = 1;
    double b = this->b;
    double f_a = this->p->operator[](a);
    double f_b = this->p->operator[](b);
    f_x = 100;

    int k = 1;

    if(print) std::cout << "\t\t\t  FALSA POSICAO\n";
    if(print) std::cout << "\t\t     x\t\t  f(x)\t\t   b-a\n\n";

    if(b - a < this->precision) return (a + b)/2.;

    while ( this->precision < erro && this->precision < fabs(f_x) ) {

        x = (a*f_b - b*f_a) / (f_b - f_a);

        f_x = this->p->operator[](x);

        if (f_a * f_x < 0) {
            b = x;
            f_b = f_x;
        } else {
            a = x;
            f_a = f_x;
        }

        if(print) printIter(k, x, f_x, b-a);

        k++;
    }

    return x;
}

// OK //
double Solver::byNewtonRaphson(bool print, double mult) {

    double x0 = (this->a + this->b) / 2.;
    double x, f_x, _time;
    struct timeval init;

    gettimeofday(&init, NULL);
    
    if(print) std::cout << "\t\t\t  NEWTON-RAPHSON\n";
    if(print) std::cout << "INTERVALO = [" << this->a << ", " << this->b << "]\n";
    if(print) std::cout << "\t\t     x\t\t  f(x)\t\t   b-a\n\n";

    if(print) printIter(0, x0, this->p->operator[](x0), this->b - this->a);

    if(fabs(this->p->operator[](x0)) < this->precision) {
        printTime(&init);
        return x0;
    }

    for(int k = 1;k<this->maxIter ;k++) {
        x = x0 - mult * this->p->operator[](x0)/this->p->operator()(x0);
        f_x = this->p->operator[](x);
        
        if(print) printIter(k, x, f_x, b-a);

        if(fabs(f_x) < this->precision || fabs(x - x0) < this->precision) {
            printTime(&init);
            return x;
        }
        x0 = x;
    }
}

// OK //
double Solver::bySecant(bool print, double mult) {
    double x0 = this->a;
    double x1 = this->b;
    double f_x0 = this->p->operator[](x0);
    double f_x1 = this->p->operator[](x1);
    double x, f_x, _time;
    struct timeval init;

    gettimeofday(&init, NULL);

    if(print) std::cout << "\t\t\t  SECANTE\n";
    if(print) std::cout << "INTERVALO = [" << this->a << ", " << this->b << "]\n";
    if(print) std::cout << "\t\t     x\t\t  f(x)\t\t   b-a\n\n";

    if(print) printIter(0, x0, this->p->operator[](x0), this->b - this->a);

    if(fabs(f_x0) < this->precision) {
        printTime(&init);
        return x0;
    }

    if(fabs(f_x1) < this->precision || fabs(x1 - x0) < this->precision) {
        printTime(&init);
        return x1;
    }

    for(int k = 1;k<this->maxIter ;k++) {
        f_x0 = this->p->operator[](x0);
        f_x1 = this->p->operator[](x1);
        x = x1 - mult * (f_x1/(f_x1 - f_x0)) * (x1 - x0);
        f_x = this->p->operator[](x);

        if(print) printIter(k, x, f_x, this->b - this->a);

        if(fabs(f_x) < this->precision || fabs(x - x1) < this->precision) {
            printTime(&init);
            return x;
        }
        x0 = x1;
        x1 = x;
    }

        // if(this->p->operator[](this->a) * this->p->operator[](this->b) > 0){
        //     std::cout<<"Invervalo inválido\n";
        //     return 0;
        // }
        // double x0 = this->a; 
        // double x1 = this->b; 
        // double x2;

        // int maxIter = 12; 
        // int k=0; 
        // int k1=0;

        // if(fabs(this->p->operator[](x0) ) <= this->precision) return x0;
        // if(fabs(this->p->operator[](x1)) <= this->precision || fabs(x1-x0) <= this->precision) return x1;


        // while(k!=maxIter){
        //     std::cout.precision(4);
        //     x2 = x1 - mult * ((this->p->operator[](x1)/(this->p->operator[](x1) - this->p->operator[](x0))) * (x1-x0));
        //     std::cout<<"Iteração "<<k<<std::endl;
        //     std::cout<<"x"<<k1<<" = "<<x0<<" -- x"<<k1+1<<" = "<<x1<<"\nx"<<k1+2<<" = "<<x2;
        //     std::cout<<" -- f(x"<<k1+2<<") = "<<this->p->operator[](x2)<<std::endl<<"("<<"x"<<k1+2<<" - x"<<k1+1<<")"<<" = "<<fabs(x2-x1)<<"\n\n";

        //     if(fabs(this->p->operator[](x2)) <= this->precision || fabs(x2-x1) <= this->precision) return x2;

        //     x0 = x1;
        //     x1 = x2;
        //     k++; k1++;
        // }

    return std::numeric_limits<double>::quiet_NaN();
}

// OK //
double Solver::byNewtonForPoly(bool print, double mult) {

    double x = (this->a + this->b) / 2.;
    double dx = x;
    double b, c, f_x, _time;
    struct timeval init, end;

    gettimeofday(&init, NULL);

    if(print) std::cout << "\t\t\t  NEWTON-PARA-POLINÔMIOS\n";
    if(print) std::cout << "INTERVALO = [" << this->a << ", " << this->b << "]\n";
    if(print) std::cout << "\t\t     x\t\t  f(x)\t\t   b-a\n\n";

    if(print) printIter(0, x, this->p->operator[](x), this->b - this->a);

    if(fabs(this->p->operator[](x)) < this->precision) {
        printTime(&init);
        return x;
    }

    for(int k = 1; k < this->maxIter; k++) {
        b = this->p->getCoeficient(this->p->getDegree());
        c = b;

        for(int i = this->p->getDegree()-1; i > 0; i--) {
            b = this->p->getCoeficient(i) + b*x;
            c = b + c*x;
        }

        b = this->p->getCoeficient(0) + b*x;

        if(fabs(b) < this->precision) {
            printTime(&init);
            return x;
        }

        dx = b/c;
        x = x - mult * dx;
        f_x = this->p->operator[](x);

        if(fabs(dx) < this->precision) {
            printTime(&init);
            return x;
        }
        
        if(print) printIter(k, x, f_x, this->b - this->a);
    }
}