#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to, weight, index;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
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

int findMST(vector<Edge>& edges, int n, int ignore_edge = -1) {
    UnionFind uf(n);
    int mst_weight = 0;
    int edges_used = 0;
    
    for (int i = 0; i < edges.size(); ++i) {
        if (i == ignore_edge) continue;
        
        int u = edges[i].from;
        int v = edges[i].to;
        int weight = edges[i].weight;
        
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst_weight += weight;
            edges_used++;
            if (edges_used == n - 1)
                break;
        }
    }
    
    if (edges_used != n - 1)
        return INT_MAX; // No valid MST found
    
    return mst_weight;
}

vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
    int m = edges.size();
    vector<Edge> sorted_edges(m);
    
    for (int i = 0; i < m; ++i) {
        sorted_edges[i] = {edges[i][0], edges[i][1], edges[i][2], i};
    }
    
    sort(sorted_edges.begin(), sorted_edges.end());
    
    int mst_weight = findMST(sorted_edges, n);
    
    vector<int> critical;
    vector<int> pseudo_critical;
    
    for (int i = 0; i < m; ++i) {
        // Check if edge i is critical
        int mst_without_edge = findMST(sorted_edges, n, i);
        if (mst_without_edge > mst_weight) {
            critical.push_back(sorted_edges[i].index);
            continue;
        }
        
        // Check if edge i is pseudo-critical
        UnionFind uf(n);
        uf.unite(sorted_edges[i].from, sorted_edges[i].to);
        int mst_with_edge = sorted_edges[i].weight;
        
        for (int j = 0; j < m; ++j) {
            if (i == j) continue;
            
            int u = sorted_edges[j].from;
            int v = sorted_edges[j].to;
            int weight = sorted_edges[j].weight;
            
            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                mst_with_edge += weight;
            }
        }
        
        if (mst_with_edge == mst_weight) {
            pseudo_critical.push_back(sorted_edges[i].index);
        }
    }
    
    return {critical, pseudo_critical};
}

int main() {
    int n = 5;
    vector<vector<int>> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {3, 4, 4}, {0, 4, 5}, {2, 4, 6}};
    
    vector<vector<int>> results = findCriticalAndPseudoCriticalEdges(n, edges);
    
    cout << "Critical Edges: ";
    for (int edge : results[0]) {
        cout << edge << " ";
    }
    cout << endl;
    
    cout << "Pseudo-critical Edges: ";
    for (int edge : results[1]) {
        cout << edge << " ";
    }
    cout << endl;
    
    return 0;
}
