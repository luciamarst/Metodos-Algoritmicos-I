
// NOMBRE Y APELLIDOS

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <math.h>
using namespace std;

using hora = pair<int, int>;

//Para tener un identificador unico de cada horairo y usarlo como key del map
int convertirHoraAMinutos(int horas, int minutos) {
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59) {
        std::cerr << "Formato de hora inválido.\n";
        return -1; // Valor para indicar error
    }

    return horas * 60 + minutos;
}

int resolver(vector<hora> peliculas){
    int vistas = 1;
    int libre = peliculas[0].second+10;
    for(int i = 1; i < peliculas.size();i++){
        if(peliculas[i].first >= libre){
            vistas++;
            libre = peliculas[i].second+10;
        }
    }
    return vistas;
}

bool resuelveCaso() {
    
    int N;
    cin >> N;
    
    if (N == 0)
        return false;
    
    vector<hora> peliculas;
    unordered_map<int, int> hora_duracion;    
    for(int i = 0; i < N; i++){
        string inicio;
        int duracion;
        cin >> inicio >> duracion; 
        
        string horas, minutos;
        stringstream ss(inicio);
        getline(ss, horas, ':');
        getline(ss, minutos, ':');

        int duracionHora = convertirHoraAMinutos(stoi(horas), stoi(minutos)); //Creamos la clave identificadora de un horario
        hora h = {duracionHora,duracionHora + duracion};//Creamos el tipo hora para el vector
        peliculas.push_back(h);
    }

    sort(peliculas.begin(), peliculas.end()); //Los orde aoms crecientemente para poder recorrerlos de forma ordenada
    int n = resolver(peliculas);

   cout << n << endl;
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
