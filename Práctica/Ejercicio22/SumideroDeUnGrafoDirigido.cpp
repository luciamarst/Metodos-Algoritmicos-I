
// Lucia Martínez Martínez

#include <iostream>
#include "Digrafo.h"
#include <set>
#include <fstream>
using namespace std;

int verticeSumidero(Digrafo const& g,vector<int> const& a){
    int v = g.V();
    for(int i = 0; i < v; i++){
        size_t grado = g.ady(i).size();
        if(grado == 0){
            if(a[i] == v - 1)
                return i;
        }
    }

    return -1;
}


bool resuelveCaso() {
    
    int V, A;
    //Leer caso de prueba: cin>>...
    cin >> V;
    if (!std::cin)
        return false;
 
    Digrafo grafo(V);
    cin >> A;

    vector<int> adyacentes(V,0);
    for(int i = 0; i < A; i++){
        int v, w;
        cin >> v >> w;
        grafo.ponArista(v, w);
        adyacentes[w]++;
    }
    

    int sumidero = verticeSumidero(grafo,adyacentes);

    if(sumidero == -1)
        cout << "NO" << endl;
    else
        cout << "SI " << sumidero  << endl;

    //Resolver problema
    //Escribir resultado
    return true;
}


int main() {
    
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
