#include <iostream>
#include <fstream>
#include "bintree_eda.h"
#include <math.h>

using namespace std;

struct valores {
    bool esA;
    long nivel, minimo, maximo;
};

valores esAVL(bintree<long> const& a) {

    if (a.empty()) {
        return {true, 0, INT_MIN,INT_MAX };
    }
    else if (a.left().empty() && a.right().empty()) {
        return {true, 1, a.root(), a.root()};
    }
    else if (a.left().empty()) {
        valores dcha = esAVL(a.right());
        bool equib = a.root() < a.right().root() && (dcha.nivel > 1 ? false : true);
        return { equib, dcha.nivel + 1, min(a.root(), dcha.minimo), max(a.root(), dcha.maximo) };
    }
    else if (a.right().empty()) {
        valores izq = esAVL(a.left());
        bool equib = a.root() > a.left().root()  && (izq.nivel > 1 ? false : true);
        return { equib, izq.nivel + 1, min(a.root(), izq.minimo), max(a.root(), izq.maximo) };
    }
    else {
        valores izq = esAVL(a.left());
        valores dcha = esAVL(a.right());

        bool equib = izq.esA && dcha.esA && abs(izq.nivel - dcha.nivel) < 2 && izq.maximo < a.root() && dcha.minimo > a.root() && a.root() > a.left().root() && a.root() < a.right().root();

        return {equib, max(izq.nivel, dcha.nivel) +1, min(izq.minimo, dcha.minimo), max(izq.maximo, dcha.maximo)};
    }
}

void resuelveCaso() {
    
    bintree<long> arbol = leerArbol((long) - 1);
    bool es = esAVL(arbol).esA;

    if (es) cout << "SI" << endl;
    else cout << "NO" << endl;
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    unsigned int numCasos;
    std::cin >> numCasos;
    // Resolvemos
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }


#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}