#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
vector<int> indegree(MAXN, 0);
vector<int> dp(MAXN, 0);

int main() {
    int N, M;
    cin >> N >> M;
    
    for (int i = 0; i < M; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        indegree[y]++;
    }
    
    // Topological sort using Kahn's algorithm
    queue<int> q;
    for (int i = 1; i <= N; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
            // Update dp[v] using dp[u]
            dp[v] = max(dp[v], dp[u] + 1);
        }
    }
    
    // Find the maximum value in dp array
    int longest_path_length = 0;
    for (int i = 1; i <= N; ++i) {
        longest_path_length = max(longest_path_length, dp[i]);
    }
    
    cout << longest_path_length << endl;
    
    return 0;
}
