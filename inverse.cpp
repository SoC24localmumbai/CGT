#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1e18;

int main() {
    int n;
    cin >> n;
    
    vector<vector<long long>> d(n, vector<long long>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
        }
    }
    
    // Check for symmetry and diagonal zeros
    for (int i = 0; i < n; ++i) {
        if (d[i][i] != 0) {
            cout << "NO" << endl;
            return 0;
        }
        for (int j = i + 1; j < n; ++j) {
            if (d[i][j] != d[j][i]) {
                cout << "NO" << endl;
                return 0;
            }
            if (i != j && d[i][j] == 0) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    
    // Check triangle inequality
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (d[i][j] > 0 && d[j][k] > 0 && d[i][k] > d[i][j] + d[j][k]) {
                    cout << "NO" << endl;
                    return 0;
                }
            }
        }
    }
    
    // Check if it can represent a tree
    // We need to construct a tree from this distance matrix
    // Use Prim's algorithm or Kruskal's algorithm to verify if we can construct a tree
    vector<bool> visited(n, false);
    vector<long long> minDist(n, INF);
    minDist[0] = 0;
    long long totalWeight = 0;
    
    for (int iter = 0; iter < n; ++iter) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || minDist[i] < minDist[u])) {
                u = i;
            }
        }
        
        if (minDist[u] == INF) {
            cout << "NO" << endl;
            return 0;
        }
        
        visited[u] = true;
        totalWeight += minDist[u];
        
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && d[u][v] < minDist[v]) {
                minDist[v] = d[u][v];
            }
        }
    }
    
    // Check if we covered all nodes and have only one connected component
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    
    cout << "YES" << endl;
    
    return 0;
}
