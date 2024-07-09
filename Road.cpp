#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, cost;
    
    bool operator<(const Edge& other) const {
        return cost < other.cost;
    }
};

struct UnionFind {
    vector<int> parent, rank;
    
    UnionFind(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    
    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }
    
    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        
        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v])
                parent[root_v] = root_u;
            else if (rank[root_u] < rank[root_v])
                parent[root_u] = root_v;
            else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = {a-1, b-1, c}; // Convert cities to 0-indexed
    }
    
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    int total_cost = 0;
    int edges_used = 0;
    
    for (const auto& edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            total_cost += edge.cost;
            edges_used++;
            if (edges_used == n - 1) // Found MST with n-1 edges
                break;
        }
    }
    
    if (edges_used == n - 1)
        cout << total_cost << endl;
    else
        cout << "IMPOSSIBLE" << endl;
    
    return 0;
}
