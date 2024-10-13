
// NOMBRE Y APELLIDOS

#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

struct paciente{
    string nombre;
    int gravedad;
    int ordenLlegada;
};

bool operator<(paciente const& a, paciente const& b) {
    return a.gravedad < b.gravedad ||
    (a.gravedad == b.gravedad && a.ordenLlegada > b.ordenLlegada);
}

bool resuelveCaso() {
    
    int nOperaciones = 0;
    //Leer caso de prueba: cin>>...
    cin >> nOperaciones;
    if (nOperaciones == 0)
        return false;
    
    char op;
    
    priority_queue<paciente> pq;

    for(int i = 0; i < nOperaciones; i++){
        cin >> op;
        if(op == 'I'){
            paciente p;
            cin >> p.nombre >> p.gravedad;
            pq.push({p.nombre, p.gravedad, i});
        }
        else{
            cout << pq.top().nombre << "\n";
            pq.pop();
        }
    }
    cout << "---\n";
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