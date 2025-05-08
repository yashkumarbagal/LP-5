#include <iostream>
#include <vector>
#include <omp.h>
#include <stack>

using namespace std;

// Function to perform DFS traversal
void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(node);
    visited[node] = true;
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                #pragma omp critical
                s.push(neighbor);  // Push into stack in a critical section
            }
        }
    }
}

int main() {
    int n, e;
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    cout << "Enter the number of edges: ";
    cin >> e;
    
    vector<vector<int>> graph(n);
    
    cout << "Enter the edges (u v): " << endl;
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // Assuming it's an undirected graph
    }
    
    vector<bool> visited(n, false);
    int start_node;
    cout << "Enter the starting node for DFS: ";
    cin >> start_node;
    
    cout << "DFS Traversal starting from node " << start_node << ": ";
    dfs(start_node, graph, visited);
    
    return 0;
}
