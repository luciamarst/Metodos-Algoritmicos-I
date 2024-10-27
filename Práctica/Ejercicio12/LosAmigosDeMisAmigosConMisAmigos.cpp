
/*@ <answer>
 *
 * Nombre y Apellidos:  Lucia Martinez Martinez
 *
 *@ </answer> */

/*@ <answer>
 
 Para resolver este ejercicios, solo hay que darse cuenta que al tratar las amistades como una grafo, es muy fácil observar cual 
 es el subgrafo mas grande (es decir, el grupo de amigos de mis amigos mas grande).

 Por tanto, para este problema basta con estudiar para cada nodo cual es su distancia mas larga en aristas, de esta manera llegamos
 a la a la solución del problema.

El coste de este algoritmo es O(V + A), donde V es el número de vértices y A el número de aristas.
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

#include <iostream>
#include "Grafo.h"
#include <deque>
#include <fstream>
using namespace std;

#ifndef CAMINODFS_H_
#define CAMINODFS_H_

using namespace std;
using Camino = deque<int>;

class ComponenteConexa {
private:
    vector<bool> visit;
    int maxim;
    
    //Se encarga de recorrer el grafo en profundidad, marcando los nodos que se han visitado y y sumando +1 
    //al tamaño de la componente conexa
    int dfs(Grafo const& G, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                tam += dfs(G, w);
            }
        }

        return tam;
    }

public:

//Iniciamos el constructor, de manera que llamamos a dfs para que recorrar el grafo.
//La idea princiapl es que para cada vértice busque hasta cuantos vertices puede llegar, que son los amigos de sus amigos
    ComponenteConexa(Grafo const& G) : visit(G.V(), false), maxim(0) {
        for (int v = 0; v < G.V(); v++) {
            if (!visit[v]){
                int tam = dfs(G, v);

                //Elegimos entre el maixmo actual y el tamaño de la componente conexa
                maxim = max(maxim, tam);
            }
                
        }
    }

    int maximun() const {
        return maxim;
    }
};

#endif
void resuelveCaso() {

   int N, M;
   cin >> N >> M;

   Grafo G(N + 1);
   while (M--) {
       int v, w;
       cin >> v >> w;
       G.ponArista(v, w);
   }

    ComponenteConexa camino(G);

    cout << camino.maximun() << endl;
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
