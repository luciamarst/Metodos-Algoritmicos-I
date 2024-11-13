/*@ <answer>
 *
 * Lucia Martínez Martínez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue> 
#include <stack>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

/*@ <answer>

El ejercicio consiste en evaluar si puede realizarse un numero de tareas donde una tarea B depende de una tarea A, es decir, si A se realiza, B tambien se tiene que realizar. O viceversa

Para ello, basta con tuilizar un orden topológico, es decir, una busqueda en profundidad mientras se comprueba que no haya ciclos.

Lo más importante es que si hay un ciclo, no se puede realizar el orden topológico, ya que no se puede realizar una tarea si depende de otra que no se ha realizado.

Por tanto, con comprobar que se trata de un grado dirigido sin ciclos es posible que haya una solución. Ya que al tratarse de una búsqueda en profundidad,
 se recorren todos los nodos y se comprueba que no haya ciclos.

 Para comprobar que no hay ciclos en un grafo dirigido, usamos un vector de booleanos auxiliar en el vamos llevando los elementos que se han añadido a la cola o no.
 Primeero los marcamos como que se han añadido, luego finalmente los que se añaden de verdad a la cola se marcan como falsos.
 Con eso conseguimos que cuando un nodo ya haya sido visitado, pero no haya salido de la busqueda en profundidad, es que hay un ciclo.

 El coste de la solución es O(V + A) siendo V el numero de vertices y A el numero de aristas del grafo.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),dist(g.V(), INF), ult(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
             for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCaminoHasta(int v) const {
        Valor distancia(int v) const { return dist[v]; 
    }
    
    Camino<Valor> camino(int v) const {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ult[v]; a.desde() != origen; a = ult[a.desde()])
        cam.push_front(a);
        cam.push_front(a);
        return cam;
    }


private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ult;
    IndexPQ<Valor> pq;
    
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ult[w] = a;
            pq.update(w, dist[w]);
        }
    }
    
};

bool resuelveCaso() { 
     int N,K, S,E;
     cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0) 
        return false;
   
    
    Digrafo g((S +E) + 1);
    int nAristas = S +E;
    while(nAristas--){
        int a,b;
        cin >> a >> b;
        g.ponArista(a - 1, b - 1);

        for(int i = a; i <= (N+a) - 1;i++){
            g.ponArista(a - 1, i);
        }
    }



    OrdenTopologico orden(g);
    
    deque<int> cola = orden.orden();

    if(orden.noHayCilos()){
        cout << "Imposible";
    }else{
        for(int v : cola){
            cout << v + 1<< " ";
        }
    }
    cout << '\n';
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}