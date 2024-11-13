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
#include "Digrafo.h"
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

class OrdenTopologico{
public:

    // g es DAG
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false), en_recursion(g.V(), false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    // devuelve la ordenación topológica
    std::deque<int> const& orden() const {
        return _orden;
    }

    bool noHayCilos(){
        return ciclo;
    }

   

private:
    bool ciclo = false;
    std::vector<bool> visit;
    std::vector<bool> en_recursion; //Llevamos la cuenta de los elementos que se han recorrido durante la recursion
    std::deque<int> _orden; // ordenación topológica
    void dfs(Digrafo const& g, int v) {
        visit[v] = true; //Marcamos este vertice como visitado
        en_recursion[v] = true; //Marcamos que estamos en la busqueda en profundidad

        for (int w : g.ady(v)) {//Observamos sus vecinos
            if (!visit[w]) //Si el vecino w no ha sido visitado, seguimos realizando la búsqueda en profundidad para este vecino
              dfs(g, w); //Realizamos la busuqeda para ese vertice w
            else if(en_recursion[w]){ //Si ya ha sido visitado, pero no hemos salido de la busqueda en profundidad, es que hay un ciclo
                ciclo = true; //Por tanto, hay un ciclo
                return;//Cortamos ejecucion
            }

        }
         _orden.push_front(v); //Una vez salimos
        en_recursion[v] = false; //Marcamos que este vertice ya no esta en la busqueda en profundidad
    }
    
};

bool resuelveCaso() { 
    
    Digrafo g(std::cin, 1);
    if (!cin) 
        return false;
   
    

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