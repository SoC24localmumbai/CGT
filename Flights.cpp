#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Build adjacency list
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& flight : flights) {
            int from = flight[0];
            int to = flight[1];
            int price = flight[2];
            graph[from].push_back({to, price});
        }
        
        // Priority queue: {cost, city, stops}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, src, 0}); // Initial state: cost 0, start from src, 0 stops
        
        // Distance map to track the minimum cost to reach each city with certain stops
        unordered_map<int, unordered_map<int, int>> minCost;
        minCost[src][0] = 0; // Cost to reach src with 0 stops is 0
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            int cost = curr[0];
            int city = curr[1];
            int stops = curr[2];
            
            if (city == dst) {
                return cost; // Found the destination with the minimum cost
            }
            
            if (stops > k) {
                continue; // Skip if number of stops exceeds k
            }
            
            for (auto& neighbor : graph[city]) {
                int nextCity = neighbor.first;
                int flightCost = neighbor.second;
                int newCost = cost + flightCost;
                
                if (minCost[nextCity].find(stops + 1) == minCost[nextCity].end() || newCost < minCost[nextCity][stops + 1]) {
                    minCost[nextCity][stops + 1] = newCost;
                    pq.push({newCost, nextCity, stops + 1});
                }
            }
        }
        
        return -1; // No valid path found
    }
};

int main() {
    Solution solution;
    int n, src, dst, k;
    
    // Input number of cities (n), source city (src), destination city (dst), and maximum stops (k)
    cout << "Enter the number of cities (n): ";
    cin >> n;
    cout << "Enter the number of flights: ";
    int numFlights;
    cin >> numFlights;
    
    vector<vector<int>> flights(numFlights, vector<int>(3));
    cout << "Enter the flights in the format [from, to, price]:" << endl;
    for (int i = 0; i < numFlights; ++i) {
        cin >> flights[i][0] >> flights[i][1] >> flights[i][2];
    }
    
    cout << "Enter the source city (src): ";
    cin >> src;
    cout << "Enter the destination city (dst): ";
    cin >> dst;
    cout << "Enter the maximum number of stops (k): ";
    cin >> k;
    
    int cheapestPrice = solution.findCheapestPrice(n, flights, src, dst, k);
    cout << "Cheapest price from " << src << " to " << dst << " with at most " << k << " stops: " << cheapestPrice << endl;
    
    return 0;
}
