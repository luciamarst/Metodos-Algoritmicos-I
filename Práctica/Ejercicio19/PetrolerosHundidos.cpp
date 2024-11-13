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
#include "ConjuntosDisjuntos.h"

/*@ <answer>

 El ejercicio se resuelve con una busqueda en profundidad ya que una vez detectada una mancha, nos interesa saber como de grande es cumpliendo
 las restricciones de que los pixeles tienen que ser adyacentes vertical y/o horizontalmente. Las diagonales no cuentan como
 adyacentes.

 Por eso, una vez que mientras recorremos la matriz del problema encontramos un #, llamamos a dfs, con el fin de hacer esta
 busqueda en profundidad, contando el numeor de manchas adyacentes para esta mancha. Luego vamos actualizando el maximo
 

 En cuanto al coste: se presenta con un O(F * C) siendo F el numero de filas y C el numero de columans de la matriz. 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

using Mapa = vector<string>;

class Manchas{
public:

//Constructor de la clase. Se encarga de iniciar el valor de F, C ademas de la matriz F*C de visitados, que obviamente al inicio esta a false
//El num y el maximo tambien tienen que ser 0, ya que podria haber mapas sin manchas,y por consecuencia, sin maixmo
    Manchas(Mapa const& mapa) :M(mapa), F(mapa.size()), C(mapa[0].size()), visit(F, vector<bool>(C, false)), num(0), maxim(0) {
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                if (!visit[i][j] && M[i][j] == '#') { // se recorre una nueva mancha
                    posPadres.push_back({i,j});
                    ++num; //Aumentamos el numero de manchas que hay en el mapa
                    int nuevotam = dfs(M, i, j); //Hacemos una busqueda en profundiad para el numero de pixeles de esta mancha
                    maxim = max(maxim, nuevotam);//Si es mayor que el maixmo anterior, lo actualizamos
                }
            }
        }
    }

    int numero() const { return num; } //Devuelve el nuemro de manchas
    int maximo() const { return maxim; } //Devuelve el tamaño maximo de pixels de una mancha
    ConjuntosDisjuntos getConjuntos() const { return conjuntos; } //Devuelve los conjuntos disjuntos
    void inserMax(int max) { maxim = max; } //Inserta un nuevo maximo
    bool corecto(int i, int j) const{//Comprueba si una posicion en la matriz es correcta, es decir, si esta dentro de los limites de la matriz
        return 0 <= i && i < F && 0 <= j && j < C;
    }
    bool contieneMancha(Mapa const& M, int i, int j) const{//Comprueba si una posicion en la matriz contiene una mancha
        return M[i][j] == '#';
    }
    vector<pair<int,int>> const getDirs(){return dirs;}

    void anyadirMancha(int f, int c) {
        M[f][c] = '#'; // Nueva mancha de petróleo

        int tamNueva = 1;
        for (auto d : dirs) { // Para cada casilla adyacente en las 8 direcciones
            int i = f + d.first;
            int j = c + d.second;
            
            if (corecto(i, j) && M[i][j] == '#' && !conjuntos.unidos(f * C + c, i * C + j)) { // Es una mancha adyacente valida y los conjuntos no estan unidos
                tamNueva += conjuntos.tam(i * C + j);
                conjuntos.unir(f * C + c, i * C + j);
            }
        }

        maxim = max(maxim, tamNueva);
    }
private:
    int F = 0, C = 0; //Fila y columna de la matriz
    int num = 0; //Numero de manchas de la matriz
    vector<vector<bool>> visit; //Matriz con los nodos visitados
    const vector<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1},{-1,-1},{1,1},{-1,1},{1,-1}}; //Direcciones validas
    int maxim = 0; //Numero de pixeles de la mancha mas grande
    ConjuntosDisjuntos conjuntos = ConjuntosDisjuntos(F*C);
    vector<pair<int,int>> posPadres;
    Mapa M;

   

    //BUSQUEDA EN PROFUNDIDAD
    int dfs(Mapa const& M, int i, int j){
        visit[i][j] = true; //Marcamos como visitado
        int tam = 1; //Tamaño 1 porque si hemos entrado aqui es porque hemos detectado una mancha

        //Realizamos la busqueda para todas las direcciones contempladas (UP, DOWN, LEFT Y/O RIGHT)
        for(pair<int,int> p : dirs){
            int ni = i + p.first, nj = j + p.second; //Nueva fila y columna para la direccion p
            
            if(corecto(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]){ //Si es una posicion correcta, hay una mancha y además no lo hemos visitamos, aumentamos el tamaño de la mancha
                tam += dfs(M, ni, nj); //Aumentamos el tamaño de la mancha
                conjuntos.unir((i * C + j), (ni* C + nj));
            }
        }


        return tam; //Devolvemos el tamaño de pixeles de la mancha
    }
};

bool resuelveCaso() { //El coste de la funcion obviamente es O(F*C), siendo f el numero de filas y c el numero de columans
    int F, C;
    cin >> F >> C; // número de filas y columnas
        
    if (!cin) 
        return false;
   
    Mapa mapa(F);//Construimos el mapa con el numero de filas

    // leemos la imagen
    for (string & linea : mapa)
        cin >> linea;
    
    // la analizamos
    Manchas manchas(mapa);
    cout << manchas.maximo() << ' ';
    int nuevasManchas = 0;
    cin >> nuevasManchas;

    for(int i = 0; i < nuevasManchas; i++){
        int x, y;
        cin >> x >> y;
        x-= 1; y -=1;
        
        manchas.anyadirMancha(x, y);

        cout << manchas.maximo() << ' ';
    }
    
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