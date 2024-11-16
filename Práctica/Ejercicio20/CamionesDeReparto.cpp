//NOMBRE y APELLIDOS


#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
using namespace std;

class reparto {
private:
    bool _puede;

    GrafoValorado<int> g;
    std::vector<bool> visit;
    void dfs (int origen, int destino, int anchura) { //recorrido en profundidad para ver si puede llegar al destino
        visit[origen] = true;
        for (auto a : g.ady(origen)) {
            if (a.valor() >= anchura) { //Filtramos. Sinuestro valor es menor que la anchura, no podemos pasar, por tanto, ni estudiamos la opcion
                int w = a.otro(origen);
                if (!visit[w]) {
                     dfs(w, destino, anchura);

                     if(w == destino) _puede = true; //Si al salir de la busqueda en profundidad, hemos llegado al destino, es que existe un camino posible
                }

            }
        }
        
    }
public:
    reparto(GrafoValorado<int>grafo,int v, int e):visit(v),g(0), _puede(false) {
        g = grafo; 
    }

    bool puede(int origen, int destino, int anchura) { //Hacmos un dfs para ver si puede llegar al destino, si nuestro nodo destino se ha visito, es que entonces existe como minimo un camino posible
        dfs(origen, destino, anchura);
        return _puede;
    }
};

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int v, e;
    std::cin >> v;
   if (!std::cin)  // fin de la entrada
      return false;
   std::cin >> e;

   GrafoValorado<int> g(v);
   for (int i = 0; i < e; ++i) {
       int a, b, valor;
       std::cin >> a >> b >> valor;
       g.ponArista({ a - 1,b - 1,valor });
   }


   
   int casos;
   std::cin >> casos;
   while (casos--) {
       reparto r(g, v, e); //Para cada pregunta iniciamos las variables porque es un recorrido nuevo
       int a, b, valor;
       std::cin >> a >> b >> valor;
       if (r.puede(a-1, b-1, valor)) std::cout << "SI\n";
       else std::cout << "NO\n";
   }
   
   // escribir sol
   
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