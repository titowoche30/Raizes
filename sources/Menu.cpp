#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#elif __unix__
#define CLEAR_SCREEN "clear"
#endif

#include "../headers/Solver.h"
#include "../headers/Polynomial.h"
#include "../headers/Menu.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

vector<Polynomial> polis;

void Menu::mestre(){
    int g;
    cout<<"(1) - Digitar polinômios\n(2) - Exibir polinômios digitados\n(3) - Calcular raíz pelo método de Newton para polinômios\n"
            "(4) - Calcular raíz pelo método de Newton para multiplicidade\n";
    cout<<"(5) - Calcular raíz pelo método da Secante para multiplicidade\n(6) - Calcular raíz pelos 3 métodos\n";
    cout<<"(7) - Calcular raíz de todos os polinômios para os 3 métodos\n(8) - Usar polinômio exemplo\n";
    cout <<"(9) - Remover Polinômios\n(0) - Sair\n\n";
    cin>>g;

    system(CLEAR_SCREEN);

    switch(g) {
        case(1): g1(); break;
        case(2): g2(); break;
        case(3): g3(); break;
        case(4): g4(); break;
        case(5): g5(); break;
        case(6): g6(); break;
        case(7): g7(); break;
        case(8): g8(); break;
        case(9): g9(); break;
        case(0): exit(0);
        default: cout<<"Dígito inválido\n\n";
    }
    mestre();     
}

//MÉTODOS NUMÉRICOS
void Menu::g0(string metodo) {
    system(CLEAR_SCREEN);
    int s = int(polis.size());
    int aux, k, aux2, aux3, aux4, maxIter;
    double epsilon, a, b, mult;
    int j = 0;
    string intervalo;
    vector<int> qtd;

    if(s==0) cout<<"Nenhum polinômio foi digitado\n";
    else{
        g2();
        cout << "(1) - Encontrar as raízes para todos os polinômios\n" <<
             "(2) - Encontrar as raízes para polinômios específicos\n(0) - Voltar\n";
        cin >> aux;

        if (aux <= 0 || aux > 2) {
            system(CLEAR_SCREEN);
            mestre();
        } else if (aux == 1) {
            system(CLEAR_SCREEN);
            g2();
            cout << "(1) - Digitar os intervalos de cada polinômio\n" <<
                 "(2) - Usar intervalos automáticos\n(0) - Voltar\n";
            cin >> aux3;

            if (aux3 == 0) {
                system(CLEAR_SCREEN);
                g0(metodo);
            } else if (aux3 > 2)
                mestre();

            if (aux3 == 1) {
                system(CLEAR_SCREEN);
                g2();
                cout << "Digite o máximo de iterações " << "\n";
                cin >> maxIter;
                cout << "\n";

                while (s != 0) {
                    cout << "Digite a e b do intervalo [a,b] do polinômio " << j + 1 << "\n";
                    cin >> a;
                    cin >> b;

                    cout << "Digite a precisão para o polinômio " << j + 1 << "\n";
                    cin >> epsilon;

                    cout << "Digite a multiplicidade para o polinômio " << "\n";
                    cin >> mult;
                    cout << "\n\n\n";

                    Solver solver = Solver(a, b, epsilon, maxIter, &polis[j]);

                    if (metodo == "poly") {
                        solver.byNewtonForPoly(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "newton") {
                        solver.byNewtonRaphson(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "secante") {
                        solver.bySecant(true, mult);
                        cout << "\n\n";
                    }
                    j++;
                    s--;
                }
            } else if (aux3 == 2) {
                system(CLEAR_SCREEN);
                g2();
                cout << "Digite o máximo de iterações " << "\n";
                cin >> maxIter;
                cout << "\n";

                while (s != 0) {
                    cout << "Digite a precisão para o polinômio " << j + 1 << "\n";
                    cin >> epsilon;

                    cout << "Digite a multiplicidade para o polinômio " << j + 1 << "\n";
                    cin >> mult;
                    cout << "\n\n\n";

                    Solver solver = Solver(epsilon, maxIter, &polis[j]);

                    if (metodo == "poly") {
                        solver.byNewtonForPoly(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "newton") {
                        solver.byNewtonRaphson(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "secante") {
                        solver.bySecant(true, mult);
                        cout << "\n\n";
                    }
                    j++;
                    s--;
                }
            }
        } else if (aux == 2) {
            system(CLEAR_SCREEN);
            g2();
            if (s != 1) {
                cout << "Quantos polinômios deseja utilizar? " << "\n";
                cin >> k;
                if (k <= 0) return mestre();

                cout << "Quais polinômios deseja utilizar?" << "\n";
                for (int i = 0; i < k; i++) {
                    cin >> aux2;
                    qtd.push_back(aux2);
                }
            } else {
                k = 1;
                qtd.push_back(1);
            }
            system(CLEAR_SCREEN);
            g25(qtd);
            cout << "(1) - Digitar os intervalos de cada polinômio\n" <<
                 "(2) - Usar intervalos automáticos\n(0) - Voltar\n";
            cin >> aux4;

            if (aux4 == 0) {
                system(CLEAR_SCREEN);
                g0(metodo);
            } else if (aux4 > 2)
                mestre();

            if (aux4 == 1) {
                system(CLEAR_SCREEN);
                g25(qtd);
                cout << "Digite o máximo de iterações " << "\n";
                cin >> maxIter;
                cout << "\n";
                for (int l = 0; l < k; l++) {
                    cout << "Digite a e b do intervalo [a,b] do polinômio " << qtd[l] << "\n";
                    cin >> a;
                    cin >> b;

                    cout << "Digite a precisão para o polinômio " << qtd[l] << "\n";
                    cin >> epsilon;

                    cout << "Digite a multiplicidade para o polinômio " << qtd[l] << "\n";
                    cin >> mult;
                    cout << "\n\n\n";

                    Solver solver = Solver(a, b, epsilon, maxIter, &polis[qtd[l] - 1]);
                    if (metodo == "poly") {
                        solver.byNewtonForPoly(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "newton") {
                        solver.byNewtonRaphson(true, mult);
                        cout << "\n\n";
                    } else if (metodo == "secante") {
                        solver.bySecant(true, mult);
                        cout << "\n\n";
                    }
                }
            } else if (aux4 == 2) {
                system(CLEAR_SCREEN);
                g25(qtd);
                cout << "Digite o máximo de iterações " << "\n";
                cin >> maxIter;
                cout << "\n";
                for (int l = 0; l < k; l++) {
                    cout << "Digite a precisão para o polinômio " << qtd[l] << "\n";
                    cin >> epsilon;

                    cout << "Digite a multiplicidade para o polinômio " << qtd[l] << "\n";
                    cin >> mult;
                    cout << "\n\n\n";

                    Solver solver = Solver(epsilon, maxIter, &polis[qtd[l] - 1]);
                    if (metodo == "poly") {
                        solver.byNewtonForPoly(true, mult);
                        cout << "\n\n";

                    } else if (metodo == "newton") {
                        solver.byNewtonRaphson(true, mult);
                        cout << "\n\n";

                    } else if (metodo == "secante") {
                        solver.bySecant(true, mult);
                        cout << "\n\n";
                    }
                }
            }
        }
    }
}

//RECEBE POLINÔMIOS
void Menu::g1(){
    int p; int g;
    double aux,aux2;
    vector <double> coefs,graus;
    int si = int(polis.size());
    system(CLEAR_SCREEN);

    cout<<"Quantos polinômios deseja inserir?\n";
    cin>>p;
    if(p<=0) {
        system(CLEAR_SCREEN);
        cout<<"Dígito inválido\n\n";
    }else {
        for (int i = 0; i < p; i++) {
            cout << "Digite o grau do polinômio " << si + 1 << "\n";
            cin >> aux;
            graus.push_back(aux);
            si++;
        }

        system(CLEAR_SCREEN);

        for (int j = 0; j < p; j++) {
            cout << "Digite os " << graus[j] + 1 << " coeficientes do polinômio " << j + 1 <<
                 " de grau " << graus[j] << "\n";
            while (graus[j] >= 0) {
                cin >> aux2;
                coefs.push_back(aux2);
                graus[j]--;
            }
            Polynomial polio = Polynomial(coefs);
            polis.push_back(polio);
            coefs.clear();
        }

        system(CLEAR_SCREEN);
        g2();
    }

}

//EXIBE TODOS OS POLINÔMIOS
void Menu::g2(){

    int p = int(polis.size());
    if(p==0) {
        cout<<"Nenhum polinômio foi digitado\n\n";
    }else{
        cout<<"\n\nPolinômios digitados:\n";
        for (int k = 0; k < p; k++) {
            cout<<k+1<<" - ";
            polis[k].printExpression();
            }
        }
    cout<<"\n\n";

}

//EXIBE POLINÔMIOS ESPECÍFICOS
void Menu::g25(vector <int> qtd){
    int p = int(qtd.size());
    if(p==0) {
        cout<<"Nenhum polinômio foi digitado\n\n";
    }else {
        cout << "\n\nPolinômios a serem usados:\n";
        for (int k = 0; k < p; k++) {
            cout << qtd[k] << " - ";
            polis[(qtd[k] - 1)].printExpression();
        }
        cout << "\n\n";
    }
}

//NEWTON POLI
void Menu::g3() {
    g0("poly");
}

//NEWTON-RAPHSON
void Menu::g4() {
    g0("newton");
}

//SECANTE
void Menu::g5() {
    g0("secante");
}

//RAÍZ DE 1 OU MAIS POLINÔMIOS PELOS 3 MÉTODOS COM INTERVALO AUTOMÁTICO
void Menu::g6(){
    system(CLEAR_SCREEN);
    int s = int(polis.size()); int aux,k,aux2,aux3,aux4,maxIter; double epsilon,a,b,mult;
    int j = 0; string intervalo;
    vector <int> qtd,mults;

    if(s==0) cout<<"Nenhum polinômio foi digitado\n\n";
    else {
        g2();
        cout << "(1) - Encontrar as raízes de todos os polinômios\n" <<
             "(2) - Encontrar as raízes de polinômios específicos\n(0) - Voltar\n";
        cin >> aux;

        if (aux <= 0 || aux > 2) {
            system(CLEAR_SCREEN);
        } else {
            if (aux == 1) {
                g7();
            }
            else {
                if (aux == 2) {
                    system(CLEAR_SCREEN);
                    g2();
                    if (s != 1) {
                        cout << "Quantos polinômios deseja utilizar? " << "\n";
                        cin >> k;
                        if (k <= 0) {
                            system(CLEAR_SCREEN);
                            cout << "Dígito inválido";
                        } else {
                            cout << "Quais polinômios deseja utilizar?" << "\n";
                            for (int i = 0; i < k; i++) {
                                cin >> aux2;
                                qtd.push_back(aux2);
                            }
                            system(CLEAR_SCREEN);
                            g25(qtd);
                            cout << "Digite o máximo de iterações para os " << k << " polinômios\n";
                            cin >> maxIter;
                            cout << "\n";
                            cout << "Digite a precisão para os " << k << " polinômios\n";
                            cin >> epsilon;
                            cout << "\n";
                            cout << "Digite as multiplicidades para os " << k << " polinômios respectivamente\n";
                            for (int i = 0; i < k; i++) {
                                cin >> aux;
                                mults.push_back(aux);
                            }

                            cout << "\n\n";
                            while (k != 0) {
                                cout<<"Polinômio "<<qtd[j]<<" - ";
                                polis[qtd[j]-1].printExpression(); cout<<" \n\n";
                                Solver solver = Solver(epsilon,maxIter,&polis[qtd[j]-1]);
                                solver.byNewtonForPoly(true, mults[j]);
                                cout << "\n\n";
                                solver.byNewtonRaphson(true, mults[j]);
                                cout << "\n\n";
                                solver.bySecant(true, mults[j]);
                                cout << "\n\n";

                                j++; k--;
                            }
                        }
                    } else {
                        k = 1;
                        qtd.push_back(1);
                        system(CLEAR_SCREEN);
                        g25(qtd);
                        cout << "Digite o máximo de iterações para o polinômio\n";
                        cin >> maxIter;
                        cout << "\n";
                        cout << "Digite a precisão para o polinômio\n";
                        cin >> epsilon;
                        cout << "\n";
                        cout << "Digite a multiplicidade para o polinômio\n";
                        cin>>aux3; cout << "\n\n";
                        polis[0].printExpression(); cout<<"\n\n";
                        Solver solver = Solver(epsilon,maxIter,&polis[0]);
                        solver.byNewtonForPoly(true,aux3);
                        cout << "\n\n";
                        solver.byNewtonRaphson(true, aux3);
                        cout << "\n\n";
                        solver.bySecant(true, aux3);
                        cout << "\n\n";

                    }
                }
            }
        }
    }
    //system(CLEAR_SCREEN);
   // g25(qtd);
}

//RAÍZ DE TODOS POLINÔMIOS PELOS 3 MÉTODOS COM INTERVALO AUTOMÁTICO
void Menu::g7() {
    int maxIter,aux;
    int j = 0;
    double epsilon,mult;
    int s = (polis.size());
    vector <int> mults,qtd;
    system(CLEAR_SCREEN);
    if(s==0) cout<<"Nenhum polinômio foi digitado\n";
    else if(s==1){
        aux = 1;
        qtd.push_back(1);
        system(CLEAR_SCREEN);
        g25(qtd);
        cout << "Digite o máximo de iterações para o polinômio\n";
        cin >> maxIter;cout << "\n";

        cout << "Digite a precisão para o polinômio\n";
        cin >> epsilon;cout << "\n";

        cout << "Digite a multiplicidade para o polinômio\n";
        cin>>mult; cout << "\n\n";

        polis[0].printExpression(); cout<<"\n\n";

        Solver solver = Solver(epsilon,maxIter,&polis[0]);
        solver.byNewtonForPoly(true,mult);
        cout << "\n\n";
        solver.byNewtonRaphson(true, mult);
        cout << "\n\n";
        solver.bySecant(true, mult);
        cout << "\n\n";

    }else {
        g2();
        cout << "Digite o máximo de iterações \n";
        cin >> maxIter;
        cout << "\n";
        cout << "Digite a precisão \n";
        cin >> epsilon;
        cout << "\n";
        cout << "Digite as multiplicidades para os " << s << " polinômios respectivamente\n";
        for (int i = 0; i < s; i++) {
            cin >> aux;
            mults.push_back(aux);
        }

        cout << "\n\n";
        while (s != 0) {
            cout << "Polinômio " << j + 1 << " - ";
            polis[j].printExpression();
            cout << " \n\n";
            Solver solver = Solver(epsilon, maxIter, &polis[j]);
            solver.byNewtonForPoly(true, mults[j]);
            cout << "\n\n";
            solver.byNewtonRaphson(true, mults[j]);
            cout << "\n\n";
            solver.bySecant(true, mults[j]);
            cout << "\n\n";

            j++;
            s--;
        }

    }

}

//POLINÔMIO EXEMPLO: + x^4 - 5x^3 + 6x^2 + 4x - 8
void Menu::g8(){
    system(CLEAR_SCREEN);
    vector <double> coefs = {1.,-5.,6.,4.,-8.};
    Polynomial p = Polynomial(coefs);
    cout<<"Polinômio exemplo = "; p.printExpression();
    cout<<"\n";
    polis.push_back(p);
}

//REMOVE POLINÔMIO
void Menu::g9() {
    system(CLEAR_SCREEN);
    g2();
    int aux,k;
    int s = int(polis.size());

    if(s==0)
        cout<<"Nenhum polinômio foi digitado\n";
    else if(s==1)
        polis.erase(polis.begin());
    else{
        cout << "Quantos polinômios deseja remover? " << "\n";
        cin >> k;
        if (k <= 0) cout<<"Dígito inválido";

        cout << "Quais polinômios deseja remover?" << "\n";
        for (int i = 0; i < k; i++) {
            cin >> aux;
            polis.erase(polis.begin()+(aux-1));
        }
    }

    system(CLEAR_SCREEN);
    g2();

}

