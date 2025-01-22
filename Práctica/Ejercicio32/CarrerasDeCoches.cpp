//NOMBRE y APELLIDOS

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

void resolver(deque<int> pilas, int P){
    int sol = 0;

    while(!pilas.empty() && pilas.size() > 1) {
        if(pilas[0] + pilas[(pilas.size() -1)] >= P) {
            sol++;
            pilas.pop_front();
            pilas.pop_back();
        }
        else {
            if(pilas[0] < pilas[(pilas.size() -1)]) {
                pilas.pop_front();
            }
            else {
                pilas.pop_back();
            }
        }
    }

    cout << sol << endl;
}

void resuelveCaso() {
    int N, P;
    cin >> N >> P;

    deque<int> pilas(N);
    for(int i = 0; i < N; i++) {
        cin >> pilas[i];
    }
    
    sort(pilas.begin(), pilas.end());
    resolver(pilas, P);
}

int main() {
    // Para la entrada por fichero.
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
