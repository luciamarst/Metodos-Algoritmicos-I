
// NOMBRE Y APELLIDOS

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include "ConjuntosDisjuntos.h"
using namespace std;

using Mapa = vector<string>;

class PetrolerosHundidos{
public:
    PetrolerosHundidos(Mapa const& m) :M(m), F(m.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), manchaGrande(0){
        
        for(int i = 0; i < F; i++){
            for(int j = 0; j < C; j++){
                if(m[i][j] == '#' && !visit[i][j]){
                    int tam = dfs(m,i,j);
                    manchaGrande = max(manchaGrande, tam);
                }
            }
        }
    }

    bool esCorrecto(int i, int j) {
        return i >= 0 && i < F && j >= 0 && j < C;
    }

    int manchaMasGrande() const{
        return manchaGrande;
    }

    void nuevaMancha(int i, int j){
        M[i][j] = '#';
        int tam = 1;

        for(pair<int,int> dir : dirs){
            int nuevaI = i + dir.first;
            int nuevaJ = j + dir.second;

            if(esCorrecto(nuevaI,nuevaJ) &&  M[nuevaI][nuevaJ] == '#' && !cjto.unidos(i*C+j, nuevaI*C+nuevaJ)){
                tam += cjto.tam(nuevaI*C+nuevaJ);
                cjto.unir(i*C+j, nuevaI*C+nuevaJ);
            }
        }

        manchaGrande = max(manchaGrande, tam);
    }
private:
    Mapa M;
    vector<pair<int,int>> dirs = {{1,0}, {0,1}, {-1,0}, {0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    int F, C;
    vector<vector<bool>> visit;
    int manchaGrande;
    ConjuntosDisjuntos cjto = ConjuntosDisjuntos(F*C);

    int dfs(Mapa const& m, int i, int j){
        visit[i][j] = true;
        int tam = 1;

        for(pair<int,int> dir : dirs){
            int nuevaI = i + dir.first;
            int nuevaJ = j + dir.second;

            if(esCorrecto(nuevaI,nuevaJ) && !visit[nuevaI][nuevaJ] && m[nuevaI][nuevaJ] == '#'){
                tam += dfs(m, nuevaI, nuevaJ);
                cjto.unir(i*C+j, nuevaI*C+nuevaJ);
            }
        }

        return tam;
    }
};

bool resuelveCaso() {
    int  F, C;
    
    cin >> F >> C;

    if(!std::cin)
        return false;
 
    Mapa M(F);

    for(string &linea: M){
        cin >> linea;
    }
    
    PetrolerosHundidos manchas(M);

    cout << manchas.manchaMasGrande() << " "; 
    

    int K;
     cin >> K;

    for(int i = 0; i < K; i++){
        int v,w;
        cin >> v >> w;
        manchas.nuevaMancha(v-1,w-1);
        cout << manchas.manchaMasGrande() << " ";
    }

    cout << "\n";
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
   
    while(resuelveCaso());
    
    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("pause");
#endif
    return 0;
}
