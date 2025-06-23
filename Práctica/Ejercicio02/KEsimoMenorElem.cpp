//NOMBRE y APELLIDOS


#include <iostream>
#include <fstream>
#include "TreeSet_AVL.h"

using namespace std;

bool resuelveCaso() {
    Set<int> arbol;

    int nElem, valor;
    cin >> nElem;

    if (nElem == 0)
        return false;

    for (int i = 0; i < nElem; i++) {
        cin >> valor;
        arbol.insert(valor);
    }

    int nPreguntas = 0;
    cin >> nPreguntas;
    int preguntas = 0;
    int sol = 0;

    for (int i = 0; i < nPreguntas; i++) {
        cin >> preguntas;

        try {
            sol = arbol.kesimo(preguntas);
            cout << sol << endl;
        }
        catch (exception e) {
            cout << "??" << endl;
        }
        
    }

    cout << "---" << endl;

    return true;
}

int main() {
    // Para la entrada por fichero.
// ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}