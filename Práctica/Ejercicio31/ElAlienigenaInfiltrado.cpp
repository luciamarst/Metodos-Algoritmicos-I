
// NOMBRE Y APELLIDOS

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

using Tarea = pair<int, int>;
class CompararTareas{
public:
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) const{
        return a.first < b.first;
    }
};


void resolver(vector<Tarea> tareas,int duracion, pair<int,int> rango){
    int sol = 0;
    int tramo_cubierno;

    tramo_cubierno = rango.first;
    int siguiente = 0;
    
    while(tramo_cubierno < rango.second){
        int maximo = tramo_cubierno;


        while(siguiente < tareas.size() && tareas[siguiente].first <= tramo_cubierno){
            maximo = max(maximo, tareas[siguiente].second);
            siguiente++;
        }

        if(maximo > tramo_cubierno){
            sol++;
            tramo_cubierno = maximo;
        }
        else{
            cout << "Imposible" << endl;
            return;
        }
    }
    cout << sol << endl;
}

bool resuelveCaso() {
    int C, F, N;
    //Leer caso de prueba: cin>>...
    cin >> C >> F >> N;
    
    if (C == 0 && F == 0 && N == 0)
        return false;
    

    if(N > 0){
        int intervalo = (F) - C;
        vector<Tarea> tareas(N);

        for(int i = 0; i < N; i++){
            int inicio, fin;
            cin >> inicio >> fin;
            tareas[i] = {inicio, fin};
        }

        sort(tareas.begin(), tareas.end(), CompararTareas());
        resolver(tareas, intervalo, {C, F});
    //Resolver problema
    //Escribir resultado
    }
    else{
        cout << "Imposible" << endl;
    }
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
