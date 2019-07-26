#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#elif __unix__
#define CLEAR_SCREEN "clear"
#endif

#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <vector>
#include "headers/Solver.h"
#include "headers/Menu.h"
#include "headers/Polynomial.h"

using namespace std;

int main() {

    system(CLEAR_SCREEN);
    cout<<"\nPrimeiro Trabalho de Métodos Numéricos I - Raízes de Equações\n\n";
    cout<<"--------------------Equipe:Hexaedro Convexo--------------------\n\n";

    Menu menu = Menu();
    menu.mestre();
}