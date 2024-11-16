
// Lucía Martínez Martínez

/*
@author lucia martínez martínez
@ <answer>

Para resolver el problema del archipielago se utiliza un algoritmo de kruskal, ya que este algortimo recorre
las aristas de un grafo valorado en orden creciente, es decir, de los valores más bajos a los más grandes.
De esta manera, como recorremos primero las aristas con menor valor, minimizamos el coste de la construcción de los puentes
en este problema, que es el objetivo.

El algoritmo de Kruskal también se caracteriza por tener que ser acíclico, si es cíclico, no se puede construir el puente

Por tanto, para resolver este problema, con ir recorriendo el grafo por las aristas de menor valor (se utiliza una cola de prioridad 
para saber que arista es la menor valor y recorrer primero las de menor valor) y comprobando que no se forme un ciclo, es suficiente.

El coste de este algoritmo es O(E log E) siendo E el número de aristas del grafo.

Primero se tienen que ordenar las aristas del grafo para tratarlas en orden creciente, que suele hacerse con un quicksort o heapsort, con
coste promedio de O (E log E), siendo E el número de aristas del grafo.

Luego, también hay que tener en cuenta las operaciones de unir y buscar de la estructura de datos de conjuntos disjuntos, 
que tienen un coste de O(log V), siendo V el número de vértices del grafo.

Por tanto, el coste total del algoritmo es O(E log E + E log V) = O(E log E)

@ <answer>

*/
#include <iostream>

#include <fstream>
#include <queue>
#include "ConjuntosDisjuntos.h"
#include "GrafoValorado.h"

using namespace std;


template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    int visit;
    Valor coste;
    int V;

public:
    Valor costeARM() const { //Devuelve el coste minimo para construir  los puentes que unan todas las islas
        return coste;
    }
    
    bool getVisit() const { //Comprueba si el grafo es aciclico
        return visit == (V - 1); //Comprobamos que es aciclico, ya que si hay algún ciclo el algoritmo de kruskal descansa en paz
    }
        
    std::vector<Arista<Valor>> const& ARM() const {
     return _ARM;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), visit(0), V(g.V()) {
        auto ar = g.aristas();
        std::priority_queue<Arista<int>, std::vector<Arista<int>>, std::greater<Arista<int>>> cola(ar.begin(),ar.end());
        ConjuntosDisjuntos cjtos(g.V());
        while (!cola.empty()) {
            auto a = cola.top(); cola.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v,w)) {
                cjtos.unir(v, w);
                
                visit++;
                _ARM.push_back(a); 
                coste += a.valor();

                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }
};


bool resuelveCaso() {
    
    int V;
    cin >> V;
    if (!std::cin)
        return false;
    
    int A;
    cin >> A;

    GrafoValorado<int> grafo(V);

    for(int i = 0; i < A; i++){
        int v, w, valor;
        cin >> v >> w >> valor;
        Arista<int> arista(v-1, w-1, valor);
        grafo.ponArista(arista);
    }
    
    ARM_Kruskal kruskal(grafo);

   
    if(kruskal.getVisit())
        cout << kruskal.costeARM() << endl;
    else
        cout << "No hay puentes suficientes" << endl;
    


    //Resolver problema
    //Escribir resultado
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
