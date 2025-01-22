//Lucia martinez martinez

/*

//@answer

Para abordar este problema, se utilizara un algoritmo de dijkstra para encontrar el menor camino posible.
Para ello, también debemos modificar ligeramente el codigo base, para cambiar el vector distancia de entero por un vector de pares <int,int>, donde en el primer par
llevaremos la cuenta de las distancias acumuladas por donde pasamossy en el segundo el numero de caminos por el que hemos pasado.

Normalmente, el algoritmo de dijkstra se utiliza con grafos dirigidos valorados, por ello, para este caso hay que modificar la base para utilizar un grado valorado
no dirigado, ya que en este problema podemos ir de un vértice a otro sin importar la dirección.

Una vez hecho esto, para cada consulta construimos un grafo dijkstra, el cual recorreremos con un bfs.

Este bfs se utiliza para estudiar el grafo desde el vertice origen desde el que se hace la consulta y estudiar la distancia en caminos desde ese origen a todos los 
demas vertices (para ello utilizamos un vector de enteros, distBFS). Una vez terminado el recorrido en anchura, ya tenemos el vector con las distancias del recorrido.

Estas distancias bfs nos serán útiles para saber que desde el origen es posible llegar al destino, esto se debe a que el vector inicia todos su valores a INF y a no ser
que se pase por un vertice, este valor no cambiara, por tanto, si queremos saber si un vértice v tiene un camino desde el origen, basta con comprobar 
si la distBFS[destino] != INF

Algo similar hacemos para comprobar si una vez conocido el camino con un recorrido más corto, es además el camino con el menor numero de caminos. Para esto, empleamos
el 2º par del vector dist, que como se ha mencionado anteriormente, lleva la cuenta del número de caminos desde un origen. 
Si este número es igual al de distBFS[destino] podemos concluir que se trata del mismo camino.


El coste de realizar un BFS es de O(V+A), siendo V el número de vértices y A el número de aristas.
El coste de realizar un Dijkstra es de O((V+A) log V), siendo V y A lo mismo que antes.

Por tanto, el coste total del ejercicios es de O((V+A) log V).

//@answer

*/

#include <iostream>
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
#include <limits>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

template <typename Valor>
class mejorCamino{ //recibe el grafo ya leido
private:
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> distanciaBFS;//bfs. Si es INF, indica que no se ha marcado. Guarda la distancia en nº vertices a cualquier vertice desde origen
    std::vector<std::pair<int,int>> dist; //Dijkstra. Guarda la distancia en coste a cualquier vertice y la dist en nºvertices. 1st coste 2nd nº vertices
    GrafoValorado<int> g;
    IndexPQ<std::pair<int,int>> pq; //Dijkstra, se encarga de ordenar los vertices a visitar segun su coste


    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);
        if (dist[w].first > dist[v].first + a.valor()) {
            dist[w].first = dist[v].first + a.valor(); //cambia el coste porque el vertice al que vamos tiene mayor coste
            dist[w].second = dist[v].second + 1; //guarda el numero de vertices al camino de menor coste
            pq.update(w, dist[w]); //se comporta como push si no estaba. mete el vector a la cola a visitar, cambiando su prioridad si fuese necesario
        }

        else if (dist[w].first == dist[v].first + a.valor() && dist[w].second > dist[v].second + 1) {
            dist[w].second = dist[v].second + 1; //guarda el numero de vertices al camino de menor coste
            pq.update(w, dist[w]);
        }
    }
    void Dijkstra(int origen) { //coste de O(a * logV), buscamos el camino mas corto justo al numero de camions que se atraviesen en este camino
        dist[origen] = {0,0};
        pq.push(origen, {0,0});
        while (!pq.empty()) {
            int v = pq.top().elem; 
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }

    void bfs(int origen) { //nº vertices de camino mas corto de origen al resto de vertices.El coste es de O(v+a)
        distanciaBFS[origen] = 0; //La distancia del origen a si mismo es 0, ya que no hemos pasado por ningun camio aun
        std::queue<int> cola;
        cola.push(origen);

        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (auto ar : g.ady(v)) {
                int w = ar.otro(v);
                if (distanciaBFS[w] == INF) { //Si no hemos pasado por el vertice
                    distanciaBFS[w] = distanciaBFS[v] + 1; //Añadimos un camino mas
                    cola.push(w);
                }
            }
        }
    }

public:
    void resuelveCaso(int origen, int destino) {
        bfs(origen); 
        if (distanciaBFS[destino] != INF) { //Si el nodo destino no ha sido visitado durante la busqueda es que no hay camino posible desde el origen
            Dijkstra(origen); //Si hay camino, hacemos dijkstra para encontrar el camino mas corto
            std::cout << dist[destino].first<< " "; //Una vez hecho, sabemos la distancia del origen hasta el destino
            if (dist[destino].second == distanciaBFS[destino]) { //Ademas, gracias al añadir un pair donde se lleva la cuenta del peso de las aritas valoradas y el numero de caminos por el que hemos pasado
                std::cout << "SI\n"; //podemos saber si el camino encontrado es el mas corto (hablando en cuando  numero de caminos)
            }
            else {
                std::cout << "NO\n";
            }
        }
        else {
            std::cout << "SIN CAMINO\n";
        }
    }
    mejorCamino(GrafoValorado<int> grafo, int n) :g(0), distanciaBFS(n, INF), pq(n), dist(n, { INF,0 }) {
        g = grafo;

    }

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n, a;
    std::cin >> n >> a;
   if (!std::cin)  // fin de la entrada
      return false;
   int v, w, valor;
   GrafoValorado<int> g(n);
   for (int i = 0; i < a; ++i) {
       std::cin >> v >> w >> valor;
       g.ponArista({ v - 1, w - 1, valor });
   }
   
   int consultas;
   std::cin >> consultas;
   while (consultas--) {
       int origen, destino;
       std::cin >> origen >> destino;
       mejorCamino(g,n).resuelveCaso(origen-1, destino-1);
   }
   // escribir sol
   std::cout << "---\n";
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
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