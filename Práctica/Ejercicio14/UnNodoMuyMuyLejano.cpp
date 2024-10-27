/*@ <answer>
 *
 * Lucia Martínez Martínez
 *
 *@ </answer> */

#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <queue> 
#include <stack>
#include <vector>
using namespace std;

/*@ <answer>

 El ejercicio plantea calcular los nodos que no son posibles visitar en un red a partir de un nodo inicial y teniendo en cuenta un rango TTL,
 de forma que cualquier nodo que este a una distancia myor de TTL dsde el nodo inciial no se podrá visitar.

 Este problema se puede resolver mediante un recorrido en anchura, ya que se trata de encontrar los nodos a menor distancia de nuestro vértice.
 De manera que el recorrido en anchura conseguimos explotar los nodos a menor distancia antes.

 La clave es 

 En cuanto al coste: se presenta con un O(V + A) siendo V el número de vertices que posee el grafo y A el número de aristas. 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

using Camino = queue<int>;

class CaminoMasCorto {
public:
    CaminoMasCorto(Grafo const& G, int s) : visit(G.V(), false), ant(G.V()), dist(G.V()), s(s){
        bfs(G);
    }

    bool hayCamino(int v) const { return visit[v]; }

    int distancia(int v) const { return dist[v]; }

    Camino camino(int v) const {
        if (!hayCamino(v)) throw domain_error("No hay camino");
        Camino cam;
        for (int x = v; x != s; x = ant[x])  //Contruimos camino
            cam.push(x);
        cam.push(s);
        return cam;
    }

private:
    vector<bool> visit; //Para controlar si un nodo ha sido ya visitado o no, se marca si lo ha sido
    vector<int> ant; //LLeva la cuenta del nodo anterior
    vector<int> dist; //Distancia 
    int s; //nODO

    // recorrido en anchura desde s, el objetivo es encontrar los nodos a menor distancia de nuestro vértice
    //Esto se consigue con un recorido en anchura
    void bfs(Grafo const& G) {
        queue<int> q;
        dist[s] = 0; //La distancia de un nodo a si mismo es 0
        visit[s] = true;
        q.push(s);


        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.ady(v)) {
                if (!visit[w]){
                    ant[w] = v;//Guardamos el anterior del nodo actual en la posicion del nodo actual
                    dist[w] = dist[v] + 1; //Sumamos una arista mas a la distancia
                    visit[w] = true; //Lo marcamos como visitados y lo añadimos a la cola
                    q.push(w);
                }
            }
        }
    }
};


bool resuelveCaso() {

    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    Grafo G(N + 1);
    for(int i = 0; i < C; i++) {
        int v, w;
        cin >> v >> w;
        G.ponArista(v, w);
    }

    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int s, TTL;
        cin >> s >> TTL;
        int nodosLejanos = 0;

        CaminoMasCorto cam(G, s);

        //Para cada pregunta se recorren todos los vertices del grafo
        for (int v = 1; v < G.V(); v++){

            if (!cam.hayCamino(v))//Si no hay camino para ese vertice, sumamos como nodo lejano(es decir, si no forma aprte del grafo conexo)
                nodosLejanos++;
            else if (cam.distancia(v) > TTL) //O bien si la distancia de nuestro camino estudiado es mayor a TTL
                nodosLejanos++;
        }
             
        
        cout << nodosLejanos << "\n";
    }

    cout << "---\n";
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