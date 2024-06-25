#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 300005;

// Function to find the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to construct the graph based on friendship conditions
void construct_graph(int n, vector<int>& legs, vector<vector<int>>& graph) {
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (gcd(legs[i], legs[j]) > 1) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
}

// BFS to find the shortest path from source to target
bool bfs(int n, vector<vector<int>>& graph, int source, int target, vector<int>& path) {
    vector<bool> visited(n + 1, false);
    vector<int> parent(n + 1, -1);
    queue<int> q;
    
    q.push(source);
    visited[source] = true;
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (current == target) {
            break;
        }
        
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    if (!visited[target]) {
        return false; // No path found
    }
    
    // Reconstruct the path from source to target
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    
    return true;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> legs(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> legs[i];
    }
    
    int s, t;
    cin >> s >> t;
    
    // Graph representation using adjacency list
    vector<vector<int>> graph(n + 1);
    
    // Construct the graph based on friendship conditions
    construct_graph(n, legs, graph);
    
    // Variables for BFS result
    vector<int> path;
    
    // Perform BFS from spider s to spider t
    if (bfs(n, graph, s, t, path)) {
        cout << path.size() << endl;
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    } else {
        cout << "-1" << endl;
    }
    
    return 0;
}
