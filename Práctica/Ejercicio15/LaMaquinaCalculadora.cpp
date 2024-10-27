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
using namespace std;

/*@ <answer>

 El ejercicio re sevuelve con una busqueda en anchura ya que lo que nos conviene es minimizar el numero de operaciones para llegar
 al destino desde el origen.

 Para ello, utilizamos la misma implementacion usando una cola para el recorrido en anchura.

 Utilizamos un vector para almacenar las distancias de los nodos al origen, inicializandolos a infinito.
 Además de una cola donde vamos introduciendo los nodos que vamos visitando para tratarlos en siguientes iteracoines

 De esta forma, conseguimos tratar todas las posibilidades de ir aplicando las 3 operaciones 

 En cuanto al coste: se presenta con un O(V + A) siendo V el número de vertices que posee el grafo y A el número de aristas. 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

using Camino = queue<int>;


int MAX = 10000;//Numero maximo de nodos
int INFINITO = 1000000000;//Inifito para marcar la distancia de los nodos no visitados

int adyacente(int v, int i) { //Cogemos el modulo de la op porque el adyacente es el indice del vector de distancias, es decir, el numero de nodo es el resultado que queremos
    switch (i) {
        case 0: return (v + 1) % MAX; // + 1
        case 1: return (v * 2) % MAX; // * 2
        case 2: return v / 3; // / 3
    }
}

// recorrido en anchura desde s, el objetivo es encontrar los nodos a menor distancia de nuestro vértice
//Esto se consigue con un recorido en anchura
int bfs(int origen, int destino) {

    if(origen == destino){
        return 0;
    }

    vector<int> dist(MAX, INFINITO);
    dist[origen] = 0; //La distancia de un nodo a si mismo es 0
    queue<int> q;
    q.push(origen);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        //Solo podemos hacer tres operaiocnes por lo tanto el recorrido es de 3
        for(int i = 0; i < 3; i++){
            int w = adyacente(v, i);

            if (dist[w] == INFINITO) {
                dist[w] = dist[v] + 1;//Sumamos 1 por cada operaciones realizada para llegar al destino
                if(w == destino){
                    return dist[w];
                }
                else q.push(w);
            }
        }
    }
}



bool resuelveCaso() {

    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    
    cout << bfs(N, C) << "\n";

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