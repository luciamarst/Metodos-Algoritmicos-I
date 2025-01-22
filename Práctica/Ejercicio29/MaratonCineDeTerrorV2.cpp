
// NOMBRE Y APELLIDOS

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <math.h>
using namespace std;


//Para transformar laduracion a un horario y poder sumarselo a la hora recuperada
struct Pelicula {
    int inicio;
    int fin;
};

class ComparadorPeliculas {
public:
    bool operator()(Pelicula const& a, Pelicula const& b) const {
        return a.fin < b.fin;
    }
};

void resolver(vector <Pelicula> cine, int N) {
    int vistas = 1;
    int libre = cine[0].fin + 10;
    for (int i = 1; i < N; i++) {
        if (cine[i].inicio >= libre) {
            vistas++;
            libre = cine[i].fin + 10;
        }
    }
    cout << vistas << "\n";
}

bool resuelveCaso() {
    
    int N;
    cin >> N;
    
    if (N == 0)
        return false;
    
    vector <Pelicula> cine(N);
    int hora, minutos, duracion;
    char c; 

    for (int i = 0; i < N; i++) {
        cin >> hora >> c >> minutos >> duracion;
        cine[i].inicio = hora * 60 + minutos; //Transformo la hora de inicio a minutos
        cine[i].fin = cine[i].inicio + duracion; //Calculo la hora de fin
    }
    

    sort(cine.begin(), cine.end(),ComparadorPeliculas()); //Los orde aoms crecientemente para poder recorrerlos de forma ordenada
    resolver(cine, N);
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
