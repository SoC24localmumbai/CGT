#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

void addEdge(vector<vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u); // Since the graph is undirected
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<vector<int>> graph(N + 1);
    
    // Read edges
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(graph, a, b);
    }
    
    // Read guards' positions and stamina
    vector<pair<int, int>> guards;
    for (int i = 0; i < K; ++i) {
        int p_i, h_i;
        cin >> p_i >> h_i;
        guards.push_back({p_i, h_i});
    }
    
    // Array to mark guarded vertices
    vector<bool> guarded(N + 1, false);
    
    // Process each guard using BFS
    for (auto& guard : guards) {
        int p_i = guard.first;
        int h_i = guard.second;
        
        vector<bool> visited(N + 1, false);
        queue<pair<int, int>> q; // (vertex, distance)
        q.push({p_i, 0});
        visited[p_i] = true;
        
        while (!q.empty()) {
            int current = q.front().first;
            int dist = q.front().second;
            q.pop();
            
            if (dist > h_i) {
                continue;
            }
            
            guarded[current] = true;
            
            for (int neighbor : graph[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, dist + 1});
                }
            }
        }
    }
    
    // Collect and print guarded vertices
    vector<int> result;
    for (int v = 1; v <= N; ++v) {
        if (guarded[v]) {
            result.push_back(v);
        }
    }
    
    cout << result.size() << endl;
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}
