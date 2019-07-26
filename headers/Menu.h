#ifndef POLYNOMS_MENU_H
#define POLYNOMS_MENU_H

#include "Polynomial.h"
#include "Solver.h"
#include <iostream>
#include <vector>

class Menu {

public:
    void mestre();
    void g0(std::string metodo);
    void g1();
    void g2();
    void g25(std::vector <int> qtd);
    void g3();
    void g4();
    void g5();
    void g6();
    void g7();
    void g8();
    void g9();
};

#endif