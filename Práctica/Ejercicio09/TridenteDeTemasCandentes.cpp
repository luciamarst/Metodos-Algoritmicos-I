#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "IndexPQ.h" // Incluye tu archivo de cola de prioridad personalizada
using namespace std;

struct Tendencia {
    string tema;
    int menciones;
    int antiguedad;
};

// Comparador personalizado para la cola de prioridad
struct Comparador {
    bool operator()(const Tendencia& a, const Tendencia& b) const {
        if (a.menciones == b.menciones) {
            return a.antiguedad < b.antiguedad; // Ordenar por antigüedad en orden ascendente
        }
        return a.menciones < b.menciones; // Ordenar por menciones en orden ascendente
    }
};

bool resuelveCaso() {
    int nOp = 0;
    cin >> nOp;

    if (!std::cin)
        return false;

    string op;
    unordered_map<string, Tendencia> posicion;
    vector<Tendencia> tendencias;
    IndexPQ<Tendencia, Comparador> podio(nOp); // Inicializa la cola de prioridad con el número máximo de operaciones
    string tema;
    int menciones;

    for (int i = 0; i < nOp; i++) {
        cin >> op;

        if (op == "C") {
            cin >> tema >> menciones;
            Tendencia t = {tema, menciones, i};
            posicion.insert({tema, i});
            podio.update(i, t);
        } else if (op == "E") {
            cin >> tema >> menciones;

            if (posicion.count(tema) != 0) {
                int index = posicion[tema];
                Tendencia t = podio.top(); // Obtener la tendencia desde la cola de prioridad
                podio.pop(index); // Eliminar la entrada antigua de la cola de prioridad

                t.menciones -= menciones;
                if (t.menciones == 0) {
                    posicion.erase(tema);
                } else {
                    podio.push(index, t); // Insertar la nueva entrada en la cola de prioridad
                }
            } else {
                exit(1);
            }
        } else if (op == "TC") {
            // Imprimir el podio (solo los tres primeros)
            vector<int> top3;
            while (!podio.empty() && top3.size() < 3) {
                top3.push_back(podio.top().elem);
                podio.pop(top3.back());
            }
            for (size_t j = 0; j < top3.size(); ++j) {
                cout << (j + 1) << " " << tendencias[top3[j]].tema << endl;
            }
            cout << "---" << endl;
            // Volver a insertar los elementos en la cola de prioridad
            for (int index : top3) {
                podio.push(index, tendencias[index]);
            }
        }
    }

    return true;
}

int main() {
    
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