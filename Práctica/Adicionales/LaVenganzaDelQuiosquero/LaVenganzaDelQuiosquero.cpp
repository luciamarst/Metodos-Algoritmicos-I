
// Lucía Martínez Martínez y Jorge Aured Zarzoso

#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

/*
//EXPLICACION DEL ALGORITMO
    Inicializamos un conjunto excluidos vacío para rastrear los valores que no podemos incluir.
    Iteramos desde 1 hasta que hayamos seleccionado.
    Si el valor actual 𝑥 no está en excluidos, lo añadimos a nuestra solución y añadimos S-a a excluidos
    Continuamos hasta que no hayamos seleccionado N valores
    
//COSTE DEL PROBLEMA
    El coste del problema es O(N) ya que iteramos N veces y en cada iteración realizamos operaciones de coste constante.

//DEMOSTRACION DE OPTIMALIDAD
    Nuestro objetivo es demostrar que seleccionar las N resistencias más pequeñas que cumplan esta restricción produce el menor costo

    Supongamos que existe una solución mejor
    Sea R1,R2...,Rn la solución producida por nuestro algoritmo voraz
    y sea R'1, R'2,...,R'n una solución óptima.


    Como el algoritmo selecciona resistencias en orden ascendente y evita
    cualquier valor si S-x ya está seleccionado, lo que implica 
    que para algún i, R'i != Ri, entonces Ri > R'i, pero:

    Si Ri > R'i, entonces R'i no se excluye por la restriccion R'i +(S-R'i) = S,
    lo que significa que R'i debería haber sido seleccionado por el algoritmo
    Esto contradice como funciona el algoritmo, el cual selecciona las resistencias
    más pequeñas que cumplen la restricción


    Por lo tanto, no puede existir una solución mejor que la porducida
    por nuestro algoritmo voraz
*/

long long minimoCosto(int N, int S) {
    unordered_set<int> excluidos;
    long long costo = 0;
    int seleccionadas = 0;
    
    for (int i = 1; seleccionadas < N; ++i) {
        // Si el valor actual no está excluido, lo seleccionamos
        if (excluidos.find(i) == excluidos.end()) {
            costo += i;               // Añadimos el costo de esta resistencia
            seleccionadas++;          // Incrementamos el contador de seleccionadas
            excluidos.insert(S - i);  // Excluimos el complemento para evitar pares que sumen S
        }
    }
    
    return costo;
}

bool resuelveCaso() {
    int N, S;

    if (!std::cin)
        return false;
 
    while (cin >> N >> S) {
        cout << minimoCosto(N, S) << "\n";
    }    
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
