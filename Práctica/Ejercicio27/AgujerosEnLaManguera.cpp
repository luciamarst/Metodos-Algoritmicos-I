
// Lucia Martinez Martinez 

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*
//@answer
//EXPLICACIÓN DE LA SOLUCIÓN:
El algortimo usado es una algortimo voraz, en el cual buscamos la solucion óptima de colocar los parches sobre los aguejros de la manguera
de la forma mas eficiente posible. Es decir, usar el mínimo de parches posibles.

//COSTE DE LA SOLUCION:
El coste del algoritmo es de O(N), siendo N el numero de agujeros que hay en la manguera, ya que tenemos que recorrerlos para ir
poniendo los parches.

//@answer
*/

int resolver(vector<int> const& posiciones, int L){
    int numero_parches = 0;

    if(L == 0){
        numero_parches = 0;
        return numero_parches;
    }
    else if(posiciones.size() == 1){
        return 1;
    }

    int i = 0;
    int primerParche = posiciones[0];
    numero_parches = 1;
    i+=1;

    while(i < posiciones.size()){

        if(primerParche != -1 && (posiciones[i] - primerParche) > L ){
            primerParche = posiciones[i];
            numero_parches++;
        }

        i++;
    }

    return numero_parches;
}

bool resuelveCaso() {
    
    //Leer caso de prueba: cin>>...
    int N,L;
    cin >> N >> L;
    
    if (!std::cin)
        return false;
 
    vector<int> posiciones_agujeros;
    for(int i = 0; i < N; i++){
        int pos;
       cin >> pos;
       posiciones_agujeros.push_back(pos);
    }

    

    cout << resolver(posiciones_agujeros,L) << '\n';
    //Resolver problema
    //Escribir resultado
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
