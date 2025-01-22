
// NOMBRE Y APELLIDOS

#include <iostream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <fstream>
#include <limits>
using namespace std;

template <typename Valor>
class Dijkstra{
public:
    Dijkstra(DigrafoValorado<Valor> const& g) : dist(g.V(), INF), pq(g.V()) {
        dist[0] = 0;
        pq.push(0, 0);
        
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }

    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v ) const{return dist[v];}


private:
   const int INF = std::numeric_limits<int>::max();
   vector<int> dist;
   IndexPQ<int> pq;

   void relajar(AristaDirigida<int> a){
        int v= a.desde();
        int w = a.hasta();

        if(dist[w] > dist[v] + a.valor()){
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
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

    DigrafoValorado<int> grafo(V);
    for(int i = 0; i < A; i++){
        int v, w, valor;
        cin >> v >> w >> valor;
        grafo.ponArista({v-1, w-1, valor});
    }

    Dijkstra<int> grafo_normal(grafo);
    Dijkstra<int> grafo_inverso(grafo.inverso());

    int origen, nPaquetes;
    cin >> origen >> nPaquetes;
    
    origen--;
    int sol = 0;
    for(int i = 0; i < nPaquetes; i++){
        int destino;
        cin >> destino;
        destino--;
        if(grafo_normal.hayCamino(destino) && grafo_inverso.hayCamino(origen)){
            sol += grafo_inverso.distancia(destino) + grafo_normal.distancia(destino);
        }else{
            cout << "Imposible\n";
            break;
        }
    }

    if(sol != 0)
        cout << sol << "\n";
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
