#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <set>
#include <queue>

using namespace std;

int solve(int N, int M, vector<tuple<int, int, int>>& roads) {
    // Crear listas de adyacencia para representar el grafo
    vector<vector<pair<int, int>>> adj(N + 1);

    for (auto [u, v, cost] : roads) {
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }

    // Función para calcular los costos mínimos de una planta a todos los pueblos
    auto dijkstra = [&](int start) {
        vector<int> dist(N + 1, 1e9); // Inicializar todas las distancias como infinitas
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [current_cost, u] = pq.top();
            pq.pop();

            if (current_cost > dist[u]) continue;

            for (auto [v, cost] : adj[u]) {
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    };

    // Obtener los costos mínimos desde la planta norte (1) y sur (N)
    vector<int> dist_from_north = dijkstra(1);
    vector<int> dist_from_south = dijkstra(N);

    // Crear listas con los costos hacia los pueblos desde cada planta
    vector<int> north_costs, south_costs;

    for (int i = 2; i < N; ++i) { // Los pueblos están entre 2 y N-1
        north_costs.push_back(dist_from_north[i]);
        south_costs.push_back(dist_from_south[i]);
    }

    // Ordenar los costos en orden ascendente
    sort(north_costs.begin(), north_costs.end());
    sort(south_costs.begin(), south_costs.end());

    // Sumar los costos más bajos para atender a (N-2)/2 pueblos desde cada planta
    int total_cost = 0;
    int half = (N - 2) / 2;

    for (int i = 0; i < half; ++i) {
        total_cost += north_costs[i];
        total_cost += south_costs[i];
    }

    return total_cost;
}

int resuelveCaso() {
    
    int N, M;
    cin >> N >> M;

    if(!std::cin) return false;

    vector<tuple<int, int, int>> roads;

    for (int i = 0; i < M; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        roads.push_back({u, v, cost});
    }

    cout << solve(N, M, roads) << endl;
    

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