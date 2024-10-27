
/*@ <answer>
 *
 * Lucia Martinez Martinez
 *
 *@ </answer> */

/*@ <answer>
 
 Para resolver este ejercicio, hay que utilizar dos vectores. Uno que se encargue de llevar la cuenta de los componenetes, es decir,
 los vértices del problema. Y otro que lleve el numero maximo de nodos conexos a ese vertice v .

 Para ello, cada vez que realicemos una busqueda para un vertice v, el array de componentes guardará en esa posición v
 el tamaño de maximos (ya que se va añadiendo según se tratan los vertices). De esta manera, el tamaño de la componente conexa
 de cada vertice es el tamaño del array maximos en la posicion de su componente.

 --Ejemplo. Grafo 5 -> 4-> 2 -> {1,5}
    componente[5] = 0 , ya que maximos.size() =0
    maximos.push_back(4) -> {4}, tam = 1

    componente[4] = 1
    maximos.push_back(4) -> {4,4}, tam = 2

    componente[2] = 2
    maximos.push_back(4) -> {4,4,4}, tam = 3

    Y asi sicesivamente, de tal manera que para acceder a la posicion correcta del maximo asociado a cada vértice se hace:
     -maximos[componente[v]]

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

class ComponenteConexa {
private:
    vector<bool> visit;
    vector<int> maximos;
    vector<int> componente;
    
    //Se encarga de recorrer el grafo en profundidad, marcando los nodos que se han visitado y y sumando +1 
    //al tamaño de la componente conexa
    int dfs(Grafo const& G, int v) {
        visit[v] = true;

        //En cada vertice del array componentes, es decir, los vertices del grafo, pongo el tamaño de la componente conexa
        //Conforme vamos añadiendo el numero maximo de nodos conexos a cada vertices, el array de maximos crece en tamaño
        //Por tanto, el tamaño de la componente conexa de cada nodo es el tamaño del array maximos en la posicion de su componente
        componente[v] = maximos.size();
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
    ComponenteConexa(Grafo const& G) : visit(G.V(), false), componente(G.V(), 0) {
        for (int v = 0; v < G.V(); v++) {
            if (!visit[v]){
                int tam = dfs(G, v);

                //PGuardamos en el array de maximos el tamaño para el vertice estudiado
               maximos.push_back(tam);
            }
                
        }
    }

    int getTamanyoV(int v) const {

        //Deuelvo el numero maximo de nodos conexos del vertice v. Podemos acceder a su maximo con el array de componenete[v], como
        //he explicado anteriormente, almacenamos el tamaño de la componente conexa de cada vertice en el array de maximos 
        return maximos[componente[v]];
    }
};

#endif

bool resuelveCaso() {
    
    int N = 0;
    cin >> N;
    if (!std::cin)
        return false;
 
  int M = 0;
  cin >> M;

  Grafo g(N+1);
    int amigo;
  for(int i = 1; i <= M; i++){
    int nGrupo;
    cin >> nGrupo;

    if(nGrupo > 0)
        cin >> amigo;
    for(int j = 1; j < nGrupo; j++){
      int amigo2;
      cin >> amigo2;
      g.ponArista(amigo, amigo2);
      amigo = amigo2;
    }
  }

    ComponenteConexa camino(g);
    
    for(int i = 1; i < g.V(); i++){
        std::cout << camino.getTamanyoV(i) << " ";
    }

    cout << '\n';
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
