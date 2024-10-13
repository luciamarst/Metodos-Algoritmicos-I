
// NOMBRE Y APELLIDOS

#include <iostream>
#include <queue>
#include <fstream>
using namespace std;

bool resuelveCaso() {
    
    int D, P1, P2;
    //Leer caso de prueba: cin>>...
    cin >> D >> P1 >> P2;
    if (!std::cin)
        return false;
 
    priority_queue<int,vector<int>, less<int>> pq1;
    for(int i = 0; i < P1; i++){
        int p;
        cin >> p;
        pq1.push(p);
    }

    priority_queue<int,vector<int>, less<int>> pq2;
    for(int i = 0; i < P2; i++){
        int p;
        cin >> p;
        pq2.push(p);
    }

    long int tiempo = 0;
    bool dronVolando = true;
    int i = 1;
    vector<long int> sol;
    while(dronVolando){

        if(!pq1.empty() && !pq2.empty()){
            tiempo += min(pq1.top(), pq2.top());

            if(pq1.top() < pq2.top()){
               if(pq2.top() - pq1.top() > 0) pq2.push(pq2.top() - pq1.top());
            }
            else if(pq1.top() > pq2.top()){
               if(pq1.top() - pq2.top() > 0) pq1.push(pq1.top() - pq2.top());
            }

            pq1.pop();
            pq2.pop();

            if(i == D){
                sol.push_back(tiempo);
                i = 0;
                tiempo = 0;
            }
        }
        else if(pq1.empty() || pq2.empty()){
            dronVolando = false;
           if(tiempo > 0) sol.push_back(tiempo);
            
        }

        i++;
    }
    //Resolver problema
    //Escribir resultado
    if(sol.size() == 0){
        std::cout << "0\n";
        return true;
    }
    for(int i = 0;  i < sol.size(); i++){
        std::cout << sol[i] << " ";
    }
    std::cout << "\n";
    
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