#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // Step 1: Build the graph and in_degree array
        vector<vector<int>> graph(numCourses);
        vector<int> in_degree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            int course = prereq[0];
            int prerequisite = prereq[1];
            graph[prerequisite].push_back(course);
            in_degree[course]++;
        }
        
        // Step 2: Initialize a queue with all courses that have zero in_degree
        queue<int> q;
        for (int course = 0; course < numCourses; ++course) {
            if (in_degree[course] == 0) {
                q.push(course);
            }
        }
        
        // Step 3: Perform topological sort using BFS
        vector<int> topological_order;
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            topological_order.push_back(current);
            
            for (int neighbor : graph[current]) {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        // Step 4: Check if we were able to include all courses in topological_order
        if (topological_order.size() == numCourses) {
            return topological_order;
        } else {
            return {};
        }
    }
};

int main() {
    Solution solution;
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;
    
    int numPrerequisites;
    cout << "Enter the number of prerequisites: ";
    cin >> numPrerequisites;
    
    vector<vector<int>> prerequisites(numPrerequisites);
    cout << "Enter the prerequisites in the format [ai, bi]:\n";
    for (int i = 0; i < numPrerequisites; ++i) {
        int ai, bi;
        cin >> ai >> bi;
        prerequisites[i] = {ai, bi};
    }
    
    vector<int> result = solution.findOrder(numCourses, prerequisites);
    
    // Output the result
    cout << "Order of courses to take: ";
    if (result.empty()) {
        cout << "Impossible to finish all courses due to cyclic dependencies.\n";
    } else {
        cout << "[ ";
        for (int course : result) {
            cout << course << " ";
        }
        cout << "]\n";
    }
    
    return 0;
}
