
// NOMBRE Y APELLIDOS

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct caja{
    int id;
    int tiempo;
};

bool operator>(caja const& a, caja const& b) {
    return a.tiempo > b.tiempo ||
    (a.tiempo == b.tiempo && a.id > b.id);
}

bool resuelveCaso() {
    
    //Leer caso de prueba: cin>>...
    int nCajas = 0;
    int nPersonas = 0;

    cin >> nCajas >> nPersonas;
    
    if (nCajas == 0)
        return false;
 
    int tiempo = 0;
    priority_queue<caja, vector<caja>, greater<>> pq;

    for(int i = 0; i < nCajas; i++){
        pq.push({i+1, 0});
    }

    for(int i = 0; i < nPersonas; i++){
        cin >> tiempo;
        caja c = pq.top();
        c.tiempo += tiempo;
        pq.pop();
        pq.push(c);
    }

     cout << pq.top().id << "\n";
    
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