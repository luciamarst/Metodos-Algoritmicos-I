
// NOMBRE Y APELLIDOS

#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

bool resuelveCaso() {
    
    int primerPajaro = 0;
    //Leer caso de prueba: cin>>...
    cin >> primerPajaro;
    if (!std::cin)
        return false;
 

    //Introducimos el primer pajaro
    priority_queue<int, vector<int>, greater<int>> pajaros_crecientes;
    priority_queue<int, vector<int>, less<int>> pajaros_decrecientes;
    
    pajaros_crecientes.push(primerPajaro);
    pajaros_decrecientes.push(primerPajaro);

    //Tratamos las parejas de pajaros
    int nParejas = 0;
    cin >> nParejas;

    int p1 = 0, p2 = 0;
    for(int i = 0; i < nParejas; i++){
        cin >> p1 >> p2;

        int maxPareja = max(p1,p2);
        int minPareja = min(p1,p2);

        pajaros_crecientes.push(p1);
        pajaros_crecientes.push(p2);

        pajaros_decrecientes.push(p1);
        pajaros_decrecientes.push(p2);

        if(pajaros_crecientes.top() < maxPareja && pajaros_decrecientes.top() > minPareja){

            if(primerPajaro < minPareja){
                primerPajaro = minPareja;
            }   
            else if(primerPajaro > maxPareja){
                primerPajaro = maxPareja;
            }
        }
        else if(pajaros_decrecientes.top() < minPareja){
            primerPajaro = pajaros_decrecientes.top();
        }
        else if(pajaros_crecientes.top() > maxPareja){
            primerPajaro = pajaros_crecientes.top();
        }
       
        

        cout << primerPajaro << ' ';

    }
    cout << '\n';
    
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