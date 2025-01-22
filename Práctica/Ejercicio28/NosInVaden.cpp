
// Lucia Martinez Martinez

/*
//@answer
//Explicacion de la solucion
 Para llegar a una solucion óptima, lo que se ha usado ha sido dos vectores, para llevar la cuenta de enemigos y defensores.
 Se han ordenado ambos vectores, los enemigos en orden creciente, asegurando que los del final siempre van a ser los batallones
 con mas soldados, mientras que los defensores se han ordenado decrecientemente, teniendo como primeros los batallones con mas soldados
 tambien.

 Sabiendo esto, lo que se hace es comparar el final de los enemigos con el principio de los defensores, si este valor es menor o igual, 
 se consigue una victoria, eliminando ademas del vector de enemigos ese batallon.
 Cuando no se da este caso, se elimina tambien el batallon porque ya lo hemos tratado y seguir estudiando las entradas.
 
 De esta forma, conseguimos estudiar con un coste linaal  la solución, ya que solo recorremos una vez el vector de enemigos y defensores.

//Coste de la solucion
 El coste de la solucion esde O(N), siendo eN el numero de enemigos y defensores, ya que solo recorremos una vez ambos vectores.

//@answer
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

int resolver(vector<int> e, vector<int> d){
    int victorias = 0;
    int i = 0;

    while(!e.empty()){
        if(e.back() <= d[i]){
            victorias++;
            e.pop_back();
            
             i++;
        }else{
            e.pop_back();
        }
    }

    return victorias;
}

bool resuelveCaso() {
    
    int N;
    std::cin >> N;
    
    if (!std::cin)
        return false;
 
    vector<int> enemigos;
    for(int i = 0; i < N; i++){
        int enemigo;
        cin >> enemigo;
        enemigos.push_back(enemigo);
    }

    sort(enemigos.begin(), enemigos.end());

    vector<int> defensa;
    for(int i = 0; i < N; i++){
        int defensor;
        cin >> defensor;
        defensa.push_back(defensor);
    }

    sort(defensa.begin(), defensa.end(), greater<int>());
    //Resolver problema
    //Escribir resultado
    cout << resolver(enemigos, defensa) << endl;
    return true;
}


int main() {
    
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
