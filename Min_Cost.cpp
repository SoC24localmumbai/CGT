#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX / 2; // Using a large enough value to prevent overflow

int minCost(vector<vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    
    // Directions: 1 -> right, 2 -> left, 3 -> down, 4 -> up
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    // Priority queue to store (cost, (x, y))
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<vector<int>> cost(m, vector<int>(n, INF));
    
    // Starting point
    cost[0][0] = 0;
    pq.push({0, {0, 0}});
    
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int cur_cost = top.first;
        int x = top.second.first;
        int y = top.second.second;
        
        // If current cost is greater than stored cost, skip
        if (cur_cost > cost[x][y]) continue;
        
        // Explore neighbors
        for (auto& dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                int next_cost = cur_cost + (grid[x][y] != dir.first + 1);
                
                if (next_cost < cost[nx][ny]) {
                    cost[nx][ny] = next_cost;
                    pq.push({next_cost, {nx, ny}});
                }
            }
        }
    }
    
    // Return minimum cost to reach bottom-right corner
    return cost[m-1][n-1] == INF ? -1 : cost[m-1][n-1];
}

int main() {
    int m, n;
    
    // Input dimensions of the grid
    cout << "Enter number of rows (m): ";
    cin >> m;
    cout << "Enter number of columns (n): ";
    cin >> n;
    
    // Input the grid elements
    vector<vector<int>> grid(m, vector<int>(n));
    cout << "Enter the grid elements:" << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
        }
    }
    
    // Compute minimum cost to ensure a valid path
    int result = minCost(grid);
    cout << "Minimum cost to ensure a valid path: " << result << endl;
    
    return 0;
}
