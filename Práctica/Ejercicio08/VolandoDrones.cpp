
// NOMBRE Y APELLIDOS

#include <iostream>
#include <queue>
#include <fstream>
#include <list>
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

    list<int> l1, l2;
    long int tiempo = 0;
    bool dronVolando = true;
    int i = 0;
    vector<long int> sol;

    while(!pq1.empty() && !pq2.empty()){

        while(!pq1.empty() && !pq2.empty() && i < D){
            tiempo += min(pq1.top(), pq2.top()); 

            if(pq1.top() < pq2.top()){
                l2.push_back(pq2.top() - pq1.top());
            }
            else if(pq1.top() > pq2.top()){
                l1.push_back(pq1.top() - pq2.top());
            }

            pq1.pop();
            pq2.pop();

            i++;
        }

        for (int val : l1) {
            pq1.push(val);
        }
        l1.clear();
        for (int val : l2) {
            pq2.push(val);
        }
        l2.clear();
        

        cout << tiempo << " ";
        tiempo = 0;
        i = 0;
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