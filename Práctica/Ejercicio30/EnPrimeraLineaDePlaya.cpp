
// NOMBRE Y APELLIDOS

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

using Edificio = pair<int, int>;

class ComparadorEdificios {
public:
    bool operator()(Edificio const& a, Edificio const& b) const {
        return a.second < b.second;
    }
};


void resolver(vector<Edificio> edificios, unordered_map<int, bool> edificios_con_tunel){
    int sol = 0;
    Edificio e1 = edificios[0];
    if(edificios_con_tunel.count(e1.second) == 0){
        edificios_con_tunel[e1.second] = true;
        sol++;
    }
    int i = 1;
    while(i < edificios.size()){
        Edificio e2 = edificios[i];

        if(e2.first < e1.second){
            if(!edificios_con_tunel.count(e1.second)){
                edificios_con_tunel[e2.second] = true;
                sol++;
                
                e1 = e2;
            }
            
        }
        else if(e2.first > e1.second){
            if(!edificios_con_tunel.count(e2.second)){
                edificios_con_tunel[e2.second] = true;
                sol++;
                
                e1 = e2;
            }
        }
        else{
            if(!edificios_con_tunel.count(e2.second)){
                edificios_con_tunel[e2.second] = true;
                sol++;
                
                e1 = e2;
            }
        }
        i++;
    }
    cout << sol << endl;
}

bool resuelveCaso() {
    int A;
    //Leer caso de prueba: cin>>...
    cin >> A;
    if (A == 0)
        return false;
 
    int inicio, fin;
    unordered_map<int, bool> edificios_con_tunel;
    vector<Edificio> edificios;

    for (int i = 0; i < A; i++)
    {
        cin >> inicio >> fin;
        edificios.push_back({inicio, fin});
        edificios_con_tunel[i] = false;
    }
    
    unordered_map<int, bool> tuneles;

    sort(edificios.begin(), edificios.end(), ComparadorEdificios());
    resolver(edificios, tuneles);
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
