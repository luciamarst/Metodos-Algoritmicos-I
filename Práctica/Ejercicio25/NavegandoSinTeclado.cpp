
// Lucia Martinez Martinez

#include <iostream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <fstream>
#include <limits>
using namespace std;

class Enlaces {

public:
    Enlaces(DigrafoValorado<int> g, vector<int> const& v) : grafo(g), vertices(v), dist(g.V(), INF), pq(g.V()) {
        lectura();

        if(vertices.size() > 0){
            Dijkstra(0);
            if(dist[g.V() - 1] != INF)
                cout << dist[g.V() - 1] << endl;
            else
                cout << "IMPOSIBLE\n";
            
        }
        else
            cout << "No hay enlaces" << endl;
    }


private:
    DigrafoValorado<int> grafo;
    const int INF = std::numeric_limits<int>::max();
    vector<int> dist;
    vector<int> vertices;
    IndexPQ<int> pq;
    
    void Dijkstra(int origen){
        dist[0] = vertices[0];
        pq.push(origen, 0);
        
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : grafo.ady(v))
                relajar(a);
        }
    }

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        
        if (dist[w] > dist[v] + a.valor() + vertices[w]) {
            dist[w] = dist[v] + a.valor() + vertices[w];
            pq.update(w, dist[w]);
        }
    }

    
    void lectura(){
        int e;
        cin >> e;

        for(int i = 0; i < e; i++){
            int v, w, valor;
            cin >> v >> w >> valor;
            grafo.ponArista({v-1, w-1, valor});
        }
    }

};

bool resuelveCaso() {
    int nPaginas;
    //Leer caso de prueba: cin>>...
    cin >> nPaginas;
    if (nPaginas == 0)
        return false;
 

    vector<int> paginas;
    for(int i = 0; i < nPaginas; i++){
        int pagina;
        cin >> pagina;
        paginas.push_back(pagina);
    }

    DigrafoValorado<int> g(nPaginas);


    Enlaces enlaces(g, paginas);
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
