#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;
const int INF = INT_MAX;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    // Step 1: Create adjacency list representation of the graph
    vector<vector<pii>> graph(n + 1);
    for (auto& time : times) {
        int u = time[0], v = time[1], w = time[2];
        graph[u].emplace_back(v, w);
    }
    
    // Step 2: Initialize distances array
    vector<int> dist(n + 1, INF);
    dist[k] = 0;
    
    // Step 3: Priority queue for Dijkstra's algorithm
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, k});  // {distance, node}
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        // Explore neighbors
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Step 4: Check if all nodes are reachable and find the maximum distance
    int maxTime = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == INF) return -1;  // Node i is not reachable
        maxTime = max(maxTime, dist[i]);
    }
    
    return maxTime;
}

int main() {
    int n, m;
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;
    
    vector<vector<int>> times(m, vector<int>(3));
    cout << "Enter the edges in the format (u, v, w) where u is source, v is target, and w is time:" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> times[i][0] >> times[i][1] >> times[i][2];
    }
    
    int k;
    cout << "Enter the source node k (1 to " << n << "): ";
    cin >> k;
    
    int minTime = networkDelayTime(times, n, k);
    
    cout << "Minimum time to reach all nodes: " << minTime << endl;
    
    return 0;
}
