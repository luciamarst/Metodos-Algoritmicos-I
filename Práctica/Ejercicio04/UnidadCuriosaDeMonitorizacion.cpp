
// NOMBRE Y APELLIDOS

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct usuario{
    long long int id;
    long long int periodo;
    long long int suma;
};


bool operator<(usuario const& a, usuario const& b) {
    return b.suma < a.suma ||
    (a.suma == b.suma && b.id < a.id);
}



bool resuelveCaso() {
    
    int nIds = 0;
    cin >> nIds;


    if (nIds == 0)
        return false;
 
    priority_queue<usuario> pq;
    
    for(int i = 0; i < nIds; i++){
        usuario u;
        cin >> u.id >> u.periodo;
        pq.push({u.id, u.periodo, u.periodo});
    }

    int K = 0;
    cin >> K;

    for(int i = 0; i < K; i++){
        usuario u = pq.top();
        pq.pop();

        cout << u.id << "\n";
        u.suma += u.periodo;
        
        pq.push(u);
    }

    cout << "---\n";
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