#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;

vector<vector<int>> adj;
vector<int> goods_type;
vector<int> min_dist;
vector<vector<int>> dist;

void bfs(int start, int n) {
    queue<int> q;
    vector<bool> visited(n + 1, false);
    q.push(start);
    visited[start] = true;
    dist[start][start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                dist[start][v] = dist[start][u] + 1;
            }
        }
    }
}

int main() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    
    goods_type.resize(n + 1);
    adj.resize(n + 1);
    dist.resize(n + 1, vector<int>(n + 1, INF));
    
    for (int i = 1; i <= n; ++i) {
        cin >> goods_type[i];
    }
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Calculate shortest distances using BFS from each town
    for (int i = 1; i <= n; ++i) {
        bfs(i, n);
    }
    
    // Calculate minimum expenses for each town
    vector<int> min_expense(n + 1, INF);
    for (int i = 1; i <= n; ++i) {
        int town_type = goods_type[i];
        vector<int> min_dist_by_type(k + 1, INF);
        
        for (int j = 1; j <= n; ++j) {
            int neighbor_type = goods_type[j];
            if (town_type != neighbor_type) {
                min_dist_by_type[neighbor_type] = min(min_dist_by_type[neighbor_type], dist[i][j]);
            }
        }
        
        // Sort distances to find the minimum s-1 distances to other types
        sort(min_dist_by_type.begin() + 1, min_dist_by_type.end());
        
        int sum = 0;
        for (int j = 1; j <= s - 1; ++j) {
            sum += min_dist_by_type[j];
        }
        
        min_expense[i] = sum;
    }
    
    // Output the minimum expense for each town
    for (int i = 1; i <= n; ++i) {
        cout << min_expense[i] << " ";
    }
    cout << endl;
    
    return 0;
}
