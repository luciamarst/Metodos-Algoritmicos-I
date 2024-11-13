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

Resolucion del problema mediante busqueda en anchura. Se trata de un grafo dirigido con un numero de vertices N*N, 
donde cada vertice tiene K aristas que le llevan a los siguientes K vertices.

Yo creo que tambien se peude resolver con un algoritmo de Dijkstra, pero en la construccion del grafo es un poco liosa porque habria que poner aristas entre
O y D y desde O hasta sus K siguientes casillas, lo que podría tener un coste muy grande.

Por tanto, optar por una búsqueda en anchura que minimiza el número de pasos (objetivo del problema) es mejor opción. En cuanto a implementación
y a en cuanto a efiencia.

El coste de este algortimo es de O(V+ A) siendo V el numero de vertices y A el numero de aristas del grafo.
Recuerda que cada vertice V tiene K aristas que le llevan a los siguientes K vertices además de si es una serpiente/escalera y no coincide con un K siguiente

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int MAX = 10000000;
const int INF = 10000;

//Esto funciona porque al buscar el camino mas corto, como se usa una cola, se va a tratar antes el camino mas corto que lleve a la solucion
//Por eso, como cortamos la ejecución, se trata el camino mas corto y se deevuelve la solución, si no se hiciera asi, la solución
//podría sobreescribirse por una solución válida pero peor
int bfs(int N, int K, vector<int> const& saltos) {
    int destino = N * N;
    queue<int> q;
    vector<int> distancia(destino + 1, INF); //Distancias

    distancia[1] = 0; //Empezamos en la casilla 1, por lo que el numero de pasos que llevamos es 0
    q.push(1); //Psuheamos el 1 para empezar a tratar el tablero

    while(!q.empty()) { //Mientras la cola este llena, es decir, haya casillas que tratar
       int v = q.front(); //Consultamos el primero
       q.pop(); //Lo popeamos

       for (int i = 1; i <= K && v + 1 <= destino; i++) { //Tratamos las K casillas siguientes
          int w = saltos[v + i]; //Consultamos los saltos, iniciados en resuelveCaso, donde se guarda el destino de cada casilla. Si no es una serpeinte o escalera, w = v + 1, en cambio si
            //es una serpiente o escalera, w = destino de la serpiente o escalera
          
          if (distancia[w] == INF) { //Si esa casilla destino es igual a INF, significa que nuca se ha pasado por ella, es decir, no se ha visitado. Asi nos aseguramos que no se sobree
          //escriba el valor, ya que sino perderiamos el valor minimo que tenemos
            distancia[w] = distancia[v] + 1; //Por tanto, en esa casilla gaurdamos el numero de pasos qie llevamos
             if (w == destino) //Si se da que justo w es igual a la casilla destino, ya hemos acabado y podemos devolver el numero de pasos que hemos calculado
               return distancia[destino]; //Deolvemos el numero de pasos
            
            q.push(w); //Si no es el destino, pusheamos la casilla w para tratarla en la siguiente iteracion
          }
       }
    }
   
   return -1;
}

bool resuelveCaso() {
   
   int N, K, S, E;
   cin >> N >> K >> S >> E;
   
   if (N == 0)
      return false;
   
   vector<int> saltos(N * N + 1);
   for (int i = 1; i <= N * N; ++i) {
       saltos[i] = i; //Inicializamos los saltos, los saltos cuyo valor sean diferente de su indice, son saltos que o bien son escaleras o bien son serpientes
   }

   int O, D;
   for (int i = 0; i < S + E; i++) {
       cin >> O >> D; //Leemos los saltos de serpeitne/escaleras y les asignamos a la posicion O el valor D, para saber que para la casilla O se tiene el destino D
       saltos[O] = D;
   }
   
   //Se realiza un recorrido en anchura
   cout << bfs(N, K, saltos) << "\n";
   
   // escribir la solución

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