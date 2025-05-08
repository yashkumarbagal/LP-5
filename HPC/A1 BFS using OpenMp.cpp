#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void parallelBFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "Parallel BFS Traversal: ";

    while (!q.empty()) {
        int qSize = q.size();
        vector<int> nextLevel;

        for (int i = 0; i < qSize; i++) {
            int node = q.front(); q.pop();
            cout << node << " ";

            // Traditional loop to avoid range-based for error
            for (int j = 0; j < graph[node].size(); j++) {
                int neighbor = graph[node][j];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    nextLevel.push_back(neighbor);
                }
            }
        }

        for (int i = 0; i < nextLevel.size(); i++) {
            q.push(nextLevel[i]);
        }
    }

    cout << endl;
}

int main() {
    int n, m, start_node;

    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start_node;

    cout << "Enter Pairs of Edges:\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    parallelBFS(start_node);

    return 0;
}


// g++ -fopenmp openmp_example.cpp -o openmp_example
// ./openmp_example
// openmp_example.exe
