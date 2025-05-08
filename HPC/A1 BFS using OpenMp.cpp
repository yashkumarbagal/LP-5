#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
#include <iomanip>  // for setprecision

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

// Sequential BFS traversal
void sequentialBFS(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    cout << "Sequential BFS Traversal: ";

    while (!q.empty()) {
        int qSize = q.size();
        for (int i = 0; i < qSize; i++) {
            int node = q.front(); q.pop();
            cout << node << " ";

            // Traditional loop to avoid range-based for error
            for (int j = 0; j < graph[node].size(); j++) {
                int neighbor = graph[node][j];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    cout << endl;
}

// Parallel BFS traversal
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

    // Sequential BFS
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start timing the sequential BFS
    double start_time_seq = omp_get_wtime();
    sequentialBFS(start_node);
    double end_time_seq = omp_get_wtime();
    double time_seq_ms = (end_time_seq - start_time_seq) * 1000;

    cout << "Sequential BFS Execution time: " << fixed << setprecision(6) << time_seq_ms << " milliseconds" << endl;

    // Reset visited array for parallel BFS
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start timing the parallel BFS
    double start_time_par = omp_get_wtime();
    parallelBFS(start_node);
    double end_time_par = omp_get_wtime();
    double time_par_ms = (end_time_par - start_time_par) * 1000;

    cout << "Parallel BFS Execution time: " << fixed << setprecision(6) << time_par_ms << " milliseconds" << endl;

    return 0;
}
