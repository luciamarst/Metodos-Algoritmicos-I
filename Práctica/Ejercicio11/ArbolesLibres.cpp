
/*@ <answer>
 *
 * Nombre y Apellidos: Lucia Martinez Martinez
 *
 *@ </answer> */

/*@ <answer>
 
 Para comprobar si el grafo es libre se tendrá que comprobar si para cada 
 par de vertices del grafo está conectado por un camino. Para ello, se creará
 un patrón de resolución de problema que tendrá un método recursivo llamado dfs (busqueda en profunidad) cuyo funcionamiento
 consistirá en comprobar si el vértice está visitado, si no lo está se marcará como visitado y se sumará
 + 1 al atributo visitados. Para comprobar que el grafo es acíclico se deberá cumplir que la propiedad V - 1 = A.

 Conclusión: Para comprobar que este grafo es conexo y acíclico se deberá comprobar que el número de vertices visitados es igual al número 
 total de vertices y que el número de aristas es igual a V - 1 respectivamente.

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
using Camino = deque<int>; // Representacion de caminos

class CaminoDFS {
private:
   vector<bool> visit; // visit[v], vector para comprobar si existe un camino entre vertices
   int V, A;
   int visitados;

//dfs se encarga de contar los nodos visitados ademas de avanzar recursivamente por los nodos. Marcando los visitados
   void dfs(Grafo const& g, int v) { //O(V + A) EN EL CASO PEOR
      visitados++;
      visit[v] = true;
      for (int w : g.ady(v)) {
         if (!visit[w]) {
            dfs(g, w);
         }
      }
   }

public:

    //Contructor de la clase
    //El visit, inicia el vector de booleanos todo a false con tamaño de g.V()
   CaminoDFS(Grafo const& g) : visit(g.V(), false), V(g.V()), A(g.A()), visitados(0) {
      dfs(g, 0);
   }

    //Devuelve si hay camino entre dos vertices (ya esta visitado)
   bool hayCamino(int v) const {
      return visit[v];
   }

    //Para saber si un grafo es acíclico, basta con saber que elnúmero de vertices menos 1 es igual al numero de aristas
    //Ademas para comprobar que es conexo, el numeor de v visitados tiene que ser igual al numero de vertices
   bool esArbolLibre() const {
      return (visitados == V) && (V - 1 == A);
   }

};

#endif 
bool resuelveCaso() {
    
    int nV = 0;
    //Leer caso de prueba: cin>>...
    cin >> nV;
    if (!std::cin)
        return false;
 
    int nA = 0;
    cin >> nA;
    Grafo grafo(nV);
    int v = 0, w = 0;
    for(int i = 0; i < nA; i++){
        cin >> v >> w;
        grafo.ponArista(v,w);
    }

    //Contruimos la clase caminos en funcion del grafo que hemos iniciado
    CaminoDFS c(grafo);

    if(c.esArbolLibre()){
        cout << "SI\n";
    }
    else{
        cout << "NO\n";
    }
    
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
