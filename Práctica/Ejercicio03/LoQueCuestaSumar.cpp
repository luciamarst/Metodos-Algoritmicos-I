
// NOMBRE Y APELLIDOS

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


// Custom operator< removed as it is not needed for priority_queue<int>

bool resuelveCaso() {
    int nSumandos = 0;
    //Leer caso de prueba: cin>>...
    cin >> nSumandos;

    if (nSumandos == 0)
        return false;
 

    long long int valorSumando = 0;
    priority_queue<long long int, vector<long long int>, greater<long long int>> pq;

    for(int i = 0; i < nSumandos; i++){
        cin >> valorSumando;
        pq.push(valorSumando);
    }
    
    long long int sumaAritmetica = 0;
    long long int coste = 0;

    vector<int> sumas;
    while(pq.size() > 1){

        long long int primerElem = pq.top();
        pq.pop();
        long long int secondElem = pq.top();
        pq.pop();

        sumaAritmetica = primerElem + secondElem;
        pq.push(sumaAritmetica);

        
        coste += sumaAritmetica;
    }


    std::cout << coste << "\n";
    
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