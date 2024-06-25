#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
using namespace std;

typedef pair<double, int> pdi;  // pair of probability and node index

double maxProbability(int n, vector<vector<double>>& edges, vector<double>& succProb, int start, int end) {
    // Step 1: Create graph adjacency list
    unordered_map<int, vector<pair<int, double>>> graph;
    for (int i = 0; i < edges.size(); ++i) {
        int a = edges[i][0], b = edges[i][1];
        double prob = succProb[i];
        graph[a].emplace_back(b, prob);
        graph[b].emplace_back(a, prob);
    }
    
    // Step 2: Dijkstra's algorithm to find maximum probability path
    vector<double> maxProbability(n, 0.0);
    maxProbability[start] = 1.0;
    priority_queue<pdi> pq;  // max-heap of pair<double, int>
    pq.push({1.0, start});
    unordered_set<int> visited;
    
    while (!pq.empty()) {
        pdi top = pq.top();
        pq.pop();
        
        double prob = top.first;
        int u = top.second;
        
        if (visited.count(u)) continue;
        visited.insert(u);
        
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            double edgeProb = neighbor.second;
            double newProb = prob * edgeProb;
            if (newProb > maxProbability[v]) {
                maxProbability[v] = newProb;
                pq.push({newProb, v});
            }
        }
    }
    
    // Step 3: Return the maximum probability to reach 'end' node
    return maxProbability[end];
}

int main() {
    int n, m;
    cout << "Enter the number of nodes (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;
    
    vector<vector<double>> edges(m, vector<double>(2));
    vector<double> succProb(m);
    
    cout << "Enter the edges in the format (a, b) and their success probabilities:" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> succProb[i];
    }
    
    int start, end;
    cout << "Enter the start node index (0 to " << n-1 << "): ";
    cin >> start;
    cout << "Enter the end node index (0 to " << n-1 << "): ";
    cin >> end;
    
    double result = maxProbability(n, edges, succProb, start, end);
    cout << "Maximum probability to go from " << start << " to " << end << ": " << result << endl;
    
    return 0;
}
