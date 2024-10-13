
// NOMBRE Y APELLIDOS

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

struct tarea{
    long long int inicio;
    long long int fin;
    long long int periodica = 0;
    bool p = false;
    long long int id;
};

bool operator>(tarea const& a, tarea const& b){
    return a.inicio == b.inicio ? a.id > b.id : a.inicio > b.inicio;
}
bool resuelveCaso() {
    
    long long int N, M, T;
    //Leer caso de prueba: cin>>...
    cin >> N >> M >>T;
    if (!std::cin)
        return false;
 
    priority_queue<tarea, vector<tarea>, greater<tarea>> pq;

    int j = 0;
    for(int i = 0; i < N; i++){
        tarea t;
        cin >> t.inicio >> t.fin;
        t.id = i+1;
        pq.push(t);
        j = i + 1;
    }

    for(int i = 0; i < M; i++){
        tarea t;
        cin >> t.inicio >> t.fin >> t.periodica;
        t.id = i + N;
        pq.push({t.inicio, t.fin, t.periodica, true, t.id});
    }

    int tiempo = 0;
    while(!pq.empty() && tiempo <= pq.top().inicio && tiempo <= T){
        tarea t = pq.top();
        pq.pop();
        tiempo = t.fin;

        if(t.p){
            t.inicio += t.periodica;
            t.fin += t.periodica;
            pq.push(t);
        }


    }
    
     if(!pq.empty() && pq.top().inicio < tiempo && pq.top().inicio < T){
        cout << "SI\n";
    }
    else{
        cout << "NO\n";
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