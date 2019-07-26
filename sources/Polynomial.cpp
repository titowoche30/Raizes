#include "../headers/Polynomial.h"

#include <iostream>
#include <cstdarg>
#include <cmath>
#include <limits>
#include <vector>

// OK //
std::string signStr(double x) {
    if(x > 0) return " + ";
    if(x < 0) return " - ";
    if(x == 0) return " + ";
}

int signP(double x) {
    if(x > 0) return 1;
    if(x < 0) return -1;
    if(x == 0) return 0;
}

// OK //
Polynomial::Polynomial(double degree, ...) {

    this->degree = (int) degree;
    this->coeficients = new double[this->degree + 1];

    va_list args;
    va_start(args, degree);
    int count = 0;

    while(count <= this->degree) {
        this->coeficients[this->degree - count] = va_arg(args, double);
        count++;
    }
}

// OK //
Polynomial::Polynomial(std::vector<double> &coeficients) {
    
    this->degree = (int) coeficients.size() - 1;
    this->coeficients = new double[this->degree + 1];

    for(int i = 0; i<coeficients.size(); i++)
        this->coeficients[this->degree - i] = coeficients[i];

}

// OK //
void Polynomial::printExpression() {

    std::cout << "P(x) = ";

    for(int i = this->degree; i >= 0; i--) {
        if (i == 0)
            std::cout << signStr(this->coeficients[i]) << fabs(this->coeficients[i]);

        else {
            if (this->coeficients[i] == 0)
                continue;
            else {
                std::cout << signStr(this->coeficients[i]);

                if (this->coeficients[i] == -1 || this->coeficients[i] == 1)
                    std::cout << "x^" << i;

                else
                    std::cout << fabs(this->coeficients[i]) << "x^" << i;
            }
        }
    }
    std::cout << "\n";
}

// OK //
void Polynomial::printDerivate() {

    std::cout << "P'(x) = ";
    
        for(int i = this->degree; i > 0; i--) {
            if (i == 0)
                std::cout << signStr(this->coeficients[i]) << fabs(this->coeficients[i]);

            else {
                if (this->coeficients[i] == 0)
                    continue;
                else {
                    std::cout << signStr(this->coeficients[i]);
                    std::cout << i * fabs(this->coeficients[i]) << "x^" << i-1;
                }
            }
        }
        std::cout << "\n";

}

// OK //
double Polynomial::getDegree() {
    return this->degree;
}

// OK //
double Polynomial::getCoeficient(int i) {
    return this->coeficients[i];
}

// OK //
double Polynomial::operator[](double x) {

    if(x == std::numeric_limits<double>::quiet_NaN())
        return std::numeric_limits<double>::quiet_NaN();

    double b = this->coeficients[this->degree];

    for(int i = this->degree - 1; i >= 0; i--)
        b = this->coeficients[i] + b*x;

    return b;
}

// OK //
double Polynomial::operator()(double x) {

    if(x == std::numeric_limits<double>::quiet_NaN())
        return std::numeric_limits<double>::quiet_NaN();

    double a = this->degree * this->coeficients[this->degree];

    for(int i = this->degree-1; i > 0; i--)
        a = i * this->coeficients[i] + a*x;

    return a;
}


double Polynomial::radius1() {
    double j, h;
    j = this->degree * fabs(this->coeficients[0]/this->coeficients[1]);
    h = pow(fabs(this->coeficients[0]/this->coeficients[this->degree]), 1./this->degree);

    if(j<h)
       return j;
    else
       return h;
}


double Polynomial::radius2() {

    double value;
    double max = 0;

    for(int i = this->degree-1; i >= 0; i--) {
        value = fabs(this->coeficients[i]/this->coeficients[this->degree]);

        if(value > max)
            max = value; 
    }
    
    return ++max;
}

int Polynomial::signChange() {

    int count = 0;
    int sign = 0;
    int last = signP(this->coeficients[0]);

    for(int i = 1; i <= this->degree; i++) {
        sign = signP(this->coeficients[i]);
        if(sign == 0)
            continue;
        else
            if(sign != last) {
                last = sign;
                count++;
            }
    }
        
    return count;
}

std::vector<double> Polynomial::positiveRoots() {

    std::vector<double> p;
    int v = this->signChange(); 

    for(int i = 0; i <= v; i+=2)
        p.push_back(v-i);
    
    if(p.size() == 0)
        return {};
    else
        return p;
}