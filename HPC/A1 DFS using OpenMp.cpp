#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>
#include <iomanip>  // for setprecision

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

// Sequential DFS traversal
void sequentialDFS(int start) {
    stack<int> s;
    s.push(start);
    visited[start] = true;

    cout << "Sequential DFS Traversal: ";

    while (!s.empty()) {
        int node = s.top(); s.pop();
        cout << node << " ";

        for (int i = 0; i < graph[node].size(); i++) {
            int neighbor = graph[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }

    cout << endl;
}

// Parallel DFS traversal
void parallelDFS(int start) {
    stack<int> s;
    s.push(start);
    visited[start] = true;

    cout << "Parallel DFS Traversal: ";

    while (!s.empty()) {
        int node = s.top(); s.pop();
        cout << node << " ";

        // OpenMP parallelism to push neighbors
        #pragma omp parallel for shared(s, node)
        for (int i = 0; i < graph[node].size(); i++) {
            int neighbor = graph[node][i];
            #pragma omp critical
            {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
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

    // Sequential DFS
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start timing the sequential DFS
    double start_time_seq = omp_get_wtime();
    sequentialDFS(start_node);
    double end_time_seq = omp_get_wtime();
    double time_seq_ms = (end_time_seq - start_time_seq) * 1000;

    cout << "Sequential DFS Execution time: " << fixed << setprecision(6) << time_seq_ms << " milliseconds" << endl;

    // Reset visited array for parallel DFS
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    // Start timing the parallel DFS
    double start_time_par = omp_get_wtime();
    parallelDFS(start_node);
    double end_time_par = omp_get_wtime();
    double time_par_ms = (end_time_par - start_time_par) * 1000;

    cout << "Parallel DFS Execution time: " << fixed << setprecision(6) << time_par_ms << " milliseconds" << endl;

    return 0;
}
